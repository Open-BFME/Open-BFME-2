// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva005CCCD0@Rva005CCCD0@@QAEXPAUVisitor005CCCD0@@@Z, retail 0x005CCCD0, 44 bytes.
// Iterates list<Rva005F8F96> at +8, calls visitor vtable slot 0 with node data m_00; stops on false.
// Evidence: neighbour List_base clear proves node layout (next at +0, data at +8); caller 0x005CCD36 forwards [ecx+4].
struct TargetRef00217D4C { virtual void *destroy(unsigned int flags); int references; };
struct Visitor005CCCD0 { virtual bool visit(TargetRef00217D4C *p); };
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
    void rva005CCCD0(Visitor005CCCD0 *v);
};
void Rva005CCCD0::rva005CCCD0(Visitor005CCCD0 *v)
{
    ListNode005CCCD0 *sentinel = m_08;
    ListNode005CCCD0 *cur = sentinel->m_next;
    if (cur == sentinel)
        return;
    do {
        ListNode005CCCD0 *nxt = cur->m_next;
        TargetRef00217D4C *d = cur->m_data00;
        if (!v->visit(d))
            return;
        cur = nxt;
    } while (cur != sentinel);
}
class Rva005CCD36 {
public:
    int m_00;
    Rva005CCCD0 *m_04;
    void rva005CCD36(Visitor005CCCD0 *v);
};
void Rva005CCD36::rva005CCD36(Visitor005CCCD0 *v)
{
    m_04->rva005CCCD0(v);
}
