// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva0022C0CDSubsystem@@QAE@XZ, retail 0x0022DA03, 71 bytes.
//
// Evidence: the pin has carried this ctor address since the GameEngine::init
// recovery (initSubsystem<Rva0022C0CDSubsystem> news it), and
// Rva002E0427Dtor.cpp -- the rowed destructor of the same object -- names the
// three members: int at +0x0C, then two 0x14-byte hash members at +0x10 and
// +0x24 over the rowed SubsystemInterface base 0x001B4E63, with the same
// vtable 0x00BE7628 stored here. The member constructors are the rowed
// hash_map<int,Element> instantiations 0x0022D95A and 0x00224C76. Total size
// 0x38 matches the GameEngineInit view.

#include <hash_map>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<unsigned int>::operator()(unsigned int const &x,unsigned int const &y)const  { return x < y; } }
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void *& vector<void *, allocator<void *> >::operator[](unsigned int); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::begin(); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::end(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::size() const; }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end
// Declaration-only: retail keeps one _STL::max<unsigned int> (17-byte jae
// shape); this TU's flags would emit a private copy.
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}

#include "../../Include/Common/Rva0022D95AElement.h"

struct Rva00224C76Element
{
	char bytes[1];
	bool operator<(const Rva00224C76Element &) const;
	bool operator==(const Rva00224C76Element &) const;
};

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

namespace _STL {
template <> hash_map<int, Rva0022D95AElement>::hash_map();
template <> hash_map<int, Rva00224C76Element>::hash_map();
}

class Rva0022C0CDSubsystem : public SubsystemInterface
{
public:
	Rva0022C0CDSubsystem();
	virtual ~Rva0022C0CDSubsystem();

private:
	int m_0C; // +0x0C
	_STL::hash_map<int, Rva0022D95AElement> m_10; // +0x10
	_STL::hash_map<int, Rva00224C76Element> m_24; // +0x24
};

Rva0022C0CDSubsystem::Rva0022C0CDSubsystem()
	: m_0C(0)
{
}
