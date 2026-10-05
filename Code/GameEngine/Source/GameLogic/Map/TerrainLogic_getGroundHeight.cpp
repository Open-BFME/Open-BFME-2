// cl: /O1 /arch:SSE /DNDEBUG /MD
// ZH donor: GeneralsMD TerrainLogic.cpp getGroundHeight and getLayerHeight,
// the default (flat, zero-height) implementations.
// ?getGroundHeight@TerrainLogic@@UBEMMMPAUCoord3D@@@Z @0x0027CE9A 34B and
// ?getLayerHeight@TerrainLogic@@UBEMMMW4PathfindLayerEnum@@PAUCoord3D@@_N@Z
// @0x0027CEBC 34B are slots 6 and 7 of the TerrainLogic vftable 0x00BFB2C8,
// right after newMap (slot 5, 0x00284290) as in Zero Hour's declaration
// order; their ret 0xC / ret 0x14 match the three- and five-argument
// signatures. The Zero Hour bodies, built /O1 /arch:SSE, place uniquely.

typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x, y, z;

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

class TerrainLogic
{
public:
	virtual ~TerrainLogic();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05();
	virtual Real getGroundHeight( Real x, Real y, Coord3D* normal = 0 ) const;
	virtual Real getLayerHeight( Real x, Real y, PathfindLayerEnum layer, Coord3D* normal = 0, Bool clip = true ) const;
};

//-------------------------------------------------------------------------------------------------
/** default get height for terrain logic */
//-------------------------------------------------------------------------------------------------
Real TerrainLogic::getGroundHeight( Real x, Real y, Coord3D* normal ) const
{
	if( normal )
		normal->zero();

	return 0;

}  // end getHight

//-------------------------------------------------------------------------------------------------
/** default get height for terrain logic */
//-------------------------------------------------------------------------------------------------
Real TerrainLogic::getLayerHeight( Real x, Real y, PathfindLayerEnum layer, Coord3D* normal, Bool clip ) const
{
	if( normal )
		normal->zero();

	return 0;

}  // end getLayerHeight
