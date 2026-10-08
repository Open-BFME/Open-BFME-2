// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva0057718D@Rva0057718D@@QAEXXZ, retail 0x0057718D..0x005771F4 (103
// bytes): the update the rowed slot 0x005772FA tail-calls on its +0x08
// object. It runs the +0x0C object's rowed 0x0057539C, the +0x04 checklist
// (rowed 0x005CCEB6), the +0x18 StrategicInGameUI::ManualPhaseEnder (rowed
// Update), the +0x28 notifier (rowed 0x005CD708) and, when set, the +0x14
// object's empty hook (the rowed 0x000B3FD0 fold). Once -- the +0x38 flag --
// when TheLivingWorldLogic's pinned 0x002B5EB5 test holds, the object reached
// through the +0x0C object's +0x04 field (two rowed pointer-chase getters)
// has its slot 2 run.

class Rva00575383
{
public:
	void rva0057539C();
};

class Rva005CCEB6
{
public:
	void rva005CCEB6();
};

namespace StrategicInGameUI
{
class ManualPhaseEnder
{
public:
	void Update();
};
}

class Rva005CD708
{
public:
	void rva005CD708();
};

class Rva000B3FD0
{
public:
	void rva000B3FD0();
};

class Rva002B5EB5
{
public:
	bool rva002B5EB5();
};

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva00328A83PtrChaseField
{
public:
	int get() const;
};

class Rva0042D6AEPtrChaseField
{
public:
	int get() const;
};

class Rva0057718DTarget
{
public:
	virtual void t0();
	virtual void t1();
	virtual void t2();
};

struct Rva0057718DSource
{
	unsigned char m_pad00[0x04];
	Rva00328A83PtrChaseField *m_field04;	// +0x04
};

class Rva0057718D
{
public:
	void rva0057718D();
private:
	unsigned char m_pad00[0x04];
	Rva005CCEB6 m_checklist04;				// +0x04
	unsigned char m_pad05[0x0C - 0x05];
	Rva0057718DSource *m_source0C;			// +0x0C
	unsigned char m_pad10[0x14 - 0x10];
	Rva000B3FD0 *m_hook14;					// +0x14
	StrategicInGameUI::ManualPhaseEnder m_phaseEnder18;	// +0x18
	unsigned char m_pad19[0x28 - 0x19];
	Rva005CD708 m_notifier28;				// +0x28
	unsigned char m_pad29[0x38 - 0x29];
	bool m_done38;							// +0x38
};

void Rva0057718D::rva0057718D()
{
	reinterpret_cast<Rva00575383 *>(m_source0C)->rva0057539C();
	m_checklist04.rva005CCEB6();
	m_phaseEnder18.Update();
	m_notifier28.rva005CD708();
	if (m_hook14)
		m_hook14->rva000B3FD0();
	if (!m_done38 && reinterpret_cast<Rva002B5EB5 *>(TheLivingWorldLogic)->rva002B5EB5())
	{
		const Rva0042D6AEPtrChaseField *field = (const Rva0042D6AEPtrChaseField *)m_source0C->m_field04->get();
		Rva0057718DTarget *target = (Rva0057718DTarget *)field->get();
		if (target)
		{
			target->t2();
			m_done38 = true;
		}
	}
}
