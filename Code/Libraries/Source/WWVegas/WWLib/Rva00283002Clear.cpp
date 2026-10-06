// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?rva00283002@Rva00283002@@QAEXXZ @0x00283002 49B: list clear destroying nodes at +8 via 0x00200667 then freeing via 0x00030830 plus resetting sentinel. Evidence: abuts CreateNode 0x00282FE0 which allocates 12 with data at +8; callees rowed free plus pinned dtor; callers at 0x00283429 plus 0x00283584 plus 0x00283EB3 plus 0x0028339E.
class Rva00200667 {
public:
    ~Rva00200667();
};
struct ListNode {
    ListNode *m_next;
    ListNode *m_prev;
    Rva00200667 m_data;
};
typedef char ListNodeSizeCheck[sizeof(ListNode) == 12 ? 1 : -1];
class Rva00283002 {
public:
    void rva00283002();
private:
    ListNode *m_head;
};
extern "C" void __cdecl free(void *block);
void Rva00283002::rva00283002()
{
    ListNode *head = m_head;
    ListNode *cur = head->m_next;
    if (cur != head) {
        do {
            ListNode *tmp = cur;
            cur = cur->m_next;
            tmp->m_data.~Rva00200667();
            free(tmp);
        } while (cur != m_head);
    }
    m_head->m_next = m_head;
    m_head->m_prev = m_head;
}
