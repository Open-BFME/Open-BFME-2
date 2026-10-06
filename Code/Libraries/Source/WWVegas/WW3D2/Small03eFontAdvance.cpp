// cl: /DNDEBUG /MD /EHsc
// Transferred from Open-BFME-1 5cae4bdff game/Libraries/Source/WWVegas/WW3D2/Small03eFontAdvance.cpp;
// bfme1_sweep places the same masked body at BFME2 0x001586E0. Addresses in the donor text are BFME1.
// The Get_Char_Data declaration is adapted to the matched target signature at
// 0x00158520 (private, class-keyed record), as in Small03fFontTwin.cpp.
//
// Retail 0x00941450 is the FontCharsClass metric-sum body: it forwards the
// character to Get_Char_Data, tests the raw return, and adds the two
// halfword metrics at +4 and +2. The layout witness is the proven sibling
// Get_Char_Metric at 0x00941400 (same record, movsx pair, add). IDENTITY IS
// NOT RECOVERED: the record keeps its address token and the method name is
// a placeholder for the unproven semantic identity.
class FontCharsClassCharDataStruct;

struct Rva00941450CharRecord
{
	unsigned short value;
	short metric;
	short extra_metric;
};

class FontCharsClass
{
private:
	const FontCharsClassCharDataStruct *Get_Char_Data(unsigned short character);

public:
	int Rva00941450Body(unsigned short ch);
};

int FontCharsClass::Rva00941450Body(unsigned short ch)
{
	const Rva00941450CharRecord *data =
		(const Rva00941450CharRecord *)Get_Char_Data(ch);
	if (data != 0)
	{
		return data->extra_metric + data->metric;
	}
	return 0;
}
