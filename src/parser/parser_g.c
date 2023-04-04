#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    char *line_start = buffer;
    char *line_end = buffer;
    size_t bytes_read;
    int fd;

    /* Open the input file */
    fd = open("../../scenes/test.rt", O_RDONLY);
    if (fd == -1) {
        perror("Error: Could not open input file");
        return 1;
    }

    /* Read the file in chunks */
    while ((bytes_read = read(fd, line_end, BUFFER_SIZE - (line_end - buffer))) > 0) {
        char *buf_end = buffer + bytes_read;
        char *p = line_start;

        /* Parse each line in the buffer */
        while (p < buf_end) {
            /* Find the end of the line */
            char *q = strchr(p, '\n');
            if (q == NULL) {
                q = buf_end;
            } else {
                q++;
            }

            /* Parse the line character by character */
            float sp = 0.0f;
            int x = 0, y = 0, z = 0;
            int r = 0, g = 0, b = 0;
            int sp_fractional_part = 0;
            int x_sign = 1, y_sign = 1, z_sign = 1;
            int r_sign = 1, g_sign = 1, b_sign = 1;
            int state = 0;  // state 0 = parsing "sp", state 1 = parsing "x", etc.
            char *c = p;
            while (c < q) {
                if (*c == ' ' || *c == '\t') {
                    c++;
                    continue;
                }
                if (state == 0) {
                    if (*c == 's') {
                        state++;
                    } else {
                        fprintf(stderr, "Error: Could not parse input line\n");
                        return 1;
                    }
                } else if (state == 1) {
                    if (*c == 'p') {
                        state++;
                    } else if (*c == '.') {
                        sp_fractional_part = 1;
                    } else if (*c == '-') {
                        sp = -sp;
                    } else if (*c >= '0' && *c <= '9') {
                        if (sp_fractional_part) {
                            sp += (*c - '0') / 10.0f;
                        } else {
                            sp = sp * 10.0f + (*c - '0');
                        }
                    } else if (*c == ',') {
                        state++;
                    } else {
                        fprintf(stderr, "Error: Could not parse input line\n");
                        return 1;
                    }
                } else if (state == 2) {
                    if (*c == '-') {
                        x_sign = -1;
                    } else if (*c >= '0' && *c <= '9') {
                        x = x * 10 + (*c - '0');
                    } else if (*c == ',') {
                        x *= x_sign;
                        state++;
                    } else {
						printf("test1\n");
                        fprintf(stderr, "Error: Could not parse input line\n");
                        return 1;
                    }
                } else if (state == 3) {
                    if (*c == '-') {
                        y_sign = -1;
                    } else if (*c >= '0' && *c <= '9') {
                        y = y * 10 + (*c - '0');
                    } else if (*c == ',') {
                        y *= y_sign;
                        state++;
                    } else {
						printf("test2\n");
                        fprintf(stderr, "Error: Could not parse input line\n");
                        return 1;
                    }
                } else if (state == 4) {
                    if (*c == '-') {
                        z_sign = -1;
                    } else if (*c >= '0' && *c <= '9') {
                        z = z * 10 + (*c - '0');
                    } else if (*c == ',') {
                        z *= z_sign;
                        state++;
                    } else {
						printf("test3\n");
                        fprintf(stderr, "Error: Could not parse input line\n");
                        return 1;
                    }
                } else if (state == 5) {
                    if (*c == '-') {
                        r_sign = -1;
                    } else if (*c >= '0' && *c <= '9') {
                        r = r * 10 + (*c - '0');
                    } else if (*c == ',') {
                        r *= r_sign;
                        state++;
                    } else {
						printf("test4\n");
                        fprintf(stderr, "Error: Could not parse input line\n");
                        return 1;
                    }
                } else if (state == 6) {
                    if (*c == '-') {
                        g_sign = -1;
                    } else if (*c >= '0' && *c <= '9') {
                        g = g * 10 + (*c - '0');
                    } else if (*c == ',') {
                        g *= g_sign;
                        state++;
                    } else {
						printf("test5\n");
                        fprintf(stderr, "Error: Could not parse input line\n");
                        return 1;
                    }
                } else if (state == 7) {
                    if (*c == '-') {
                        b_sign = -1;
                    } else if (*c >= '0' && *c <= '9') {
                        b = b * 10 + (*c - '0');
                    } else {
						printf("test6\n");
                        fprintf(stderr, "Error: Could not parse input line\n");
                        return 1;
                    }
                    b *= b_sign;
                }
                c++;
            }

            /* Print the parsed values */
            printf("sp = %f, x = %d, y = %d, z = %d, r = %d, g = %d, b = %d\n", sp, x, y, z, r, g, b);

            /* Move the line_start pointer to the next line */
            line_start = q;
        }

        /* Move the remaining partial line to the beginning of the buffer */
        line_end = buffer + (line_end - line_start);
        line_start = buffer;
		// memmove(void *dst, const void *src, size_t len);
        // memmove(buffer, line_start, line_end);
    }

    /* Close the input file */
    close(fd);

    return 0;
}