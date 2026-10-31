// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ??0Rva001095B2@@QAE@XZ @0x0010B9B7 (18B) and ??0Rva00109610@@QAE@XZ @0x0010BA71 (18B).
// Derived default constructors of the two shadow-family classes whose destructors are rowed
// at 0x001095B2 (Rva001095B2Dtor.cpp) and 0x00109610 (Rva00109610Dtor.cpp) and whose scalar
// deleting destructors are 0x0010B9C9 / 0x0010BA83. Each calls its out-of-line base ctor and
// stores its own vtable (0x007CF9F4 / 0x007CFA00): the first over Rva007B1380 (rowed ctor
// 0x00109D8C), the second over Rva000F0F2B (rowed ctor 0x000F0F2B). Bases are declared only as
// far as the ctor call and virtual dispatch need. The first slot is the deleting destructor,
// as in Rva001095B2Dtor.cpp and Rva00109610Dtor.cpp.
#pragma inline_depth(0)
#include "../../../GameEngineDevice/Source/W3DDevice/GameClient/Shadow/BfmeShadowPrefix.h"
#pragma inline_depth()

class Rva001095B2Owned
{
public:
	virtual void *deleteInstance(int pool);
};

class Rva007B1380 : public BfmeShadowBufferOwnerBase
{
public:
	Rva007B1380();
	void rva00109D64();
};

class Rva001095B2 : public Rva007B1380
{
public:
	Rva001095B2();
	virtual ~Rva001095B2();

private:
	// BfmeShadowBufferOwnerBase fills +0x00..+0x57
	Rva001095B2Owned *m_58; // +0x58
	Rva001095B2Owned *m_5C; // +0x5C
};

Rva001095B2::Rva001095B2()
{
}

class Rva000F0F2B
{
public:
    Rva000F0F2B();
    virtual ~Rva000F0F2B();
protected:
    char m_body[0x68 - 4];
};

class Rva00109610 : public Rva000F0F2B
{
public:
	Rva00109610();
	virtual ~Rva00109610();
};

// Select-any like the W3DProjectedShadowInit.cpp copy (this retail body comes
// first in link order, so it is the copy the link keeps); the anchor keeps the
// body emitted.
inline Rva00109610::Rva00109610()
{
}

// Retain the inline body's ledger emission without changing its callers.
// ?bfmeEmitRva00109610Ctor@@YAXPAVRva00109610@@@Z absent-from-retail
void bfmeEmitRva00109610Ctor(Rva00109610 *p)
{
	p->Rva00109610::Rva00109610();
}
