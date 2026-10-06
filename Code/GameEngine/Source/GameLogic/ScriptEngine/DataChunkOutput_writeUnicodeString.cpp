// cl: /Ireference/shims/bfme2_ascii
//
// DataChunkOutput::writeUnicodeString, retail 0x0030708E, 99 bytes.
//
// Ported from the Zero Hour reference
// (GameEngine/Source/Common/System/DataChunk.cpp, writeUnicodeString)
// and the BFME1 donor DataChunk.cpp.
// Retail writes a U16 length then len*2 wide bytes, destroying the by-value
// UnicodeString temp via the pinned wide releaseBuffer at 0x00036E70.
// Evidence: caller at 0x00307E46 in writeDict passes the Dict Unicode temp;
// empty wide path corresponds to retail VA 0x00BBB5C4.

typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;

extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(
	const void *chunkBuffer, unsigned int elementSize, unsigned int elementCount, void *outputFile) throw();

#include "unicode_string.h"

class DataChunkOutput
{
public:
	void writeUnicodeString(UnicodeString textValue);

private:
	void *outputStream; ///< retail this+0x00
	void *tempFile; ///< retail this+0x04
};

void DataChunkOutput::writeUnicodeString(UnicodeString textValue)
{
	UnsignedShort textLength = (UnsignedShort)textValue.getLength();
	::fwrite((const char *)&textLength, sizeof(UnsignedShort), 1, tempFile);
	::fwrite(textValue.str(), textLength * sizeof(WideChar), 1, tempFile);
}
