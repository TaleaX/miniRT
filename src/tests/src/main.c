#include "../include/main.h"

void	init_ray(t_ray *ray, t_vec3 origin, t_vec3 direction)
{
	ray->origin = origin;
	ray->direction = direction;
}

t_vec3	at(double t, t_ray ray)
{
	return (vec3_add(ray.origin, vec3_scalar(ray.origin, t)));
}

void	at_px(double t, t_ray ray, t_pixel *px)
{
	px->hitpoint = vec3_add(ray.origin, vec3_scalar(ray.origin, t));
	px->normal = px->hitpoint;
	vec3_normalize(&px->normal);
	return;
}

// void	init_ray(t_ray *ray, t_vec3 origin, t_vec3 direction)
// {
// 	ray->origin = origin;
// 	ray->direction = direction;
// }

double	random_double(void)
{
	return ((double)rand() / (double)((double)RAND_MAX + 1.0));
}

double	random_min_max(double min, double max)
{
	return (random_double() * (max - min) + min);
}

void	init_vec3(t_vec3 *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

t_vec3	random_in_usphere(void)
{
	t_vec3	random_point;

	while (true)
	{
		init_vec3(&random_point, random_min_max(-1, 1), \
		random_min_max(-1, 1), random_min_max(-1, 1));
		if (vec3_length_squared(random_point) >= 1)
			continue ;
		return (random_point);
	}
}

t_ray	get_ray(double h, double v)
{
	t_ray	ray;
	t_vec3	x;
	t_vec3	y;
	t_vec3	viewport_px;
	t_vec3	rd;
	t_vec3	offset;

	x = vec3_scalar(data()->camera.viewport_horizontal, h);
	y = vec3_scalar(data()->camera.viewport_vertical, v);
	viewport_px = vec3_add(data()->camera.lower_left_corner, vec3_add(x, y));

	ray.origin = data()->camera.origin;
	ray.direction = vec3_subtraction(ray.origin, viewport_px);
	return (ray);
}

static void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void hook(void *param) {
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE)) {
		mlx_close_window(mlx);
	}
}

t_data	*data(void)
{
	static t_data data;
	return (&data);
}

t_vec3	CanvasToViewport(int x, int y)
{
	return ((t_vec3){x * VW / WIDTH, y * VH / HEIGHT, 1});
}

t_vec3	CanvasToViewportRandom(double x, double y)
{
	// x += random_min_max(0,2);
	// x -= random_min_max(0,2);
	// y += random_min_max(0,2);
	// y -= random_min_max(0,2);
	x += random_double();
	x -= random_double();
	y += random_double();
	y -= random_double();
	return ((t_vec3){x * VW / WIDTH, y * VH / HEIGHT, 1});
}

double	hit_sphere(t_obj sphere, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	t_vec3	oc;
	double	t1;
	double	t2;

	oc = vec3_subtraction(sphere.center, ray.origin);
	a = vec3_dot(ray.direction, ray.direction);
	b = 2.0 * vec3_dot(oc, ray.direction);
	c = vec3_dot(oc, oc) - sphere.radius * sphere.radius;
	
	discriminant = b * b - 4.0 * a * c;
	
	if (discriminant < 0.0)
		return (-1);
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t2 < t1)
		t1 = t2;
	return (t1);
}

bool	hit_obj(t_ray ray, t_pixel *px)
{
	int		i;
	double	t;

	i = 0;
	t = 0;
	px->t = __DBL_MAX__;
	px->obj_id = -1;
	while (i < data()->n_objs)
	{
		if (data()->objects[i].obj_type == SPHERE)
			t = hit_sphere(data()->objects[i], ray);
		if (t > 0.001 && t < px->t && t <= 1000)
		{
			px->obj_id = i;
			px->t = t;
		}
		++i;
	}
	if (px->obj_id == -1)
		return (false);
	return (true);
}

t_color	TraceRay(t_ray ray, t_pixel *px, int depth)
{
	t_vec3	target;

	// if (depth <= 0)
	// 	return ((t_color){0,0,0,1});
	if (hit_obj(ray, px))
	{
		return(data()->objects[px->obj_id].color);
		// target = vec3_add(px, )
	}
	return ((t_color){0,0,0,1});
}

void	samples(int y, int x)
{
	int		s;
	t_ray	ray;

	s = 0;
	while (s < SAMPLES)
	{
		ray.origin = (t_vec3){0,0,0};
		ray.direction = CanvasToViewportRandom(x, y);
		data()->px[y + (HEIGHT/2)][x + (WIDTH/2)].c = color_add(data()->px[y + (HEIGHT/2)][x + (WIDTH/2)].c, TraceRay(ray, &data()->px[y + (HEIGHT/2)][x + (WIDTH/2)], 1));
		s++;
	}
}

