/*
 * color definitions
 */
 #define BLACK          0
 #define BLUE           1
 #define GREEN          2
 #define CYAN           3
 #define RED            4
 #define MAGENTA        5
 #define BROWN          6
 #define LIGHT_GREY     7
 #define DARK_GREY      8
 #define LIGHT_BLUE     9
 #define LIGHT_GREEN   10
 #define LIGHT_CYAN    11
 #define LIGHT_RED     12
 #define LIGHT_MAGENTA 13
 #define LIGHT_BROWN   14
 #define WHITE         15

/*
 * available functions
 */
 extern void fb_write(unsigned int i, unsigned char c, unsigned char bg, unsigned char fg);
 extern void fb_move_cursor(unsigned int row, unsigned int col);
 extern void fb_clear();
 extern void fb_write_str(unsigned int row, unsigned int col, const char *str, unsigned char bg, unsigned char fg);
 