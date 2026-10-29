// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport46
//
// One-instruction thunks and tiny leaves from unrowed .text gaps, each
// bounded by its neighbour's ret/padding and its own ret or tail jump.
// Every callee is a rowed body reached through its ledger spelling; owners
// are not recovered, so the views are address-named. Skeletons match matched
// twins (STLport _Destroy<QueuedDownload> 0x005BC6F5, GameInfo::endGame
// 0x003FF296, vector<pair<int,int>>::size 0x00626DE0).
#include <vector>

// --- STLport _Destroy(p): p->~T(), a tail jump to the rowed destructor.
//   0x0023E8A3 -> ??1Rva0023D377 0x0023D377
//   0x00282922 -> ??1Rva00200667 0x00200667 (ICF-shared with list dtors)
//   0x0032CD10 -> ??1Rva0032C2F7 0x0032C2F7
//   0x0032EA76 -> ??1Rva0032E83A 0x0032E83A
class Rva0023D377 { public: ~Rva0023D377(); };
class Rva00200667 { public: ~Rva00200667(); };
class Rva0032C2F7 { public: ~Rva0032C2F7(); };
class Rva0032E83A { public: ~Rva0032E83A(); };

template void _STL::_Destroy<Rva0023D377>(Rva0023D377 *);
template void _STL::_Destroy<Rva00200667>(Rva00200667 *);
template void _STL::_Destroy<Rva0032C2F7>(Rva0032C2F7 *);
template void _STL::_Destroy<Rva0032E83A>(Rva0032E83A *);

//   0x0021792B -> ??1GeometryRecord 0x0004F82B (GeometryInfoDtor.cpp)
//   0x002CFAB0 -> ??1Nugget@ModuleInfo 0x002CF51B (ThingTemplate.cpp)
struct GeometryRecord { ~GeometryRecord(); };
class ModuleInfo { public: struct Nugget { ~Nugget(); }; };
template void _STL::_Destroy<GeometryRecord>(GeometryRecord *);
template void _STL::_Destroy<ModuleInfo::Nugget>(ModuleInfo::Nugget *);

//   0x0021BA46 -> ??1BfmeStringRecord002199C8 0x0021A0C2
//   0x0021BA4F -> ??1BfmeStringRecord00219A68 0x0021A728
//   0x002B8373 -> ??1BfmeAssignRecord52 0x002B707E
//   0x002B837C -> ??1Member44 0x002B6B4C
//   0x002BC57F -> vector<Rva002BB6BE20Rec> dtor 0x002BBB57 (declared only)
class BfmeStringRecord002199C8 { public: ~BfmeStringRecord002199C8(); };
class BfmeStringRecord00219A68 { public: ~BfmeStringRecord00219A68(); };
class BfmeAssignRecord52 { public: ~BfmeAssignRecord52(); };
class Member44 { public: ~Member44(); };
struct Rva002BB6BE20Rec;
namespace _STL { template <> vector<Rva002BB6BE20Rec>::~vector(); }
template void _STL::_Destroy<BfmeStringRecord002199C8>(BfmeStringRecord002199C8 *);
template void _STL::_Destroy<BfmeStringRecord00219A68>(BfmeStringRecord00219A68 *);
template void _STL::_Destroy<BfmeAssignRecord52>(BfmeAssignRecord52 *);
template void _STL::_Destroy<Member44>(Member44 *);
template void _STL::_Destroy<_STL::vector<Rva002BB6BE20Rec> >(_STL::vector<Rva002BB6BE20Rec> *);

// --- 0x001F4A37 (9B, cdecl): whether the string argument is empty, a tail
// jump to the rowed StringBase<char>::isEmpty 0x00001E2F.
template <typename T> class StringBase
{
public:
	bool isEmpty() const;
private:
	T *m_data;
};
bool Rva001F4A37IsEmpty(const StringBase<char> &text)
{
	return text.isEmpty();
}

// --- 0x0026AFD1 (9B, cdecl): runs the rowed void member 0x00268B04 on the
// pointer argument.
class Rva00268B04 { public: void rva00268B04(); };
void Rva0026AFD1Run(Rva00268B04 *target)
{
	target->rva00268B04();
}

// --- 0x002C7515 (9B, cdecl): BitFlags<218>::any of the pointer argument,
// a tail jump to the rowed 0x002C7501.
template <int N> class BitFlags
{
public:
	bool any() const;
};
bool Rva002C7515Any(const BitFlags<218> *flags)
{
	return flags->any();
}

// --- 0x002E74AC (9B): sets the byte at +0x1E and clears the one at +0x1F
// (GameInfo::endGame's two-byte-store shape).
class Rva002E74ACFlags
{
public:
	void rva002E74AC();
private:
	char m_pad00[0x1E];
	bool m_1E;
	bool m_1F;
};
void Rva002E74ACFlags::rva002E74AC()
{
	m_1E = true;
	m_1F = false;
}

// --- 0x00329D1F (9B): vector::size() for a 128-byte element (sar 7);
// BfmePod128 is the ledger's 128-byte stand-in (SidesListDataChunks.cpp).
struct BfmePod128 { int a[32]; };
template _STL::vector<BfmePod128>::size_type _STL::vector<BfmePod128>::size() const;
