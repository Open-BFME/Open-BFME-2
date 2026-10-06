// cl: /DNDEBUG /MD /EHsc
//
// FontCharsClass::Blit_Char, retail 0x001587C0 (215 bytes).
// Dedicated TU (render2dsentence.cpp keeps the ZH simple-copy Blit as an
// orphan per the boxrobj precedent; that file has 30 present-unmatched
// markers and must not be disturbed).
//
// Source is the BFME1 FontCharsClass_Blit_Char_BFME.cpp nibble-expansion
// blit VERBATIM (retail carries the same expansion idiom: and 0xfffff000 /
// shl 4 / and 0x0f00 / or / shl 4 / and 0x00f0 / or / shl 4 / and 0x000f /
// or / shl 4, plus the PixelOverlap-conditional OR with plain store).
// BFME2 adaptations, all retail-measured:
// - Callee is the Thai-first loadCharacterData helper @0x00158580 (the
//   standard retail font idiom per the spacing TU), NOT Get_Char_Data.
// - CharHeight lives at this+0x2C, PixelOverlap at this+0x38
//   (spacing-proven offsets).
// Identity proof: sole direct caller 0x00159CC4 sits inside the
// reloc-named Build_Sentence_Not_Centered @0x00159700 (the documented
// Blit_Char consumer family); the record layout (Value@+0, Width@+2,
// ExtraSpacing@+4) matches the spacing record.
// (A 222B nibble twin at 0x001588A0 with an x-bias clamp and an
// unconditional OR was briefly misnamed Blit_Char and retracted in this
// same commit; its caller 0x00159424 sits in unidentified 0x00158E90.)

struct FontCharsClassCharDataStruct
{
	unsigned short Value;
	short Width;
	short ExtraSpacing;
	char m_pad06[2];
	unsigned short *Buffer;
};

class FontCharsClass
{
public:
	const FontCharsClassCharDataStruct *loadCharacterData(unsigned short ch);
	void Blit_Char(unsigned short ch, unsigned short *dest_ptr, int dest_stride, int x, int y);
private:
	char m_pad00[0x2C];
	int CharHeight;
	char m_pad30[4];
	int CharOverhang;
	int PixelOverlap;
};

// ?Blit_Char@FontCharsClass@@QAEXGPAGHHH@Z
void FontCharsClass::Blit_Char(unsigned short ch, unsigned short *dest_ptr, int dest_stride, int x, int y)
{
	unsigned int *dest = reinterpret_cast<unsigned int *>(dest_ptr);
	FontCharsClassCharDataStruct const *data = loadCharacterData(ch);
	if (data != 0 && data->Width != 0) {
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
				if (col < PixelOverlap) {
					curData |= dest[col];
				}
				dest[col] = curData;
				src_ptr++;
			}
			dest += dest_inc;
		}
	}
}
