// ?nonzero@Rva002E6AC5Nonzero@@QBE_NXZ
// partial score=0.87 date=2026-10-09
// cl: /O1 /arch:SSE /G7 /MD
// Partial native 002E6AC5/15: all bytes except TEST ECX,ECX vs CMP ECX,EAX.
// Parent lead: BFME1 9cbfb551 PathfindCell nullable pointer operation.
// Native boundary aligned from2E6A82, each complete RET0 leaf; word offset24.
// Owner and field identity remain unresolved.
class Rva002E6AC5Nonzero
{
public:
    bool nonzero() const;
    const unsigned *m_pointee;
};
bool Rva002E6AC5Nonzero::nonzero() const
{
    bool result = false;
    if (m_pointee)
        result = m_pointee[9] != 0;
    return result;
}
