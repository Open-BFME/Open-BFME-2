// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc
// ?Rva00515633Delete@@YAXXZ @ 0x00515633 108B
// Delete save file built from wide literal via GameState helper then DeleteFileW.
// Evidence: StringBase<G> ctor row 0x00037E30 plus releaseBuffer row 0x00036E70 plus rva002DC74A row 0x002DC74A plus TheGameState plus TheNullChr plus DeleteFileW IAT plus caller 0x005158BD plus prev OpaqueSingleInheritanceDtors /O1.
typedef unsigned short WideChar;

#include "unicode_string.h"


class Rva002DC74A
{
public:
	UnicodeString rva002DC74A(const UnicodeString &src) const;
};

class GameState;
extern GameState *TheGameState;
extern "C" __declspec(dllimport) int __stdcall DeleteFileW(const WideChar *lpFileName);

void __cdecl Rva00515633Delete(void)
{
	UnicodeString path = ((const Rva002DC74A *)TheGameState)->rva002DC74A(UnicodeString((const WideChar *)L"00000000.sav"));
	DeleteFileW(path.str());
}
