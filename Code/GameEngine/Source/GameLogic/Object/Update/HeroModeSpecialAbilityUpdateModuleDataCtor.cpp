// cl: /Ireference/shims/bfme2_ascii /MD /DNDEBUG /EHsc
//
// ??0HeroModeSpecialAbilityUpdateModuleData@@QAE@XZ, retail 0x0049227B
// (90 bytes). EH ModuleData ctor over the pinned SpecialAbilityUpdateModuleData intermediate
// base (0x0044EB54, size 0xC8): installs vtable 0x00C4DF58, zeroes the
// +0xC8 string member inline, sets it from the empty literal through the
// AsciiString set alias pin at 0x000055F5, then clears the +0xCC word and
// the +0xD0/+0xD1 flags. Two unwind states count the base and the member
// for the throwing set call. Donor: BFME1
// HeroModeSpecialAbilityUpdateModuleDataCtorThunk.cpp (same shape with a
// 0x250 base and the member at +0x254; BFME2 shrinks the base to 0xC8 with
// the member at +0xC8 and calls the one-arg set).

#include "ascii_string.h"

class __declspec(novtable) SpecialAbilityUpdateModuleData
{
public:
	SpecialAbilityUpdateModuleData();
	virtual ~SpecialAbilityUpdateModuleData();

private:
	unsigned char m_opaque[0xC4];
};

class HeroModeSpecialAbilityUpdateModuleData : public SpecialAbilityUpdateModuleData
{
public:
	HeroModeSpecialAbilityUpdateModuleData();
	virtual ~HeroModeSpecialAbilityUpdateModuleData(); // declared only; defined in HeroModeSpecialAbilityUpdateModuleDataDtor.cpp (0x004922F1)

private:
	AsciiString m_stringC8;	// +0xC8
	int m_intCC;	// +0xCC
	bool m_flagD0;	// +0xD0
	bool m_flagD1;	// +0xD1
};

HeroModeSpecialAbilityUpdateModuleData::HeroModeSpecialAbilityUpdateModuleData()
	: SpecialAbilityUpdateModuleData()
{
	m_stringC8.set("");
	m_intCC = 0;
	m_flagD0 = false;
	m_flagD1 = false;
}
