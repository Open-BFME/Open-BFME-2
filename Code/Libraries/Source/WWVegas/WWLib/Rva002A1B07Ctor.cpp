// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva002A1B07@@QAE@XZ @0x002A1B07 22B.
// Default ctor constructing the Drawable-pointer list member at +4 through
// the pinned List_base ctor with a stack allocator temp. Evidence: thiscall
// no-arg ret; lea ecx [esi+4] plus lea-push temp allocator matching the
// pinned List_base 0x00239BB0; caller at 0x002A3C1B; +0 left uninitialized.
#include <list>
class Drawable;
class Rva002A1B07
{
public:
	Rva002A1B07();
private:
	int m_00;
	_STL::list<Drawable *> m_list04;
};
Rva002A1B07::Rva002A1B07()
{
}
