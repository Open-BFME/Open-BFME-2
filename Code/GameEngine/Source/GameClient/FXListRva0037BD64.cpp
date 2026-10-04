// cl: /Ireference/shims/bfmelist /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva0037BD64@FXList@@QAEHXZ @0x0037BD64 29B: pop front int from list at +4 else 0; calls rowed list<int>::pop_front at 0x0037BCF9.
// Evidence: caller 0x0037D0A7 passes FXList* at +0xC both to FXList::addFXNugget and here; retail add ecx 4 empty-check cmp [eax] eax front at +8 pop_front.
#include <list>
class FXList
{
public:
	int rva0037BD64();
private:
	int m_unused00;
	_STL::list<int> m_nuggets;
};
int FXList::rva0037BD64()
{
	if (m_nuggets.empty())
		return 0;
	int v = m_nuggets.front();
	m_nuggets.pop_front();
	return v;
}
