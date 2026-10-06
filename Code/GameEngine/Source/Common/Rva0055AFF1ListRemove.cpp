// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0055AFF1@Rva0055AFF1@@QAEXH@Z @ 0x0055AFF1, 46 bytes.
// Single-erase of int value from list at +0x1C. Evidence: retail walks nodes
// via [eax+8] comparing to [ebp+8] then calls rowed list<int>::erase
// 0x438539; caller 0x55B0FB passes its arg through.
#include <list>

class Rva0055AFF1
{
public:
	void rva0055AFF1(int value);
	char m_pad[0x1C];
	_STL::list<int, _STL::allocator<int> > m_list;
};

void Rva0055AFF1::rva0055AFF1(int value)
{
	_STL::list<int, _STL::allocator<int> >::iterator it = m_list.begin();
	while (it != m_list.end() && *it != value) {
		++it;
	}
	m_list.erase(it);
}
