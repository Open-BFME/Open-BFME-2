// ?Rva00339B50_ParseSpecialAbilities@INI@@SAXPAV1@PAX1PBX@Z
// partial score=0.93 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /GX
// Rva00339B50_ParseSpecialAbilities (retail 0x00339B50, 74 bytes), in the INI
// parse run beside Rva00339AF1_ParseSciences. Each remaining token is looked
// up through the rowed SpecialPowerStore::findSpecialPowerTemplate
// (0x0029B6EB, AsciiString built in the outgoing argument slot) on
// TheSpecialPowerStore (VA 0x00E02D4C); a hit appends the id (+0x14) of its
// final override (rowed Overridable::friend_getFinalOverride 0x00288609) to
// the 4-byte vector at the store (push_back fold 0x004DFCB0). Serves the
// SpecialAbilities entry 0x00C3BE84. Callback name address-derived.

#include "ascii_string.h"

typedef unsigned int UnsignedInt;

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
};

class SpecialPowerTemplate : public Overridable
{
public:
	UnsignedInt getID() const { return m_id; }
private:
	unsigned char m_unreconstructed_00[0x14];
	UnsignedInt m_id;	// +0x14
};

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);
};

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

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps);
	static void Rva00339B50_ParseSpecialAbilities(INI *ini, void *instance, void *store, const void *userData);
};

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
			UnsignedInt id = ((const SpecialPowerTemplate *)power->friend_getFinalOverride())->getID();
			ids->push_back(id);
		}
	}
}
