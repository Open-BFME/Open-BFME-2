// Target facts (code addresses are RVAs): DataChunkInfo has no bases or virtual functions. DataChunkInput::parse 0x00307AC0 constructs it at EBP-0x2C: 0x00307ADD/0x00307AE0 clear its two string words without installing a vftable. Destructor 0x003073DA installs no table either; there are no constructor/destructor tables to reconcile.
// parse assigns label +0 at 0x00307BB1/0x00307BB4 and parentLabel +4 at 0x00307BBD/0x00307BC0 through StringBase<char>::set (0x000366F0), version (unsigned word) +8 at 0x00307BCB, and dataSize (dword) +0xC at 0x00307BD4. The record occupies 0x10 bytes below the next local at EBP-0x1C; ParseSizeOnly 0x00302EA5 independently compares its unsigned word +8.
// parse calls the non-virtual destructor at 0x00307C13; 0x003073F2/0x003073FD destroy strings +4/+0 through releaseBuffer 0x00036410. Declare that rowed destructor out of line. Zero Hour GeneralsMD Common/DataChunk.h supplies the struct key, field names and signed Int dataSize, corroborated by these accesses; no donor header is included.
#ifndef BFME2_COMMON_DATACHUNKINFO_H
#define BFME2_COMMON_DATACHUNKINFO_H

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

struct DataChunkInfo
{
    ~DataChunkInfo();

    AsciiString label;
    AsciiString parentLabel;
    unsigned short version;
    int dataSize;
};

#endif
