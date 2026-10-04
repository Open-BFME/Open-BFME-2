// ?Rva0007A75EGuardedQuery@@YAXXZ
// partial score=0.81 date=2026-10-05
// cl: /O2 /DNDEBUG /MD /EHsc
// Banked native ABI draft, not a verified or link-complete recovery.
// Whole BF1 Rva00755C80GuardedQuery.cpp at 6583b3c1ff21db4a561285717028fdafc780b7db
// supplies the guarded-call/store pattern. Native Ghidra 7A75E/21 passes the
// nonnull pointer at VA DE1FB8 in ECX to 7A54B/443 and stores EAX to DE1FB0.
// The destination has an existing zero-initialized int definition; this draft
// reuses that representation. The pointer's provider and complete 443-byte
// callee remain unavailable. This declaration projects observed register bits
// only; original types, class, method name and return meaning are unknown.
class Rva0007A54BCallView
{
public:
    int readReturnBits();
};
extern Rva0007A54BCallView *g_Rva00DE1FB8;
extern int g_Va001FDEB0;

void Rva0007A75EGuardedQuery()
{
    if (g_Rva00DE1FB8)
        g_Va001FDEB0 = g_Rva00DE1FB8->readReturnBits();
}
