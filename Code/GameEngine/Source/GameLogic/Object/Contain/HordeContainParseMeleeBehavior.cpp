// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?parseMeleeBehavior@HordeContainModuleData@@SAXPAVINI@@PAX1PBX@Z, retail
// 0x004691B7..0x00469294 (221B), cdecl FieldParse proc.
//
// "MeleeBehavior" token of HordeContain: the name is looked up with
// INI::parseIndexList in the four-name table at VA 0x00DC9954 ("Swarm"
// "WaitForLeader" "HoldGround" "Amoeba"), the matching behaviour object is
// allocated into the store (Swarm and HoldGround are 4-byte objects whose
// inline constructors only store their vtables 0x00C448A8 / 0x00C4489C;
// WaitForLeader is the 0x10-byte Rva00584C42 and anything else the
// 0x70-byte Rva005876D5, both with rowed constructors), and the object's
// fields are then read from the INI through its slot 2 (buildFieldParse into
// a MultiIniFieldParse) and INI::initFromINIMulti.
//
// Evidence (target): HordeContainModuleData's FieldParse table entry at
// VA 0x00C45764 is { "MeleeBehavior", this proc, 0, 0x258 } (the module data
// vtable is ??_7HordeContainModuleData@@6B@ 0x008457B0); a second table built
// in code at 0x00425E20 also uses it. WorldBuilder twin 0x10B0330
// (callgraph lead) has the same switch with base vtable stores. Both 4-byte
// vtables follow the base vtable ??_7Rva00468A46@@6B@ (0x00844890) and share
// its slot 2. Callees: parseIndexList 0x0002EC4E / operator new 0x0002FDA0 /
// the two rowed constructors / MultiIniFieldParse ctor 0x0002BAA0 /
// initFromINIMulti 0x0002D7A8. The behaviour class names stay
// address-derived.

class MultiIniFieldParse
{
public:
	MultiIniFieldParse();
private:
	const void *m_fieldParse[16];
	unsigned m_extraOffset[16];
	int m_count;
};

class INI
{
public:
	static void parseIndexList(INI *ini, void *instance, void *store, const void *userData);
	void initFromINIMulti(void *what, const MultiIniFieldParse &parseTableList);
};

// Common base of the melee behaviours. Retail's base vtable is
// ??_7Rva00468A46@@6B@ (0x00844890: deleting destructor, one behaviour
// method, buildFieldParse); the view keeps its own name so it does not
// compete with that class's rowed single-slot view.
class Rva004691B7MeleeBehavior
{
public:
	virtual ~Rva004691B7MeleeBehavior();
	virtual void slot1();
	virtual void buildFieldParse(MultiIniFieldParse &p);
};

class Rva004691B7Swarm : public Rva004691B7MeleeBehavior
{
public:
	virtual void slot1();
};

class Rva004691B7HoldGround : public Rva004691B7MeleeBehavior
{
public:
	virtual void slot1();
};

class Rva00584C42 : public Rva004691B7MeleeBehavior
{
public:
	Rva00584C42();
private:
	char m_pad04[0x10 - 0x04];
};

class Rva005876D5 : public Rva004691B7MeleeBehavior
{
public:
	Rva005876D5();
private:
	char m_pad04[0x70 - 0x04];
};

extern const char *TheMeleeBehaviorNames[];

class HordeContainModuleData
{
public:
	static void parseMeleeBehavior(INI *ini, void *instance, void *store, const void *userData);
};

void HordeContainModuleData::parseMeleeBehavior(INI *ini, void *instance, void *store, const void *userData)
{
	int type;
	INI::parseIndexList(ini, 0, &type, TheMeleeBehaviorNames);
	Rva004691B7MeleeBehavior **behavior = (Rva004691B7MeleeBehavior **)store;
	switch (type)
	{
	case 0:
		*behavior = new Rva004691B7Swarm;
		break;
	case 1:
		*behavior = new Rva00584C42;
		break;
	case 2:
		*behavior = new Rva004691B7HoldGround;
		break;
	default:
		*behavior = new Rva005876D5;
		break;
	}
	MultiIniFieldParse p;
	(*behavior)->buildFieldParse(p);
	ini->initFromINIMulti(*behavior, p);
}
