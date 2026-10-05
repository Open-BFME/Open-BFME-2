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
    typedef _STL::_Rb_tree_iterator<Rva00500500,
        _STL::_Nonconst_traits<Rva00500500> > Iterator;
    void insert(Rva00500BF5Node *&result, Rva00500BF5Node *x,
                Rva00500BF5Node *y, const Rva00500500 &value,
                Rva00500BF5Node *known_order);
    void *createNode(const Rva00500500 &value);
    Iterator insertWorker(Rva00500BF5Node *x, Rva00500BF5Node *y,
                          const Rva00500500 &value, Rva00500BF5Node *known_order);
    Iterator insertEqual(const Rva00500500 &value);
    Iterator insertEqualWorker(const Rva00500500 &value);
    Iterator insertEqual(Iterator position, const Rva00500500 &value);
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

// Target 0x00500C7D/59B, called by the hint worker at 0x00500F6E.
// STLport _tree.c::insert_equal(value) traverses the same unsigned-key tree
// then returns the iterator constructed by the rowed insertion worker.
Rva00500BF5Tree::Iterator Rva00500BF5Tree::insertEqual(const Rva00500500 &value)
{
    Rva00500BF5Node *y = m_header;
    Rva00500BF5Node *x = m_header->parent;
    while (x != 0) {
        y = x;
        x = *reinterpret_cast<const unsigned *>(&value) < x->key ? x->left : x->right;
    }
    return insertWorker(x, y, value, 0);
}

// Iterator return and explicit output-reference spellings have the same
// hidden-result ABI. The declaration keeps MSVC from inspecting the worker
// when it compiles callers in this unit.
#pragma comment(linker, "/alternatename:?insertWorker@Rva00500BF5Tree@@QAE?AU?$_Rb_tree_iterator@VRva00500500@@U?$_Nonconst_traits@VRva00500500@@@_STL@@@_STL@@PAURva00500BF5Node@@0ABVRva00500500@@0@Z=?insert@Rva00500BF5Tree@@QAEXAAPAURva00500BF5Node@@PAU2@1ABVRva00500500@@1@Z")

#pragma comment(linker, "/alternatename:?insertEqualWorker@Rva00500BF5Tree@@QAE?AU?$_Rb_tree_iterator@VRva00500500@@U?$_Nonconst_traits@VRva00500500@@@_STL@@@_STL@@ABVRva00500500@@@Z=?insertEqual@Rva00500BF5Tree@@QAE?AU?$_Rb_tree_iterator@VRva00500500@@U?$_Nonconst_traits@VRva00500500@@@_STL@@@_STL@@ABVRva00500500@@@Z")

// Target 0x00500F6E/250B. STLport 4.5.3 insert_equal(hint, value),
// with the unsigned first-word ordering independently established above.
Rva00500BF5Tree::Iterator Rva00500BF5Tree::insertEqual(
    Iterator position, const Rva00500500 &value)
{
    Rva00500BF5Node *pos = reinterpret_cast<Rva00500BF5Node *>(position._M_node);
    if (pos == m_header->left) {
        if (m_count <= 0)
            return insertEqualWorker(value);
        if (!(pos->key < *reinterpret_cast<const unsigned *>(&value)))
            return insertWorker(pos, pos, value, 0);
        if (pos->left == pos)
            return insertWorker(0, pos, value, 0);

        Iterator after = position;
        ++after;
        Rva00500BF5Node *next = reinterpret_cast<Rva00500BF5Node *>(after._M_node);
        if (next == m_header || !(next->key < *reinterpret_cast<const unsigned *>(&value))) {
            if (pos->right == 0)
                return insertWorker(0, pos, value, pos);
            return insertWorker(next, next, value, 0);
        }
        return insertEqualWorker(value);
    } else if (pos == m_header) {
        if (!(*reinterpret_cast<const unsigned *>(&value) < m_header->right->key))
            return insertWorker(0, m_header->right, value, pos);
        return insertEqualWorker(value);
    } else {
        Iterator before = position;
        --before;
        bool pos_less = pos->key < *reinterpret_cast<const unsigned *>(&value);
        Rva00500BF5Node *prev = reinterpret_cast<Rva00500BF5Node *>(before._M_node);
        if (!pos_less && !(*reinterpret_cast<const unsigned *>(&value) < prev->key)) {
            if (prev->right == 0)
                return insertWorker(0, prev, value, prev);
            return insertWorker(pos, pos, value, 0);
        }
        Iterator after = position;
        ++after;
        Rva00500BF5Node *next = reinterpret_cast<Rva00500BF5Node *>(after._M_node);
        if (pos_less &&
            (next == m_header || !(next->key < *reinterpret_cast<const unsigned *>(&value)))) {
            if (pos->right == 0)
                return insertWorker(0, pos, value, pos);
            return insertWorker(next, next, value, 0);
        }
        return insertEqualWorker(value);
    }
}
