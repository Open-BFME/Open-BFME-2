// cl: /O1 /MD
// ?Rva002EBCD6Split@@YAXPAXPAH1@Z @0x002EBCD6 32B unlock 9 callers
// Evidence: sibling Split at 0x002EBCA7 in Rva002EBBFBIsOdd.cpp; retail calls rowed Get then cdq-sub-sar half store then remainder store.
int __cdecl Rva002E9B31Get(void *p);
void __cdecl Rva002EBCD6Split(void *p, int *outHalf, int *outRest)
{
	int v = Rva002E9B31Get(p);
	int h = v / 2;
	*outHalf = h;
	*outRest = v - h;
}
