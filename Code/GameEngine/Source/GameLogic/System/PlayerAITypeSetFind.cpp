// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfme2_ascii
// stlport
// Native 215479..2154BE RET4; WB B6BBD0 and SidesList32FC70 bind the
// receiver to ThePlayerAITypeSet. Records have name+0 and maps+4, stride16.
// Target original lookup method name unknown; address spelling retained.
#include <vector>
#include "ascii_string.h"
struct PlayerAITypeRecord {
    AsciiString m_name;
    _STL::vector<AsciiString> m_libraryMaps;
};
class PlayerAITypeSet {
public:
    int rva00215479(const AsciiString &name);
private:
    char m_prefix[0xC];
    _STL::vector<PlayerAITypeRecord> m_types;
};
int PlayerAITypeSet::rva00215479(const AsciiString &name)
{
    for (unsigned int i=0; i<m_types.size(); ++i)
        if (m_types[i].m_name.compare(name)==0) return i;
    return -1;
}
