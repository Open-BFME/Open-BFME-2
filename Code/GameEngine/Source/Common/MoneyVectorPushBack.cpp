// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /D_STLP_USE_STATIC_LIB
// stlport46
// Native 006BF950/59B appends the existing nonpolymorphic 36-byte record.
// Its former Money identity was refuted by the complete copy and overflow
// providers. Application type and original method name remain unknown.
#include <new>
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

#include "../../Include/Common/BfmeFalseBE.h"

struct BfmeStringRecord00063BE4
{
    unsigned int words[7];
    AsciiString text;
    unsigned char tail0, tail1;

    // The native copy shares a string under the static lock and throws no C++
    // exception; the complete call-chain evidence is in the identity packet.
    BfmeStringRecord00063BE4(const BfmeStringRecord00063BE4 &) throw();
};

struct BfmeElemBE { char data[36]; };
typedef char RecordCopySizeIs36[sizeof(BfmeStringRecord00063BE4) == 36 ? 1 : -1];

class BfmeVecBE
{
public:
    void overflow(BfmeElemBE *, const BfmeElemBE &, const BfmeFalseBE &, unsigned, bool);
    BfmeElemBE *start, *finish, *limit;
    void rva006BF950(const BfmeElemBE &);
};

void BfmeVecBE::rva006BF950(const BfmeElemBE &value)
{
    if (finish != limit) {
        if (finish)
            new(finish) BfmeStringRecord00063BE4(
                *reinterpret_cast<const BfmeStringRecord00063BE4 *>(&value));
        ++finish;
    } else {
        // Default initialization gives this empty trait no payload operation.
        BfmeFalseBE tag;
        overflow(finish, value, tag, 1, true);
    }
}
