// cl: /MD /ICode/Libraries/Source/WWVegas/WWLib
// ??_G?$SimpleDynVecClass@E@@UAEPAXI@Z @0x001A8050 30B
// Deleting dtor slot 0 of vtable 0x007D71EC; calls ??1?$SimpleDynVecClass@E@@UAE@XZ
// (0x001A7F20, pinned) then rowed operator delete at 0x0002FD60; StreakLine donor
// virtual dtor. Retail's destructor has no unwind frame: its array frees are
// nonthrowing, so this unit declares operator delete[] that way.
#include <new>
#define _OPERATOR_NEW_DEFINED_
#include "simplevec.h"

// Instantiating the destructor emits the class's vtable and with it the deleting
// destructor, exactly as the stock WWLib template defines both.
template SimpleDynVecClass<unsigned char>::~SimpleDynVecClass(void);
