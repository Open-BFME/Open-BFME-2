// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// platformsdk
//
// Two memory-pool slot forwarders after the replaced C free (0x00030830).
// The slots are the MemoryPool exports Rva00030730Init resolves with
// GetProcAddress: VA 0x00DE03F4 is ?_GetBlockSize@MemoryPool@@YAIPAXI@Z and
// VA 0x00DE03EC is ?_VerifyIntegrity@MemoryPool@@YAXXZ. Names stay
// address-derived; the shapes come from the retail bytes.

#include <windows.h>
	// retail RVA 0x009E03EC (.bss), defined here

typedef unsigned int (__cdecl *GetBlockSizeFunction)(void *, unsigned int);
typedef void (__cdecl *VerifyIntegrityFunction)(void);

// --- 0x00031420 (12B): forward a message to OutputDebugStringA. Its address
// is taken at 0x00033D37 (a GeneralAllocator trace-callback store).

void rva00031420(const char *text)
{
	OutputDebugStringA(text);
}

// --- 0x000308F0 (6B): tail-jump into the heap-allocator slot VA 0x00DE03E4
// (?_GetHeapAllocator@MemoryPool@@YAPAVGeneralAllocator@Allocator@EA@@I@Z),
// unreferenced.
namespace EA { namespace Allocator { class GeneralAllocator; } }
