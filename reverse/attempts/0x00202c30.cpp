// ?getStaticGameLODIndex@GameLODManager@@QAEHVAsciiString@@@Z
// partial score=0.9 date=2026-09-24
// cl: /O1 /DNDEBUG /MD /EHsc
// Partial 0.9 for ?getStaticGameLODIndex@GameLODManager@@QAEHVAsciiString@@@Z @0x00202C30 (70B retail).
// BFME1 GameLODManagerGetStaticGameLODIndex.cpp donor with BFME2 repairs:
// five-entry VeryLow table (retail 0x00DB969C strings VeryLow/Low/Medium/High/VeryHigh,
// proven via game.dat .data dump) instead of donor six; out-of-line compareNoCase
// via rowed 0x00037980 (donor inlines via _memicmp/strlen); no DEBUG_CRASH (donor
// has none; ZH TU adds one); return minus-one.
// Wall (toolchain-canonical, 10+ probes: /O1//O2//GX//GX-//EHa//EHs//GR, dtor-throw/
// empty/no-dtor, extern/unsigned/while all inert or worse): retail has single EH
// state-or-minus-one at end with no state-zero at start; this toolchain emits
// state-zero mov-[ebp-4]-esi at start plus state-minus-one (73B) or state-zero
// only with throw-dtor (69B). Needs state-scheduling lever, do not retry blind.
// Probes in build/probe_lod.cpp (compile_source + read_object_symbol_bytes).
typedef int Int;
class AsciiString {
public:
    ~AsciiString();
    int compareNoCase(const char *other) const;
private:
    struct Data { Int refs; unsigned short len; unsigned short cap; char txt[1]; };
    Data *m_data;
};
static const char *BfmeStaticGameLODNames[5]={"VeryLow","Low","Medium","High","VeryHigh"};
class GameLODManager { public: Int getStaticGameLODIndex(AsciiString name); };
Int GameLODManager::getStaticGameLODIndex(AsciiString name)
{
    for (Int i=0;i<5;++i) { if (name.compareNoCase(BfmeStaticGameLODNames[i])==0) return i; }
    return -1;
}
