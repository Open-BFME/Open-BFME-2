// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// CreateAHeroClass copy ctor, retail 0x0021F876 125 bytes. Copy ctor
// copying five StringBase<char> plus vector<CreateAHeroSubClass> with EH states 0-4.
// Evidence: caller 0x0021FA36, rowed vector copy 0x0021F404, pin StringBase
// copy 0x000365F0 via public QAE spelling, unblocks 0x0021FA1A.
// The strings are AsciiString members with an inline copy ctor: retail forms
// each member address before pushing the source (the banked attempt called
// StringBase's copy ctor directly and pushed first).

#include "ascii_string.h"
#include <vector>



#include "../../Include/GameLogic/CreateAHeroManager.h"

namespace _STL
{
// Suppress duplicate vector<CreateAHeroSubClass> copy/dtor COMDATs; retail's copy is
// rowed at 0x0021F404 and dtor at 0x0021F7A7. The row below keeps calling
// them, so its bytes are unchanged. This also drops the transitive
// _Construct/_Destroy/__destroy_aux wrong copies this file emitted.
template <> vector<CreateAHeroManager::CreateAHeroSubClass, allocator<CreateAHeroManager::CreateAHeroSubClass> >::vector(const vector<CreateAHeroManager::CreateAHeroSubClass, allocator<CreateAHeroManager::CreateAHeroSubClass> > &);
template <> vector<CreateAHeroManager::CreateAHeroSubClass, allocator<CreateAHeroManager::CreateAHeroSubClass> >::~vector();
}

typedef CreateAHeroManager::CreateAHeroClass CreateAHeroClass;

class CreateAHeroManager::CreateAHeroClass
{
public:
	CreateAHeroClass(const CreateAHeroClass &other);
private:
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	AsciiString m_0C;
	AsciiString m_10;
	_STL::vector<CreateAHeroManager::CreateAHeroSubClass, _STL::allocator<CreateAHeroManager::CreateAHeroSubClass> > m_14;
};

CreateAHeroClass::CreateAHeroClass(const CreateAHeroClass &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
	, m_0C(other.m_0C)
	, m_10(other.m_10)
	, m_14(other.m_14)
{
}
