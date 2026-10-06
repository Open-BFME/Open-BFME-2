// cl: /O1
// stlport
// ?rva002B7B25@Rva002B7B25@@QAEXXZ retail 0x002B7B25 76 bytes.
// Chain lane: erase vector at +0x10c via rowed STL erase 0x0031BD55,
// then call just-landed Rva002E21D1::rva002E21D1 on each element of
// vector at +0x8c. Evidence: callee 0x002E21D1 rowed by own landing;
// same erase row and loop shape as 0x002E21D1; neighbours /O1.
#include <vector>

class Rva002E21D1
{
public:
	void rva002E21D1();
};

class Rva002B7B25
{
public:
	void rva002B7B25();
private:
	char m_pad[0x8c];
	_STL::vector<void *> m_8c;
	char m_pad98[0x10c - 0x98];
	_STL::vector<void *> m_10c;
};

// ?rva002B7B25@Rva002B7B25@@QAEXXZ
void Rva002B7B25::rva002B7B25()
{
	_STL::vector<void *> *v = &m_10c;
	v->erase(v->begin(), v->end());
	for (unsigned int i = 0; i < m_8c.size(); ++i) {
		((Rva002E21D1 *)m_8c[i])->rva002E21D1();
	}
}
