// cl: /DNDEBUG /MD

// ?rva0039EA4E@Rva0039EA4E@@QAEPAURva0039EA4ENode@@ABURva0039D8FBKey@@@Z @0x0039EA4E (78B).
// RB-tree lower_bound for the TeamFactory prototype map. Callers are the
// find/insert bodies at 0x39F597 0x39F5FE 0x39F692 0x39FB87 0x3A2943; the
// 8-byte two-int key is compared by the rowed Rva0039D8FBLess at 0x0039D8FB.
// Header +0x00 root at +0x04, node +0x08 left / +0x0C right / +0x10 key.
// The accumulator local is declared before header/cur on purpose: that order
// is what makes MSVC /O1 keep the result in ebx (as retail) instead of copying
// it to the free esi and destructively reusing ebx for the tail address.
struct Rva0039D8FBKey
{
    int m_first;
    int m_second;
};

int __cdecl Rva0039D8FBLess(const Rva0039D8FBKey &a, const Rva0039D8FBKey &b);

struct Rva0039EA4ENode
{
    int m_color00;
    Rva0039EA4ENode *m_parent04;
    Rva0039EA4ENode *m_left08;
    Rva0039EA4ENode *m_right0C;
    Rva0039D8FBKey m_key10;
};

class Rva0039EA4E
{
public:
    Rva0039EA4ENode *rva0039EA4E(const Rva0039D8FBKey &key);

private:
    Rva0039EA4ENode *m_header00;
};

Rva0039EA4ENode *Rva0039EA4E::rva0039EA4E(const Rva0039D8FBKey &key)
{
    Rva0039EA4ENode *j = m_header00;
    Rva0039EA4ENode *header = m_header00;
    Rva0039EA4ENode *x = header->m_parent04;
    while (x) {
        if (!(unsigned char)Rva0039D8FBLess(x->m_key10, key)) {
            j = x;
            x = x->m_left08;
        } else
            x = x->m_right0C;
    }
    if (j == header || (unsigned char)Rva0039D8FBLess(key, j->m_key10))
        j = header;
    return j;
}
