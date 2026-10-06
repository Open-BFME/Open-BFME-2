// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva00540C59@Rva00540C59@@QAEXPAVDataChunkOutput@@@Z, retail 0x00540C59 89B.
// Five-float keyframe writer: interpolation tag at +0 via rowed
// Rva005C706A::rva005C706A, then floats at +4 +8 +0xC +0x10 +0x14 via
// DataChunkOutput::writeReal. Sibling of Rva00540CED (three floats).
// Evidence: five fld/fstp writeReal sequences; outer array at 0x00540F0B
// strides 0x1C; shares this with the tag writer.

class DataChunkOutput
{
public:
	void writeInt(int value);
	void writeReal(float value);
};

class Rva005C706A
{
public:
	void rva005C706A(DataChunkOutput *out);
	int m_key;
};

class Rva00540C59
{
public:
	void rva00540C59(DataChunkOutput *out);
	Rva005C706A m_interp;
	float m_04;
	float m_08;
	float m_0c;
	float m_10;
	float m_14;
};

void Rva00540C59::rva00540C59(DataChunkOutput *out)
{
	m_interp.rva005C706A(out);
	out->writeReal(m_04);
	out->writeReal(m_08);
	out->writeReal(m_0c);
	out->writeReal(m_10);
	out->writeReal(m_14);
}
