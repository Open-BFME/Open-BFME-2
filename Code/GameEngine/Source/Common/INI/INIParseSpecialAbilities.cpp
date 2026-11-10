// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /GX
// Rva00339B50_ParseSpecialAbilities (retail 0x00339B50, 74 bytes), in the INI
// parse run beside parseScienceVector. Each remaining token is looked
// up through the rowed SpecialPowerStore::findSpecialPowerTemplate
// (0x0029B6EB, AsciiString built in the outgoing argument slot) on
// TheSpecialPowerStore (VA 0x00E02D4C); a hit appends the id (+0x14) of its
// final override (rowed Overridable::friend_getFinalOverride 0x00288609) to
// the 4-byte vector at the store (push_back fold 0x004DFCB0). Serves the
// SpecialAbilities entry 0x00C3BE84. Callback name address-derived.
// The final override is held in a named local: retail then reuses the
// AsciiString argument-address slot [ebp-4] for the pushed id.

#include "ascii_string.h"

typedef unsigned int UnsignedInt;

#include "../../../Include/Common/Overridable.h"
#include "../../../Include/Common/SpecialPower.h"

// getID's read without its own final-override walk: the caller already holds
// the final override, and the by-value return is the pushed temporary.
static inline UnsignedInt idOf(const SpecialPowerTemplate *final) { return final->m_id; }

#include "../../../Include/Common/SpecialPowerStore.h"

extern SpecialPowerStore *TheSpecialPowerStore;

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector;
template <> class vector<UnsignedInt, allocator<UnsignedInt> >
{
public:
	void push_back(const UnsignedInt &x);
private:
	UnsignedInt *m_start;
	UnsignedInt *m_finish;
	UnsignedInt *m_endOfStorage;
};
}

#include "../../../Include/Common/INI/INI.h"

// ?Rva00339B50_ParseSpecialAbilities@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva00339B50_ParseSpecialAbilities(INI *ini, void *, void *store, const void *)
{
	_STL::vector<UnsignedInt, _STL::allocator<UnsignedInt> > *ids = (_STL::vector<UnsignedInt, _STL::allocator<UnsignedInt> > *)store;
	const char *token;
	while ((token = ini->getNextTokenOrNull(0)) != 0)
	{
		const SpecialPowerTemplate *power = TheSpecialPowerStore->findSpecialPowerTemplate(AsciiString(token));
		if (power)
		{
			const SpecialPowerTemplate *final = power->getFO();
			ids->push_back(idOf(final));
		}
	}
}
