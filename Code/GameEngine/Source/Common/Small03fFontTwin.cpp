// cl: /DNDEBUG /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// Retail 0x009414A0 is the metric-sum twin of the FontCharsClass body at
// 0x00941450: it forwards the character to Get_Char_Data, tests the raw
// return, and adds the two halfword metrics at +4 and +2. The ternary
// spelling is what emits retail's `test eax,eax` + `movsx ecx,[eax+4]` /
// `movsx edx,[eax+2]` + `add ecx,edx` + `mov eax,ecx` form (the if/else
// spelling in Small03eFontAdvance.cpp emits the ecx-first mirror).
// IDENTITY IS NOT RECOVERED: the record keeps its address token and the
// method name is a placeholder for the unproven semantic identity.
class FontCharsClassCharDataStruct;

struct Rva009414A0CharRecord
{
	unsigned short value;
	short metric;
	short extra_metric;
};

#include "../../../Libraries/Source/WWVegas/WW3D2/FontCharsClass.h"

int FontCharsClass::Rva009414A0Body(unsigned short ch)
{
	const Rva009414A0CharRecord *data =
		(const Rva009414A0CharRecord *)Get_Char_Data(ch);
	return data ? data->extra_metric + data->metric : 0;
}
