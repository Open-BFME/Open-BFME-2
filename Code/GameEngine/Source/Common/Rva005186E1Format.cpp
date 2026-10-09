// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?Rva005186E1Format@@YAXPAVOptionPreferences@@PAVAsciiString@@@Z @0x005186E1 117B
// Builds 9-int "%d" list into output AsciiString via OptionPreferences dispatch plus separator concat.
// Evidence: caller 0x0051889D pushes OptionPreferences* plus this+0x314 AsciiString* with __cdecl cleanup; rowed dispatch format concat releaseBuffer; separator 0x007BFB20 plus "%d" 0x007BE164.
#include "ascii_string.h"


class OptionPreferences
{
public:
	int Rva002E42AFDispatch(int idx);
	void setSetting(int setting, int value);
};

extern "C" __declspec(dllimport) int __cdecl atoi(const char *text);


void Rva005186E1Format(class OptionPreferences *prefs, class AsciiString *out)
{
	((StringBase<char> *)out)->clear();
	AsciiString tmp;
	for (int i = 0; i < 9; ++i)
	{
		int v = prefs->Rva002E42AFDispatch(i);
		tmp.format((char *)"%d", v);
		if (i != 0)
			((StringBase<char> *)out)->concat((char *)",");
		((StringBase<char> *)out)->concat(*(const StringBase<char> *)&tmp);
	}
}

// Retail 0x00518658, 137 bytes: the inverse, parsing up to nine
// ","-separated numbers into the options' settings 0-8 (OptionPreferences::
// setSetting 0x002E553D). Its one caller, 0x00519D91, passes the options
// screen's +0x314 preset text and a local OptionPreferences.
void Rva00518658Parse(const AsciiString &text, class OptionPreferences *prefs)
{
	AsciiString rest(text);
	AsciiString token;
	for (int i = 0; i < 9; ++i)
	{
		if (!rest.nextToken(&token, ","))
			break;
		prefs->setSetting(i, atoi(token.str()));
	}
}
