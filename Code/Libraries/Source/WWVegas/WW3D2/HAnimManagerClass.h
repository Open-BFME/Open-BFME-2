// HAnimManagerClass: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_HANIMMANAGERCLASS_H
#define CANONICAL_HANIMMANAGERCLASS_H

class HAnimClass;

class HAnimManagerClass
{
public:
	bool Add_Anim(HAnimClass *anim);
	HAnimClass *Get_Anim(const char *name);
	HAnimClass *Peek_Anim(const char *name);
};

#endif // CANONICAL_HANIMMANAGERCLASS_H
