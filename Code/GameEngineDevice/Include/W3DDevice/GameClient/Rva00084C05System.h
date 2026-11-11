// Rva00084C05System: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA00084C05SYSTEM_H
#define CANONICAL_RVA00084C05SYSTEM_H

class Rva00084206Track;
class Rva00084B18RenderObj;
class SceneClass;

class Rva00084C05System
{
public:
	Rva00084206Track *bind(Rva00084B18RenderObj *robj, float length, const char *texture, const char *a, const char *b);
	void init(SceneClass *scene);
	void update();
};

#endif // CANONICAL_RVA00084C05SYSTEM_H
