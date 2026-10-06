// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva00540CB2@Rva00540CB2@@QAE_NPAVDataChunkInput@@PAUDataChunkInfo@@@Z, retail 0x00540CB2 59B.
// Three-float keyframe reader, inverse of Rva00540CED writer: interpolation tag
// at +0 via rowed Rva005C702D reader, then three floats at +4 +8 +0xC via
// DataChunkInput::readReal. Returns false when the tag reader fails.
// Evidence: calls 0x5C702D then three readReal/fstp sequences; neighbours
// 0x00540C59 and 0x00540CED are the five- and three-float writers; caller at
// 0x54235C shares this.

class DataChunkInput
{
public:
	float readReal();
};

struct DataChunkInfo
{
	void *m_label;
	void *m_parentLabel;
	unsigned short version;
	unsigned short m_pad;
	int dataSize;
};

class Rva005C702D
{
public:
	bool rva005C702D(DataChunkInput *file, DataChunkInfo *info);
	int m_key;
};

class Rva00540CB2
{
public:
	bool rva00540CB2(DataChunkInput *file, DataChunkInfo *info);
	Rva005C702D m_interp;
	float m_04;
	float m_08;
	float m_0c;
};

bool Rva00540CB2::rva00540CB2(DataChunkInput *file, DataChunkInfo *info)
{
	if (!m_interp.rva005C702D(file, info))
		return false;
	m_04 = file->readReal();
	m_08 = file->readReal();
	m_0c = file->readReal();
	return true;
}
