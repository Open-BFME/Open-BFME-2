// cl: /MD
// ?rva006E3710@Rva006E3710@@QAE_NPAURva006E3710Node@@@Z @0x006E3710 39B.
// Walks a singly linked list via +0x48 looking for the pointer at this+0x9c.
// Evidence: unlock lane packet; ret 4 with ecx use implies __thiscall method;
// false when target null or found in list, true otherwise.
struct Rva006E3710Node { char _pad[0x48]; Rva006E3710Node *m_next; };
class Rva006E3710 {
    char _lead[0x9c];
    Rva006E3710Node *m_target;
public:
    bool rva006E3710(Rva006E3710Node *p);
};
bool Rva006E3710::rva006E3710(Rva006E3710Node *p)
{
    Rva006E3710Node *target = m_target;
    if (!target)
        return false;
    for (Rva006E3710Node *q = p; q; q = q->m_next) {
        if (q == target)
            return false;
    }
    return true;
}
