// cl: /O1 /DNDEBUG /MD
//
// ?rva00262D40@AIUpdateInterface@@QAEXH@Z, retail 0x00262D40, 59 bytes.
// ?rva00262D7B@AIUpdateInterface@@UBE_NXZ, retail 0x00262D7B, 20 bytes.
// ?rva00262D8F@AIUpdateInterface@@UBE_NXZ, retail 0x00262D8F, 20 bytes.
// ?rva00262DA3@AIUpdateInterface@@UBE_NXZ, retail 0x00262DA3, 8 bytes.
// ?rva00262DAB@AIUpdateInterface@@UBE_NXZ, retail 0x00262DAB, 20 bytes.
// ?rva00262DBF@AIUpdateInterface@@UBE_NXZ, retail 0x00262DBF, 20 bytes.
// ?rva00262DD3@AIUpdateInterface@@QBE_NPBVObject@@@Z, retail 0x00262DD3, 81 bytes.
// ?rva00262EFF@AIUpdateInterface@@UAEXPAX00@Z, retail 0x00262EFF, 26 bytes.
// ?rva002632E1@AIUpdateInterface@@QAEXXZ, retail 0x002632E1, 13 bytes.
// ?rva002632EE@AIUpdateInterface@@QAEXXZ, retail 0x002632EE, 46 bytes. Not
// onObjectCreated (that is vtable slot 5, 0x002625C8): no vtable holds this
// body; 0x004501CD and 0x00492095 call it directly.
// ?rva0026336D@AIUpdateInterface@@QAEXXZ, retail 0x0026336D, 73 bytes.

struct Coord3D
{
	float x, y, z;
};

#define VM10(p) \
	virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

class Slot42Target
{
public:
	VM10(t0_)
	VM10(t1_)
	VM10(t2_)
	VM10(t3_)
	virtual void t40();
	virtual void t41();
	virtual void vslot42(int zero); // slot 42 -> offset 0xA8
};

class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_position; // +0x38
	float m_angle; // +0x44
	char m_pad48[0x74 - 0x48];
	unsigned int m_id; // +0x74
	char m_pad78[0x250 - 0x78];
	Slot42Target *m_ptr250; // +0x250
};

class State
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8();
	virtual bool pred9() const;
	virtual void v10();
	virtual bool pred11() const;
	virtual bool pred12() const;
	virtual bool pred13() const;

	int m_id; // +4
};

class StateMachine
{
public:
	virtual void sm0(); virtual void sm1(); virtual void sm2(); virtual void sm3();
	virtual void sm4(); virtual void sm5(); virtual void sm6();
	virtual void initDefaultState(); // slot 7 -> offset 0x1C
	virtual void setState(int state); // slot 8 -> offset 0x20
	virtual void sm9(); virtual void sm10(); virtual void sm11();
	virtual bool pred12() const;
	virtual void vslot13(); // slot 13 -> offset 0x34

	State *m_currentState; // +0x04
	char m_pad08[0x50 - 8];
	State *m_state50; // +0x50

	bool isInPred9() const { return m_currentState ? m_currentState->pred9() : true; }
	bool isInPred11() const { return m_currentState ? m_currentState->pred11() : true; }
	bool isInPred12() const { return m_currentState ? m_currentState->pred12() : true; }
	bool isInPred13() const { return m_currentState ? m_currentState->pred13() : true; }
};

class AIStateMachine : public StateMachine
{
public:
	void rva0035033F();
};

