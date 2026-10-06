// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// DataChunkOutput::writeAsciiString, retail 0x00307033, 91 bytes.
//
// Ported from the Zero Hour reference
// (GameEngine/Source/Common/System/DataChunk.cpp, writeAsciiString).
// Retail inlines AsciiString::getLength/str the way the BFME string header
// does: the shared buffer keeps a 16-bit length at offset 4 and the
// characters at offset 8, with a null buffer reading as empty.

typedef unsigned short UnsignedShort;

extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(
	const void *chunkBuffer, unsigned int elementSize, unsigned int elementCount, void *outputFile);

struct AsciiStringHeader
{
	int headerRefCount;
	UnsignedShort headerLength; ///< retail +0x04
	UnsignedShort headerCapacity;
	char headerData[1]; ///< retail +0x08
};

class AsciiString
{
public:
	int getLength() const
	{
		return asciiData ? asciiData->headerLength : 0;
	}

	const char *getStringData() const
	{
		return asciiData ? &asciiData->headerData[0] : "";
	}

private:
	AsciiStringHeader *asciiData;
};

class DataChunkOutput
{
public:
	void writeAsciiString(const AsciiString &textValue);

private:
	void *outputStream; ///< retail this+0x00
	void *tempFile; ///< retail this+0x04
};

// ?writeAsciiString@DataChunkOutput@@QAEXABVAsciiString@@@Z
void DataChunkOutput::writeAsciiString(const AsciiString &textValue)
{
	UnsignedShort textLength = textValue.getLength();
	::fwrite((const char *)&textLength, sizeof(UnsignedShort), 1, tempFile);
	::fwrite(textValue.getStringData(), textLength, 1, tempFile);
}
