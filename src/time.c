#include "io.h"
/*
 * time library
 */

/*
 * read processor's timestamp counter
 * value is increased by 1000000000 (10^9) every second
 * ^^ need to verify this value
 */
unsigned long long
rdtsc()
{
    unsigned high_bits, low_bits;
    __asm__("rdtsc": "=a"(low_bits), "=d"(high_bits));
    
    unsigned long long tsc;
    tsc = ((unsigned long long)low_bits) | (((unsigned long long)high_bits) << 32);
    return tsc;
}

unsigned long long
get_median_clock_rate()
{
    unsigned base, max;
    __asm__("mov $0x16, %%eax \n\t"
    "cpuid \n": "=a"(base), "=b"(max));

    return ((base+max)/2);
}

/*
 * driver function to access CMOS and the Real-Time Clock (RTC)
 */
unsigned long
rtc(unsigned char option)
{
    // lets just get the seconds value as a test
    outb(CMOS_WRITE_PORT, (0 << 7) | (option));
    unsigned long hour = inb(CMOS_READ_PORT);
    return hour;
}

void
sleep(unsigned int seconds)
{
    // unsigned long long init_tsc = rdtsc();
    // unsigned long long offset = get_median_clock_rate() * seconds;
    // unsigned long long end_tsc = init_tsc + offset;
    // while (rdtsc() < end_tsc){
    //     continue;
    // }
    // return;

    // try using rtc
    unsigned long init_sec = rtc(CMOS_SECONDS);
    while (rtc(CMOS_SECONDS) <= init_sec + seconds){}
    return;
}
