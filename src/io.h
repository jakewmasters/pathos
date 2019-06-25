// framebuffer ports
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5
// framebuffer commands
#define FB_HIGH_BYTE_CMD 14
#define FB_LOW_BYTE_CMD 15

void outb(unsigned short port, unsigned char data);
