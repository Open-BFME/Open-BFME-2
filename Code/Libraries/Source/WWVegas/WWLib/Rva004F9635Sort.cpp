// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva004F9635@LivingWorldAutoResolveBattle@@QAEXPAURva004F9635Rec@@@Z @0x004F9635 35B.
// Native198B helper4F9658 and29B caller4F9E59 retain their receiver
// across this call. ECX is unused by this35B body but the callable ABI is
// thiscall; the previous stdcall owner and secondary alias are retired.
// Range sort: run the rowed _STL::sort 0x004F9565 over the record's pointer
// pair with a zeroed Rva004F9185Cmp. The template is declared but never
// defined here so the call binds to the rowed copy.
struct TreeHintRef00217D4C;

struct Rva004F9185Cmp
{
};

namespace _STL
{
template<class _RI, class _C>
void sort(_RI __first, _RI __last, _C __comp);
}

struct Rva004F9635Rec
{
	TreeHintRef00217D4C *m_0;
	TreeHintRef00217D4C *m_4;
};

class LivingWorldAutoResolveBattle {public: void rva004F9635(Rva004F9635Rec *);};

void LivingWorldAutoResolveBattle::rva004F9635(Rva004F9635Rec *r)
{
	Rva004F9185Cmp comp = {};
	_STL::sort(r->m_0, r->m_4, comp);
}
