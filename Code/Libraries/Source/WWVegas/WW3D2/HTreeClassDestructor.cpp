// cl: /O2 /DNDEBUG /MD
//
// HTreeClass destructor, retail 0x001667E0, 26 bytes.
// Dedicated TU so htree.cpp cannot see this body. Calls Free then the
// C allocator on the owned pointer at +0x1C.

extern "C" void __cdecl free(void *);

class HTreeClass
{
	char pad[0x1C];
	void *Owned;

public:
	void Free();
	~HTreeClass();
};

HTreeClass::~HTreeClass()
{
	Free();
	if (Owned)
		free(Owned);
}
