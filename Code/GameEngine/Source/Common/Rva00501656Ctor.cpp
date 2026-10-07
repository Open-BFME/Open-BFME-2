// ??0Rva00501656@@QAE@XZ
// partial score=0.93 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <set>
#include <vector>

struct PlayerAITypeEntry { char bytes[16]; };
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

Rva00501656::Rva00501656()
	: m_10(_STL::allocator<PlayerAITypeEntry>()),
	  m_1c(_STL::allocator<PlayerAITypeEntry>()),
	  m_28(_STL::allocator<PlayerAITypeEntry>()),
	  m_34(_STL::allocator<PlayerAITypeEntry>()),
	  m_40(_STL::allocator<PlayerAITypeEntry>())
{
}
