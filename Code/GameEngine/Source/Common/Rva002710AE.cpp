// cl: /MD

// Rva002710AE::rva002710AE at RVA 0x002710AE, 57B. Unlock lane: all callees rowed (slot 0x14 bool,
// getDesiredGatherers 0x005508E2). Caller at 0x004A1B0C in 0x004A1A69.
// Guard virtual bool at +0x14 on arg2, then resolve gatherer pointer via
// BuildListInfo and copy bytes at +0x445/+0x446 to this.

class BuildListInfo
{
public:
	int getDesiredGatherers();
};

class Arg2
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual bool v5();
};

class Rva002710AE
{
public:
	void rva002710AE(BuildListInfo *a1, Arg2 *a2);

private:
	char m_pad[0x445];
	unsigned char m_445;
	unsigned char m_446;
};

void Rva002710AE::rva002710AE(BuildListInfo *a1, Arg2 *a2)
{
	if (!a2->v5())
		return;
	unsigned char *p = (unsigned char *)a1->getDesiredGatherers();
	if (!p)
		return;
	m_445 = *(p + 0x445);
	m_446 = *(p + 0x446);
}
