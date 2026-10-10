// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0040B4F9@Rva0040B4F9@@QAEXXZ @ 0x0040B4F9 (53B). Sort two int vectors if non-empty via rowed sort.
// Evidence: retail sizes (finish-start)>>2 at +4/+8 and +10/+14 then calls rowed ??$sort@PAH 0x0040B4B6; caller 0x0040BD7B in 0x0040BC7C; neighbours share int sort flags.
#include <vector>
#include <algorithm>

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

class Rva0040B4F9
{
public:
	void rva0040B4F9();
private:
	int m_00;
	_STL::vector<int> m_04;
	_STL::vector<int> m_10;
};

void Rva0040B4F9::rva0040B4F9()
{
	if (m_04.size() > 0)
		_STL::sort(m_04.begin(), m_04.end());
	if (m_10.size() > 0)
		_STL::sort(m_10.begin(), m_10.end());
}
