// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva005F8EDAAptCall@@YAHPAVRva00222A8BTarget@@PAXPBD22PAPAX@Z @0x005F8EDA 38B.
// Chain from just-landed rva00222B19 twin pin: target as this plus level prefix function argc2 a0 deref-a1 plus three zeros.
// Evidence: calls rowed-pinned rva00222B19 0x00222B19; callers six 91B unblockees; neighbours Disp8CmpBoolGetters and Rva005F8F31Forwarder.
class Rva00222A8BTarget
{
public:
	int rva00222B19(void *level, const char *prefix, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};
int __cdecl Rva005F8EDAAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0, void **ppA1)
{
	void *a1 = *ppA1;
	return target->rva00222B19(level, prefix, function, 2, a0, a1, 0, 0, 0);
}
