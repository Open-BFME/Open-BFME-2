// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00357DF8@Rva00357DF8@@QAEXABUBfmeSpecialPowerTimer8@@@Z @0x00357DF8 28B
// Retail inserts arg at list begin via rowed list<BfmeSpecialPowerTimer8>::insert 0x0036E30E.
// Evidence: same 28B double-deref begin shape as sibling 0x00357E14 (BfmeFloat4Record),
// callees rowed, callers 0x00358076/0x00357F5E wait on this row (LINK BONUS).
#include <list>

struct BfmeSpecialPowerTimer8
{
	unsigned int m_templateID;
	unsigned int m_readyFrame;
};

class Rva00357DF8
{
public:
	void rva00357DF8(const BfmeSpecialPowerTimer8 &rec);

private:
	_STL::list<BfmeSpecialPowerTimer8, _STL::allocator<BfmeSpecialPowerTimer8> > m_list; // +0
};

void Rva00357DF8::rva00357DF8(const BfmeSpecialPowerTimer8 &rec)
{
	m_list.insert(m_list.begin(), rec);
}
