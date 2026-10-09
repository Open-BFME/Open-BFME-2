// cl: /DNDEBUG /MD

// ?rva00448DCB@Rva00448DCB@@QAEPAURva00448DCBNode@@ABUBfmeStringRecord00448113@@@Z @0x00448DCB (78B).
// RB-tree find for the BfmeStringRecord00448113 tree (the string-record set whose lower_bound and insert are
// rowed in stlport_rb_tree_BfmeStringRecord00448113_*.cpp): the same lower_bound-then-check walk as
// Rva0039EA4E::rva0039EA4E (RTS/Rva0039EA4EFinish.cpp) with the rowed free operator< 0x00448D3C (node key at +0x10),
// returning the header when the key is not present. Target evidence: retail body and the operator< REL32 read byte
// for byte; class and method names are address-derived.
struct BfmeStringRecord00448113;
bool operator<(const BfmeStringRecord00448113 &left, const BfmeStringRecord00448113 &right);

struct Rva00448DCBNode
{
    int m_color00;
    Rva00448DCBNode *m_parent04;
    Rva00448DCBNode *m_left08;
    Rva00448DCBNode *m_right0C;
    char m_key10[1];
};

class Rva00448DCB
{
public:
    Rva00448DCBNode *rva00448DCB(const BfmeStringRecord00448113 &key);

private:
    Rva00448DCBNode *m_header00;
};

Rva00448DCBNode *Rva00448DCB::rva00448DCB(const BfmeStringRecord00448113 &key)
{
    Rva00448DCBNode *j = m_header00;
    Rva00448DCBNode *header = m_header00;
    Rva00448DCBNode *x = header->m_parent04;
    while (x) {
        if (!(*(const BfmeStringRecord00448113 *)x->m_key10 < key)) {
            j = x;
            x = x->m_left08;
        } else
            x = x->m_right0C;
    }
    if (j == header || key < *(const BfmeStringRecord00448113 *)j->m_key10)
        j = header;
    return j;
}
