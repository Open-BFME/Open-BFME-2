// cl: /MD /GX /DNDEBUG
//
// Slot 9 ("create": a fresh tactic of the same kind) of the skirmish-AI
// tactic prototypes the Rva00506909 generator pools hold. Every body is the
// same new-and-construct shape; only the size and the constructor differ.
// The classes keep the address-derived names of their rowed destructors
// (Rva005DC73CDerived.cpp and siblings); sizes are the allocation sizes,
// the ctors are pinned at their addresses, and the tactic names their ctors
// pass to the base are noted from the ctor bodies.

class Rva004ECECD
{
public:
	virtual ~Rva004ECECD();
	virtual Rva004ECECD *create();
};

#define TACTIC(name, size) \
	class name : public Rva004ECECD \
	{ \
	public: \
		name(); \
		virtual Rva004ECECD *create(); \
	private: \
		unsigned char m_data[size - sizeof(Rva004ECECD)]; \
	}; \
	Rva004ECECD *name::create() \
	{ \
		return new name; \
	}

// 0x005A9A57, ctor 0x005A9988 (AIBasePenetrationTroopsTactic), 0x58 bytes
TACTIC(Rva005A990B, 0x58)

// 0x005A9C71, ctor 0x005A9C1E (SiegeGates), 0x60 bytes
TACTIC(Rva005A9ACD, 0x60)

// 0x005A9DA2, ctor 0x005A9D33 (SimpleSiege), 0x60 bytes
TACTIC(Rva005A9CB3, 0x60)

// 0x005AA2A7, ctor 0x005AA23E (FlankAttack), 0x5C bytes
TACTIC(Rva005AA55D, 0x5C)

// 0x005AA82E, ctor 0x005AA7DF (SimpleDefense), 0x58 bytes
TACTIC(Rva005AA735, 0x58)

// 0x005AAAD6, ctor 0x005AA9DB (SimpleExpansion), 0x60 bytes
TACTIC(Rva005AA860, 0x60)

// 0x005AADA7, ctor 0x005AABC6 (AIRoamingDefenseTactic), 0x5C bytes
TACTIC(Rva005AAB91, 0x5C)

// 0x005AB203, ctor 0x005AB1B4 (AIStartWoTRBattleTactic), 0x58 bytes
TACTIC(Rva005AB125, 0x58)

// 0x005AC8F2, ctor 0x005AC7EC (AIRingHeroTactic), 0x68 bytes
TACTIC(Rva005AC7E1, 0x68)


// The clones that also carry one setting over from the prototype.
#define TACTIC_COPY(name, size, type, offset) \
	class name : public Rva004ECECD \
	{ \
	public: \
		name(); \
		virtual Rva004ECECD *create(); \
	private: \
		unsigned char m_pad[offset - sizeof(Rva004ECECD)]; \
		type m_copied; \
		unsigned char m_tail[size - offset - sizeof(type)]; \
	}; \
	Rva004ECECD *name::create() \
	{ \
		name *tactic = new name; \
		tactic->m_copied = m_copied; \
		return tactic; \
	}

// 0x005AB41F, ctor 0x005AB3BE (ReturnTheRing), 0x68 bytes, copies +0x5C
TACTIC_COPY(Rva005AB309, 0x68, int, 0x5C)

// 0x005AB9AF, ctor 0x005AB91D (StructureCreep), 0x80 bytes, copies +0x68
TACTIC_COPY(Rva005AB7E5, 0x80, int, 0x68)

// 0x005ACFAB, ctor 0x005ACF38 (FarmKillSquad), 0x64 bytes, copies the +0x60 flag
TACTIC_COPY(Rva005ACCE4, 0x64, bool, 0x60)
