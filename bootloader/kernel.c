#include "framebuffer.h"

#if defined(__linux__) // cheating here, need to actually use cross-compiler
#error "need to use cross-compiler"
#endif

#if !defined(__i386__)
#error "compile for the right target ;)"
#endif

int kmain(){
    fb_clear();
}