// ??0Rva00177860@@QAE@XZ
// partial score=1.0 date=2026-10-04
// cl: /O1 /arch:SSE2 /Ireference/shims/bfmeshader /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath
// Donor: Open-BFME-1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/GameEngine/Source/Common/Open2Conv002.cpp, compiled /O1.
// Target Ghidra00177860/195B has four owned pointer fields +0/+4/+8/+C,
// refcount dword +4, disposal slot0, and a texture handle +14 released by
// the matched TextureClass::Release_Ref at0061ED10. Its EH cleanup state
// proves the texture owning subobject. Data xrefs identify shared pointer
// slots009F7044/009F7048; retail initializes both to zero and accesses them
// from00177860,00177923,00177F82. Source names and the class role are unknown;
// the index-buffer interpretation of these slots in the donor is unproven.

#include "shader.h"

class Rva00177860Ref
{
public:
	virtual void dispose();
	// ?Rva00177860Ref::release present-unmatched
	void release()
	{
		if (--m_refs == 0)
			dispose();
	}
	int m_refs;
};

class TextureClass
{
public:
	void Release_Ref();
};

class Rva00177860TextureRef
{
public:
	// ?Rva00177860TextureRef::Rva00177860TextureRef present-unmatched
	Rva00177860TextureRef() : m_ptr(0) {}
	// ?Rva00177860TextureRef::~Rva00177860TextureRef present-unmatched
	~Rva00177860TextureRef()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}
	TextureClass *m_ptr;
};

Rva00177860Ref *Rva009F7044 = 0;
Rva00177860Ref *Rva009F7048 = 0;

class Rva00177860
{
public:
	Rva00177860();
	~Rva00177860();
	Rva00177860Ref *m_00;
	Rva00177860Ref *m_04;
	Rva00177860Ref *m_08;
	Rva00177860Ref *m_0c;
	int m_10;
	Rva00177860TextureRef m_14;
	unsigned int m_18;
	float m_1c, m_20, m_24, m_28;
};

Rva00177860::~Rva00177860()
{
	if (m_00) { m_00->release(); m_00 = 0; }
	if (m_04) { m_04->release(); m_04 = 0; }
	if (m_08) { m_08->release(); m_08 = 0; }
	if (m_0c) { m_0c->release(); m_0c = 0; }
	Rva00177860Ref *globalA = Rva009F7044;
	if (globalA)
		globalA->release();
	Rva00177860Ref *globalB = Rva009F7048;
	if (globalB)
	{
		bool last = globalB->m_refs == 1;
		globalB->release();
		if (last)
		{
			Rva009F7044 = 0;
			Rva009F7048 = 0;
		}
	}
}

// Native constructor59B via two opaque FX publishers with new2C.
// Address-derived raw32 data source; original field/global meaning unknown.
// Native DIR32 reads existing ShaderClass::_PresetAdditiveSpriteShader at9B624C.
Rva00177860::Rva00177860()
    : m_00(0), m_04(0), m_08(0), m_0c(0), m_10(0), m_14(),
      m_18(ShaderClass::_PresetAdditiveSpriteShader.Get_Bits()), m_1c(1.0f), m_20(1.0f), m_24(1.0f), m_28(1.0f)
{}
