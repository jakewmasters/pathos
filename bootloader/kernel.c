int kmain(){
    char *vram = (char *) 0xb8000;
    *vram = 'X';
    return 0xdeadbeef;
}