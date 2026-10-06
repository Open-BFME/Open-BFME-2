// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva00540CED@Rva00540CED@@QAEXPAVDataChunkOutput@@@Z, retail 0x00540CED 61B.
// Vector3-style keyframe writer: interpolation tag at +0 via rowed
// Rva005C706A::rva005C706A (table 0xC74934 step/line/catm default catm),
// then three floats at +4 +8 +0xC via DataChunkOutput::writeReal.
// Evidence: calls 0x5C706A then three fld/fstp writeReal sequences;
// outer array at 0x00540F4D strides 0x14 (time plus this 0x10 body);
// shares this with the tag writer (same ECX).

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

class Rva00540CED
{
public:
	void rva00540CED(DataChunkOutput *out);
	Rva005C706A m_interp;
	float m_04;
	float m_08;
	float m_0c;
};

void Rva00540CED::rva00540CED(DataChunkOutput *out)
{
	m_interp.rva005C706A(out);
	out->writeReal(m_04);
	out->writeReal(m_08);
	out->writeReal(m_0c);
}
