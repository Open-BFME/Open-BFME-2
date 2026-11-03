// cl: /O1 /MD /DNDEBUG /EHsc
// ?rva002788C7@Drawable@@QAE_NHH@Z, retail 0x002788C7 (119B, RET 8): for a
// Drawable whose template has kind-of byte +0x118 bit 0x40 set, lazily
// allocate the 0x310-byte helper (rowed ctor 0x00278869, taking the
// Drawable) into +0x45C, then forward both arguments to its 0x00276952
// query; false without the kind bit or the helper. Names address-derived;
// public wrapper spelling keeps its original raw dword carrier ABI. The
// now-recovered helper interprets those carriers as point/direction addresses.

#include "../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef bool Bool;

class Drawable;

class Rva002768AC
{
public:
	Rva002768AC(Drawable *drawable);
	Bool rva00276952(const Coord3D *point, Coord3D *direction);
private:
	unsigned char m_bytes[0x310];
};

struct DrawableTemplateKindView
{
	unsigned char m_pad000[0x118];
	unsigned char m_kindOf118; // +0x118
};

class Drawable
{
public:
	Bool rva002788C7(Int point, Int direction);
private:
	void *m_vtable;
	const DrawableTemplateKindView *m_template; // +0x04
	unsigned char m_pad008[0x45C - 0x08];
	Rva002768AC *m_helper; // +0x45C
};

Bool Drawable::rva002788C7(Int point, Int direction)
{
	if (!(m_template->m_kindOf118 & 0x40))
		return false;
	if (m_helper == 0)
		m_helper = new Rva002768AC(this);
	if (m_helper == 0)
		return false;
	return m_helper->rva00276952(reinterpret_cast<const Coord3D *>(point), reinterpret_cast<Coord3D *>(direction));
}
