// cl: -DNDEBUG -MD -EHsc -Ireference/shims/bfme2_ascii
// The string xref names MPPositionInfo. Retail writes 0x0107C7D0 during registration and 0x010F5E78 before return. No caller names the derived class, so the class keeps the retail address.

#include "ascii_string.h"

// Retail vtable 0x0107C7D0: BfmeParserBindingBaseVE's vftable, i.e.
// ??_7BfmeParserBindingBaseVE@@6B@ (targets/game/reverse/dir32_addresses.csv).
// The declaration carries no C++ name: __identifier spells the retail symbol
// exactly, so the store below references the defining name.
extern "C" int __identifier("??_7BfmeParserBindingBaseVE@@6B@")[];

// Retail 0x00306EDC, the callback the rowed DataChunkParser ctor 0x000ABB87 registers
// (retail pushes it at 0x000ABB8F); it forwards a chunk to the parser's slot 1.
class BfmeTargetCW;
unsigned char bfmeAskCW(void *, void *, BfmeTargetCW *);

class UserParser;
class DataChunkInput;
struct DataChunkInfo;
typedef bool (*BfmeParserCallback)(DataChunkInput &, DataChunkInfo *, void *);

#include "../../Include/Common/DataChunk.h"

class BfmeParserRegistrationVE
{
public:
    BfmeParserRegistrationVE(DataChunkInput *table, AsciiString *name,
        AsciiString *label)
    {
        m_vftable = __identifier("??_7BfmeParserBindingBaseVE@@6B@");
        m_table = table;
        m_parser = table->registerParser(*name, *label,
            (BfmeParserCallback)&bfmeAskCW, this);
    }
    ~BfmeParserRegistrationVE();

protected:
    void *m_vftable;
    DataChunkInput *m_table;
    UserParser *m_parser;
};

// Derived vtable 0x010F5E78: no symbol in dir32_addresses.csv names it.
// Retail RVA 0x0080747C (.rdata, 8 B) holds two matched code pointers.
extern "C" {
void __identifier("??_GRva003B241AOwner@@QAEPAXI@Z")();
void __identifier("?rva003028F1@Rva003028F1@@UAE_NAAVDataChunkInput@@PAUDataChunkInfo@@@Z")();
}
extern void *g_010F5E78[2] =
{
	(void *)&__identifier("??_GRva003B241AOwner@@QAEPAXI@Z"),
	(void *)&__identifier("?rva003028F1@Rva003028F1@@UAE_NAAVDataChunkInput@@PAUDataChunkInfo@@@Z"),
};

// The constructor's EH cleanup destroys the base subobject whose matched dtor is
// the one at RVA 0x003B241A (the class that installs this vtable).
#pragma comment(linker, "/alternatename:??1BfmeParserRegistrationVE@@QAE@XZ=??1BfmeParserBindingBaseVE@@UAE@XZ")

class Gen004502D0ParserRegistration : public BfmeParserRegistrationVE
{
public:
    Gen004502D0ParserRegistration(void *extra, DataChunkInput *table,
        AsciiString *labelOverride);

private:
    void *m_0c;
    int m_10;
};

Gen004502D0ParserRegistration::Gen004502D0ParserRegistration(
    void *extra, DataChunkInput *table, AsciiString *labelOverride)
    : BfmeParserRegistrationVE(table,
        (AsciiString *)&AsciiString("MPPositionInfo"),
        labelOverride ? labelOverride : (AsciiString *)&AsciiString::TheEmptyString)
{
    Gen004502D0ParserRegistration *self = this;
    self->m_0c = extra;
    self->m_vftable = g_010F5E78;
    self->m_10 = 0;
}
