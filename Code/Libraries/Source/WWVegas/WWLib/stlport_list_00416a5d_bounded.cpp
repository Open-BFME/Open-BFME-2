// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?Rva00416A5DPush@@YAXABUBfmeStringRecord00415F34@@@Z @0x00416A5D 57B
// Bounded queue: push BfmeStringRecord00415F34 via rowed push_back at
// 0x0041691F then if size>100 pop_front via rowed 0x00416939. List comes
// from GameSpyInfoInterface vslot 26 ([eax+0x68]); global TheGameSpyInfo at
// 0x00A02320 (?TheGameSpyInfo@@3PAVGameSpyInfoInterface@@A). Evidence: retail
// loop is inlined list::size (distance begin->end) counting to 0x64.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct BfmeStringRecord00415F34 { unsigned char m_data[24]; };
struct Rva00416939Pod { int a[3]; };

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
class GameSpyInfoInterface : public VSlots<26>
{
public:
	virtual _STL::list<BfmeStringRecord00415F34> *GetList(void);
};
extern GameSpyInfoInterface *TheGameSpyInfo;

void __cdecl Rva00416A5DPush(const BfmeStringRecord00415F34 &rec)
{
	_STL::list<BfmeStringRecord00415F34> *lst = TheGameSpyInfo->GetList();
	lst->push_back(rec);
	if (lst->size() > 100)
		((_STL::list<Rva00416939Pod> *)lst)->pop_front();
}
