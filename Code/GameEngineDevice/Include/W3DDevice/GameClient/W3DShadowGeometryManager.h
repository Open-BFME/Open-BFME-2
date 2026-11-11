// W3DShadowGeometryManager: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_W3DSHADOWGEOMETRYMANAGER_H
#define CANONICAL_W3DSHADOWGEOMETRYMANAGER_H

class RenderObjClass;

class W3DShadowGeometryManager
{
public:
	int Load_Geom(RenderObjClass *robj, const char *name);
	void rva000F1AD8();
};

#endif // CANONICAL_W3DSHADOWGEOMETRYMANAGER_H
