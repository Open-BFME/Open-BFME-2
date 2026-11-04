// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Thing::getDrawable, retail 0x005508E2 (7 bytes): the Drawable pointer at
// +0x84. SpawnPointProductionExitUpdate::initializeBonePositions calls it
// there; retail folded the body with BuildListInfo's identical getter.

class Drawable;

#include "thing.h"

// Object, which derives from Thing at offset 0, keeps its Drawable at +0x84.
class Object : public Thing
{
public:
	char m_pad60[0x84 - 0x60];
	Drawable *m_drawable;	// +0x84
};

Drawable *Thing::getDrawable(void) const
{
	return static_cast<const Object *>(this)->m_drawable;
}
