bool	hit_obj(t_ray ray, t_pixel *px, double t_max)
{
	int		i;
	bool	hit;
	double	t;
	double	t_closest;
	double m;
	int	s = 0;

	i = 0;
	hit = false;
	t = 0;
	t_closest = __DBL_MAX__;
	px->obj_id = 0;
	px->t = 0;
	while (i < data()->n_objs)
	{
		if (data()->objects[i].obj_type == SPHERE)
			t = hit_sphere(data()->objects[i], ray);
		else if (data()->objects[i].obj_type == PLANE)
			t = hit_plane(data()->objects[i], ray);
		else
		{
			t = hit_cylinder(data()->objects[i], ray);
		}
		if (t > 0.001 && t < t_closest && t <= t_max)
		{
			px->hitpoint = get_hitpos(ray.origin, ray.direction, t);
			if (data()->objects[i].obj_type == SPHERE)
				px->normal = vec3_subtraction(data()->objects[i].center, px->hitpoint);
			else if (data()->objects[i].obj_type == CYLINDER)
			{
				m = vec3_dot(vec3_subtraction(data()->objects[i].center, px->hitpoint),data()->objects[i].axis);
				px->normal = vec3_subtraction(vec3_scalar(data()->objects[i].axis, m), vec3_subtraction(data()->objects[i].center, px->hitpoint));
			}
			else if (data()->objects[i].obj_type == PLANE)
			{
				px->normal = data()->objects[i].normal;
			}
			vec3_normalize(&px->normal);
			set_face_normal(ray, &px->normal);
			px->t = t;
			px->material = data()->objects[i].material;
			px->color = data()->objects[i].color;
			px->fuzz = data()->objects[i].fuzz;
			px->specular = data()->objects[i].specular;
			// data()->objects[px->obj_id] = room.spheres[i].center;
			px->obj_id = i;
			// rec->radius = room.spheres[i].radius;
			s = i;
			hit = true;
			t_closest = t;
		}
		++i;

	}
	return (hit);
}