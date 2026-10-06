// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Oy-
//
// ?setOpacity@Shadow@@QAEXH@Z, retail 0x003308F6, 159 bytes.
// Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/ShadowSetOpacity.cpp,
// matched 169 bytes there).

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class Shadow
{
public:
	void setOpacity(Int value);
	void rva00330995(Int color);

private:
	char m_pad00[0x24];
	UnsignedInt m_color;
	Int m_diffuse;
	UnsignedInt m_opacity;
	char m_pad30[4];
	UnsignedInt m_type;
};

inline void Shadow::setOpacity(Int value)
{
	m_opacity = value;

	if (m_type & 0x1420)
	{
		m_diffuse = (m_color & 0x00ffffff) + (value << 24);
	}
	else if (m_type & 0x0840)
	{
		Real fvalue = (Real)m_opacity / 255.0f;
		m_diffuse = (Int)((Real)(m_color & 0xff) * fvalue)
			| ((Int)((Real)((m_color >> 8) & 0xff) * fvalue) << 8)
			| ((Int)((Real)((m_color >> 16) & 0xff) * fvalue) << 16);
	}
}

void Shadow::rva00330995(Int color)
{
	m_color = (UnsignedInt)color & 0xffffff;

	if (m_type & 0x1420)
	{
		m_diffuse = ((Int)color & 0xffffff) | ((Int)m_opacity << 24);
	}
	else if (m_type & 0x0840)
	{
		Real fvalue = (Real)m_opacity / 255.0f;
		m_diffuse = ((Int)((Real)((color >> 16) & 0xff) * fvalue) << 16)
			| (((Int)((Real)((color >> 8) & 0xff) * fvalue)) << 8)
			| (Int)((Real)(color & 0xff) * fvalue);
	}
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
void (Shadow::*_bfmeInlineAnchor_Shadow_setOpacity_0)(Int value) = &Shadow::setOpacity;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?SetTexture@Rva00330995@@QAEXPAX@Z=?rva00330995@Shadow@@QAEXH@Z")
