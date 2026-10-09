// ?shouldActivate@AISpellBookEnshroudingMist@@UAE_NPAVObject@@@Z
// partial score=0.93 date=2026-10-09
// cl: /O1 /MD /GX /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// AISpellBookEnshroudingMist::shouldActivate, retail 0x005D7B65 (160 bytes), slot 6 of
// the spell book's vftable. Name from the debug build's AISpellBookEnshroudingMist (wb-lead);
// the +0x28 base finder, the +0x520 template field and the 0x005EE8DD picker are retail's.
//
// Collect the caster's player's units in combat, take the first whose template
// (+0x04) has kind 1 at +0x520 and offer that unit's position (+0x38) to the AoE
// target picker.
#include <vector>

class Player;
class ModuleData;
struct Coord3D;
void __cdecl Rva00030830GameFree(void *);
// The native vector storage frees through GameMemory's free (0x00030830).
namespace _STL {
template<> inline _Vector_base<const ModuleData *, allocator<const ModuleData *> >::~_Vector_base() {if(_M_start)Rva00030830GameFree(_M_start);}
}

struct EnshroudingMistTemplate
{
	char m_pad000[0x520];
	int m_520;		// +0x520
};

struct EnshroudingMistUnit
{
	char m_pad00[4];
	EnshroudingMistTemplate *m_template;	// +0x04
	char m_pad08[0x38 - 8];
	float m_position[3];			// +0x38
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class AISpellBookBase
{
public:
	void findUnitInCombat(_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > *vec, Player *player);
};

class Rva005EE816
{
public:
	bool rva005EE8DD(const Coord3D *pos, Object *source);
};

class AISpellBookEnshroudingMist
{
public:
	virtual bool shouldActivate(Object *source);
	char m_pad04[0x28 - 4];
	AISpellBookBase m_base;		// +0x28
};

bool AISpellBookEnshroudingMist::shouldActivate(Object *source)
{
	_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > units;
	m_base.findUnitInCombat(&units, source->getControllingPlayer());
	for (_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> >::iterator it = units.begin(); it != units.end(); ++it) {
		if (((EnshroudingMistUnit *)*it)->m_template->m_520 == 1)
			return ((Rva005EE816 *)this)->rva005EE8DD((const Coord3D *)((EnshroudingMistUnit *)*it)->m_position, source);
	}
	return false;
}
