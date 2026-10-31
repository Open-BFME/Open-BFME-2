// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// BFME2 STLport tree: AsciiString key and opaque 0xDF4-byte mapped object.
// ??1TreeHintOpaque0043671B@@QAE@XZ @0x00229840 53B destroys UnicodeString +0 and 0xDE8 subobject +4; deleting dtor 0x002DDE27 and list clear 0x00434EC9 prove identity; layout from copy 0x0022D106.
// hint 0x436E3B -> insert 0x4367AF -> _M_insert 0x43671B -> node 0x436234.
// The node allocates 0xE08 bytes and constructs its 0xDF8-byte value at node+16.
// _Construct 0x43616A calls pair copy 0x435DAA: AsciiString copy 0x365F0,
// then the mapped object copy constructor 0x22D106 on the second pair field.
// Comparison reaches the established AsciiString operator< at 0x5598C.
// Semantic donor: BFME1 RvaTreeInsertUniqueHint.cpp and STLport pair/tree.
#include <stl/_prolog.h>
#include <stl/type_traits.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#undef _STLP_DEFAULT_CONSTRUCTED
#define _STLP_DEFAULT_CONSTRUCTED(_TTp) _TTp()
#include <map>
#include "ascii_string.h"
bool operator<(const AsciiString &, const AsciiString &);
// The mapped copy at 0x22D106 proves a UnicodeString, a 0xDE8-byte
// subobject, and two final words. Its original application type is unknown.
#include "unicode_string.h"
// Full 216-byte retail constructor 0x22CE19 installs vptr 0xBE7560,
// copies string/scalar members and nested subobjects. Keep its ownership
// operations out of line; its application class and virtual slots are unknown.
struct BfmeSubobject0022CE19 {
    virtual ~BfmeSubobject0022CE19();
    unsigned char m_opaque[0xDE4];
    BfmeSubobject0022CE19();
    BfmeSubobject0022CE19(const BfmeSubobject0022CE19 &);
    BfmeSubobject0022CE19 &operator=(const BfmeSubobject0022CE19 &);
};
struct TreeHintOpaque0043671B {
    UnicodeString m_text;
    BfmeSubobject0022CE19 m_subobject;
    unsigned int m_wordDEC, m_wordDF0;
    TreeHintOpaque0043671B();
    TreeHintOpaque0043671B(const TreeHintOpaque0043671B &);
    ~TreeHintOpaque0043671B();
    TreeHintOpaque0043671B &operator=(const TreeHintOpaque0043671B &);
};
inline TreeHintOpaque0043671B::TreeHintOpaque0043671B(const TreeHintOpaque0043671B &other)
    : m_text(other.m_text), m_subobject(other.m_subobject),
      m_wordDEC(other.m_wordDEC), m_wordDF0(other.m_wordDF0) {}

TreeHintOpaque0043671B::~TreeHintOpaque0043671B() {}

typedef _STL::pair<const AsciiString, TreeHintOpaque0043671B> TreeHintPair0043671B;
typedef _STL::_Rb_tree<AsciiString, TreeHintPair0043671B, _STL::_Select1st<TreeHintPair0043671B>, _STL::less<AsciiString>, _STL::allocator<TreeHintPair0043671B> > TreeHint0043671B;
// Cleanup owns the verified 56-byte destructor. This /EHsc insertion unit
// would otherwise emit a 52-byte copy without the allocator unwind transition.
extern template TreeHint0043671B::~_Rb_tree();
// Retail uses its static byte allocator and has no node cleanup catch block.
// ?_M_create_node@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UTreeHintOpaque0043671B@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UTreeHintOpaque0043671B@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintOpaque0043671B@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UTreeHintOpaque0043671B@@@_STL@@@2@ABU?$pair@$$CBVAsciiString@@UTreeHintOpaque0043671B@@@2@@Z
template <>
TreeHint0043671B::_Link_type TreeHint0043671B::_M_create_node(const TreeHintPair0043671B &value)
{
    _Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<TreeHintPair0043671B>), 0);
    _STL::_Construct(&node->_M_value_field, value);
    return node;
}
template TreeHint0043671B::iterator TreeHint0043671B::insert_unique(TreeHint0043671B::iterator, const TreeHintPair0043671B &);

// The map wrapper directly calls this tree's verified hinted insertion.
typedef _STL::map<AsciiString,TreeHintOpaque0043671B,_STL::less<AsciiString >,_STL::allocator<TreeHintPair0043671B> > MapInsert00436e3b;
template MapInsert00436e3b::iterator MapInsert00436e3b::insert(MapInsert00436e3b::iterator, const TreeHintPair0043671B &);

template void _STL::_Construct<TreeHintOpaque0043671B,TreeHintOpaque0043671B>(TreeHintOpaque0043671B*, const TreeHintOpaque0043671B&);

template TreeHintOpaque0043671B &MapInsert00436e3b::operator[](const AsciiString &);

// Retail Ghidra entry 0x00435CE0 is 25 bytes and ends at RET. Its REL32 at
// +0xF calls the rowed tree constructor 0x00434C3D. The neighboring 0x00436E3B
// insertion chain supports the AsciiString to TreeHint map specialization.
template _STL::map<AsciiString, TreeHintOpaque0043671B,
    _STL::less<AsciiString>,
    _STL::allocator<TreeHintPair0043671B> >::map();
