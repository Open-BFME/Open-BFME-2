// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// Rva00222278Parse (0x00222278, 182 bytes): INI block parser that builds a
// reference-counted Rva00221C15 entry from the next token and the owner's
// +0x0C template, and stores it under that name in the owner's +0x28 map
// when the name is new. Address-derived names: identity unproven.
// Retail keeps the new entry pointer in EDI through the map's operator[] and
// the reference assignment (0x002174A4) to the reference's inlined
// destructor, and homes the reference in the dead ownerPtr slot: cl only
// does both when the assignment body is visible in the unit, so it is
// defined here out of line (byte-identical to retail); the reference's
// constructor takes the count.
#include "ascii_string.h"
#include <stl/_prolog.h>
#include <stl/type_traits.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#undef _STLP_DEFAULT_CONSTRUCTED
#define _STLP_DEFAULT_CONSTRUCTED(_TTp) _TTp()
#include <map>
// bfme link decl-only begin
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_create_node@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UTreeHintRef00221D6B@@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString; struct TreeHintRef00221D6B;
namespace _STL { template <> _Rb_tree_node<pair<AsciiString const ,TreeHintRef00221D6B> > * _Rb_tree<AsciiString,pair<AsciiString const ,TreeHintRef00221D6B>,_Select1st<pair<AsciiString const ,TreeHintRef00221D6B> >,less<AsciiString>,allocator<pair<AsciiString const ,TreeHintRef00221D6B> > >::_M_create_node(pair<AsciiString const ,TreeHintRef00221D6B> const &); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UTreeHintRef00221D6B@@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString; struct TreeHintRef00221D6B;
namespace _STL { template <> void allocator<_Rb_tree_node<pair<AsciiString const ,TreeHintRef00221D6B> > >::deallocate(_Rb_tree_node<pair<AsciiString const ,TreeHintRef00221D6B> > *,unsigned int) const; }
class INI { public: const char *getNextToken(const char *s); };
class Rva00221A58 { public: Rva00221A58(const Rva00221A58 &other); private: char m_pad[0x1C]; };
class Rva00221B42 { private: char m_pad[0x20]; };
class Rva00221C15 { public: Rva00221C15(const AsciiString &a, const Rva00221A58 &b, INI *ini); const void *m_vtable; int m_refs; Rva00221B42 m_08; };
struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C(TargetRef00217D4C *target) : m_ptr(target) { if (m_ptr) ++m_ptr->references; }
	~TreeHintRef00217D4C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
	__declspec(noinline) TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other)
	{
		if (this != &other)
		{
			if (other.m_ptr)
				++other.m_ptr->references;
			if (m_ptr)
				ReleaseTreeHintRef00217D4C(m_ptr);
			m_ptr = other.m_ptr;
		}
		return *this;
	}
	TargetRef00217D4C *m_ptr;
};
struct TreeHintRef00221D6B { TargetRef00217D4C *m_ptr; };
typedef _STL::map<AsciiString, TreeHintRef00221D6B, _STL::less<AsciiString>, _STL::allocator<_STL::pair<const AsciiString, TreeHintRef00221D6B> > > Map00221D6B;
typedef _STL::map<AsciiString, AsciiString, _STL::less<AsciiString>, _STL::allocator<_STL::pair<const AsciiString, AsciiString> > > AsciiMap;
struct Owner00222278 { char m_00[0x0C]; Rva00221A58 m_0C; Map00221D6B m_28; };
void __cdecl Rva00222278Parse(INI *ini, void *ownerPtr)
{
	AsciiString key(ini->getNextToken((const char *)0));
	Owner00222278 *owner = (Owner00222278 *)ownerPtr;
	Rva00221C15 *obj = new Rva00221C15(key, owner->m_0C, ini);
	TreeHintRef00217D4C temp((TargetRef00217D4C *)obj);
	if (((AsciiMap &)owner->m_28).find(key) == ((AsciiMap &)owner->m_28).end()) ((TreeHintRef00217D4C &)owner->m_28[key]) = temp;
}
