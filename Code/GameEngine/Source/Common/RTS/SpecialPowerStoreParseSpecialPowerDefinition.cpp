// cl: /O1 /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Target3B15D6..3B17F3 (541B) SpecialPowerStore::parseSpecialPowerDefinition.
// Reference: Zero Hour Common/RTS/SpecialPower.cpp; clean BFME1 donor
// SpecialPowerStoreParseSpecialPowerDefinition.cpp at9cbfb551fe20dae985f91f2319d8997287b6a705.
// Target facts: DefaultSpecialPower/error strings; TheSpecialPowerStoreE02D4C;
// rowed find3B11D2/29B6EB ctor3B140E copy3B1337 set3B0FAC; template80B;
// store vectorC/id18; override next4/flag8; tableDC0E78 via existing getter3B0FA0.
// Donor semantics: named creation or final override; copy under existing guard;
// duplicate INIException; initialize from target field table. Full hot/EH exact.
// Typed pointer-vector ABI uses existing ModuleData provider4DFCB0. Binding
// pointer by reference preserves the target escaping local without a new pin.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <vector>

#include "../../../Include/Common/INI/FieldParse.h"
#include "string_base.h"

typedef unsigned int UnsignedInt;
typedef bool Bool;

struct FieldParse;

// Raised only while an override is being copied over its original.
extern unsigned char g_00E01EA8;			// 0x012ED611

#include "ascii_string.h"
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
inline const char *specialPowerNameText(const AsciiString &name) {
 const char *data=*(const char *const *)&name;
 return data ? data+8 : "";
}
// BFME keeps the load type at INI+0x08.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
#include "../../../Include/Common/INI/INI.h"

enum { INI_LOAD_CREATE_OVERRIDES = 2 };

typedef void (*INIFieldParseProc)( INI *ini, void *instance, void *store, const void *userData );

#include "../../../Include/Common/Overridable.h"
#include "../../../Include/Common/SpecialPower.h"

// Retail inlines Zero Hour's override walk and markAsOverride here (the
// out-of-line owners are 0x001E35DF and 0x00248D08).
inline Overridable *Overridable::friend_getFinalOverride()
{
	if (m_nextOverride)
		return m_nextOverride->friend_getFinalOverride();
	return this;
}
__forceinline void Overridable::markAsOverride()
{
	m_isOverride = true;
}

class Rva003B1101 { public:
 Rva003B1101(); Rva003B1101 &operator=(const Rva003B1101 &other);
 char data[0x80];
};
class Rva003B0FAC { public: void rva003B0FAC(const AsciiString &,int); };
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

// ZH SpecialPower.h is the semantic guide; target template size80/name10/id14.
class SpecialPowerStore : public SubsystemInterface
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate( AsciiString name );
	static void parseSpecialPowerDefinition( INI *ini );

protected:
	SpecialPowerTemplate *findSpecialPowerTemplatePrivate( AsciiString name );

	_STL::vector<const ModuleData *> m_specialPowerTemplates;	// target +0x0C
	UnsignedInt m_nextSpecialPowerID;				// target +0x18
};

extern SpecialPowerStore *TheSpecialPowerStore;

void Rva001DEE74Parse( INI *ini, void *instance, void *store, const void *userData );
void iniParseObjectFilter( INI *ini, void *instance, void *store, const void *userData );
#include "../../../Include/Common/Rva003B1017.h"

// The SpecialPowerNames index list (VA 0x00DC0B40).
extern const char *SpecialPowerNames[];

// .data name list VA 0x00DC0DD4, the Flags bit names. Retail puts no null
// after PATHABLE_ONLY: the list runs on through a copy of the attribute
// modifier names to the null at VA 0x00DC0E60. Only the table below refers
// to it.
const char *SpecialPowerFlagNames[] =
{
	"NEEDS_TARGET",
	"WATER_OK",
	"NEEDS_OBJECT_FILTER",
	"LIMIT_DISTANCE",
	"NO_FORBIDDEN_OBJECTS",
	"RESPECT_RECHARGE_TIME_DISCOUNT",
	"PATHABLE_ONLY",
	"ATTRIBUTE_NONE",
	"ARMOR",
	"DAMAGE_ADD",
	"DAMAGE_MULT",
	"RESIST_FEAR",
	"RESIST_TERROR",
	"EXPERIENCE",
	"RANGE",
	"SPEED",
	"CRUSH_DECELERATE",
	"RESIST_KNOCKBACK",
	"SPELL_DAMAGE",
	"RECHARGE_TIME",
	"PRODUCTION",
	"HEALTH",
	"HEALTH_MULT",
	"VISION",
	"BOUNTY_PERCENTAGE",
	"MINIMUM_CRUSH_VELOCITY",
	"AUTO_HEAL",
	"SHROUD_CLEARING",
	"RATE_OF_FIRE",
	"DAMAGE_STRUCTURE_BOUNTY_ADD",
	"CRUSHER_LEVEL",
	"COMMAND_POINT_BONUS",
	"CRUSHABLE_LEVEL",
	"CRUSHED_DECELERATE",
	"INVULNERABLE",
	NULL
};

