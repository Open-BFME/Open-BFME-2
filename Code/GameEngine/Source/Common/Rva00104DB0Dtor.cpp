// cl: /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ??1Rva00104DB0@@UAE@XZ, retail 0x00104DB0, 54 bytes.
// Evidence: leaf lane pin dtor, callers in Rva00104E03Dtor and deleting dtor, callee Render2DSentenceClass dtor pin 0x00157C70.
#include "../../../Libraries/Source/WWVegas/WW3D2/Render2DSentenceClass.h"

class Rva00104DB0Base
{
public:
	Rva00104DB0Base();
	virtual ~Rva00104DB0Base() {}
};
// ??0Rva00104DB0Base@@QAE@XZ @0x00104DA7 9B: the default constructor, storing the
// class's own vtable (VA 0x00BCF7E8) and returning this.
Rva00104DB0Base::Rva00104DB0Base()
{
}

class Rva00104DB0 : public Rva00104DB0Base
{
public:
	virtual ~Rva00104DB0();
private:
	Render2DSentenceClass m_sentence;
};

Rva00104DB0::~Rva00104DB0()
{
}
