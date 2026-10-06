// cl: /Ireference/shims/bfme2_ascii /EHsc /O1 /arch:SSE /G7
// ??1Rva005D073A@@UAE@XZ @ 0x005D073A 81B. The packet pin and deleting-dtor
// caller establish the destructor identity. Retail calls the rowed
// Rva002B7250::rva002B7250 on TheLivingWorldLogic+0x2C, passing the +8 base.
// The two vtable addresses and stores are target evidence; the two-base model
// and two-base model are structural inferences from those stores and the
// callee parameter. A parameter's ledger spelling does not establish a
// CreateAHeroData base: that class's verified table is 0x00C38D88, whereas
// this body restores 0x00C62A14. Shape follows neighboring MI dtors
// Rva005D06CB and Rva005D078B.
class CreateAHeroData; // retained only for the existing callee ABI spelling

class Rva005D073ASecondBase
{
public:
	virtual ~Rva005D073ASecondBase() {}
};

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *p);
};

class LivingWorldLogic
{
public:
	char m_pad[0x2C];
	Rva002B7250 m_holder2C;
};
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva005D073AFirstBase
{
public:
	virtual ~Rva005D073AFirstBase() {}
private:
	int m_04;
};

class Rva005D073A : public Rva005D073AFirstBase, public Rva005D073ASecondBase
{
public:
	virtual ~Rva005D073A();
};

Rva005D073A::~Rva005D073A()
{
	TheLivingWorldLogic->m_holder2C.rva002B7250(
		reinterpret_cast<CreateAHeroData *>(static_cast<Rva005D073ASecondBase *>(this)));
}
