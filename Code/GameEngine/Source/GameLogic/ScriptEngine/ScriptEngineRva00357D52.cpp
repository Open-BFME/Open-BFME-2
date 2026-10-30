// cl: /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva00357D52@ScriptEngine@@QAEXABVAsciiString@@@Z, retail 0x00357D52, 52 bytes.
// Removes the BfmeStringRecord00204A30 entry whose word0 equals the CRC of the name.
// Target evidence: vector at +0x1A49C/+0x1A4A0 stride 0x14 with first-dword compare (same as 0x0035789D trigger lookup);
// callee CRC at 0x003ECA13 (rowed realcrc_one_arg) and single erase at 0x00357CA2 (rowed BfmeStringRecord erase 55B);
// tail-called after 0x0035789D by 0x003BCA43.

#include "ascii_string.h"

unsigned long Rva003ECA13Get(const AsciiString &s);

struct BfmeStringRecord00204A30
{
    unsigned int word0;
    AsciiString text0;
    unsigned int word1;
    AsciiString text1;
    unsigned int word2;
};

#include <vector>

namespace _STL
{
// Bind the element erase to the rowed record-vector worker.
template <> BfmeStringRecord00204A30 *vector<BfmeStringRecord00204A30, allocator<BfmeStringRecord00204A30> >::erase(BfmeStringRecord00204A30 *pos);
}

class ScriptEngine
{
public:
    void rva00357D52(const AsciiString &name);
private:
    char m_pad[0x1A49C];
    _STL::vector<BfmeStringRecord00204A30> m_vec1A49C;
};

void ScriptEngine::rva00357D52(const AsciiString &name)
{
    unsigned long crc = Rva003ECA13Get(name);
    _STL::vector<BfmeStringRecord00204A30> &vec = m_vec1A49C;
    for (BfmeStringRecord00204A30 *it = vec.begin(); it != m_vec1A49C.end(); ++it) {
        if (it->word0 == crc) {
            vec.erase(it);
            break;
        }
    }
}
