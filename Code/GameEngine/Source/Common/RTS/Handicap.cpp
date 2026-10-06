// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// Handicap accessor.
// Near-miss donor from Open-BFME-1 RTS/Handicap.cpp
// (?getHandicap@Handicap@@QBEMW4HandicapType@1@PBVThingTemplate@@@Z @0x000C8410):
// retail ThingTemplate flag byte is at +0x108 (not +0xC8).

typedef float Real;

class ThingTemplate
{
public:
	unsigned char m_beforeKindFlags[0x108];
	unsigned char m_otherKindFlags : 7;
	unsigned char m_isBuilding : 1;
};

class Handicap
{
public:
	enum HandicapType
	{
		BUILDCOST,
		BUILDTIME
	};

	Real getHandicap(HandicapType type, const ThingTemplate *thingTemplate) const;

private:
	enum ThingType
	{
		GENERIC,
		BUILDINGS
	};

	Real m_handicaps[2][2];
};

// ?getHandicap@Handicap@@QBEMW4HandicapType@1@PBVThingTemplate@@@Z
Real Handicap::getHandicap(HandicapType type, const ThingTemplate *thingTemplate) const
{
	ThingType thingType;
	if (thingTemplate->m_isBuilding)
	{
		thingType = BUILDINGS;
	}
	else
	{
		thingType = GENERIC;
	}
	return m_handicaps[type][thingType];
}
