// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva002E2F39@Rva002E2F39@@QAEXABURva002E2D10Record@@@Z 0x002E2F39 11: tail-forwards to vector push_back.
// Evidence: rowed push_back 0x002E2D10 plus caller 0x0037EB3C.
#include <vector>

struct Rva002E2D10Record { Rva002E2D10Record(); Rva002E2D10Record(const Rva002E2D10Record&); ~Rva002E2D10Record(); Rva002E2D10Record&operator=(const Rva002E2D10Record&); private: char bytes[216]; };

class Rva002E2F39
{
private:
	char m_pad[0x1A8];
	_STL::vector<Rva002E2D10Record> m_vec;
public:
	void rva002E2F39(const Rva002E2D10Record &x);
};

void Rva002E2F39::rva002E2F39(const Rva002E2D10Record &x)
{
	return m_vec.push_back(x);
}
