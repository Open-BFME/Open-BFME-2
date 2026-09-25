// cl: /O2 /MD

// ??_GGridCullSystemClass, the scalar deleting destructor in vtable 0xCEFCB0
// slot 0 (retail 0x0071B170).  The class is declared locally only so its
// deleting destructor is emitted; the complete-destructor call resolves
// through that destructor's own row at 0x0071AD00.
class GridCullSystemClass
{
public:
	__declspec(noinline) virtual ~GridCullSystemClass();
private:
	int m_famgen;
};

GridCullSystemClass::~GridCullSystemClass()
{
	m_famgen = 0;
}

void famgenDelete(GridCullSystemClass *p)
{
	delete p;
}
