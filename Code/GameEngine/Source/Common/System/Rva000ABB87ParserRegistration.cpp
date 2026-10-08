// cl: /MD /Ireference/shims/bfme2_ascii
// BFME1 donor: game/GameEngine/Source/Common/Rva00190610ParserRegistrationCtor.cpp,
// revision 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24, base registration constructor.
// Native 0x000ABB87 is a complete 44B thiscall entry (RET12), independently
// called by 23 native sites including PolygonTriggers constructor 0x00328B9A.
// It registers name/label with rowed DataChunkInput::registerParser 0x00307779
// and native callback 0x00306EDC, storing the input at +4 and parser at +8.
// Target table VA BC9574 has two slots: rowed deleting body 0x000AD930 and
// __purecall 0x0003B810. Rowed constructor 0x000ABD56 separately installs
// adjacent table BC957C, proving the boundary of this complete two-slot table.
// Original class name and the table's C++ name remain unknown. The explicit
// 12B view preserves the donor's registration purpose and native offsets.
#include "ascii_string.h"

class UserParser;
class DataChunkInput;
struct DataChunkInfo;
typedef bool (__cdecl *Rva000ABB87Callback)(DataChunkInput &, DataChunkInfo *, void *);

class DataChunkInput
{
public:
    UserParser *registerParser(const AsciiString &name, const AsciiString &label,
        Rva000ABB87Callback callback, void *userData);
};

class BfmeTargetCW;
unsigned char bfmeAskCW(void *, void *, BfmeTargetCW *);
// Reuse the existing complete two-slot provider; the old class spelling is
// a linker compatibility key, not an original target identity claim.
extern "C" unsigned char __identifier("??_7BfmeParserBindingBaseVE@@6B@");
#pragma comment(linker, "/alternatename:?bfmeDropVE@BfmeSubVE@@QAEXPAX@Z=?handle@Q1Forwardee0000871A@@QAEXH@Z")
#pragma comment(linker, "/alternatename:?bfmeFreeVE@@YAXPAX@Z=??3@YAXPAX@Z")
// Native AD930 calls306D7B atAD93F and scalar delete2FD60 atAD94C.
// The unlink argument is one native dword; the existing pointer/int spellings
// preserve that thiscall ABI. The operator delete signature is unchanged.
// These synthetic slot spellings are referenced only as addresses in the
// provider's two-slot table. Native BC9574 supplies their actual targets.
#pragma comment(linker, "/alternatename:?bfmeSlot0@BfmeParserBindingBaseVE@@UAEXXZ=?bfmeKillVE@BfmeThingVE@@QAEPAXH@Z")
#pragma comment(linker, "/alternatename:?bfmeSlot1@BfmeParserBindingBaseVE@@UAEXXZ=__purecall")

class DataChunkParser
{
public:
    DataChunkParser(DataChunkInput *input, const AsciiString *name,
        const AsciiString *label);
private:
    const void *opaque00;
    DataChunkInput *input04;
    UserParser *parser08;
};

DataChunkParser::DataChunkParser(DataChunkInput *input,
    const AsciiString *name, const AsciiString *label)
{
    opaque00 = &__identifier("??_7BfmeParserBindingBaseVE@@6B@");
    input04 = input;
    parser08 = input->registerParser(*name, *label,
        (Rva000ABB87Callback)&bfmeAskCW, this);
}
