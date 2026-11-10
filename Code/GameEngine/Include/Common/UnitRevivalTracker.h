// UnitRevivalTracker: canonical declarations for the members 8 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_UNITREVIVALTRACKER_H
#define CANONICAL_UNITREVIVALTRACKER_H

class ArmySummarySystem;
struct Coord3D;
class Image;
class Object;
class Player;
struct Rva002E2D10Record;
class ThingTemplate;

class UnitRevivalTracker
{
public:
	void addInitialBuildUnit(const ThingTemplate *tmpl, Player *player);
	void addRevivableUnit(const Rva002E2D10Record &entry, Player *player);
	Object *productionSystemNewObject(unsigned int, const Coord3D *);
	bool productionSystemQueueCreateUnit(int, int, const Image **);
	void removeBuildUnit(const ThingTemplate *tmpl);
	void retrieveHeroesForArmySummary(ArmySummarySystem *summary);
};

#endif // CANONICAL_UNITREVIVALTRACKER_H
