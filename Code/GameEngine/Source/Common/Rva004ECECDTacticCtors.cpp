// cl: /MD /GX /DNDEBUG /Ireference/shims/bfme2_ascii
//
// Constructors of the skirmish-AI tactic prototypes: each builds its base
// with the tactic's name (a temporary AsciiString) and then clears its own
// fields. Class names are the address-derived ones of their rowed
// destructors; the bases are the four intermediate tactic bases whose
// destructors are rowed (AITacticOffensive ... Rva005DCC24) over the AITactic.cpp
// object AITactic. Sizes are the allocation sizes in their slot-9 creates.
#include "ascii_string.h"

class AITactic
{
public:
	virtual ~AITactic();
};

class Rva0015334F
{
public:
	__declspec(nothrow) Rva0015334F();
private:
	unsigned char m_data[0x10];
};

class AITacticOffensive : public AITactic
{
public:
	AITacticOffensive(const AsciiString &name);
	unsigned char m_pad04[0x58 - 4];
};

class AITacticSiege : public AITactic
{
public:
	AITacticSiege(const AsciiString &name);
	unsigned char m_pad04[0x5C - 4];
};

class AITacticDefensive : public AITactic
{
public:
	AITacticDefensive(const AsciiString &name);
	unsigned char m_pad04[0x58 - 4];
};

class Rva005DCBE3 : public AITactic
{
public:
	Rva005DCBE3(const AsciiString &name, int kind);
	unsigned char m_pad04[0x58 - 4];
};

class Rva005DCC24 : public AITactic
{
public:
	Rva005DCC24(const AsciiString &name);
	unsigned char m_pad04[0x58 - 4];
};

// AIBasePenetrationTroopsTactic, 0x005A9988
class AIBasePenetrationTroopsTactic : public AITacticOffensive
{
public:
	AIBasePenetrationTroopsTactic();
};

AIBasePenetrationTroopsTactic::AIBasePenetrationTroopsTactic()
	: AITacticOffensive(AsciiString("AIBasePenetrationTroopsTactic"))
{
}

// SiegeGates, 0x005A9C1E
class AISiegeGatesTactic : public AITacticSiege
{
public:
	AISiegeGatesTactic();
private:
	bool m_5C;
	unsigned char m_pad5D[3];
};

AISiegeGatesTactic::AISiegeGatesTactic()
	: AITacticSiege(AsciiString("SiegeGates"))
{
	m_5C = false;
}

// SimpleSiege, 0x005A9D33
class AISimpleSiegeTactic : public AITacticSiege
{
public:
	AISimpleSiegeTactic();
private:
	int m_5C;
};

AISimpleSiegeTactic::AISimpleSiegeTactic()
	: AITacticSiege(AsciiString("SimpleSiege")), m_5C(0)
{
}

// FlankAttack, 0x005AA23E
class AIFlankAttackTactic : public AITacticOffensive
{
public:
	AIFlankAttackTactic();
private:
	Rva0015334F *m_58;
};

AIFlankAttackTactic::AIFlankAttackTactic()
	: AITacticOffensive(AsciiString("FlankAttack"))
{
	m_58 = new Rva0015334F;
}

// SimpleDefense, 0x005AA7DF
class Rva005AA735 : public AITacticDefensive
{
public:
	Rva005AA735();
};

Rva005AA735::Rva005AA735()
	: AITacticDefensive(AsciiString("SimpleDefense"))
{
}

// SimpleExpansion, 0x005AA9DB
class AISimpleExpansionTactic : public Rva005DCBE3
{
public:
	AISimpleExpansionTactic();
private:
	int m_58;
	int m_5C;
};

AISimpleExpansionTactic::AISimpleExpansionTactic()
	: Rva005DCBE3(AsciiString("SimpleExpansion"), 0), m_58(0), m_5C(0)
{
}

// AIRoamingDefenseTactic, 0x005AABC6
class AIRoamingDefenseTactic : public Rva005DCC24
{
public:
	AIRoamingDefenseTactic();
private:
	bool m_58;
	unsigned char m_pad59[3];
};

AIRoamingDefenseTactic::AIRoamingDefenseTactic()
	: Rva005DCC24(AsciiString("AIRoamingDefenseTactic"))
{
	m_58 = false;
}

// AIStartWoTRBattleTactic, 0x005AB1B4
class AIStartWoTRBattleTactic : public Rva005DCC24
{
public:
	AIStartWoTRBattleTactic();
};

AIStartWoTRBattleTactic::AIStartWoTRBattleTactic()
	: Rva005DCC24(AsciiString("AIStartWoTRBattleTactic"))
{
}

// AIRingHeroTactic, 0x005AC7EC
class AIRingHeroTactic : public Rva005DCC24
{
public:
	AIRingHeroTactic();
private:
	int m_58;
	int m_5C;
	bool m_60;
	unsigned char m_pad61[3];
	int m_64;
};

AIRingHeroTactic::AIRingHeroTactic()
	: Rva005DCC24(AsciiString("AIRingHeroTactic"))
{
	m_58 = 0;
	m_5C = 0;
	m_60 = false;
	m_64 = 0;
}

// ReturnTheRing, 0x005AB3BE
class AIReturnTheRingTactic : public Rva005DCC24
{
public:
	AIReturnTheRingTactic();
private:
	int m_58;
	int m_5C;
	int m_60;
	bool m_64;
	bool m_65;
	unsigned char m_pad66[2];
};

AIReturnTheRingTactic::AIReturnTheRingTactic()
	: Rva005DCC24(AsciiString("ReturnTheRing"))
{
	m_58 = 0;
	m_5C = 0;
	m_60 = 0;
	m_64 = false;
	m_65 = false;
}

// StructureCreep, 0x005AB91D (its destructor is 0x005AB7E5)
class AIStructureCreepTactic : public Rva005DCC24
{
public:
	AIStructureCreepTactic();
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

AIStructureCreepTactic::AIStructureCreepTactic()
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

class AIFarmKillSquad : public Rva005DCC24
{
public:
	AIFarmKillSquad();
private:
	int m_58;
	int m_5C;
	bool m_60;
	unsigned char m_pad61[3];
};

AIFarmKillSquad::AIFarmKillSquad()
	: Rva005DCC24(AsciiString("FarmKillSquad"))
{
	m_58 = 0;
	m_5C = 0;
	m_60 = GetGameLogicRandomValue(1, 100,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITacticsGenerator\\TargetlessTactics\\AIFarmKillSquad.cpp",
		53) < 20;
}
