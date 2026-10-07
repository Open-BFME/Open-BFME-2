// cl: /MD

class ModelConditionFlags
{
public:
	bool rva000B3EB3() const;
};

class Rva00263546
{
public:
	bool rva00263546(const Rva00263546 *other) const;
};

// ?rva0053BA87@@YGHPAX0@Z @0x0053BA87 90B
// Target evidence: checks ModelConditionFlags at first+0x1E0 and first+0x194 through
// rowed 0x000B3EB3; tests each against second+0x10C through rowed 0x00263546; returns 3
// for the first overlap or the second non-overlap and 2 otherwise.
// Structural inference: the two owner views and their wider identities remain address-derived.
int __stdcall rva0053BA87(void *firstOwner, void *secondOwner)
{
	ModelConditionFlags *firstFlags = (ModelConditionFlags *)((char *)firstOwner + 0x1E0);
	if (firstFlags->rva000B3EB3()
		&& ((Rva00263546 *)((char *)secondOwner + 0x10C))->rva00263546((const Rva00263546 *)firstFlags))
		return 3;

	ModelConditionFlags *secondFlags = (ModelConditionFlags *)((char *)firstOwner + 0x194);
	if (secondFlags->rva000B3EB3()
		&& !((Rva00263546 *)((char *)secondOwner + 0x10C))->rva00263546((const Rva00263546 *)secondFlags))
		return 3;

	return 2;
}
