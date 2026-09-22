// cl: /DNDEBUG /MD /EHa /Oy-
//
// Debug::PreStaticInit, retail 0x000385F0 (114 bytes).
//
// Zero Hour initialises a static Debug Instance member by member here.
// BFME2 (like BFME 1, b1 0x00889500, same bytes but for sizeof(Debug))
// creates the singleton on first use instead, placement-constructed in a
// DebugAllocMemory block (0x9F68 bytes), the constructor at
// 0x00038440 does the member setup, and every call bumps the reference
// count at +0x9C7C before returning the pointer kept in theDebug
// (0x00DE0880).

#include <new>      // placement new, as the debug library uses it

void *DebugAllocMemory(size_t numBytes);

class Debug
{
public:
	virtual ~Debug();

private:
	Debug();

	static Debug *PreStaticInit();

	unsigned char m_pad04[0x9C78];
	int refCount;                        // +0x9C7C
	unsigned char m_pad9C80[0x9F68 - 0x9C80];
};

Debug *theDebug;

// ?PreStaticInit@Debug@@CAPAV1@XZ
Debug *Debug::PreStaticInit()
{
	if (!theDebug)
		theDebug = new (DebugAllocMemory(sizeof(Debug))) Debug;
	++theDebug->refCount;
	return theDebug;
}
