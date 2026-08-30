// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// The retail memory-pool build replaces the C allocator entry points. Its
// free wrapper forwards the block with memory class 3 to the game allocator.

typedef void (__cdecl *GameFreeFunction)(void *, int);
extern "C" GameFreeFunction __gameMemFreePtr;

extern "C" void __cdecl free(void *block)
{
	__gameMemFreePtr(block, 3);
}
