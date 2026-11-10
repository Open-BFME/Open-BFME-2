// ??1Rva006FBC90Owner@@UAE@XZ @0x006FBC90, 82 bytes. Target Ghidra evidence:
// the deleting wrapper at 0x006FBC60 calls this body and conditionally frees
// the object; the wrapper is referenced by vtable 0x00CED880. This destructor
// stores that vtable, destroys the opaque member at +8 through 0x0070A840,
// then calls the matched base destructor at 0x006DE350. The member/base
// class identities remain RVA-derived; the Zero Hour LadderPreferences name
// is not used because its separately matched BFME2 layout differs.

// The scalar deleting destructor emitted here releases through the
// chain-block pool at 0x00E176F4 with the class size, as retail's does.
#include "../../../Libraries/Source/Apt/Rva006D2A60.h"

extern Rva006D2A60 *g_pChainBlockAllocatorF4;   // 0x00E176F4

// The owner is the AptValueWithHash-derived frame stack of
// AptFrameStackConstructors.cpp, which constructs it and emits the first copy
// of its vtable. The Apt value interface below is AptScriptFunction.h's
// declaration order, so this copy names the same 15 slots; only the hash
// member at +8 keeps the rowed Rva0070A840 destructor spelling, because
// ??1AptNativeHash@@QAE@XZ (pinned at the same 0x0070A840) has no row.
struct AptNativeHash;
class EAStringC;

#include "../../../Libraries/Source/Apt/AptValue.h"

class __declspec(novtable) AptValueGC : public AptValue
{
public:
	virtual bool IsGarbageCollected() const;
protected:
	virtual ~AptValueGC() {}
};

struct Rva0070A840
{
	~Rva0070A840();
	char m_data[0x14];
};

class __declspec(novtable) AptValueWithHash : public AptValueGC
{
public:
	virtual AptNativeHash *GetNativeHashVirtual();
	virtual bool ContainsNativeHashVirtual() const;
	virtual void RegisterReferences() const;
	virtual void DestroyGCPointers();
protected:
	virtual ~AptValueWithHash() {}
	Rva0070A840 mNativeHash; // +0x08
};

class Rva006FBC90Owner : public AptValueWithHash
{
	AptValue *parent; // +0x1C
public:
	virtual ~Rva006FBC90Owner();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
};

Rva006FBC90Owner::~Rva006FBC90Owner()
{
}
