// cl: /O2 /G6 /DNDEBUG /MD
//
// FontCharsClass::Get_Char_Data, retail 0x00158520, 81 bytes.
// Dedicated TU. Retail is a map lookup at this+0x450, not the ZH
// ASCIICharArray / UnicodeCharArray walk in render2dsentence.cpp.

class FontCharsClassCharDataStruct;

struct FontCharNode
{
	char m_unreconstructed_00[0x14];
	FontCharsClassCharDataStruct const *m_data;
};

class FontCharMap
{
public:
	FontCharNode *header;
	FontCharNode *find(unsigned short const &);
};

class FontCharsClass
{
	void *m_unreconstructed_00;
	void *m_unreconstructed_04;
	FontCharsClass *AlternateUnicodeFont;
	char m_unreconstructed_0C[0x450 - 0x0C];
	FontCharMap m_chars;

	FontCharsClassCharDataStruct const *Store_GDI_Char(unsigned short ch);
	FontCharsClassCharDataStruct const *Get_Char_Data(unsigned short ch);
};

FontCharsClassCharDataStruct const *FontCharsClass::Get_Char_Data(unsigned short ch)
{
	unsigned short key = ch;
	FontCharsClass *cur = this;
	for (;;)
	{
		FontCharNode *node = cur->m_chars.find(ch);
		FontCharsClassCharDataStruct const *p = 0;
		if (node != cur->m_chars.header)
			p = node->m_data;
		if (p == 0)
			p = cur->Store_GDI_Char(key);
		if (p != (FontCharsClassCharDataStruct const *)-1)
			return p;
		FontCharsClass *alt = cur->AlternateUnicodeFont;
		if (alt == 0 || cur == alt)
			return 0;
		cur = alt;
	}
}
