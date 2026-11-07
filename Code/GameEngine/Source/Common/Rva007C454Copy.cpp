// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ??0Rva007C454@@QAE@ABV0@@Z @0x0007C404 80B: copy constructor of the
// CameraClass-derived Rva007C454 (rowed ctor 0x0007C3CD, deleting dtor
// 0x0007C5B9 with its -0x8 thunk 0x0007C3FC). Caller: its clone slot
// 0x0007C4C6 (call at 0x0007C4EE). It copies the base through the rowed
// CameraClass copy 0x00134C50, installs both vptrs (0x00BC6C58 at +0 and
// 0x00BC6C54 at +8, the secondary base the thunk proves) and copies the
// vector holder at +0x3FC through the rowed Rva005386F5 copy 0x005386F5.

// The canonical CameraClass (over the canonical RenderObjClass): the class's tables are
// retail's 131-slot 0x00BC6C58 and one-slot 0x00BC6C54 rather than stand-in bases' (P24).
#define BFME_RO_DTOR_DECL_ONLY
#include "../../../Libraries/Source/WWVegas/WW3D2/CameraClass.h"

class Rva005386F5
{
public:
	Rva005386F5(const Rva005386F5 &other);
	~Rva005386F5();
private:
	char m_pad[0x10];
};

class Rva007C454 : public CameraClass
{
public:
	Rva007C454(const Rva007C454 &other);
	virtual ~Rva007C454();
	virtual RenderObjClass *Clone() const;
	virtual bool Cull_Sphere(const SphereClass &sphere) const;
	virtual bool Cull_Box(const AABoxClass &box) const;
private:
	Rva005386F5 m_3FC;
};

Rva007C454::Rva007C454(const Rva007C454 &other) :
	CameraClass(other),
	m_3FC(other.m_3FC)
{
}
