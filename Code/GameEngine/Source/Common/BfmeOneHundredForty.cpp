// One more: a four-byte reader that takes the bytes most significant first.

class BfmeCursorXF
{
public:
	const unsigned char *m_bfmeData;			// +0x00
	unsigned int m_bfmeValue;					// +0x04
	int m_bfmeBits;								// +0x08
	int m_bfmeCount;							// +0x0c
};

void bfmeReadWordXF(BfmeCursorXF *out, const unsigned char *data)
{
	out->m_bfmeData = data;

	unsigned int value = data[0];
	value = (value << 8) + data[1];
	value = (value << 8) + data[2];
	value = (value << 8) + data[3];
	out->m_bfmeValue = value;

	out->m_bfmeBits = 0x20;
	out->m_bfmeCount = 4;
}

// BF1 9cbfb551fe Common/Rva009ACB80ByteSetter.cpp is the clean semantic donor.
// Target 1BD570..1BD57F RET0 bounded by INT3; cdecl pointer andbyte writes1AC
// Original owner/purpose is unproven; retain an independent address-owned type.
struct Rva001BD570Fields { unsigned char unknown[0x1AC]; unsigned char value1AC; };
void __cdecl setByte_Rva001BD570(Rva001BD570Fields *fields,unsigned char value) { fields->value1AC=value; }

// BF1 9cbfb551fe Common/Rva009ACB90ByteGetter.cpp is the clean semantic donor.
// Target 1BD580..1BD58B RET0 bounded by INT3; cdecl pointer returnsAL from1AC
// Original owner/purpose is unproven; retain an independent address-owned type.
struct Rva001BD580Fields { unsigned char unknown[0x1AC]; unsigned char value1AC; };
unsigned char __cdecl getByte_Rva001BD580(const Rva001BD580Fields *fields) { return fields->value1AC; }
