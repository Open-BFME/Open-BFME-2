// CollisionManagerImpl: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_COLLISIONMANAGERIMPL_H
#define CANONICAL_COLLISIONMANAGERIMPL_H

class Rva009A36F0Param;

class CollisionManagerImpl
{
public:
	void UnRegisterObject(Rva009A36F0Param *param);
	void Update();
};

#endif // CANONICAL_COLLISIONMANAGERIMPL_H
