// cl: /O1
// stlport
// ?rva002B7BBB@Rva002B5B55@@QAEXXZ @0x002B7BBB 64B: iterate vector at +0x118 via sibling rva002B5B55 then erase
// Evidence: same erase row 0x0031BD55 and loop shape as Rva002B7B25Clear plus Rva002B5B55Finish donor.
#include <vector>

class Rva002B5B55Arg;

class Rva002B5B55
{
public:
	void rva002B5B55(Rva002B5B55Arg *arg);
	void rva002B7BBB();
private:
	char m_pad[0x118];
	_STL::vector<void *> m_118;
};

void Rva002B5B55::rva002B7BBB()
{
	_STL::vector<void *> *v = &m_118;
	for (unsigned int i = 0; i < m_118.size(); ++i)
		rva002B5B55((Rva002B5B55Arg *)m_118[i]);
	v->erase(v->begin(), v->end());
}
