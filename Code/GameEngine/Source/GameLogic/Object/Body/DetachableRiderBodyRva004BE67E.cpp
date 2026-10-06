// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
//
// ?Rva004BE67E@DetachableRiderBody@@UBE?AVAsciiString@@XZ, retail 0x004BE67E,
// 30 bytes. Honest-address virtual returning the +0x2C AsciiString of the
// module data (ActiveBodyModuleData::m_grabObject layout from
// SupplyTruckAIUpdateModuleDataCtor.cpp / ActiveBodyModuleDataDtor.cpp)
// via the +0x04 module-data pointer the DetachableRiderBody ctor leaves
// (DetachableRiderBodyCtor.cpp 0x004C1C82).
//
// RVO shape follows GlobalDataRva002360DE.cpp (hidden return pointer in
// [ebp+8] copy-constructed via the pinned StringBase<char> copy 0x000365F0
// with the `and [ebp-4],0` EH state store; /GX keeps the frame). No callers
// in the packet. True vtable is slot 28 (offset 0x70) of 0x0085BF48, the
// +0x10 secondary installed as [esi+0x10]=0x00C5BF48 by the ctor; the packet
// serves it as slot 46 of 0x0085BF00 because tf.py only tracks disp-0
// installs so the 18-slot UpgradeMux member vtable overruns into the
// adjacent secondaries (0x0085BF00+0x48 is 0x0085BF48; slot 18 there is slot
// 0 here). Method name is an honest address name; slot index is the proof
// (SiegeDeployHordeSpecialPowerRva004C63DE.cpp precedent).

#include "ascii_string.h"


struct ActiveBodyModuleData
{
	char m_pad00[0x2C];
	AsciiString m_grabObject; // +0x2C (ActiveBodyModuleDataDtor.cpp)
};

class DetachableRiderBodyPrimary
{
public:
	virtual void primaryAnchor() = 0;

	const ActiveBodyModuleData *m_moduleData; // +0x04 (DetachableRiderBodyCtor.cpp)
	char m_pad08[0x10 - 0x08];
};

class DetachableRiderBodySecondary
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s10() = 0;
	virtual void s11() = 0;
	virtual void s12() = 0;
	virtual void s13() = 0;
	virtual void s14() = 0;
	virtual void s15() = 0;
	virtual void s16() = 0;
	virtual void s17() = 0;
	virtual void s18() = 0;
	virtual void s19() = 0;
	virtual void s20() = 0;
	virtual void s21() = 0;
	virtual void s22() = 0;
	virtual void s23() = 0;
	virtual void s24() = 0;
	virtual void s25() = 0;
	virtual void s26() = 0;
	virtual void s27() = 0;
	virtual AsciiString Rva004BE67E() const = 0;
};

class DetachableRiderBody : public DetachableRiderBodyPrimary, public DetachableRiderBodySecondary
{
public:
	virtual AsciiString Rva004BE67E() const;
};

AsciiString DetachableRiderBody::Rva004BE67E() const
{
	return m_moduleData->m_grabObject;
}
