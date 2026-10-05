// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Retail 0x00500BF5, Ghidra boundary 136 bytes. Reference algorithm:
// STLport 4.5.3 stl/_tree.c::_M_insert, also emitted by the served
// stlport_map_int_ptr_o1.cpp. Every non-call byte agrees with that donor
// except its signed comparison: retail orders the first value word unsigned.
// The target's factory is the independently rowed 0x00500BA6, which copies
// Rva00500500 (92 bytes) into a 108-byte node. This is not map<int, void *>.
// Application identity and the complete owner layout remain unknown.
// Target proves header/count at +0/+4 and node links at +4/+8/+C. The
// output reference models the iterator return slot (five popped words).
#include <set>

class Rva00500500;

struct Rva00500BF5Node
{
    unsigned color;
    Rva00500BF5Node *parent;
    Rva00500BF5Node *left;
    Rva00500BF5Node *right;
    unsigned key;
};

class Rva00500BF5Tree
{
public:
    void insert(Rva00500BF5Node *&result, Rva00500BF5Node *x,
                Rva00500BF5Node *y, const Rva00500500 &value,
                Rva00500BF5Node *known_order);
    void *createNode(const Rva00500500 &value);
private:
    Rva00500BF5Node *m_header;
    unsigned m_count;
};

// The factory does not read ECX. Bind the member spelling to its existing
// stdcall provider, retaining the caller's retail ECX setup and cleanup.
#pragma comment(linker, "/alternatename:?createNode@Rva00500BF5Tree@@QAEPAXABVRva00500500@@@Z=?Rva00500BA6Create@@YGPAU?$_Rb_tree_node@VRva00500500@@@_STL@@ABVRva00500500@@@Z")

void Rva00500BF5Tree::insert(Rva00500BF5Node *&result, Rva00500BF5Node *x,
                           Rva00500BF5Node *y, const Rva00500500 &value,
                           Rva00500BF5Node *known_order)
{
    Rva00500BF5Node *node;
    if (y != m_header &&
        (known_order != 0 ||
         (x == 0 && *reinterpret_cast<const unsigned *>(&value) >= y->key))) {
        node = reinterpret_cast<Rva00500BF5Node *>(createNode(value));
        y->right = node;
        Rva00500BF5Node *header = m_header;
        if (y == header->right)
            header->right = node;
    } else {
        node = reinterpret_cast<Rva00500BF5Node *>(createNode(value));
        y->left = node;
        Rva00500BF5Node *header = m_header;
        if (y == header) {
            header->parent = node;
            m_header->right = node;
        } else if (y == header->left) {
            header->left = node;
        }
    }
    node->left = 0;
    node->right = 0;
    node->parent = y;
    _STL::_Rb_global<bool>::_Rebalance(
        reinterpret_cast<_STL::_Rb_tree_node_base *>(node),
        reinterpret_cast<_STL::_Rb_tree_node_base *&>(m_header->parent));
    ++m_count;
    result = node;
}
