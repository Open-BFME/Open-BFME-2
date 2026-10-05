// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004F553F@Rva004F553F@@QAEXP6AXPAX0@Z0_N@Z @0x004F553F 77B.
// Visits a circular doubly-linked list forward or backward via a cdecl
// callback. Evidence: unlock lane packet; ret 0xC with EBP frame; pop-pop
// cleanup implies /O1; flag byte selects direction.
typedef void (__cdecl *Rva004F553FCb)(void *data, void *user);
struct Rva004F553FNode {
    Rva004F553FNode *m_prev;
    Rva004F553FNode *m_next;
    void *m_data;
};
class Rva004F553F {
    char _lead[0x10];
    Rva004F553FNode *m_head;
public:
    void rva004F553F(Rva004F553FCb cb, void *user, bool forward);
    void rva004F558C(int value);
};
class Object;
class TunnelTracker
{
public:
	static void healObject(Object *obj, void *user);
};
void Rva004F553F::rva004F553F(Rva004F553FCb cb, void *user, bool forward)
{
    if (forward) {
        Rva004F553FNode *cur = m_head;
        if (cur == cur->m_prev)
            return;
        do {
            cur = cur->m_next;
            cb(cur->m_data, user);
        } while (cur != m_head->m_prev);
        return;
    }
    Rva004F553FNode *cur = m_head->m_prev;
    if (cur == m_head)
        return;
    do {
        void *data = cur->m_data;
        cur = cur->m_prev;
        cb(data, user);
    } while (cur != m_head);
}

// ?rva004F558C@Rva004F553F@@QAEXH@Z @0x004F558C 20B.
// Forwards to the visitor above with a fixed callback and backward direction.
// Evidence: chain lane packet; same this as rva004F553F; ret 4.
void Rva004F553F::rva004F558C(int value)
{
    rva004F553F((Rva004F553FCb)TunnelTracker::healObject, &value, false);
}
