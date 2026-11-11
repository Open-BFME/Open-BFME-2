// Rva0050CBA2: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0050CBA2_H
#define CANONICAL_RVA0050CBA2_H

class ModuleInfo;
class Rva000B4A9F;
class Rva0013A820;

class Rva0050CBA2
{
public:
	Rva0050CBA2(void *arg);
	bool rva0050C91D(Rva0013A820 *record, ModuleInfo *modules, const void *thing, Rva000B4A9F *draw, int index);
	bool rva0050C9EF(Rva0013A820 *record, int index);
	bool rva0050CBA2(void *filename);
};

#endif // CANONICAL_RVA0050CBA2_H
