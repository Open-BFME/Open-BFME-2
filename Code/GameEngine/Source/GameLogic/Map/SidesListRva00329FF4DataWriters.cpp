// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// Reference leads: Open-BFME-1 ba7ddda7, LibraryMapLists_writeDataChunk.cpp,
// and ZH SidesList::WriteSidesDataChunk's script-list collection. BFME2's
// complete RET4 bodies are 329FF4..32A082 (142B) and 32996E..3299AD (63B).
// Target getSideInfo 2035BA proves the receiver and side-array relationship;
// the count is +3C, the embedded ScriptList begins at side+8, and library-map
// strings occupy the three-pointer vector at side+54. The existing matched
// SidesList_sidesInfo.cpp constructors independently establish those fields.
// These are borrowed prefixes, not complete allocation layouts. Method
// spellings below describe the recovered operations, not original names.
#include "ascii_string.h"

class DataChunkOutput {
public:
    void openDataChunk(char *name, unsigned short version);
    void closeDataChunk();
    void writeInt(int value);
    void writeAsciiString(const AsciiString &value);
};
class ScriptList {
public:
    static void WriteScriptsDataChunk(DataChunkOutput &, ScriptList *[], int);
};
struct LibraryMapStringVector {
    AsciiString *first;
    AsciiString *last;
    AsciiString *capacity;
};
class SidesInfo {
public:
    unsigned char prefix[0x54];
    LibraryMapStringVector libraryMaps;
};
class SidesList {
public:
    SidesInfo *getSideInfo(int index);
    void rva00329FF4WriteLibraryMaps(DataChunkOutput &output);
    void rva0032996EWriteScripts(DataChunkOutput &output);
private:
    unsigned char prefix[0x3C];
    int numSides;
};

void SidesList::rva00329FF4WriteLibraryMaps(DataChunkOutput &output) {
    output.openDataChunk("LibraryMapLists", 1);
    int count = numSides;
    for (int index = 0; index < count; ++index) {
        output.openDataChunk("LibraryMaps", 1);
        LibraryMapStringVector *maps = &getSideInfo(index)->libraryMaps;
        output.writeInt(maps->last - maps->first);
        AsciiString *last = maps->last;
        for (AsciiString *value = maps->first; value != last; ++value)
            output.writeAsciiString(*value);
        output.closeDataChunk();
    }
    output.closeDataChunk();
}

void SidesList::rva0032996EWriteScripts(DataChunkOutput &output) {
    ScriptList *scripts[20];
    int count = numSides;
    for (int index = 0; index < count; ++index)
        scripts[index] = (ScriptList *)((unsigned char *)getSideInfo(index) + 8);
    ScriptList::WriteScriptsDataChunk(output, scripts, count);
}