t_color	ray_color(t_ray ray, t_pixel *px, int depth)
{
	t_vec3	target;
	// t_ray	scattered;
	t_color	attentuate;

	if (depth <= 0)
		return ((t_color){0,0,0,1});
	if (hit_obj(ray, px))
	{
		at_px(px->t, ray, px);
		target = vec3_add(vec3_add(px->hitpoint, px->normal), random_in_usphere());
		init_ray(&ray,px->hitpoint, vec3_subtraction(px->hitpoint, target));
		return (ray_color(ray, px, depth - 1));
	}
	return ((t_color){0,0,0,1});
}

void	set_color(void)
{
	int		y;
	int		x;
	t_vec3	px;
	t_ray	ray;

	x = -(WIDTH/2);
	while (x < WIDTH/2)
	{
		y = -(HEIGHT/2);
		while (y < HEIGHT/2)
		{
			ray.origin = (t_vec3){0,0,0};
			ray.direction = CanvasToViewport(x, y);
			data()->px[y + (HEIGHT/2)][x + (WIDTH/2)].c = color_add(data()->px[y + (HEIGHT/2)][x + (WIDTH/2)].c, ray_color(ray, &data()->px[y + (HEIGHT/2)][x + (WIDTH/2)], 50));
			// data()->px[y + (HEIGHT/2)][x + (WIDTH/2)].c = TraceRay(ray, &data()->px[y + (HEIGHT/2)][x + (WIDTH/2)], 10);
			if (SAMPLES > 1)
				samples(y, x);
			y++;
		}
		x++;
	}
}

// void	set_edge(void)
// {
// 	int		y;
// 	int		x;
// 	t_vec3	px;
// 	t_ray	ray;

// 	x = -(WIDTH/2);
// 	while (x < WIDTH/2)
// 	{
// 		y = -(HEIGHT/2);
// 		while (y < HEIGHT/2)
// 		{
// 			data()->px[y + (HEIGHT/2)][x + (WIDTH/2)].c = TraceRay(ray, &data()->px[y + (HEIGHT/2)][x + (WIDTH/2)]);
// 			y++;
// 		}
// 		x++;
// 	}
// }

static double	clamp(double value, double min, double max)
{
	if (value > max)
		return (max);
	if (value < min)
		return (min);
	return (value);
}

uint32_t	get_rgba(t_color color)
{	
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;


	r = (uint8_t)(255.0 * clamp(color.r, 0.0, 1.0));
	g = (uint8_t)(255.0 * clamp(color.g, 0.0, 1.0));
	b = (uint8_t)(255.0 * clamp(color.b, 0.0, 1.0));
	a = (uint8_t)(255.0 * clamp(color.a, 0.0, 1.0));
	return (r << 24 | g << 16 | b << 8 | a);
}

void	render(void)
{
	int		y;
	int		x;
	double	scale;

	scale = 1.0f / 50;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			data()->px[y][x].c.r = sqrt(scale * data()->px[y][x].c.r);
			data()->px[y][x].c.g = sqrt(scale * data()->px[y][x].c.g);
			data()->px[y][x].c.b = sqrt(scale * data()->px[y][x].c.b);
			// data()->px[y][x].c.r *= scale;
			// data()->px[y][x].c.g *= scale;
			// data()->px[y][x].c.b *= scale;
			mlx_put_pixel(data()->g_img, x, HEIGHT - 1 - y, get_rgba(data()->px[y][x].c));
			x++;
		}
		y++;
	}
}

void	init_color(void)
{
	int		y;
	int		x;
	double	scale;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			data()->px[y][x].c = (t_color){0,0,0,1};
			x++;
		}
		y++;
	}
}

void	init_vars(void)
{
	data()->objects[0].center = (t_vec3){0,-1,3};
	data()->objects[0].radius = 1;
	data()->objects[0].color = (t_color){255,0,0,1};
	data()->objects[0].obj_type = SPHERE;
	data()->n_objs++;

	data()->objects[1].center = (t_vec3){2,0,4};
	data()->objects[1].radius = 1;
	data()->objects[1].color = (t_color){0,0,255,1};
	data()->objects[1].obj_type = SPHERE;
	data()->n_objs++;

	data()->objects[2].center = (t_vec3){-2,0,4};
	data()->objects[2].radius = 1;
	data()->objects[2].color = (t_color){0,255,0,1};
	data()->objects[2].obj_type = SPHERE;
	data()->n_objs++;
}

int32_t	main(int ac, char **av)
{
	mlx_t		*mlx;
	t_color		color;
	int			i;
	int			j;

	init_vars();
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
		return (EXIT_FAILURE);
	data()->g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	memset(data()->g_img->pixels, 0, data()->g_img->width * data()->g_img->height * sizeof(int));
	if (!data()->g_img || (mlx_image_to_window(mlx, data()->g_img, 0, 0) < 0))
		ft_error();
	init_color();
	set_color();
	render();
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}