// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD /arch:SSE
//
// ?loadPostProcess@LivingWorldRegion@@UAEXXZ, retail 0x003F08EE, 24 bytes (RET).
// Snapshot post-load step of the living-world region parsed by 0x00210620
// (class view in LivingWorldRegionConstructor.cpp): it runs the rowed
// 0x003F012F step and then hands the byte flag at +0x1A2 to the rowed
// 0x003EFDF5 setter. The setter takes the flag as a byte (retail pushes the
// register after a plain MOV AL, no extension), spelled here through a
// byte-typed view of the same member function, which is the rowed
// ?rva003EFDF5@Rva003EFDF5Host@@QAEXPAX@Z symbol. The unreconstructed
// remainder of the object is padding.

class Rva003F012F
{
public:
	void rva003F012F();
};

#include "../../../../../Libraries/Source/WWVegas/WWLib/Rva003EFDF5Host.h"

class Xfer;
#include "../../../../Include/GameLogic/LivingWorldRegion.h"

typedef void (Rva003EFDF5Host::*Rva003EFDF5ByteSetter)(bool);

void LivingWorldRegion::loadPostProcess()
{
	((Rva003F012F *)this)->rva003F012F();
	Rva003EFDF5ByteSetter setter = reinterpret_cast<Rva003EFDF5ByteSetter>(&Rva003EFDF5Host::rva003EFDF5);
	(((Rva003EFDF5Host *)this)->*setter)(m_field1A2);
}
