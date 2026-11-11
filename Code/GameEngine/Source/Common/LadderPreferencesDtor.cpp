// APT destructor at RVA 0x006D6470. Constructor 0x006D6410 calls the
// 0x006D6360 base constructor, which builds an AptNativeHash at +8, then
// writes the flag word at +0x1C. Destruction installs VA 0x00CEA264,
// destroys the hash at 0x0070A840 and calls the root destructor at 0x006DE350.
// The former LadderPreferences name came from a donor with a different layout.

// The scalar deleting destructor emitted here releases through the
// chain-block pool at 0x00E176F4 with the class size, as retail's does.
#include "../../../Libraries/Source/Apt/AptNativeHash.h"
#include "../../../Libraries/Source/Apt/Rva006D2A60.h"

extern Rva006D2A60 *g_pChainBlockAllocatorF4;   // 0x00E176F4

// The AptValue root view the first-in-link-order vtable copy
// (Rva006D6360Ctor.cpp) declares: its private slot 0 precedes the destructor.
class AptValue
{
public:
    virtual void AddRef();
    virtual void Release();
};
// Retail vtable 0x008EA228 starts with the rowed AptValue::AddRef (0x006DCAC0) and Release.
class BfmeAptValue006DCD20 : public AptValue
{
protected:
    unsigned int m_flags04;
public:
    virtual ~BfmeAptValue006DCD20();
};
struct Rva006DE350 : public BfmeAptValue006DCD20
{
	virtual ~Rva006DE350();
};

struct Rva006D6470Owner : public Rva006DE350
{
	AptNativeHash m_nativeHash; // +0x08
	unsigned int m_bits; // +0x1C

	virtual ~Rva006D6470Owner();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
};

Rva006D6470Owner::~Rva006D6470Owner()
{
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1S4Base009A1A40@@UAE@XZ=??1Rva006D6470Owner@@UAE@XZ")
