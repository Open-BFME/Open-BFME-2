// cl: /MD
// ?Rva002B47B1Get@@YAPAXXZ @0x002B47B1 18B.
// Unlock chase through global 0x00E02D6C Rva003B8BAA index/array plus +0x40
// field. Evidence: same global/index/array shape as rowed Rva003B8BAA
// in Rva003B8BAALookup.cpp, caller at 0x002B075A, prev/next same dir.
struct Rva002B47B1Elem
{
	char m_pad[0x40];
	void *m_ptr40;
};
class Rva003B8BAA
{
public:
	char m_pad[0x10];
	int m_index10;
	Rva002B47B1Elem **m_array14;
};
// TheCampaignManager (0x00E02D6C): matched references place it at VA 0xe02d6c (retail .data initial value 0).
class Rva00E02D6C;
Rva00E02D6C *TheCampaignManager = 0;
void *Rva002B47B1Get(void)
{
	Rva003B8BAA *g = ((Rva003B8BAA *)TheCampaignManager);
	return g->m_array14[g->m_index10]->m_ptr40;
}
