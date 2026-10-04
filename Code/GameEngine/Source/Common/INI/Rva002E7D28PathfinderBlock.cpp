// cl: /O1 /MD
// BFME1 donor: game/GameEngine/Source/Common/BfmeConv939.cpp,
// revision 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24, bfmeGo939E.
// Native 0x002E7D28 is a complete 23B cdecl entry; code-address reference
// 0x002F6F35 independently reaches it. Native initializer 2F6F25 names
// its registry node 'Pathfinder', and 2F6F2F stores this parser address.
// It passes a 4B scratch slot and table
// VA DBD2F8 to rowed INI::initFromINI at 0x0002DE78.
// Native data is one 16B 'SlopeLimits' entry plus a complete zero sentinel.
// Callback VA 4B3FD0 is the existing shared 1B RET; the original callback name
// is unknown. Its existing matched W3DNoDraw COFF body supplies that address
// only, without inferring a new callback identity or callable declaration.
// The descriptor's trailing words and original global/function names remain
// unknown; this view preserves their observed bits and complete extent.

struct FieldParse;
class INI
{
public:
    void initFromINI(void *destination, const FieldParse *fields);
};

// Address-only declaration of the existing code definition.
extern "C" unsigned char __identifier("?W3DNoDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")[];

struct Rva009BD2F8FieldWords
{
    const char *token00;
    const void *callback04;
    unsigned int opaque08;
    unsigned int opaque0C;
};

Rva009BD2F8FieldWords g_Rva009BD2F8[2] =
{
    { "SlopeLimits", __identifier("?W3DNoDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z"), 0, 0 },
    { 0, 0, 0, 0 }
};

void rva002E7D28(INI *input)
{
    unsigned int scratch;
    input->initFromINI(&scratch, reinterpret_cast<const FieldParse *>(g_Rva009BD2F8));
}
