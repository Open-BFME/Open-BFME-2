// cl: /O2 /MD

// ??_GModelArrayClass@HLodClass, the scalar deleting destructor for
// HLodClass::ModelArrayClass (retail 0x0019F4E0, 30 bytes). The class is
// declared locally only so its deleting destructor is emitted; the
// complete-destructor call resolves through that destructor's own row at
// 0x0019E580 and the operator delete call through the global row.
class HLodClass
{
public:
	class ModelArrayClass
	{
	public:
		__declspec(noinline) virtual ~ModelArrayClass();
	private:
		int m_famgen;
	};
};

HLodClass::ModelArrayClass::~ModelArrayClass()
{
	m_famgen = 0;
}

void famgenDelete(HLodClass::ModelArrayClass *p)
{
	delete p;
}
