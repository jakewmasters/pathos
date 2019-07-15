// framebuffer ports
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5
// framebuffer commands
#define FB_HIGH_BYTE_CMD 14
#define FB_LOW_BYTE_CMD 15
// CMOS port
#define CMOS_READ_PORT 0x71
#define CMOS_WRITE_PORT 0x70
// CMOS "registers"
#define CMOS_SECONDS 0x00
#define CMOS_MINUTES 0x02
#define CMOS_HOURS 0x04
#define CMOS_WEEKDAY 0x06
#define CMOS_DAY_OF_MONTH 0x07
#define CMOS_MONTH 0x08
#define CMOS_YEAR 0x09
#define CMOS_CENTURY 0x32 // not confirmed

void outb(unsigned short port, unsigned char data);
unsigned long inb(unsigned short port);
