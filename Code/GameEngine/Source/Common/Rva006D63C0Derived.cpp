// cl: /MD
// These derived destructors install their own vtable and destroy AptValueWithHash.
// The retail tail calls reach its complete destructor at 0x006D63C0.
#include "../../../Libraries/Source/Apt/AptObject/AptScriptFunction.h"

class AptRef
{
public:
	virtual void AddRef();
	virtual void Release();
};

// Pooled classes: the scalar deleting destructors emitted here release
// through the chain-block pool at 0x00E176F4 with the class size, as retail's
// do (rowed here; previously modelled by address-named views in
// Rva006CBF40Siblings.cpp).
class Rva006D2A60
{
public:
	void *allocBlock(int);
	void freeBlock(void*,int);
};

extern Rva006D2A60 *g_pChainBlockAllocatorF4;   // 0x00E176F4

class Rva006DE2B0 : public AptValueWithHash
{
public:
	virtual ~Rva006DE2B0();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
	AptRef *m_ctor;
	virtual void *Rva006DE210(int unused, const EAStringC &name);
	virtual bool Rva006DE240(int unused, const EAStringC &name, AptRef *value);
};

Rva006DE2B0::~Rva006DE2B0()
{
}

class Rva006DE6C0 : public AptValueWithHash
{
public:
	virtual ~Rva006DE6C0();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
	char m_pad[4]; // sizeof 0x20
};

Rva006DE6C0::~Rva006DE6C0()
{
}
