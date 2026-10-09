// cl: /O2 /MD /EHsc
// Target30830/17B and existing GameMemoryFree.cpp establish the allocator
// wrapper: block and memory class3 through the existing pointer. /O2 gives
// the retail register load and stack cleanup; the Common record uses /O1.
// This is a genuine full-byte/relocation fold of _free and adds no unique bytes.
typedef void (__cdecl *GameFreeFunction)(void *,int);
extern "C" GameFreeFunction __gameMemFreePtr;
void __cdecl Rva00030830GameFree(void *block) {__gameMemFreePtr(block,3);}
