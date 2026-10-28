// cl: /EHsc /DNDEBUG /MD
//
// ?rva00202B6C@Rva00202B6C@@QAEHVAsciiString@@@Z, retail
// 0x00202B6C, 70 bytes. Unlock lane: landing it readies 0x00202BB2 and
// 0x00202E23.
// Six-entry name table walked with compareNoCase returning the index, -1 on
// miss, with the by-value parameter destroyed at the end (MSVC
// callee-destroys rule), which is the trailing releaseBuffer call. Twin of
// getStaticGameLODIndex (GameLODManagerGetStaticGameLODIndex.cpp, 70 B,
// five-entry table at 0xDB969C); this table at 0xDB95F4 holds six entries
// (VeryLow..Custom per OptionPreferences::getStaticGameDetail, OptionsMenu.cpp). Retail
// facts:
// - compareNoCase: the canonical AsciiString forwards to the declared-only
//   StringBase<char> 1-arg body (retail calls 0x00037980), declared throw()
//   below. The caller (0x00202BB2) loads ecx from global 0xDFE144, so this
//   is a __thiscall method; the owner class is unproven, hence the honest
//   Rva address name.
// - The parameter destruction is the canonical ~AsciiString's single
//   releaseBuffer call (rowed 0x36410).
// - The table base (retail 0xDB95F4) is DIR32-masked, so any extern spelling
//   verifies; the entry values never enter .text.
// - /EHsc: the by-value parameter forces the EH prolog/teardown pair retail
//   shows. No unwind states: parameters carry none.

typedef int Int;
typedef bool Bool;

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

// throw(): a throwing leaf callee forces an `and [ebp-4],0` state init
// retail lacks; the leaf compare (0x00037980) cannot throw.
template <> int StringBase<char>::compareNoCase(const char *other) const throw();

class Rva00202B6C
{
public:
	Int rva00202B6C(AsciiString name);
};

// Retail table at 0xDB95F4: VeryLow, Low, Medium, High, UltraHigh, Custom.
const char *rva00202B6CNames[6] = { "VeryLow", "Low", "Medium", "High", "UltraHigh", "Custom" };

// ?rva00202B6C@Rva00202B6C@@QAEHVAsciiString@@@Z
Int Rva00202B6C::rva00202B6C(AsciiString name)
{
	for (Int i = 0; i < 6; ++i)
	{
		if (name.compareNoCase(rva00202B6CNames[i]) == 0)
			return i;
	}

	return -1;
}
