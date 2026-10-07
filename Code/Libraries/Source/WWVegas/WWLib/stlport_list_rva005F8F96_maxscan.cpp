// cl: /Ireference/shims/bfmelist /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /G7 /arch:SSE
// /G7 /arch:SSE give retail's cmovg pair for the running maximum (the
// banked body's only residue under the sibling flags).
struct TargetRef00217D4C;
struct ListNode005CCCD0 {
    ListNode005CCCD0 *m_next;
    ListNode005CCCD0 *m_prev;
    TargetRef00217D4C *m_data00;
    int m_data04;
};
class Rva005CCCD0 {
public:
    int m_00;
    int m_04;
    ListNode005CCCD0 *m_08;
    void rva005CCCFC();
};
// ?rva005CCCFC@Rva005CCCD0@@QAEXXZ, retail 0x005CCCFC, 58 bytes.
// Scans list at +8 for max [obj+0xc], tail-jumps to Rva005CCB16::rva005CCB16 on best's [+8].
// Evidence: same +8 list sentinel as neighbours; callee 0x005CCB16 row; caller 0x005CCE88 passes same this.
class Rva005CCB16
{
public:
    void rva005CCB16();
};
struct Obj005CCCFC
{
    int m_00;
    void *m_04;
    int m_08;
    int m_0C;
};
struct Data005CCCFC
{
    int m_00;
    int m_04;
    Obj005CCCFC *m_08;
};
void Rva005CCCD0::rva005CCCFC()
{
    ListNode005CCCD0 *sentinel = m_08;
    ListNode005CCCD0 *cur = sentinel->m_next;
    Data005CCCFC *best = 0;
    int bestVal = -1;
    if (cur == sentinel)
        return;
    do {
        Data005CCCFC *d = (Data005CCCFC *)cur->m_data00;
        Obj005CCCFC *o = d->m_08;
        int v = o->m_0C;
        cur = cur->m_next;
        if (v > bestVal) {
            best = d;
            bestVal = v;
        }
    } while (cur != sentinel);
    if (!best)
        return;
    ((Rva005CCB16 *)best->m_08)->rva005CCB16();
}