// .data VA 0x00DC0E78: 22 16-byte entries and the zero terminator. The
// rowed getter 0x003B0FA0 returns this address; offsets are into the 0x80
// template.
const FieldParse SpecialPowerTemplate::m_specialPowerFieldParse[] =
{
	{ "Flags", INI::parseBitString32, SpecialPowerFlagNames, 0x18 },
	{ "ReloadTime", INI::parseDurationUnsignedInt, NULL, 0x20 },
	{ "RequiredSciences", INI::parseScienceVector, NULL, 0x24 },
	{ "LightPointCost", INI::parseInt, NULL, 0x30 },
	{ "InitiateSound", INI::parseAudioEventRTS, NULL, 0x34 },
	{ "InitiateAtLocationSound", INI::parseAudioEventRTS, NULL, 0x38 },
	{ "UnitSpecificSoundToUseAsInitiateIntendToDoVoice", INI::parseAsciiString, NULL, 0x3C },
	{ "UnitSpecificSoundToUseAsEnterStateInitiateIntendToDoVoice", INI::parseAsciiString, NULL, 0x40 },
	{ "EvaEventToPlayOnSuccess", Rva001DEE74Parse, NULL, 0x44 },
	{ "PublicTimer", INI::parseBool, NULL, 0x58 },
	{ "Enum", INI::parseIndexList, SpecialPowerNames, 0x1C },
	{ "DetectionTime", INI::parseDurationUnsignedInt, NULL, 0x48 },
	{ "SharedSyncedTimer", INI::parseBool, NULL, 0x59 },
	{ "ViewObjectDuration", INI::parseDurationUnsignedInt, NULL, 0x4C },
	{ "ViewObjectRange", INI::parseReal, NULL, 0x50 },
	{ "RadiusCursorRadius", INI::parseReal, NULL, 0x54 },
	{ "PalantirMovie", INI::parseAsciiString, NULL, 0x5C },
	{ "ObjectFilter", iniParseObjectFilter, NULL, 0x60 },
	{ "PreventActivationConditions", Rva003B1017::parseFromINI, NULL, 0x64 },
	{ "MaxCastRange", INI::parseReal, NULL, 0x74 },
	{ "ForbiddenObjectFilter", iniParseObjectFilter, NULL, 0x78 },
	{ "ForbiddenObjectRange", INI::parseReal, NULL, 0x7C },
	{ NULL, NULL, NULL, 0 }
};

void SpecialPowerStore::parseSpecialPowerDefinition( INI *ini )
{
	// read the name
	AsciiString name = ini->getNextToken();

	SpecialPowerTemplate* specialPower = TheSpecialPowerStore->findSpecialPowerTemplatePrivate( name );

	if ( ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES )
	{
		if (specialPower)
		{
			SpecialPowerTemplate* child = (SpecialPowerTemplate*)specialPower->friend_getFinalOverride();
			specialPower = (SpecialPowerTemplate *)new Rva003B1101;
			g_00E01EA8 = true;
			*(Rva003B1101 *)specialPower = *(Rva003B1101 *)child;
			g_00E01EA8 = false;
			child->setNextOverride(specialPower);
			specialPower->markAsOverride();
		}
		else
		{
			specialPower = (SpecialPowerTemplate *)new Rva003B1101;
			const SpecialPowerTemplate *defaultTemplate = TheSpecialPowerStore->findSpecialPowerTemplate( "DefaultSpecialPower" );
			if( defaultTemplate )
			{
				g_00E01EA8 = true;
				*(Rva003B1101 *)specialPower = *(const Rva003B1101 *)defaultTemplate;
				g_00E01EA8 = false;
			}
			((Rva003B0FAC *)specialPower)->rva003B0FAC(name, ++TheSpecialPowerStore->m_nextSpecialPowerID);
			specialPower->markAsOverride();
			TheSpecialPowerStore->m_specialPowerTemplates.push_back((const ModuleData *const &)specialPower);
		}
	}
	else
	{
		if (specialPower)
		{
			throw INIException( 3, "Special power '%s' already defined", specialPowerNameText(name) );
		}
		else
		{
			specialPower = (SpecialPowerTemplate *)new Rva003B1101;
			const SpecialPowerTemplate *defaultTemplate = TheSpecialPowerStore->findSpecialPowerTemplate( "DefaultSpecialPower" );
			if( defaultTemplate )
			{
				g_00E01EA8 = true;
				*(Rva003B1101 *)specialPower = *(const Rva003B1101 *)defaultTemplate;
				g_00E01EA8 = false;
			}
			((Rva003B0FAC *)specialPower)->rva003B0FAC(name, ++TheSpecialPowerStore->m_nextSpecialPowerID);
			TheSpecialPowerStore->m_specialPowerTemplates.push_back((const ModuleData *const &)specialPower);
		}
	}

	// parse the ini definition
	if (specialPower) ini->initFromINI( specialPower, specialPower->getFieldParse() );
}
