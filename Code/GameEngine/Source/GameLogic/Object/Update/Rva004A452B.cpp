// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?Rva004A452BUpdate@@YAXPAX00@Z @0x004A452B 85B: free update over 5 groups calling ObjectCreationList 0x001F0410 and Rva001E11F8 0x001E11F8.
// Evidence: rowed callees 0x001F0410 0x001E11F8 with same two args; neighbours Rva004A44B1 and StructureCollapseUpdate onDie share flags.

class ObjectCreationList
{
public:
	void rva001F0410(void *a, void *b);
};

class Rva001E11F8
{
public:
	void rva001E11F8(int a, int b);
};

void __cdecl Rva004A452BUpdate(void *p, void *a, void *b)
{
	char *esi = (char *)p + 0x58;
	int n = 5;
	do {
		for (ObjectCreationList **pp = *(ObjectCreationList ***)(esi - 4); pp != *(ObjectCreationList ***)(esi); ++pp) {
			if (*pp)
				(*pp)->rva001F0410(a, b);
		}
		for (Rva001E11F8 **pp2 = *(Rva001E11F8 ***)(esi + 0x38); pp2 != *(Rva001E11F8 ***)(esi + 0x3C); ++pp2) {
			if (*pp2)
				(*pp2)->rva001E11F8((int)a, (int)b);
		}
		esi += 0x0C;
	} while (--n != 0);
}
