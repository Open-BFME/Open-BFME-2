// cl: /O1
// ?rva00210EE1@Rva00210EE1@@QAEXXZ @0x00210EE1 16B
// Thunk that tail-calls LivingWorldEyeTower::rva003F9B5A (rowed 0x003F9B5A)
// on the member at +0x2c4 when non-null. Evidence: callers 0x005655D4,
// callee row LivingWorldEyeTowerProcessItems.cpp, no vtable.
class LivingWorldEyeTower
{
public:
	void rva003F9B5A();
};

class Rva00210EE1
{
	char m_pad[0x2c4];
	LivingWorldEyeTower *m_eye;
public:
	void rva00210EE1();
};

void Rva00210EE1::rva00210EE1()
{
	LivingWorldEyeTower *p = m_eye;
	if (!p)
		return;
	p->rva003F9B5A();
}