class AIUpdateInterfaceBase
{
public:
	VM10(v0_)
	VM10(v1_)
	VM10(v2_)
	VM10(v3_)
	VM10(v4_)
	VM10(v5_)
	VM10(v6_)
	virtual void v70();
	virtual void rva00262EFF(void *a, void *b, void *c); // slot 71
	virtual void v72(); virtual void v73(); virtual void v74();
	virtual void v75(); virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
	virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83(); virtual void v84();
	virtual void v85(); virtual void v86(); virtual void v87();
	virtual void vslot88(); // slot 88 -> offset 0x160
	virtual void v89();
	VM10(v9_)
	VM10(v10_)
	virtual void v110();
	virtual bool rva00262D8F() const; // slot 111
	virtual void v112();
	virtual bool rva00262DA3() const; // slot 113
	virtual bool rva00262DAB() const; // slot 114
	virtual bool rva00262DBF() const; // slot 115
	virtual bool rva00262D7B() const; // slot 116
	virtual void v117(); virtual void v118(); virtual void v119();
	VM10(v12_)
	VM10(v13_)
	VM10(v14_)
	virtual AIStateMachine *makeStateMachine(); // slot 150 -> offset 0x258
};

class AIUpdateInterface : public AIUpdateInterfaceBase
{
	char m_pad04[4];
	Object *m_obj; // +0x08
	char m_pad0C[0x30 - 0x0C];
	AIStateMachine *m_machine; // +0x30
	StateMachine *m_secondaryMachine; // +0x34
	StateMachine *m_tertiaryMachine; // +0x38
	char m_pad3C[0x4C - 0x3C];
	int m_guardMode; // +0x4C
	char m_pad50[0x54 - 0x50];
	int m_guardTargetType; // +0x54
	Coord3D m_guardPos; // +0x58
	char m_pad64[0x198 - 0x64];
	unsigned int m_field198; // +0x198
	unsigned int m_field19C; // +0x19C
	float m_guardAngle; // +0x1A0
public:
	void rva00262D40(int mode);
	virtual bool rva00262D7B() const;
	virtual bool rva00262D8F() const;
	virtual bool rva00262DA3() const;
	virtual bool rva00262DAB() const;
	virtual bool rva00262DBF() const;
	bool rva00262DD3(const Object *obj) const;
	virtual void rva00262EFF(void *a, void *b, void *c);
	void rva002632E1();
	void rva002632EE();
	void rva0026336D();
};

void AIUpdateInterface::rva00262D40(int mode)
{
	m_guardMode = mode;
	Object *obj = m_obj;
	if (!obj)
		return;
	if (m_guardTargetType != 3)
		m_guardTargetType = 0;
	m_guardPos = obj->m_position;
	m_guardAngle = obj->m_angle;
	m_machine->setState(16);
}

bool AIUpdateInterface::rva00262D7B() const
{
	return m_machine->isInPred13();
}

bool AIUpdateInterface::rva00262D8F() const
{
	return m_machine->isInPred9();
}

bool AIUpdateInterface::rva00262DA3() const
{
	return m_machine->pred12();
}

bool AIUpdateInterface::rva00262DAB() const
{
	return m_machine->isInPred11();
}

bool AIUpdateInterface::rva00262DBF() const
{
	return m_machine->isInPred12();
}

bool AIUpdateInterface::rva00262DD3(const Object *obj) const
{
	unsigned int id = obj->m_id;
	int state = m_machine->m_state50 ? m_machine->m_state50->m_id : 0xF423F;
	if (state == 0x1A || (m_machine->m_currentState ? m_machine->m_currentState->m_id : 0xF423F) == 0x1A)
	{
		if (m_field198 == id)
			return true;
		if (m_field19C == id)
			return true;
	}
	return false;
}

void AIUpdateInterface::rva00262EFF(void *a, void *b, void *c)
{
	Object *obj = m_obj;
	Slot42Target *target = obj->m_ptr250;
	if (target)
		target->vslot42(0);
}

void AIUpdateInterface::rva002632E1()
{
	if (m_machine)
		m_machine->rva0035033F();
}

void AIUpdateInterface::rva002632EE()
{
	if (!m_secondaryMachine)
	{
		vslot88();
		m_secondaryMachine = m_machine;
		m_machine = makeStateMachine();
		m_machine->initDefaultState();
	}
}

void AIUpdateInterface::rva0026336D()
{
	if (!m_tertiaryMachine)
	{
		if (m_machine->isInPred9())
			m_machine->vslot13();
		m_tertiaryMachine = m_machine;
		m_machine = makeStateMachine();
		m_machine->initDefaultState();
	}
}

