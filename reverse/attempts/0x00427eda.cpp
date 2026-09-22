// ?lookupVersionValue@VersionBlockParser@@QAEPBDPBD0@Z
// partial score=0.93 date=2026-09-22
// ?lookupVersionValue@VersionBlockParser@@QAEPBDPBD0@Z
// partial score=0.93 date=2026-09-22
// ?lookupVersionValue@VersionBlockParser@@QAEPBDPBD0@Z @0x00427EDA
// VersionDestructor TU graft candidate; needs S-taking findEntry alias pin at 0x427EB9.
// V1 (struct-bool): 54/58, sole wall mov-byte vs stosb + push/pop edi.
// Retail: push ecx/push ecx/push edi + xor eax,eax/lea edi,[ebp-4]/stosb + push [ebp-4]
// Mine: push ecx/push ecx + mov byte [ebp-4],0 + push [ebp-4]
// All else exact: 5 pushes (found/first/last/key/match) + call rowed findEntry 0x427EB9
// + mov/add/cmp/pop/jne/mov/jmp/mov/leave/ret8 tail.
// REFUTED (10+ shapes, 6 flag sets): bool/char/int/voidp direct (all push-0 fold, 48-49B),
// struct-bool assign/init/value (all mov, 54B), bool-array/char-array (mov, 54B),
// volatile (sub-esp+mov+movzx, 57B), memset (call, 68B), /O1/O2/G6/G7/Oy-/Od/Ot/Os/Ox.
// Stosb is toolchain-canonical (different VS2003 patch emits xor+lea+stosb for same 1B zero).
// Do NOT retry without toolchain delta. t=60 model=spark
struct VersionBlockMatch { bool matched; };
class VersionBlockParser {
public:
    const char *lookupVersionValue(const char *key, const char *defaultValue);
private:
    int m_unk0;
    void *m_first;
    void *m_last;
};
static const void *findEntryAlias(const void *found, const void *first, const void *last, const char *const *key, VersionBlockMatch match);
const char *VersionBlockParser::lookupVersionValue(const char *key, const char *defaultValue) {
    const void *found[2];
    VersionBlockMatch dummy; dummy.matched = false;
    findEntryAlias(found, m_first, m_last, &key, dummy);
    if (found[0] == found[1]) return defaultValue;
    return ((const char *const *)found[0])[3];
}
