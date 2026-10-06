// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva005C702D@Rva005C702D@@QAE_NPAVDataChunkInput@@PAUDataChunkInfo@@@Z, retail 0x005C702D 61B.
// Interpolation-tag reader, inverse of Rva005C706A writer: default m_key to 2
// (CATM), skip when info version < 2, else readInt code and map code->key via
// the .rdata table at 0xC74934 (step/line/catm), always returning true.
// Evidence: same table as Rva005C706AWrite.cpp; callers at 0x53FB9E 0x540C17
// 0x540CBF share this plus DataChunkInput and read floats after; callee
// readInt is rowed 0x00306E78.

class DataChunkInput
{
public:
	int readInt();
};

struct DataChunkInfo
{
	void *m_label;
	void *m_parentLabel;
	unsigned short version;
	unsigned short m_pad;
	int dataSize;
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

class Rva005C702D
{
public:
	bool rva005C702D(DataChunkInput *file, DataChunkInfo *info);
	int m_key;
};

bool Rva005C702D::rva005C702D(DataChunkInput *file, DataChunkInfo *info)
{
	m_key = 2;
	if (info->version < 2)
		return true;
	int code = file->readInt();
	for (unsigned int i = 0; i < 3; ++i)
	{
		if (c_table[i].code == code)
		{
			m_key = c_table[i].key;
			break;
		}
	}
	return true;
}
