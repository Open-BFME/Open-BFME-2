// cl: /DNDEBUG /MD /EHsc /G7 /arch:SSE
//
// Four retail bodies recovered in the 0x00154320..0x00154573 cluster.
//
//  0x00154320  ?rva00154320@Rva00154320@@QAE_NMM@Z     72B
//  0x001544B0  ??1FontCharsClassGdiState@@QAE@XZ       63B
//  0x001544F0  ??_GRva001544F0@@QAEPAXI@Z              36B
//  0x00154520  ??_GFontCharsClassGdiState@@QAEPAXI@Z   83B
//
// The two deleting destructors are emitted by the free-function anchors at the
// bottom (never called; they exist only to force MSVC to emit the COMDAT).
// Anchor symbols are not ledger-checked (the declared-unmatched gate only sees
// Class::method definitions).

#include <windows.h>

// Required so `delete[]` routes through the vector delete operator ??_V; the
// declaration emits no code.
void operator delete[](void *p);

class Rva00154320
{
public:
	bool rva00154320(float a, float b);

private:
	char _pad[0xb4];
	float m_a;
	float m_b;
};

bool Rva00154320::rva00154320(float a, float b)
{
	if (m_a != a || m_b != b)
	{
		m_a = a;
		m_b = b;
		return true;
	}
	return false;
}

class Rva001544F0
{
public:
	~Rva001544F0();

	char *m_array;
};

// ?Rva001544F0::~Rva001544F0 present-unmatched
Rva001544F0::~Rva001544F0()
{
	delete[] m_array;
}

class FontCharsClassGdiState
{
public:
	~FontCharsClassGdiState();

	int m_refs;
	HBITMAP m_oldBitmap;
	HBITMAP m_bitmap;
	void *m_bits;
	HDC m_dc;
};

inline FontCharsClassGdiState::~FontCharsClassGdiState()
{
	if (m_bitmap != 0)
	{
		SelectObject(m_dc, m_oldBitmap);
		DeleteObject(m_bitmap);
		m_bitmap = 0;
	}
	if (m_dc != 0)
	{
		DeleteDC(m_dc);
		m_dc = 0;
	}
}

// Emission anchors: force the scalar deleting destructor COMDATs; each is
// devirtualized/expanded into the ??_G body compiled above.
void Rva001544F0_Anchor(Rva001544F0 *p)
{
	delete p;
}

void FontCharsClassGdiState_Anchor(FontCharsClassGdiState *p)
{
	delete p;
}

// Rowed dtor above is now a select-any inline copy (other TUs carry the same
// in-class body); this anchor forces this unit to emit its copy for the row.
#pragma inline_depth(0)
// ?bfmeEmitFontCharsClassGdiStateDtor@@YAXPAVFontCharsClassGdiState@@@Z present-unmatched
void bfmeEmitFontCharsClassGdiStateDtor(FontCharsClassGdiState *p)
{
	p->~FontCharsClassGdiState();
}
#pragma inline_depth()
