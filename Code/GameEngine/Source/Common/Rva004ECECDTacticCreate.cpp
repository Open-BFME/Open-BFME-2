// cl: /MD /GX /DNDEBUG
//
// Slot 9 ("create": a fresh tactic of the same kind) of the skirmish-AI
// tactic prototypes the Rva00506909 generator pools hold. Every body is the
// same new-and-construct shape; only the size and the constructor differ.
// The classes keep the address-derived names of their rowed destructors
// (Rva005DC73CDerived.cpp and siblings); sizes are the allocation sizes,
// the ctors are pinned at their addresses, and the tactic names their ctors
// pass to the base are noted from the ctor bodies.

class AITactic
{
public:
	virtual ~AITactic();
	virtual AITactic *create();
};

#define TACTIC(name, size) \
	class name : public AITactic \
	{ \
	public: \
		name(); \
		virtual AITactic *create(); \
	private: \
		unsigned char m_data[size - sizeof(AITactic)]; \
	}; \
	AITactic *name::create() \
	{ \
		return new name; \
	}

// 0x005A9A57, ctor 0x005A9988 (AIBasePenetrationTroopsTactic), 0x58 bytes
TACTIC(AIBasePenetrationTroopsTactic, 0x58)

// 0x005A9C71, ctor 0x005A9C1E (SiegeGates), 0x60 bytes
TACTIC(AISiegeGatesTactic, 0x60)

// 0x005A9DA2, ctor 0x005A9D33 (SimpleSiege), 0x60 bytes
TACTIC(AISimpleSiegeTactic, 0x60)

// 0x005AA2A7, ctor 0x005AA23E (FlankAttack), 0x5C bytes
TACTIC(AIFlankAttackTactic, 0x5C)

// 0x005AA82E, ctor 0x005AA7DF (SimpleDefense), 0x58 bytes
TACTIC(Rva005AA735, 0x58)

// 0x005AAAD6, ctor 0x005AA9DB (SimpleExpansion), 0x60 bytes
TACTIC(AISimpleExpansionTactic, 0x60)

// 0x005AADA7, ctor 0x005AABC6 (AIRoamingDefenseTactic), 0x5C bytes
TACTIC(AIRoamingDefenseTactic, 0x5C)

// 0x005AB203, ctor 0x005AB1B4 (AIStartWoTRBattleTactic), 0x58 bytes
TACTIC(AIStartWoTRBattleTactic, 0x58)

// 0x005AC8F2, ctor 0x005AC7EC (AIRingHeroTactic), 0x68 bytes
TACTIC(AIRingHeroTactic, 0x68)


// The clones that also carry one setting over from the prototype.
#define TACTIC_COPY(name, size, type, offset) \
	class name : public AITactic \
	{ \
	public: \
		name(); \
		virtual AITactic *create(); \
	private: \
		unsigned char m_pad[offset - sizeof(AITactic)]; \
		type m_copied; \
		unsigned char m_tail[size - offset - sizeof(type)]; \
	}; \
	AITactic *name::create() \
	{ \
		name *tactic = new name; \
		tactic->m_copied = m_copied; \
		return tactic; \
	}

// 0x005AB41F, ctor 0x005AB3BE (ReturnTheRing), 0x68 bytes, copies +0x5C
TACTIC_COPY(AIReturnTheRingTactic, 0x68, int, 0x5C)

// 0x005AB9AF, ctor 0x005AB91D (StructureCreep), 0x80 bytes, copies +0x68
TACTIC_COPY(AIStructureCreepTactic, 0x80, int, 0x68)

// 0x005ACFAB, ctor 0x005ACF38 (FarmKillSquad), 0x64 bytes, copies the +0x60 flag
TACTIC_COPY(AIFarmKillSquad, 0x64, bool, 0x60)
