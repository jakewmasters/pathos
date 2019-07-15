/*
 * PathOS Standard Library
 * by Jake Masters
 */

unsigned int 
strlen(const char *str)
{
    unsigned int len = 0;
    while (str[len] != '\0'){
        len++;
    }
    return len;
}

// borrowed from Kernighan & Ritchie
void
d_str(int d, char *str)
{
    int i, sign;
    if ((sign = d) < 0) d = -d;
    i = 0;
    do {
        str[i++] = d%10 + '0';
    } while ((d /= 10) > 0);
    if (sign < 0) str[i++] = '-';
    str[i] = '\0';
}
