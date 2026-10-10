// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?Rva00417FF0Parse@@YAXPAVINI@@PAX1PBX@Z @0x00417FF0 115B.
// Chain lane: parses BonusForLevel record via INI::initFromINI with table
// g_00C3A658 into Rva00417AB8 24B local, inserts pair<int,BfmePod24> into
// the map at the store arg via rowed insert_unique 0x00417D57, and throws
// INIException on a duplicate MinLevel.
// Evidence: caller init 0x00417AB8 (rowed), table VA 0x0083A658, format
// literal 0x00C3A6C8, ThrowInfo 0x00CFE2FC, rowed INIException filler
// 0x2F681 and _CxxThrowException 0x629094.
//
// The exception is raised through the rowed filler and __CxxThrowException
// directly, not through a throwing constructor. Retail pushes four stack
// arguments to 0x2F681 (msgbuf, argCount, format literal, the MinLevel
// value), pops all sixteen bytes, then pushes the ThrowInfo and the msgbuf
// for 0x629094. Calling the varargs INIException ctor instead makes MSVC
// 7.1 materialise a std::string for the format, which costs the extra
// `mov al,[eax]` / `mov [ebp-1],al` spill and grows the frame from 0x3c to
// 0x40. This is the same fill-then-throw shape already landed in
// Code/GameEngine/Source/Common/Rva00426D14Parse.cpp.
#include <map>

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

struct FieldParse;
extern const FieldParse g_00C3A658[];

class INI
{
public:
	void initFromINI(void *what, const FieldParse *table);
};

class Rva00417AB8
{
public:
	Rva00417AB8 *rva00417AB8();
};

struct BfmePod24
{
	int a[6];
};

// Retail's exception object lives at [ebp-0x8] and is handed to the filler by
// address; the shape below is what produces that 8-byte local.
struct INIExceptionBuf00417FF0
{
	char *mMsg;
	int m_argCount;
};

// Retail emits `add esp,0x10` immediately after this call, so the filler pops
// its own four arguments (__stdcall, @16); declaring it cdecl makes the caller
// clean 0x18 instead and shifts every later byte.
extern "C" void __stdcall rva002f681_fill(void *e, int argCount, const char *format, ...);

// Every matched sibling that throws (Rva00426D14Parse, Rva00413D58Parse,
// Rva003F9258Siblings, Rva004FD77CParse) declares the helper exactly this
// way; the resolver maps the extern "C" __CxxThrowException@8 name onto the
// pinned retail 0x00629094. It is stdcall, so retail emits no caller cleanup
// after this call.
struct _s__ThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);

// Format literal at VA 0x00C3A6C8 and TI1 INIException ThrowInfo at 0x00CFE2FC.
// Held as extern const so the pushes stay 5-byte immediates.
extern const char g_00C3A6C8[];
extern const int g_00CFE2FC;

void __cdecl Rva00417FF0Parse(INI *ini, void *, void *store, const void *)
{
	BfmePod24 tmp;
	((Rva00417AB8 *)&tmp)->rva00417AB8();
	ini->initFromINI(&tmp, g_00C3A658);
	_STL::pair<_STL::_Rb_tree<int, _STL::pair<const int, BfmePod24>, _STL::_Select1st<_STL::pair<const int, BfmePod24> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod24> > >::iterator, bool> res =
		((_STL::map<int, BfmePod24> *)store)->insert(_STL::pair<const int, BfmePod24>(tmp.a[0], tmp));
	if (!res.second) {
		INIExceptionBuf00417FF0 e;
		rva002f681_fill(&e, 1, g_00C3A6C8, tmp.a[0]);
		_CxxThrowException(&e, (const _s__ThrowInfo *)&g_00CFE2FC); __assume(0);
	}
}
