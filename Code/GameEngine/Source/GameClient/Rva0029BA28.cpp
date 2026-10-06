// cl: /DNDEBUG /MD /EHsc
// stlport
// ?rva0029BA28@Rva0029BA28@@QAEXH@Z @0x0029BA28 48B leaf called from 0x0029FEA5 list<int> at +0x18 erase first match via rowed erase 0x00438539
#include <list>

class Rva0029BA28
{
public:
	void rva0029BA28(int val);
private:
	char m_pad[24];
	_STL::list<int, _STL::allocator<int> > m_list;
};

void Rva0029BA28::rva0029BA28(int val)
{
	for (_STL::list<int, _STL::allocator<int> >::iterator it = m_list.begin(); it != m_list.end(); ++it) {
		if (*it == val) {
			m_list.erase(it);
			break;
		}
	}
}
