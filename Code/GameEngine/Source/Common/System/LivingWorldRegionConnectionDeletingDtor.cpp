// cl: /O1 /MD

// ??_GLivingWorldRegionConnection@@UAEPAXI@Z, the scalar deleting
// destructor in vtable 0x00C36E48 slot 0 (retail 0x003F2A70, 28 bytes).
// The class is declared locally only so its deleting destructor is
// emitted; the complete-destructor call resolves through that
// destructor's own row at 0x003F2517, and the operator delete through
// the rowed 0x0002FD60.
class LivingWorldRegionConnection
{
public:
	__declspec(noinline) virtual ~LivingWorldRegionConnection();
private:
	int m_famgen;
};

LivingWorldRegionConnection::~LivingWorldRegionConnection()
{
	m_famgen = 0;
}

void famgenDelete(LivingWorldRegionConnection *p)
{
	delete p;
}
