// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ??1Rva00435CDBDtor@@QAE@XZ retail 0x00435CDB 5 bytes, already pinned under
// this name: the destructor of the global at 0x00E032EC, reached from its
// rowed atexit thunk 0x007B83B9. Its only non-trivial member is the
// AsciiString -> TreeHintOpaque0043671B tree at offset 0, so the body is a
// tail jump to that tree's ~_Rb_tree (rowed 0x00435B00 in
// stlport_tree_erase_00434E94.cpp, whose type declarations are repeated here).
#include <map>
#include "ascii_string.h"
#include "unicode_string.h"
bool operator<(const AsciiString &, const AsciiString &);
struct BfmeSubobject0022CE19 {
    virtual ~BfmeSubobject0022CE19();
    unsigned char m_opaque[0xDE4];
    BfmeSubobject0022CE19(const BfmeSubobject0022CE19 &);
};
struct TreeHintOpaque0043671B {
    UnicodeString m_text;
    BfmeSubobject0022CE19 m_subobject;
    unsigned int m_wordDEC, m_wordDF0;
    TreeHintOpaque0043671B();
    TreeHintOpaque0043671B(const TreeHintOpaque0043671B &);
    ~TreeHintOpaque0043671B();
};
typedef _STL::pair<const AsciiString, TreeHintOpaque0043671B> TreeHintPair0043671B;
typedef _STL::_Rb_tree<AsciiString, TreeHintPair0043671B, _STL::_Select1st<TreeHintPair0043671B>, _STL::less<AsciiString>, _STL::allocator<TreeHintPair0043671B> > TreeHint0043671B;

class Rva00435CDBDtor
{
public:
	~Rva00435CDBDtor();
private:
	TreeHint0043671B m_00;
};

Rva00435CDBDtor::~Rva00435CDBDtor()
{
}
