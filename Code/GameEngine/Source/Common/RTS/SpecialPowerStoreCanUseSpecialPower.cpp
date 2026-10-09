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
namespace _STL { void __cdecl free(void *block); }
#define free _STL::free
#include <vector>
#undef free

typedef bool Bool;

enum ScienceType { SCIENCE_INVALID = -1 };
typedef _STL::vector<ScienceType> ScienceVec;

class Overridable;
class SpecialPowerTemplate;

class Rva0029FCB4
{
public:
	ScienceVec rva0029FCB4();
};

class SpecialPowerModuleInterface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17();
	virtual Bool rva_slot18(int mode);
};

struct Rva004211A0Key;
class Rva004211A0Host
{
public:
	Bool rva004211A0(const Rva004211A0Key *key, const Overridable *power);
};
class Rva00421520;
extern Rva00421520 *g_00E03158;

class Player
{
public:
	bool hasAnyRequiredSciences(const ScienceVec &sciences) const;
	Bool rva002A9ED9(const SpecialPowerTemplate *power);
private:
	char m_pad000[0x318];
	char m_318[4];
};

class Rva00331682Holder
{
public:
	bool test(const void *key) const;
};

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
	if (g_00E03158)
		return reinterpret_cast<Rva004211A0Host *>(g_00E03158)->rva004211A0(
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

	if (!obj->getSpecialPowerModule(specialPowerTemplate)->rva_slot18(0))
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
