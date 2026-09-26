// cl: /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MT /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// ?rva001A3930@AggregateDefClass@@QBEHXZ, retail 0x001A3930, 40 bytes.
// Gap between Is_Object_In_List (agg_def.cpp) and dup_001a39d0 (hanim.cpp).
// Size query: base 0x5C (sizeof AggregateDefClass) plus NUL-inclusive name
// length plus subobject count at +0x18 times 64 (sizeof
// W3dAggregateSubobjectStruct). Members mirror the ZH layout with the 24-byte
// subobject-list head: version +4, list +8, count +0x18, name +0x58.
// Honest address name: class plus offsets are proven, method identity is not.

#include <string.h>

struct W3dAggregateSubobjectStruct
{
	char SubobjectName[32];
	char BoneName[32];
};

class AggregateDefClass
{
public:
	virtual ~AggregateDefClass();
	int rva001A3930() const;

private:
	int m_version; // +4
	unsigned char m_listHead[0x10]; // +8..+0x17, vector head
	int m_subobjectCount; // +0x18
	unsigned char m_pad1C[0x58 - 0x1C]; // +0x1C..+0x57
	char *m_pName; // +0x58
};

int AggregateDefClass::rva001A3930() const
{
	int size = 0x5C;
	if (m_pName) {
		size += ::strlen(m_pName) + 1;
	}
	size += m_subobjectCount * sizeof(W3dAggregateSubobjectStruct);
	return size;
}
