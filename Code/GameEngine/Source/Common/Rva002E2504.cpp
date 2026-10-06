// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002E2504@Rva002E2504@@QAE_NPAVRva00318C32Ret@@PAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z 0x002E2504 116
// Evidence: pin 0x00318C32 plus rowed reserve 0x002B712E plus rowed push_back
// 0x004DFCB0; callers 0x002B6536 0x002E2DE0.
#include <vector>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class ModuleData;
class Rva00318C32Ret;
class Rva00318C79Owner
{
public:
	Rva00318C32Ret *rva00318C32();
};

class Rva002E2504
{
private:
	char m_pad[0x1B8];
	const ModuleData **m_start;
	const ModuleData **m_finish;
	unsigned int size() const { return m_finish - m_start; }
public:
	bool rva002E2504(Rva00318C32Ret *a, _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > *b);
};

bool Rva002E2504::rva002E2504(Rva00318C32Ret *a, _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > *b)
{
	bool found = false;
	for (unsigned int i = 0; i < size(); ++i)
	{
		_ReadWriteBarrier();
		Rva00318C79Owner *o = (Rva00318C79Owner *)m_start[i];
		if (o->rva00318C32() == a)
		{
			b->reserve(4);
			b->push_back(m_start[i]);
			found = true;
		}
	}
	return found;
}
