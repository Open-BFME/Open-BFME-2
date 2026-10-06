// cl: /MD /GX /DNDEBUG /Ireference/shims/bfme2_ascii
//
// Constructors of the skirmish-AI tactic prototypes: each builds its base
// with the tactic's name (a temporary AsciiString) and then clears its own
// fields. Class names are the address-derived ones of their rowed
// destructors; the bases are the four intermediate tactic bases whose
// destructors are rowed (Rva005DC73C ... Rva005DCC24) over the AITactic.cpp
// object Rva004ECECD. Sizes are the allocation sizes in their slot-9 creates.
#include "ascii_string.h"

class Rva004ECECD
{
public:
	virtual ~Rva004ECECD();
};

class Rva0015334F
{
public:
	__declspec(nothrow) Rva0015334F();
private:
	unsigned char m_data[0x10];
};

class Rva005DC73C : public Rva004ECECD
{
public:
	Rva005DC73C(const AsciiString &name);
	unsigned char m_pad04[0x58 - 4];
};

class Rva005DC87B : public Rva004ECECD
{
public:
	Rva005DC87B(const AsciiString &name);
	unsigned char m_pad04[0x5C - 4];
};

class Rva005DCB27 : public Rva004ECECD
{
public:
	Rva005DCB27(const AsciiString &name);
	unsigned char m_pad04[0x58 - 4];
};

class Rva005DCBE3 : public Rva004ECECD
{
public:
	Rva005DCBE3(const AsciiString &name, int kind);
	unsigned char m_pad04[0x58 - 4];
};

class Rva005DCC24 : public Rva004ECECD
{
public:
	Rva005DCC24(const AsciiString &name);
	unsigned char m_pad04[0x58 - 4];
};

// AIBasePenetrationTroopsTactic, 0x005A9988
class Rva005A990B : public Rva005DC73C
{
public:
	Rva005A990B();
};

Rva005A990B::Rva005A990B()
	: Rva005DC73C(AsciiString("AIBasePenetrationTroopsTactic"))
{
}

// SiegeGates, 0x005A9C1E
class Rva005A9ACD : public Rva005DC87B
{
public:
	Rva005A9ACD();
private:
	bool m_5C;
	unsigned char m_pad5D[3];
};

Rva005A9ACD::Rva005A9ACD()
	: Rva005DC87B(AsciiString("SiegeGates"))
{
	m_5C = false;
}

// SimpleSiege, 0x005A9D33
class Rva005A9CB3 : public Rva005DC87B
{
public:
	Rva005A9CB3();
private:
	int m_5C;
};

Rva005A9CB3::Rva005A9CB3()
	: Rva005DC87B(AsciiString("SimpleSiege")), m_5C(0)
{
}

// FlankAttack, 0x005AA23E
class Rva005AA55D : public Rva005DC73C
{
public:
	Rva005AA55D();
private:
	Rva0015334F *m_58;
};

Rva005AA55D::Rva005AA55D()
	: Rva005DC73C(AsciiString("FlankAttack"))
{
	m_58 = new Rva0015334F;
}

// SimpleDefense, 0x005AA7DF
class Rva005AA735 : public Rva005DCB27
{
public:
	Rva005AA735();
};

Rva005AA735::Rva005AA735()
	: Rva005DCB27(AsciiString("SimpleDefense"))
{
}

// SimpleExpansion, 0x005AA9DB
class Rva005AA860 : public Rva005DCBE3
{
public:
	Rva005AA860();
private:
	int m_58;
	int m_5C;
};

Rva005AA860::Rva005AA860()
	: Rva005DCBE3(AsciiString("SimpleExpansion"), 0), m_58(0), m_5C(0)
{
}

// AIRoamingDefenseTactic, 0x005AABC6
class Rva005AAB91 : public Rva005DCC24
{
public:
	Rva005AAB91();
private:
	bool m_58;
	unsigned char m_pad59[3];
};

Rva005AAB91::Rva005AAB91()
	: Rva005DCC24(AsciiString("AIRoamingDefenseTactic"))
{
	m_58 = false;
}

// AIStartWoTRBattleTactic, 0x005AB1B4
class Rva005AB125 : public Rva005DCC24
{
public:
	Rva005AB125();
};

Rva005AB125::Rva005AB125()
	: Rva005DCC24(AsciiString("AIStartWoTRBattleTactic"))
{
}

// AIRingHeroTactic, 0x005AC7EC
class Rva005AC7E1 : public Rva005DCC24
{
public:
	Rva005AC7E1();
private:
	int m_58;
	int m_5C;
	bool m_60;
	unsigned char m_pad61[3];
	int m_64;
};

Rva005AC7E1::Rva005AC7E1()
	: Rva005DCC24(AsciiString("AIRingHeroTactic"))
{
	m_58 = 0;
	m_5C = 0;
	m_60 = false;
	m_64 = 0;
}

// ReturnTheRing, 0x005AB3BE
class Rva005AB309 : public Rva005DCC24
{
public:
	Rva005AB309();
private:
	int m_58;
	int m_5C;
	int m_60;
	bool m_64;
	bool m_65;
	unsigned char m_pad66[2];
};

Rva005AB309::Rva005AB309()
	: Rva005DCC24(AsciiString("ReturnTheRing"))
{
	m_58 = 0;
	m_5C = 0;
	m_60 = 0;
	m_64 = false;
	m_65 = false;
}

// StructureCreep, 0x005AB91D (its destructor is 0x005AB7E5)
class Rva005AB7E5 : public Rva005DCC24
{
public:
	Rva005AB7E5();
private:
	int m_58;
	int m_5C;
	int m_60;
	int m_64;
	int m_68;
	int m_6C;
	int m_70;
	int m_74;
	bool m_78;
	bool m_79;
	unsigned char m_pad7A[2];
	int m_7C;
};

Rva005AB7E5::Rva005AB7E5()
	: Rva005DCC24(AsciiString("StructureCreep"))
{
	m_68 = -1;
	m_6C = -1;
	m_70 = -1;
	m_74 = -1;
	m_7C = -1;
	m_58 = 0;
	m_5C = 0;
	m_60 = 0;
	m_64 = 0;
	m_78 = false;
	m_79 = false;
}

// FarmKillSquad, 0x005ACF38: one squad in five farms (a d100 roll under 20)
int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class Rva005ACCE4 : public Rva005DCC24
{
public:
	Rva005ACCE4();
private:
	int m_58;
	int m_5C;
	bool m_60;
	unsigned char m_pad61[3];
};

Rva005ACCE4::Rva005ACCE4()
	: Rva005DCC24(AsciiString("FarmKillSquad"))
{
	m_58 = 0;
	m_5C = 0;
	m_60 = GetGameLogicRandomValue(1, 100,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITacticsGenerator\\TargetlessTactics\\AIFarmKillSquad.cpp",
		53) < 20;
}
