// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ?Clone@Rva007C454@@UBEPAVRenderObjClass@@XZ @0x0007C4C6 58B: the clone
// slot of the CameraClass-derived Rva007C454: return new Rva007C454(*this).
// Evidence: slot 2 of the primary vtable 0x00BC6C58 (slot 1 the rowed
// ??_GRva007C454 0x0007C5B9, slot 3 CameraClass::Class_ID, the WW3D
// RenderObjClass order Clone/Class_ID); operator new 0x0002FDA0 of 0x408
// bytes (the size the ctor caller 0x0007C538 also allocates) and the rowed
// copy ctor 0x0007C404 under an EH state.

// The canonical CameraClass (over the canonical RenderObjClass), as in the class's ctor, copy ctor and
// dtor units (P24).
#define BFME_RO_DTOR_DECL_ONLY
#include "../../../Libraries/Source/WWVegas/WW3D2/CameraClass.h"

class Rva007C454 : public CameraClass
{
public:
	Rva007C454(const Rva007C454 &other);
	virtual ~Rva007C454();
	virtual RenderObjClass *Clone() const;
	virtual bool Cull_Sphere(const SphereClass &sphere) const;
	virtual bool Cull_Box(const AABoxClass &box) const;
private:
	char m_3FC[0x408 - 0x3FC];
};

RenderObjClass *Rva007C454::Clone() const
{
	return (RenderObjClass *)new Rva007C454(*this);
}
