// ??0Rva00501656@@QAE@XZ
// partial score=0.93 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include "../../Include/Common/PlayerAITypeEntry.h"

#include <set>
#include <vector>

typedef _STL::_Vector_base<PlayerAITypeEntry, _STL::allocator<PlayerAITypeEntry> > PlayerAITypeVectorBase;
struct Rva00501219Element { char bytes[8]; };
typedef _STL::set<Rva00501219Element> Rva00501219Set;

// ??0Rva00501656@@QAE@XZ @ 0x00501656 109B: five vector bases at +0x10..+0x40 and a set at +0x4c, confirmed by adjacent dtor.
struct Rva00501656
{
	char m_pad00[0x10];
	_STL::vector<PlayerAITypeEntry> m_10;
	_STL::vector<PlayerAITypeEntry> m_1c;
	_STL::vector<PlayerAITypeEntry> m_28;
	_STL::vector<PlayerAITypeEntry> m_34;
	_STL::vector<PlayerAITypeEntry> m_40;
	Rva00501219Set m_4c;
	Rva00501656();
};

// bfme link decl-only begin
namespace _STL { template <> void _Destroy<PlayerAITypeEntry *>(PlayerAITypeEntry *,PlayerAITypeEntry *); }
namespace _STL { template <> void _Destroy<PlayerAITypeEntry>(PlayerAITypeEntry *); }
namespace _STL { template <> void _Destroy<Rva00501219Element>(Rva00501219Element *); }
namespace _STL { template <> void __destroy<PlayerAITypeEntry *,PlayerAITypeEntry>(PlayerAITypeEntry *,PlayerAITypeEntry *,PlayerAITypeEntry *); }
namespace _STL { template <> void __destroy_aux<PlayerAITypeEntry *>(PlayerAITypeEntry *,PlayerAITypeEntry *,_STL::__false_type const &); }
namespace _STL { template <> _Vector_base<PlayerAITypeEntry,_STL::allocator<PlayerAITypeEntry> >::~_Vector_base(); }
namespace _STL { template <> vector<PlayerAITypeEntry,_STL::allocator<PlayerAITypeEntry> >::~vector(); }
namespace _STL { template <> void _Rb_tree<Rva00501219Element,Rva00501219Element,_STL::_Identity<Rva00501219Element>,_STL::less<Rva00501219Element>,_STL::allocator<Rva00501219Element> >::_M_erase(_STL::_Rb_tree_node<Rva00501219Element> *); }
namespace _STL { template <> void _STLP_alloc_proxy<PlayerAITypeEntry *,PlayerAITypeEntry,_STL::allocator<PlayerAITypeEntry> >::deallocate(PlayerAITypeEntry *,unsigned int); }
namespace _STL { template <> void allocator<PlayerAITypeEntry>::deallocate(PlayerAITypeEntry *,unsigned int) const; }
// bfme link decl-only end
Rva00501656::Rva00501656()
	: m_10(_STL::allocator<PlayerAITypeEntry>()),
	  m_1c(_STL::allocator<PlayerAITypeEntry>()),
	  m_28(_STL::allocator<PlayerAITypeEntry>()),
	  m_34(_STL::allocator<PlayerAITypeEntry>()),
	  m_40(_STL::allocator<PlayerAITypeEntry>())
{
}
