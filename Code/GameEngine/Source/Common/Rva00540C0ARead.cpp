// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva00540C0A@Rva00540C0A@@QAE_NPAVDataChunkInput@@PAUDataChunkInfo@@@Z, retail 0x00540C0A 79B.
// Five-float keyframe reader, inverse of Rva00540C59 writer: interpolation tag
// at +0 via rowed Rva005C702D reader, then five floats at +4 +8 +0xC +0x10
// +0x14 via DataChunkInput::readReal. Returns false when the tag reader fails.
// Evidence: calls 0x5C702D then five readReal/fstp sequences; next row
// 0x00540C59 writes the same layout; caller at 0x5422B2 shares this.

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

class Rva00540C0A
{
public:
	bool rva00540C0A(DataChunkInput *file, DataChunkInfo *info);
	Rva005C702D m_interp;
	float m_04;
	float m_08;
	float m_0c;
	float m_10;
	float m_14;
};

bool Rva00540C0A::rva00540C0A(DataChunkInput *file, DataChunkInfo *info)
{
	if (!m_interp.rva005C702D(file, info))
		return false;
	m_04 = file->readReal();
	m_08 = file->readReal();
	m_0c = file->readReal();
	m_10 = file->readReal();
	m_14 = file->readReal();
	return true;
}
