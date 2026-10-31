// BFME 2: Convert_Color zeroes its result before the asm pack (mov [ebp-x],0 in rows read_vertex_colors
// 0x00188760 and read_dig 0x00188DF0), which Zero Hour's header lacks. dx8wrapper.cpp's own shim has it.
#include "../bfme_dx8wrapper_home_link/dx8wrapper.h"
