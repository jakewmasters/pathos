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

void
sleep(unsigned long long nanoseconds)
{
    unsigned long long init_tsc = rdtsc();
    unsigned long long end_tsc = init_tsc + nanoseconds;
    while (rdtsc() < end_tsc){
        continue;
    }
    return;
}
