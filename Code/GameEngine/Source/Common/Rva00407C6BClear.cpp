// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva00407C6B@Rva00407C6B@@QAEXXZ retail 0x00407C6B 20B
// Evidence: unlock lane; two Rb_tree int-int clears via twin pin clear 0x0021A917 (twin of dup); caller 0x00408C11; prev our Object 23B same /O1.
#include <map>

class Rva00407C6B
{
public:
	void rva00407C6B();
private:
	char m_pad[0x14];
	_STL::map<int, int> m_a;
	_STL::map<int, int> m_b;
};

void Rva00407C6B::rva00407C6B()
{
	m_a.clear();
	m_b.clear();
}
