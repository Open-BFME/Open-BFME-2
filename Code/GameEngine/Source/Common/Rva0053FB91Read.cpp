// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva0053FB91@Rva0053FB91@@QAE_NPAVDataChunkInput@@PAUDataChunkInfo@@@Z, retail 0x0053FB91 109B.
// Eight-float keyframe reader: interpolation tag at +0 via rowed Rva005C702D
// reader, then eight floats at +4 +8 +0xC +0x10 +0x14 +0x18 +0x1C +0x20 via
// DataChunkInput::readReal. Returns false when the tag reader fails.
// Evidence: calls 0x5C702D then eight readReal/fstp sequences; sibling
// five- and three-float readers at 0x540C0A and 0x540CB2; caller at 0x540B90
// shares this.

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

class Rva0053FB91
{
public:
	bool rva0053FB91(DataChunkInput *file, DataChunkInfo *info);
	Rva005C702D m_interp;
	float m_04;
	float m_08;
	float m_0c;
	float m_10;
	float m_14;
	float m_18;
	float m_1c;
	float m_20;
};

bool Rva0053FB91::rva0053FB91(DataChunkInput *file, DataChunkInfo *info)
{
	if (!m_interp.rva005C702D(file, info))
		return false;
	m_04 = file->readReal();
	m_08 = file->readReal();
	m_0c = file->readReal();
	m_10 = file->readReal();
	m_14 = file->readReal();
	m_18 = file->readReal();
	m_1c = file->readReal();
	m_20 = file->readReal();
	return true;
}
