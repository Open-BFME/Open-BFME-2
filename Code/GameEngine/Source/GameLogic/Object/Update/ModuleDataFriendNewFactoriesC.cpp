// cl: /O1 /GX /DNDEBUG /MD
// ?friend_newModuleData@FXListDie@@SAPAVModuleData@@PAVINI@@@Z @0x00253AB4 81B
// ?friend_newModuleData@DestroyDie@@SAPAVModuleData@@PAVINI@@@Z @0x00254E7D 81B
// ?friend_newModuleData@SquishCollide@@SAPAVModuleData@@PAVINI@@@Z @0x00254AAB 81B
// ?friend_newModuleData@BezierProjectileBehavior@@SAPAVModuleData@@PAVINI@@@Z @0x0024B183 84B
// ?friend_newModuleData@OpenContain@@SAPAVModuleData@@PAVINI@@@Z @0x0024B724 84B
// ?friend_newModuleData@HorseHordeContain@@SAPAVModuleData@@PAVINI@@@Z @0x002535C4 90B
// ?buildFieldParse@Rva00253510@@SAXAAVMultiIniFieldParse@@@Z @0x002534FE 18B
// ?buildFieldParse@Rva00253A78@@SAXAAVMultiIniFieldParse@@@Z @0x00253A92 34B
//
// More ModuleFactory data factories of the ModuleDataFriendNewFactories*.cpp
// shape: new the data class, and when an INI is given feed it to
// INI::initFromINIMultiProc with the class's parse proc. Each owner is the
// module name ModuleFactory::init registers the factory under (it pushes the
// name string, then the data factory, then the instance factory):
//
//   0x00253AB4 "FXListDie"            news 0x40, ctor 0x00253A78, proc 0x00253A92
//   0x00254E7D "DestroyDie"           news 0x38, ctor 0x00253510, proc 0x002534FE
//   0x00254AAB "SquishCollide"        news 8, the 9-byte vtable-only ctor rowed as
//              and "HordeMemberCollide" DelayedLuaEventUpdateModuleData, and the
//                                     shared empty `ret` stub 0x004B3FD0 as proc
//   0x0024B183 "BezierProjectileBehavior" news 0xC4, pinned base ctor 0x0045B4F1
//   0x0024B724 "OpenContain"          news 0x98, pinned base ctor 0x00465124
//   0x002535C4 "HorseHordeContain"    news 0x274: the rowed HordeContainModuleData
//              ctor, then one vptr store -- a derived data class with an inlined
//              constructor that keeps HordeContainModuleData's parse proc.
//
// The two procs are unrowed here: 0x002534FE adds the DieMuxData table
// (returned by the rowed Rva004CE52EGet) at +8; 0x00253A92 is that call inlined
// followed by FXListDie's own table 0x00BF08E0 -- a derived buildFieldParse that
// calls its base's first. The data classes keep the address names their rowed
// constructors carry.

class ModuleData;
class INI;
class MultiIniFieldParse;
struct FieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parse, unsigned int extraOffset);
};

int Rva004CE52EGet(void);

extern const FieldParse g_00BF08E0[];	// FXListDie's own table

// ---- the DieModuleData-shaped pair ------------------------------------------

class Rva00253510
{
public:
	Rva00253510();
	virtual ~Rva00253510();

	static void buildFieldParse(MultiIniFieldParse &parse)
	{
		parse.add(reinterpret_cast<const FieldParse *>(Rva004CE52EGet()), 8);
	}

private:
	unsigned char m_pad[0x38 - 4];
};

class Rva00253A78 : public Rva00253510
{
public:
	Rva00253A78();
	virtual ~Rva00253A78();

	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	unsigned char m_pad[0x40 - 0x38];
};

void Rva00253A78::buildFieldParse(MultiIniFieldParse &parse)
{
	Rva00253510::buildFieldParse(parse);
	parse.add(g_00BF08E0, 0);
}

class FXListDie
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

ModuleData *FXListDie::friend_newModuleData(INI *ini)
{
	Rva00253A78 *data = new Rva00253A78;
	if (ini)
		ini->initFromINIMultiProc(data, Rva00253A78::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class DestroyDie
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

ModuleData *DestroyDie::friend_newModuleData(INI *ini)
{
	Rva00253510 *data = new Rva00253510;
	if (ini)
		ini->initFromINIMultiProc(data, Rva00253510::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

// ---- the 8-byte data class ---------------------------------------------------

class DelayedLuaEventUpdateModuleData
{
public:
	DelayedLuaEventUpdateModuleData();
	virtual ~DelayedLuaEventUpdateModuleData();

	// Empty in retail; it resolves to the shared `ret` stub 0x004B3FD0.
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	int m_04;
};

class SquishCollide
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

ModuleData *SquishCollide::friend_newModuleData(INI *ini)
{
	DelayedLuaEventUpdateModuleData *data = new DelayedLuaEventUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DelayedLuaEventUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

// ---- data classes known by their pinned constructors ---------------------------

class Rva0045B4F1Base
{
public:
	Rva0045B4F1Base();
	virtual ~Rva0045B4F1Base();

private:
	unsigned char m_pad[0xC4 - 4];
};

class Rva0045B5E3Base
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class BezierProjectileBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

ModuleData *BezierProjectileBehavior::friend_newModuleData(INI *ini)
{
	Rva0045B4F1Base *data = new Rva0045B4F1Base;
	if (ini)
		ini->initFromINIMultiProc(data, Rva0045B5E3Base::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

class Rva00465124Base
{
public:
	Rva00465124Base();
	virtual ~Rva00465124Base();

private:
	unsigned char m_pad[0x98 - 4];
};

class OpenContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class OpenContain
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

ModuleData *OpenContain::friend_newModuleData(INI *ini)
{
	Rva00465124Base *data = new Rva00465124Base;
	if (ini)
		ini->initFromINIMultiProc(data, OpenContainModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

// ---- HorseHordeContain ---------------------------------------------------------

class HordeContainModuleData
{
public:
	HordeContainModuleData();
	virtual ~HordeContainModuleData();

	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	unsigned char m_pad[0x274 - 4];
};

class HorseHordeContainModuleData : public HordeContainModuleData
{
public:
	__forceinline HorseHordeContainModuleData() {}
	virtual ~HorseHordeContainModuleData();
};

class HorseHordeContain
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

ModuleData *HorseHordeContain::friend_newModuleData(INI *ini)
{
	HorseHordeContainModuleData *data = new HorseHordeContainModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, HorseHordeContainModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
