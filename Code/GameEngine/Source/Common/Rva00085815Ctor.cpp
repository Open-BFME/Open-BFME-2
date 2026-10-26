// cl: /MD /EHsc /DNDEBUG
// ??0Rva00085815@@QAE@XZ, retail 0x00085815, 67 bytes.
// Ctor with 16B x3 arrays at +0 and +0x30 via vector ctor plus ParabolicEase
// at +0x68 via rowed 0x0008517E with (0 0 1). Evidence: shared 3B empty ctor
// 0x0047A6A9 and vector iterator 0x00001423; caller 0x0008B888.
// The 16B elements are not Region3D (24 B): an opaque neutral element emits
// the shared empty ctor here, rowed as a genuine ICF fold.
#include "../../../Libraries/Include/Lib/Region3D.h"

typedef float Real;

class ParabolicEase
{
public:
	ParabolicEase(Real easeInTime = 0.0f, Real easeOutTime = 0.0f, Real duration = 1.0f);
private:
	Real m_in;
	Real m_out;
};

class Rva00085815Element
{
public:
	Rva00085815Element();
private:
	unsigned char m_pad[0x10];
};

Rva00085815Element::Rva00085815Element()
{
}

class Rva00085815
{
public:
	Rva00085815();
private:
	Rva00085815Element m_00[3];
	Rva00085815Element m_30[3];
	unsigned char m_pad60[8];
	ParabolicEase m_68;
};

Rva00085815::Rva00085815()
{
}
