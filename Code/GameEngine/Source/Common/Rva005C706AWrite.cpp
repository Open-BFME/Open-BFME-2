// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva005C706A@Rva005C706A@@QAEXPAVDataChunkOutput@@@Z, retail 0x005C706A 46B.
// Interpolation-tag writer: maps the int at +0 (0 STEP, 1 LINE, 2 CATM) to the
// 4-char chunk code via the .rdata table at 0xC74934 (00 step, 01 line,
// 02 catm), defaulting to catm (0x6361746d), then DataChunkOutput::writeInt.
// Evidence: table bytes at 0x874934 map 0->0x73746570 1->0x6c696e65 2->0x6361746d
// with default 0x6361746d; callers at 0x53FC07 0x540C62 0x540CF6 pass the same
// this plus DataChunkOutput and write the remaining floats after; callee
// writeInt/writeReal share 0x00306CFF (ICF-folded).

class DataChunkOutput
{
public:
	void writeInt(int value);
	void writeReal(float value);
};

struct KeyCode
{
	int key;
	int code;
};

static const KeyCode c_table[3] = {
	{ 0, 0x73746570 },
	{ 1, 0x6c696e65 },
	{ 2, 0x6361746d },
};

class Rva005C706A
{
public:
	void rva005C706A(DataChunkOutput *out);
	int m_key;
};

void Rva005C706A::rva005C706A(DataChunkOutput *out)
{
	int key = m_key;
	int code = 0x6361746d;
	for (unsigned int i = 0; i < 3; ++i)
	{
		if (c_table[i].key == key)
		{
			code = c_table[i].code;
			break;
		}
	}
	out->writeInt(code);
}
