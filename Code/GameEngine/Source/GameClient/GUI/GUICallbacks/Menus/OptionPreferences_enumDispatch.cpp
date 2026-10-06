// cl: /Ireference/shims/bfme2_ascii /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?Rva002E42AFDispatch@OptionPreferences@@QAEHH@Z, retail 0x002E42AF,
// 35 bytes, plus ?Rva002E42EEForward@OptionPreferences@@QAEHXZ at
// 0x002E42EE and ?Rva002E42F6Forward@OptionPreferences@@QAEHXZ at
// 0x002E42F6 (7 bytes each). Dedicated TU.
//
// Slot-0x1C enum-dispatch family shared with the StaticGameLOD getters:
// the dispatcher indexes a 12-byte-entry table at 0xDBD120 (key string,
// subtable, count; entry 0 is ModelLOD) and forwards the row to the same
// (key, table, count, default) virtual with a zero default. The two
// 7-byte forwarders pin rows 0 and 1. The x12 stride needs /G7 for the
// imul (bare /O1 emits lea+shl). Semantic identities unproven (opaque).

#include <map>
#include <stdlib.h>
#include <string.h>

typedef bool Bool;
typedef int Int;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

typedef _STL::map<AsciiString, AsciiString> AsciiPreferenceMap;

struct BfmeEnumTableEntry
{
	const char *m_key;
	const void *m_subtable;
	Int m_count;
};

// Retail enum-dispatch table at 0xDBD120. COMMON merges across TUs; the
// address patches from retail.
BfmeEnumTableEntry BfmeEnumTable[8];

class OptionPreferences : public AsciiPreferenceMap
{
public:
	virtual ~OptionPreferences();
	virtual void RvaPad01();
	virtual void RvaPad02();
	virtual void RvaPad03();
	virtual void RvaPad04();
	virtual void RvaPad05();
	virtual void RvaPad06();
	virtual Int GetEnumValue(const char *key, const void *table, Int count, Int defaultValue);
	Int Rva002E42AFDispatch(Int index);
	Int Rva002E42EEForward();
	Int Rva002E42F6Forward();
	Int Rva002E42FEForward();
	Int Rva002E4306Forward();
	Int Rva002E430EForward();
	Int Rva002E4316Forward();
	Int Rva002E431EForward();
	Int Rva002E4326Forward();
	Int Rva002E432EForward();
};

// ?Rva002E42AFDispatch@OptionPreferences@@QAEHH@Z
Int OptionPreferences::Rva002E42AFDispatch(Int index)
{
	return GetEnumValue(BfmeEnumTable[index].m_key, BfmeEnumTable[index].m_subtable, BfmeEnumTable[index].m_count, 0);
}

// ?Rva002E42EEForward@OptionPreferences@@QAEHXZ
Int OptionPreferences::Rva002E42EEForward(void)
{
	return Rva002E42AFDispatch(0);
}

// ?Rva002E42F6Forward@OptionPreferences@@QAEHXZ
Int OptionPreferences::Rva002E42F6Forward(void)
{
	return Rva002E42AFDispatch(1);
}

// ?Rva002E42FEForward@OptionPreferences@@QAEHXZ
Int OptionPreferences::Rva002E42FEForward(void)
{
	return Rva002E42AFDispatch(2);
}

// ?Rva002E4306Forward@OptionPreferences@@QAEHXZ
Int OptionPreferences::Rva002E4306Forward(void)
{
	return Rva002E42AFDispatch(3);
}

// ?Rva002E430EForward@OptionPreferences@@QAEHXZ
Int OptionPreferences::Rva002E430EForward(void)
{
	return Rva002E42AFDispatch(4);
}

// ?Rva002E4316Forward@OptionPreferences@@QAEHXZ
Int OptionPreferences::Rva002E4316Forward(void)
{
	return Rva002E42AFDispatch(5);
}

// ?Rva002E431EForward@OptionPreferences@@QAEHXZ
Int OptionPreferences::Rva002E431EForward(void)
{
	return Rva002E42AFDispatch(6);
}

// ?Rva002E4326Forward@OptionPreferences@@QAEHXZ
Int OptionPreferences::Rva002E4326Forward(void)
{
	return Rva002E42AFDispatch(7);
}

// ?Rva002E432EForward@OptionPreferences@@QAEHXZ
Int OptionPreferences::Rva002E432EForward(void)
{
	return Rva002E42AFDispatch(8);
}
