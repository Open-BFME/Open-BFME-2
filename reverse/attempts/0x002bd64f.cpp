// ?rva002BD64F@LivingWorldLogic@@QAEXH@Z
// partial score=1.0 date=2026-10-08
// cl: /MD /O1 /arch:SSE /G7
// ?rva002BD603@LivingWorldLogic@@QAEXH@Z at 0x002BD603, 76 bytes.
// The caller passes this as LivingWorldLogic*; the target accesses the owned-pointer slot at +0x178.
// The constructor signature comes from the target call to ??0Rva002B74DE@@QAE@PAVLivingWorldLogic@@H@Z.

class LivingWorldLogic;
class Rva002B9099 { public: void clear(); };

class Rva002B74DE
{
public:
	char m_unknown[0x28];
	Rva002B74DE(LivingWorldLogic *logic, int value);
	int Update();
};

class Rva002B90B3
{
public:
	void reset(Rva002B74DE *p);
	Rva002B74DE *m_ptr;
};

class LivingWorldLogic
{
public:
	char m_unknown[0x178];
	Rva002B90B3 m_rva002BD603OwnedPointer;

	void rva002BD603(int value);
	void rva002BD64F(int value);
};

void LivingWorldLogic::rva002BD603(int value)
{
	Rva002B74DE *p = new Rva002B74DE(this, value);
	m_rva002BD603OwnedPointer.reset(p);
}

// The existing opaque int constructor argument carries an address-sized word;
// caller 0x0020E4C8 supplies a LivingWorldBattle pointer. The original
// constructor type remains unresolved; no Battle layout is asserted here.
// Native 0x002BD64F..0x002BD6B0 RET4: allocate the same 0x28-byte
// resolver as the sibling; repeatedly call its Update until status 1 then clear.
void LivingWorldLogic::rva002BD64F(int value)
{
	Rva002B74DE *p = new Rva002B74DE(this, value);
	m_rva002BD603OwnedPointer.reset(p);
	while (m_rva002BD603OwnedPointer.m_ptr->Update() != 1) {}
	reinterpret_cast<Rva002B9099 *>(&m_rva002BD603OwnedPointer)->clear();
}
