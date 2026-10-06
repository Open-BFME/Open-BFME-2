// cl: /DNDEBUG /MD /EHsc
//
// Opaque FontCharsClass blit twin, retail 0x001588A0 (222 bytes).
// Dedicated TU (the true Blit_Char lives at 0x001587C0 in
// FontCharsClassBlitChar.cpp; same class, separate TU per the
// callee-visibility split precedent).
//
// Same nibble-expansion idiom as Blit_Char (and 0xfffff000 / shl 4 /
// and 0x0f00 / or / shl 4 / and 0x00f0 / or / shl 4 / and 0x000f / or /
// shl 4, byte-exact) with two measured deviations: x is biased by the
// record +4 word (ExtraSpacing) and clamped at zero (movsx + add + jns
// + xor), and the pixel write is an unconditional OR into the dword
// dest (no PixelOverlap conditional/store). Callee is Get_Char_Data
// @0x00158520 (REL32-decoded); CharHeight at this+0x2C.
// Identity: sole direct caller 0x00159424 sits inside unidentified
// 0x00158E90 (a 2129B Build_Sentence-shaped twin of the 2199B
// Build_Sentence_Not_Centered that calls the true Blit_Char). The class
// (FontCharsClass-private Get_Char_Data access) and signature
// (WCHAR/uint16*/int/int/int, ret 0x14) are proven; the method role is
// open, hence the address-token name. Was briefly misnamed Blit_Char
// (retracted with tombstone); one body per address.

class FontCharsClassCharDataStruct
{
	public:
	unsigned short Value;
	short Width;
	short ExtraSpacing;
	char m_pad06[2];
	unsigned short *Buffer;
};

class FontCharsClass
{
	const FontCharsClassCharDataStruct *Get_Char_Data(unsigned short ch);
public:
	void rva001588A0(unsigned short ch, unsigned short *dest_ptr, int dest_stride, int x, int y);
private:
	char m_pad00[0x2C];
	int CharHeight;
};

// ?rva001588A0@FontCharsClass@@QAEXGPAGHHH@Z
void FontCharsClass::rva001588A0(unsigned short ch, unsigned short *dest_ptr, int dest_stride, int x, int y)
{
	unsigned int *dest = reinterpret_cast<unsigned int *>(dest_ptr);
	FontCharsClassCharDataStruct const *data = Get_Char_Data(ch);
	if (data != 0 && data->Width != 0) {
		x += data->ExtraSpacing;
		if (x < 0) {
			x = 0;
		}
		int dest_inc = dest_stride >> 2;
		unsigned short *src_ptr = data->Buffer;
		dest += (dest_inc * y) + x;

		for (int row = 0; row < CharHeight; row++) {
			for (int col = 0; col < data->Width; col++) {
				unsigned short pixel = *src_ptr;
				unsigned int curData = pixel;
				curData = (curData & 0xfffff000) << 4;
				curData |= pixel & 0x0f00;
				curData <<= 4;
				curData |= pixel & 0x00f0;
				curData <<= 4;
				curData |= pixel & 0x000f;
				curData <<= 4;
				dest[col] |= curData;
				src_ptr++;
			}
			dest += dest_inc;
		}
	}
}
