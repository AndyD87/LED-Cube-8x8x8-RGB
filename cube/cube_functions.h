#ifndef _cube_functions_
   #define _cube_functions_

extern unsigned char led[3][64];

extern void cube_set_led(unsigned char, unsigned char);
extern void cube_set_color(unsigned char color);
extern void cube_set_x_line(unsigned char address, unsigned char color, unsigned char value);
extern void cube_set_y_line(unsigned char address, unsigned char color, unsigned char value);
extern void cube_set_z_line(unsigned char address, unsigned char color, unsigned char value);
extern void cube_cp_z_level(unsigned char _from, unsigned char _to);
extern void cube_mv_z_level(unsigned char _from, unsigned char _to);
extern void cube_cp_x_level(unsigned char _from, unsigned char _to);
extern void cube_mv_x_level(unsigned char _from, unsigned char _to);
extern void cube_cp_y_level(unsigned char _from, unsigned char _to);
extern void cube_mv_y_level(unsigned char _from, unsigned char _to);
extern void cube_cp_x_line (unsigned char _from, unsigned char _to);
extern void cube_mv_x_line (unsigned char _from, unsigned char _to);
extern void cube_cp_y_line (unsigned char _from, unsigned char _to);
extern void cube_mv_y_line (unsigned char _from, unsigned char _to);
extern void cube_cp_z_line (unsigned char _from, unsigned char _to);
extern void cube_mv_z_line (unsigned char _from, unsigned char _to);
extern void cube_roll_z_up(unsigned char carry);
extern void cube_roll_z_down(unsigned char carry);
extern void cube_roll_x_up(unsigned char carry);
extern void cube_roll_x_down(unsigned char carry);
extern void cube_roll_y_up(unsigned char carry);
extern void cube_roll_y_down(unsigned char carry);
extern void cube_rotate_x(unsigned char steps);
extern void cube_rotate_y(unsigned char steps);
extern void cube_rotate_z(unsigned char steps);

extern unsigned char mirror_bits(unsigned char bits);

#endif
