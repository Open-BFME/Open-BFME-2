// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// SpecialPowerStore::canUseSpecialPower, retail 0x003B1244 (227 bytes), and
// the Player gate it calls, 0x002A9ED9 (31 bytes).
//
// Identity: the existing pin names 0x003B1244. Donor: Zero Hour
// SpecialPower.cpp canUseSpecialPower (null checks, then the object must own a
// module for the power, then the controlling player must have the required
// science). BFME2 target facts: the module must also answer slot 0x48 with
// argument 0; the required sciences come back as a vector (0x0029FCB4) tested
// with Player::hasAnyRequiredSciences when the player exists and the vector is
// non-empty; the player then gates the template through 0x002A9ED9; finally
// the power is refused when the object's +0x94 holder reports the template's
// +0x64 key. 0x002A9ED9 forwards the player's +0x318 record and the template
// to the 0x00E03158 manager (0x004211A0) when that manager exists, else allows.

#include <stdlib.h>
#include <vector>

typedef bool Bool;

enum ScienceType { SCIENCE_INVALID = -1 };
// Native scalar-vector cleanup uses the rowed game-memory free wrapper.
// Keep the first compatible ScienceType destructor's allocator identity.
void __cdecl Rva00030830GameFree(void *);
namespace _STL {
template <> inline _Vector_base<ScienceType, allocator<ScienceType> >::~_Vector_base()
{ if (_M_start) Rva00030830GameFree(_M_start); }
}

typedef _STL::vector<ScienceType> ScienceVec;

class Overridable;
class SpecialPowerTemplate;

class Rva0029FCB4
{
public:
	ScienceVec rva0029FCB4();
};

#include "../../../Include/GameLogic/Module/SpecialPowerModule.h"

struct Rva004211A0Key;
class Rva004211A0Host
{
public:
	Bool rva004211A0(const Rva004211A0Key *key, const Overridable *power);
};
class Rva00421520;
extern Rva00421520 *TheLightPointSystem;

class Player
{
public:
	bool hasAnyRequiredSciences(const ScienceVec &sciences) const;
	Bool rva002A9ED9(const SpecialPowerTemplate *power);
private:
	char m_pad000[0x318];
	char m_318[4];
};

#include "../../../Include/GameLogic/Module/Rva00331682Holder.h"

class Object
{
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *power) const;
	Player *getControllingPlayer() const;
	const Rva00331682Holder *getDisabledPowers() const
	{
		return reinterpret_cast<const Rva00331682Holder *>(reinterpret_cast<const char *>(this) + 0x94);
	}
};

class SpecialPowerStore
{
public:
	Bool canUseSpecialPower(Object *obj, const SpecialPowerTemplate *specialPowerTemplate);
};

// ?rva002A9ED9@Player@@QAE_NPBVSpecialPowerTemplate@@@Z
Bool Player::rva002A9ED9(const SpecialPowerTemplate *power)
{
	if (TheLightPointSystem)
		return reinterpret_cast<Rva004211A0Host *>(TheLightPointSystem)->rva004211A0(
			reinterpret_cast<const Rva004211A0Key *>(m_318),
			reinterpret_cast<const Overridable *>(power));
	return true;
}

// ?canUseSpecialPower@SpecialPowerStore@@QAE_NPAVObject@@PBVSpecialPowerTemplate@@@Z
Bool SpecialPowerStore::canUseSpecialPower(Object *obj, const SpecialPowerTemplate *specialPowerTemplate)
{
	if (obj == 0 || specialPowerTemplate == 0)
		return false;

	if (obj->getSpecialPowerModule(specialPowerTemplate) == 0)
		return false;

	if (!obj->getSpecialPowerModule(specialPowerTemplate)->rva0049466D(0))
		return false;

	Player *player = obj->getControllingPlayer();
	ScienceVec sciences = ((Rva0029FCB4 *)specialPowerTemplate)->rva0029FCB4();
	if (player && !sciences.empty() && !player->hasAnyRequiredSciences(sciences))
		return false;

	if (!obj->getControllingPlayer()->rva002A9ED9(specialPowerTemplate))
		return false;

	if (obj->getDisabledPowers()->test(reinterpret_cast<const char *>(specialPowerTemplate) + 0x64))
		return false;

	return true;
}
