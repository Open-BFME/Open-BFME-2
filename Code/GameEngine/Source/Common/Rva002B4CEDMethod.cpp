// cl: /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva002B4CED@Rva002B4CED@@QAEXPAX@Z @0x002B4CED 84B: notify singleton then vector erase.
// Evidence: callers 0x002B4E7B 0x002BD9B4; rowed vector voidptr erase 0x001FF51F;
// pin 0x00212655 Rva00DFE1C8Host::rva00212655; global TheLivingWorldManager at VA 0x00DFE1C8.
#include <vector>
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva0021294A;
class LivingWorldManager; extern LivingWorldManager *TheLivingWorldManager;

class Rva00DFE1C8Host
{
public:
	void rva00212655(int value);
};

struct Rva002B4CEDItem
{
	int m_0;
	int m_4;
	int m_8;
};

class Rva002B4CED
{
	char m_pad[0xBC];
	_STL::vector<void *> m_vec;
public:
	void rva002B4CED(void *p);
	void rva002B753B();
};

void Rva002B4CED::rva002B4CED(void *p)
{
	if (!p)
		return;
	((Rva00DFE1C8Host *)TheLivingWorldManager)->rva00212655(((Rva002B4CEDItem *)p)->m_8);
	for (unsigned int i = 0; i < m_vec.size(); ++i) {
		if (m_vec[i] == p)
			m_vec.erase(m_vec.begin() + i);
	}
}
void Rva002B4CED::rva002B753B()
{
	_STL::vector<void *> *vec = &m_vec;
	for (unsigned int i = 0; i < vec->size(); ++i) {
		_ReadWriteBarrier();
		if (TheLivingWorldManager)
			((Rva00DFE1C8Host *)TheLivingWorldManager)->rva00212655(((Rva002B4CEDItem *)(*vec)[i])->m_8);
	}
	vec->erase(vec->begin(), vec->end());
}
