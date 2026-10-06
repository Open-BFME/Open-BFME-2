// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Thing::getDrawable, retail 0x005508E2 (7 bytes): the Drawable pointer at
// +0x84. SpawnPointProductionExitUpdate::initializeBonePositions calls it
// there; retail folded the body with BuildListInfo's identical getter.

class Drawable;

class Thing
{
public:
	Drawable *getDrawable(void) const;

private:
	char m_pad00[0x84];
	Drawable *m_drawable;	// +0x84
};

Drawable *Thing::getDrawable(void) const
{
	return m_drawable;
}

// Object::getDrawable is this body in retail (ICF; symbols.csv pin 0x005508E2, callers in matched
// rows land here). No unit defines the Object spelling any more; bind it.
#pragma comment(linker, "/alternatename:?getDrawable@Object@@QBEPAVDrawable@@XZ=?getDrawable@Thing@@QBEPAVDrawable@@XZ")
