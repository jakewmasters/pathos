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

char *
strcpy(char *str)
{
    unsigned int in_len = strlen(str) + 1;
    // nevermind, i think i need malloc :(
}

/*
 * reverses a string in place
 * came up with this on my own :)
 */
void
strrev(char *str)
{
    char aux_char = 0;
    unsigned int front_index = 0;
    unsigned int back_index = strlen(str)-1;
    while(front_index < back_index){
        aux_char = str[front_index];
        str[front_index] = str[back_index];
        str[back_index] = aux_char;
        front_index++;
        back_index--;
    }
}

/*
 * convert a base 10 decimal to a string
 */
void
d_str(int d, char *str)
{
    // borrowed this part from Kernighan & Ritchie
    int i, sign;
    if ((sign = d) < 0) d = -d;
    i = 0;
    do {
        str[i++] = d%10 + '0';
    } while ((d /= 10) > 0);
    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    // reverse
    strrev(str);
}

unsigned int
strcmp(char *str1, char *str2)
{
    if (strlen(str1) != strlen(str2)){
        return -1;
    }
    for (int i=0; i < strlen(str1); ++i){
        if (str1[i] != str2[i]){
            return -1;
        }
    }
    return 0;
}