// A bitfield read and a default-string getter.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/S3SmallAccessorFamilies.cpp); trimmed to the
// two T1 bodies the sweep places.

struct Gen_007f8dc0Bits
{
	char m_bfmeHead[0x20];
	unsigned int m_bfmeFlags;					// +0x20
};

// ?Gen_007f8ee0@@YGHPAUGen_007f8dc0Bits@@@Z
int __stdcall Gen_007f8ee0(Gen_007f8dc0Bits *bits)
{
	return (bits->m_bfmeFlags >> 29) & 1;
}

class Gen_007ea670
{
public:
	char *bfmePlatform(void);

	char m_bfmeHead[0xE1];
	char m_bfmeBuffer[1];						// +0xE1
};

// ?bfmePlatform@Gen_007ea670@@QAEPADXZ
char *Gen_007ea670::bfmePlatform(void)
{
	char *text = m_bfmeBuffer;

	if (*text == 0)
		text = "PC";

	return text;
}

// Additional raw ABI read from the whole BFME1 unit
// game/GameEngine/Source/Common/S3SmallAccessorFamilies.cpp at revision
// 5cc75ddda6455c338a5068307e587a793f96d6b3, blob
// 2d6cda34b5ca9f338c92879a2e58f06342b5c2ca. No header dependencies.
// Discovery used /O1 /Ob1; this home's unchanged settings are also exact.
// Target: independent INT3-delimited entry 0x00665440/15, RET4 and the
// native function-pointer sequence at RVA0x008E316C establish the entry.
// The word width, +0x20 read and low24 mask are target facts; the argument
// view reuses the existing raw-width sibling. Original name and owner remain
// unknown; this declaration does not establish an original object extent.
// ?rva00665440@@YGIPBUGen_007f8dc0Bits@@@Z
unsigned int __stdcall rva00665440(const Gen_007f8dc0Bits *view)
{
	return view->m_bfmeFlags & 0xFFFFFF;
}
