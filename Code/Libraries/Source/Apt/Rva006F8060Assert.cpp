// cl: /MD
// ?rva006F8060@Rva006F8060@@QAEPAV1@H@Z @0x006F8060 size 91 — assert head defined then virtual slot 8.
// Evidence: isUndefined 0x006DC010 on [this], assert line 0x8A4 cond pHead->isUndefined(),
// clear [head+0x4C], virtual [edx+8], flag bit0 pool-free this size 4, return this.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class BfmeAptValue006DCD20
{
public:
	bool isUndefined() const;
};

class Rva006F8060Head
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	int m_pad04[(0x4C / 4) - 1];
	int m4C;
};

class Rva006DB270
{
public:
	void freeBlock(void *block, int blockSize);
};

extern Rva006DB270 *g_pChainBlockAllocator;

class Rva006F8060
{
public:
	Rva006F8060 *rva006F8060(int flag);

private:
	Rva006F8060Head *m00;
};

Rva006F8060 *Rva006F8060::rva006F8060(int flag)
{
	if (!((const BfmeAptValue006DCD20 *)m00)->isUndefined())
	{
		g_bfmeAptAssertAtE17734("pHead->isUndefined()", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x8A4);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	m00->m4C = 0;
	m00->v2();
	if (flag & 1)
		g_pChainBlockAllocator->freeBlock(this, 4);
	return this;
}
