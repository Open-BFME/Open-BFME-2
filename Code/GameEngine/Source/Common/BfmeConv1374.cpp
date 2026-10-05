// BFME1 donor BfmeConv1374 reconstruction: deleting-destructor shape with
// a vptr immediate (twin SubtitleEntryCtor.cpp pattern); the drop helper
// rides a donor-evidenced pin, the conditional free is scalar delete.

void __cdecl operator delete(void *p);

extern const void *const g_00CE4A10[];

class BfmeThingVIH;

class BfmeSubVIH
{
public:
	void bfmeDropVIH(BfmeThingVIH *o);
};

class BfmeThingVIH
{
public:
	void *bfmeDelVIH(unsigned flags);

private:
	void *m_vft;
	char m_pad[8];
	BfmeSubVIH *m_sub;
};

void *BfmeThingVIH::bfmeDelVIH(unsigned flags)
{
	m_vft = (void *)g_00CE4A10;
	if (m_sub)
		m_sub->bfmeDropVIH(this);
	if (flags & 1)
		operator delete(this);
	return this;
}
