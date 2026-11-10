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

enum NameKeyType { NAMEKEY_INVALID = 0 };
class Dict;
#include "../../../Include/Common/DataChunkOutput.h"
#include "../../../Include/GameLogic/SidesInfo.h"
struct LibraryMapStringVector {
    AsciiString *first;
    AsciiString *last;
    AsciiString *capacity;
};
#include "../../../Include/Common/SidesList.h"

void SidesList::rva00329FF4WriteLibraryMaps(DataChunkOutput &output) {
    output.openDataChunk("LibraryMapLists", 1);
    int count = m_numSides;
    for (int index = 0; index < count; ++index) {
        output.openDataChunk("LibraryMaps", 1);
        LibraryMapStringVector *maps = reinterpret_cast<LibraryMapStringVector *>(getSideInfo(index)->m_tail);
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
    int count = m_numSides;
    for (int index = 0; index < count; ++index)
        scripts[index] = getSideInfo(index)->getScriptList();
    ScriptList::WriteScriptsDataChunk(output, scripts, count);
}
