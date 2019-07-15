int placeholder(){
    char *vram = (char *) 0xb8000;
    *vram = 'Y';
    return 0xdadaface;
}

int kmain(){
    char *vram = (char *) 0xb8000;
    *vram = 'X';
    return 0xdeadbeef;
}