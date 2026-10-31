// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /DNDEBUG /DWIN32 /D_WINDOWS
// stlport
//
// WorldHeightMap::ParseHeightMapData, retail 0x000B0DA8 (473 B): the height-map chunk reader in its BFME2
// form (Zero Hour's WorldHeightMap::ParseHeightMapData without the seismic arrays and with 16-bit
// heights): width, height, border size (version >= 3), boundary list (version >= 4, else one entry
// from width/height minus twice the border), the cell count (must equal width * height) and the
// height data, which version 4 stores as bytes widened by x16 + 0.5 and later versions store as
// shorts; version 1 is halved in place. Evidence: target bytes and the Zero Hour reference body
// (BFME1 WorldHeightMap.cpp ParseHeightMapData/ParseSizeOnly); callers of the rowed resize 0x000B0857.
#include <vector>
#include "ascii_string.h"
enum ErrorCode { ERROR_CORRUPT_FILE_FORMAT = 0xDEAD0005 };
#include <new>
class Dict;
class AsciiString;
struct DataChunkInfo;
class UserParser;
class ChunkInputStream;
class DataChunkInput
{
public:
	typedef bool (*Parser)(DataChunkInput &file, DataChunkInfo *info, void *userData);
	Dict readDict();
	float readReal();
	unsigned char readByte();
	AsciiString readAsciiString();
	UserParser *registerParser(const AsciiString &label, const AsciiString &parentLabel, Parser parser, void *userData);
	bool parse(void *userData);
	DataChunkInput(ChunkInputStream *stream);
	~DataChunkInput();
	int readInt();
	void readArrayOfBytes(char *, int);
	bool atEndOfChunk();
private:
	unsigned char m_data[0x28]; // +0x00 +0x00
};
struct DataChunkInfo { AsciiString label, parent; unsigned short version; };
struct BfmePod8 { int a[2]; };
class BfmePod8Vector : public _STL::vector<BfmePod8, _STL::allocator<BfmePod8> > {
public:
	void resize(unsigned int, BfmePod8);
	void resize(unsigned int);
};
class WorldHeightMap
{
public:
	bool ParseHeightMapData(DataChunkInput &file, DataChunkInfo *info);
	bool ParseSizeOnly(DataChunkInput &file, DataChunkInfo *info);
private:
	char m_opaque00[8];
	int m_width;
	int m_height;
	int m_borderSize;
	BfmePod8Vector m_boundaries;
	int m_dataSize;
	short *m_data;
};

bool WorldHeightMap::ParseHeightMapData(DataChunkInput &file, DataChunkInfo *info)
{
	int i;
	m_width = file.readInt();
	m_height = file.readInt();
	if (info->version >= 3)
		m_borderSize = file.readInt();
	else
		m_borderSize = 0;

	if (info->version >= 4)
	{
		int numBorders = file.readInt();
		m_boundaries.resize(numBorders);
		for (i = 0; i < numBorders; ++i)
		{
			m_boundaries[i].a[0] = file.readInt();
			m_boundaries[i].a[1] = file.readInt();
		}
	}
	else
	{
		BfmePod8 filler;
		m_boundaries.resize(1, filler);
		m_boundaries[0].a[0] = m_width - 2 * m_borderSize;
		m_boundaries[0].a[1] = m_height - 2 * m_borderSize;
	}

	m_dataSize = file.readInt();
	m_data = (short *)operator new[](m_dataSize * 2);
	if (m_dataSize <= 0 || m_dataSize != m_width * m_height)
		throw ERROR_CORRUPT_FILE_FORMAT;

	if (info->version == 4)
	{
		unsigned char *bytes = (unsigned char *)operator new[](m_dataSize);
		file.readArrayOfBytes((char *)bytes, m_dataSize);
		for (i = 0; i < m_dataSize; ++i)
			m_data[i] = (short)((float)bytes[i] * 16.0f + 0.5f);
		operator delete(bytes);
	}
	else
		file.readArrayOfBytes((char *)m_data, m_dataSize * 2);

	if (info->version == 1)
	{
		int newWidth = (m_width + 1) / 2;
		int newHeight = (m_height + 1) / 2;
		for (int i = 0; i < newHeight; ++i)
			for (int j = 0; j < newWidth; ++j)
				m_data[i * newWidth + j] = m_data[2 * i * m_width + 2 * j];
	}
	return true;
}

// retail 0x000B0F82 (497 B incl. trailing int3): the same reader for a map that already holds data
// (frees the old array first, version 1 shrinks width/height after the resample).
bool WorldHeightMap::ParseSizeOnly(DataChunkInput &file, DataChunkInfo *info)
{
	int i;
	m_width = file.readInt();
	m_height = file.readInt();
	if (info->version >= 3)
		m_borderSize = file.readInt();
	else
		m_borderSize = 0;

	if (info->version >= 4)
	{
		int numBorders = file.readInt();
		m_boundaries.resize(numBorders);
		for (i = 0; i < numBorders; ++i)
		{
			m_boundaries[i].a[0] = file.readInt();
			m_boundaries[i].a[1] = file.readInt();
		}
	}
	else
	{
		BfmePod8 filler;
		m_boundaries.resize(1, filler);
		m_boundaries[0].a[0] = m_width - 2 * m_borderSize;
		m_boundaries[0].a[1] = m_height - 2 * m_borderSize;
	}

	m_dataSize = file.readInt();
	if (m_data)
		operator delete[](m_data);
	m_data = (short *)operator new[](m_dataSize * 2);
	if (m_dataSize <= 0 || m_dataSize != m_width * m_height)
		throw ERROR_CORRUPT_FILE_FORMAT;

	if (info->version == 4)
	{
		unsigned char *bytes = (unsigned char *)operator new[](m_dataSize);
		file.readArrayOfBytes((char *)bytes, m_dataSize);
		for (i = 0; i < m_dataSize; ++i)
			m_data[i] = (short)((float)bytes[i] * 16.0f + 0.5f);
		operator delete(bytes);
	}
	else
		file.readArrayOfBytes((char *)m_data, m_dataSize * 2);

	if (info->version == 1)
	{
		int newWidth = (m_width + 1) / 2;
		int newHeight = (m_height + 1) / 2;
		for (int i = 0; i < newHeight; ++i)
			for (int j = 0; j < newWidth; ++j)
				m_data[i * newWidth + j] = m_data[2 * i * m_width + 2 * j];
		m_width = newWidth;
		m_height = newHeight;
	}
	return true;
}
