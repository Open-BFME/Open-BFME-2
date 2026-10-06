// cl: /DNDEBUG /MD /EHsc
//
// FontCharsClass::Get_Char_Metric, retail 0x00158690 (73 bytes). Same
// adaptation as the sibling Get_Char_Spacing unit: the donor calls the
// placeholder Get_Char_Data, but the retail REL32 decodes to 0x00158580,
// the Thai-first glyph-ensure helper landed as loadCharacterData, so the
// true spelling is declared here and no new pin is needed. Record layout
// (Value@+0, Width@+2, ExtraSpacing@+4) matches the sibling unit.

struct FontCharsClassCharDataStruct
{
	unsigned short Value;
	short Width;
	short ExtraSpacing;
};

class FontCharsClass
{
public:
	int Get_Char_Metric(unsigned short ch);
	FontCharsClassCharDataStruct const *loadCharacterData(unsigned short ch);
};

// ?Get_Char_Metric@FontCharsClass@@QAEHG@Z
int FontCharsClass::Get_Char_Metric(unsigned short ch)
{
	FontCharsClassCharDataStruct const *data = loadCharacterData(ch);
	if (data != 0)
	{
		if ((ch >= 0x0e01 && ch <= 0x0e3a) ||
			(ch >= 0x0e3f && ch <= 0x0e5b))
			return data->ExtraSpacing + data->Width;
		return data->Width;
	}
	return 0;
}