// Retail 0x004360B3 looks up the printed saved-game digest in the tree
// whose address is owned as g_Va00E032EC. Its caller passes MD5 text;
// the returned node with the tree header and returns the mapped value at +0x14.
// The insert chain establishes the value type, so the lookup is this map's
// own find: its key-only _M_find<AsciiString> is the 78-byte worker that
// /OPT:ICF folded with every other AsciiString-keyed tree at 0x001F8437.
extern unsigned g_Va00E032EC;

TreeHintOpaque0043671B *Rva004360B3(AsciiString key)
{
    MapInsert00436e3b &table = *(MapInsert00436e3b *)&g_Va00E032EC;
    MapInsert00436e3b::iterator found = table.find(key);
    if (found._M_node != table.end()._M_node)
        return &(*found).second;
    return 0;
}

// Retail 0x00437421 (482 bytes, no arguments), the last call of the LAN
// lobby start-up InitTheLan (0x0044546D): it lists the save files of type 6,
// reads each file's BFME2 metadata and indexes the entries whose digest is
// nonzero by that digest's MD5 text in this map (0x004360B3 and 0x004361B3
// search it the same way). The owning application type stays unresolved.
#include <set>
#include <string.h>
extern "C" void MD5Print(unsigned char digest[16], char output[33]);

// The file-name set GameState::iterateSaveFiles also fills (its destructor
// is rowed as ??1Rva0021C459 at 0x0021D5D5). Its elements are wide names,
// but retail calls the shared set constructor 0x000D3A71, rowed under its
// ICF fold name set<AsciiString>; the walk reads its nodes as wide names.
typedef _STL::set<AsciiString, _STL::less<AsciiString>, _STL::allocator<AsciiString> > SetConstructorAlias00437421;
// Only ~Rva0021C459 (0x0021D5D5) destroys the set; keep its tree's
// destructor chain out of this unit as for the map's tree above.
extern template _STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>, _STL::less<AsciiString>, _STL::allocator<AsciiString> >::~_Rb_tree();
class Rva0021C459 : public SetConstructorAlias00437421
{
public:
    ~Rva0021C459();
    // The tree header node, the set's first word (as iterateSaveFiles walks it).
    _STL::_Rb_tree_node_base *header() const { return *reinterpret_cast<_STL::_Rb_tree_node_base *const *>(this); }
};

// The file-list object is Rva0021DA13 (as AptSaveLoadRva0043684C.cpp spells
// it): its destructor is the 5-byte thunk 0x0021DA13 the unwind funclet
// jumps to; the normal path expands it into ~Rva0021C459 (0x0021D5D5).
class Rva0021DA13 : public Rva0021C459
{
};

class Rva002DC267
{
public:
    UnicodeString rva002DC267() const; // the save directory
};

// The 81-byte file-list provider 0x006007DA ignores ECX and takes four stack
// words; call it as GameState::iterateSaveFiles does, with the file system
// as the unused receiver.
class Rva006007DAFileSystem {};
void __stdcall Rva006007DAOpen(void *, void *, void *, void *);
union NativeSaveEnumerationCall {
    void (__stdcall *target)(void *, void *, void *, void *);
    void (Rva006007DAFileSystem::*member)(const UnicodeString *, const UnicodeString *, Rva0021C459 *, bool);
};

class GameState
{
public:
    void *rva002DBC97Get(int saveType);
    bool getSaveGameInfoFromFile(UnicodeString filename, BfmeSubobject0022CE19 *metadata);
};
class FileSystem;
extern GameState *TheGameState;
extern FileSystem *TheFileSystem;

void Rva00437421()
{
    if (TheGameState == 0)
        return;

    MapInsert00436e3b *hints = (MapInsert00436e3b *)&g_Va00E032EC;
    hints->clear();

    UnicodeString pattern(AsciiString("*"));
    pattern += (const unsigned short *)TheGameState->rva002DBC97Get(6);

    Rva0021DA13 files;
    NativeSaveEnumerationCall enumeration = {&Rva006007DAOpen};
    (((Rva006007DAFileSystem *)TheFileSystem)->*enumeration.member)(
        &((Rva002DC267 *)TheGameState)->rva002DC267(), &pattern, &files, true);

    for (_STL::_Rb_tree_node_base *node = files.header()->_M_left; node != files.header();
         node = _STL::_Rb_global<bool>::_M_increment(node))
    {
        BfmeSubobject0022CE19 metadata;
        const UnicodeString &name = static_cast<_STL::_Rb_tree_node<UnicodeString> *>(node)->_M_value_field;
        if (!TheGameState->getSaveGameInfoFromFile(name, &metadata))
            continue;

        char printedDigest[33];
        MD5Print((unsigned char *)&metadata + 0xDA8, printedDigest);
        if (strcmp(printedDigest, "00000000000000000000000000000000") == 0)
            continue;

        TreeHintOpaque0043671B hint;
        hint.m_wordDF0 = 0;
        hint.m_wordDEC = 0;
        hint.m_subobject = metadata;
        hint.m_text = name;
        (*hints)[AsciiString(printedDigest)] = hint;
    }
}
