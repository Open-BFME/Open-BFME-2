// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

// Retail's operation calls these rows for its element, spelled under separate placeholder
// names. The local element forwards to them, so the rows' own bodies run.
struct Rva00414BDBElement { ~Rva00414BDBElement(); };
class Rva001DE727 { public: Rva001DE727 &operator=(const Rva001DE727 &); };
struct Rva001DF2D3Element { Rva001DF2D3Element();Rva001DF2D3Element(const Rva001DF2D3Element&);~Rva001DF2D3Element() { ((Rva00414BDBElement *)this)->Rva00414BDBElement::~Rva00414BDBElement(); }Rva001DF2D3Element&operator=(const Rva001DF2D3Element&other) { ((Rva001DE727 *)this)->operator=(*(const Rva001DE727 *)&other); return *this; }char bytes[48]; bool operator<(const Rva001DF2D3Element&)const; bool operator==(const Rva001DF2D3Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva001DF2D3Element, _STL::allocator<Rva001DF2D3Element> >::_M_fill_insert(Rva001DF2D3Element *, unsigned int, Rva001DF2D3Element const &);

// Complete native 0x001DF428..0x001DF42D follows RET4 and precedes a
// separate EH prologue. It forwards the unchanged vector receiver and
// three arguments to the verified fill-insert at 0x001DF2D3. The original
// wrapper name and application element identity remain unknown.
class Rva001DF428 : public _STL::vector<Rva001DF2D3Element, _STL::allocator<Rva001DF2D3Element> >
{
public:
    void rva001DF428(Rva001DF2D3Element *position, unsigned int count, const Rva001DF2D3Element &value);
};
void Rva001DF428::rva001DF428(Rva001DF2D3Element *position, unsigned int count, const Rva001DF2D3Element &value)
{
    _M_fill_insert(position, count, value);
}
