// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0OCLSpecialPowerModuleData@@QAE@XZ, retail 0x004C32BC (169 bytes).
// OCL power data over the pinned Rva004930A0 base ctor (0x4930A0, 0x7C
// base): UpgradeOCL at +0x7C is an 8B upgrade-pair vector through the
// rowed Vector_base at 0x00211E58, cleared through erase at 0x003FA4DB
// (CashHack clear-lowers-to-erase precedent), m_defaultOCL at +0x88 and
// m_createLoc at +0x8C zero, UpgradeName at +0x90 is an AsciiString
// vector, NearestSecondaryObjectFilter at +0x9C builds through the
// opaque 0x3623E5 pin, and two 28B FixedStorage temps from the prototype
// at 0x00DFEFA4 feed the filter through the 0x362087 pin (ret 0x38).
// Own table 0x00C5CDC0 proves every field; the OCLSpecialPower data
// factory at 0x00251B8A news 0xAC and calls this ctor as sole caller.
// Shape follows CitadelSlaughterHordeContainModuleDataCtor (virtual base
// plus virtual derived with declared-only dtors arms the EH states; the
// compiler installs this TU's vtable through the ??_7 pin at 0x00C5CCB0,
// whose slot0 is the scalar-deleting dtor at 0x4C37A4) over
// CashHackSpecialPowerModuleDataCtor (Rva004930A0 base plus vector
// clear plus int zero). BFME1 OCLSpecialPower.cpp proves the BFME1
// member names and the m_defaultOCL-clear-m_createLoc body order.

#include <bitset>
#include <vector>
#include <string.h>

namespace _STL {
template<> bitset<128> &bitset<128>::reset();
}

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	void clear();
	~AsciiString();

private:
	void *m_data;
};

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);

private:
	unsigned char m_bytes[28];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
	void initFromStorages(BfmeFixedStorage0004543D first, BfmeFixedStorage0004543D second);

private:
	int m_x;
};

// Opaque intermediate base (DeliverPayloadAIUpdateCtor precedent: the pin
// claims only the address): the rowed SpecialPowerModuleData base plus
// 0x64 of unknown intermediate storage.
class Rva004930A0
{
public:
	Rva004930A0();
	virtual ~Rva004930A0();

private:
	unsigned char m_pad[0x7C - 4]; // +0x04..+0x7B
};

// BFME1 OCLSpecialPower.cpp parseOCLUpgradePair: science plus OCL pair.
struct OCLUpgradePair
{
	int m_science;
	int m_ocl;
};

// Virtual base plus virtual derived with declared-only dtors (no code):
// the base contributes the vptr at +0 so the base call takes this with no
// displacement, and the derived vtable store lands mid-init through the
// ??_7 pin (Citadel precedent).
class OCLSpecialPowerModuleData : public Rva004930A0
{
public:
	OCLSpecialPowerModuleData();
	virtual ~OCLSpecialPowerModuleData();

private:
	_STL::vector<OCLUpgradePair> m_upgradeOCL; // +0x7C, UpgradeOCL
	int m_defaultOCL; // +0x88, OCL
	int m_createLoc; // +0x8C, CreateLocation
	_STL::vector<AsciiString> m_upgradeName; // +0x90, UpgradeName
	Rva003623E5Member m_nearestSecondaryObjectFilter; // +0x9C, NearestSecondaryObjectFilter
};

// ??0OCLSpecialPowerModuleData@@QAE@XZ @0x4C32BC
OCLSpecialPowerModuleData::OCLSpecialPowerModuleData()
{
	m_defaultOCL = 0;
	m_upgradeOCL.clear();
	m_createLoc = 0;
	m_nearestSecondaryObjectFilter.initFromStorages(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)),
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)));
}
