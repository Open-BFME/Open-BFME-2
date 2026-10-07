// cl: /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /O1 /arch:SSE /G7
// stlport
// ?rva0031BF1B@Rva0031BF1B@@QAEXPAVModuleData@@@Z @0x0031BF1B 73B
// Removes a ModuleData node from the singly linked chain at this+0x2c,
// queues it in the vector at this+0x23c, then sets its flag at +0xc.
// Evidence: retail offsets and the rowed vector<ModuleData const *>::push_back call;
// class identity is unproven, so the address-based class name is retained.
// Donor: none.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// Reuse the verified unsigned max body at 0x00013740; this unit
// must not supply a conflicting out-of-line copy.
namespace _STL {
template <> const unsigned int& max<unsigned int>(const unsigned int&, const unsigned int&);
}

class ModuleData
{
public:
    unsigned char m_pad00[0x0c];
    int m_removed;
    unsigned char m_pad10[8];
    ModuleData *m_next;
};

class Rva0031BF1B
{
public:
    unsigned char m_pad00[0x2c];
    ModuleData *m_head;
    unsigned char m_pad30[0x20c];
    _STL::vector<const ModuleData *> m_removed;
    void rva0031BF1B(ModuleData *data);
};

void Rva0031BF1B::rva0031BF1B(ModuleData *data)
{
    if (data == 0)
        return;
    ModuleData *node = m_head;
    ModuleData *previous = 0;
    goto check_node;
find_node:
    if (node == data)
        goto found_node;
    previous = node;
    node = node->m_next;
check_node:
    if (node != 0)
        goto find_node;
    return;
found_node:
    if (previous != 0)
        previous->m_next = node->m_next;
    else
        m_head = node->m_next;
    m_removed.push_back(data);
    data->m_removed = 1;
}
