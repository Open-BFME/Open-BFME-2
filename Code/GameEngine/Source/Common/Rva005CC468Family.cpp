// cl: /MD /EHsc
// Family 4: 0x005CC468, 0x005E9295, 0x005F5694, 0x005F594C, 0x005F5D25 (28 bytes each, total 140 bytes)
// Virtual slot 7 getters returning Rva005E1753Result from global singletons.

struct Rva005E1753Result
{
	void *m_ptr;
	Rva005E1753Result();
	Rva005E1753Result(const Rva005E1753Result &);
	~Rva005E1753Result();
};

class Rva005E1753Class
{
public:
	Rva005E1753Result GetResult();
};

// One storage owner per retail address. Keep the getter's established view
// only at the call, rather than introducing another datum with its class name.
extern unsigned int g_Va00E06620[5];
class Rva005E16DA;
extern Rva005E16DA g_cancelArmyMoveButton;
extern Rva005E16DA g_cancelArmyMemberMoveButton;
extern Rva005E16DA g_upgradeUnitButton;
extern Rva005E16DA g_disbandArmyMemberButton;

class Rva005CC37C
{
public:
	virtual Rva005E1753Result rva005CC468();
};

class Rva005E9295
{
public:
	virtual Rva005E1753Result rva005E9295();
};

class Rva005F5694
{
public:
	virtual Rva005E1753Result rva005F5694();
};

class Rva005F594C
{
public:
	virtual Rva005E1753Result rva005F594C();
};

class Rva005F5D25
{
public:
	virtual Rva005E1753Result rva005F5D25();
};

Rva005E1753Result Rva005CC37C::rva005CC468()
{
	return ((Rva005E1753Class *)&g_Va00E06620)->GetResult();
}

Rva005E1753Result Rva005E9295::rva005E9295()
{
	return ((Rva005E1753Class *)&g_cancelArmyMoveButton)->GetResult();
}

Rva005E1753Result Rva005F5694::rva005F5694()
{
	return ((Rva005E1753Class *)&g_cancelArmyMemberMoveButton)->GetResult();
}

Rva005E1753Result Rva005F594C::rva005F594C()
{
	return ((Rva005E1753Class *)&g_upgradeUnitButton)->GetResult();
}

Rva005E1753Result Rva005F5D25::rva005F5D25()
{
	return ((Rva005E1753Class *)&g_disbandArmyMemberButton)->GetResult();
}
