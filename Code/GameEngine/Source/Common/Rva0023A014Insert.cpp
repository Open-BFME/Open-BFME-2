// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0023A014@Rva0023A014@@QAEXPBUBfmeStringRecord00239B46@@@Z @0x0023A014 26B: list insert end via rowed insert 0x00239E80. Evidence: caller at 0x0023ABB1 same record as 0x00239B46.
#include <list>
struct BfmeStringRecord00239B46 {
	unsigned char m_data[8];
};
class Rva0023A014
{
	_STL::list<BfmeStringRecord00239B46> m_list;
public:
	void rva0023A014(const BfmeStringRecord00239B46 *arg);
};
void Rva0023A014::rva0023A014(const BfmeStringRecord00239B46 *arg)
{
	m_list.insert(m_list.end(), *arg);
}
