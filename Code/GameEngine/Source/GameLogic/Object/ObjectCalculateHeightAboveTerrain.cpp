// cl: /DNDEBUG /MD /EHsc
//
// ?calculateHeightAboveTerrain@Object@@MBEMXZ, retail 0x0028B569 (44B).
// Zero Hour's Object override: the position's z minus TheTerrainLogic's
// getLayerHeight(x, y, m_layer, NULL, true). Evidence: slot 4 of the Object
// vtable whose slot 0 is the Object deleting destructor (entry 0x007FC300),
// the same slot the Drawable vtable fills with the rowed
// Thing::calculateHeightAboveTerrain 0x0030A4AC; that base body reads the
// same +0x38/+0x3C/+0x40 position and calls the TerrainLogic slot before
// (getGroundHeight) where this one calls slot 7 with the +0x40C layer. It
// sits between setID 0x0028B532 and the list unlink 0x0028B595, Zero Hour's
// order.

typedef float Real;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

struct Coord3D
{
	Real x, y, z;
};

class TerrainLogic
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02(); virtual void vslot03();
	virtual void vslot04(); virtual void vslot05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const;
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer, Coord3D *normal = 0, bool clip = true) const;
};
extern TerrainLogic *TheTerrainLogic;

class Object
{
public:
	virtual ~Object();
	const Coord3D *getPosition() const { return &m_cachedPos; }

protected:
	virtual Real calculateHeightAboveTerrain() const;

private:
	unsigned char m_pad004[0x38 - 4];
	Coord3D m_cachedPos; // +0x38
	unsigned char m_pad044[0x40C - 0x44];
	PathfindLayerEnum m_layer; // +0x40C
};

Real Object::calculateHeightAboveTerrain() const
{
	const Coord3D *pos = getPosition();
	Real terrainZ = TheTerrainLogic->getLayerHeight(pos->x, pos->y, m_layer);
	Real myZ = pos->z;
	return myZ - terrainZ;
}
