// cl: /O1 /MD
// Native constructors copy a four-byte key then construct the twelve-byte
// tree at +4. Their call is to the full tree-copy entry 0x00600A40;
// EDX is unused. The prior fastcall/mid-entry interpretation was incorrect.
namespace _STL {
template<class T> struct _Identity {};
template<class T> struct less {};
template<class T> class allocator {};
template<class K,class V,class KeyOfValue,class Compare,class Alloc> class _Rb_tree {
public:
 _Rb_tree(const _Rb_tree &);
 void *header; int count; char comparator; char pad[3];
};
}
struct Rva00600A40Element;
typedef _STL::_Rb_tree<Rva00600A40Element,Rva00600A40Element,_STL::_Identity<Rva00600A40Element>,_STL::less<Rva00600A40Element>,_STL::allocator<Rva00600A40Element> > NativeNestedTree;
struct Rva00600F9CElement {
 const char *key;
 NativeNestedTree tree;
 Rva00600F9CElement(const Rva00600F9CElement &);
 Rva00600F9CElement(const char *const &,const NativeNestedTree &);
};
Rva00600F9CElement::Rva00600F9CElement(const char *const &k,const NativeNestedTree &t) : key(k),tree(t) {}
