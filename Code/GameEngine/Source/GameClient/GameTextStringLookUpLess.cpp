// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// StringLookUp ordering predicate used by the BFME GameTextManager sort.

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *left, const char *right);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
#include "ascii_string.h"

struct StringLookUp
{
	AsciiString *label;
	void *info;
};

bool __stdcall compareStringLookUpLess(const void *left, const void *right)
{
	const StringLookUp *lut1 = (const StringLookUp *)left;
	const StringLookUp *lut2 = (const StringLookUp *)right;
	return _strcmpi(lut1->label->str(), lut2->label->str()) < 0;
}

bool __stdcall Rva002E56B3Less(const StringLookUp *left, const char *right)
{
	return _strcmpi(left->label->str(), right) < 0;
}

bool __stdcall Rva002E56E2Greater(const char *left, const StringLookUp *right)
{
	return _strcmpi(left, right->label->str()) < 0;
}

// TheGameText, VA 0x00DFF0BC (.data, zero-filled tail): the GameTextInterface
// singleton, read by 35 matched units (52 DIR32 sites). Zero Hour defines it in
// GameText.cpp, which BFME2 has not recovered; it is defined here, in the
// GameTextManager's split-out unit. A recovered GameText.cpp must not define it
// a second time.
class GameTextInterface;
GameTextInterface *TheGameText = 0;
