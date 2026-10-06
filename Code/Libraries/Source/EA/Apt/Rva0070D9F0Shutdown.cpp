// cl: /DNDEBUG /MD
// ?Rva0070D9F0Shutdown@@YAXXZ, retail 0x0070D9F0 (435B).
// StringPool shutdown: walks the hash buckets at g_00E18368/g_00E1836C,
// asserts each string's GC root (0x7F) and refcount (1) via StringPool.cpp
// 0x129/0x12A, tracks sCurrentMemorySaved at g_00E18374, releases each node
// through virtual slot 1, drains g_releaseVectorAtE17710 per bucket, frees
// the bucket array through g_pChainBlockAllocator, then releases the
// saConstant table at 0x00E18388..0x00E18650 (assert 0x14C).
// Evidence: own immediates file "C:\projects\bfme2patch103\bfme2\Code\Libraries\Source\Apt\string\StringPool.cpp"
// plus "pString->getGCRoot() == AptValue::MAX_GCROOT" + "pString->getRefCount() == 1"
// + "sCurrentMemorySaved == 0" + "saConstant[i].GetInternalRefCount() == 1";
// callers at 0x006CFC6D (no pushes, void); neighbours share /O2 /DNDEBUG /MD.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

class Rva006DB270
{
public:
	void freeBlock(void *block, int blockSize);
};
extern Rva006DB270 *g_pChainBlockAllocator;

class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();
	virtual void ForceDelete();
	unsigned int getRefCount() const;
};

class BfmeAptValue006DCD20
{
	virtual void slot0();
public:
	unsigned int getGCRootCount() const;
};

class AptValueVector
{
public:
	void ReleaseValues();
};
extern AptValueVector *g_releaseVectorAtE17710;

class EAStringC
{
	void *m_pData;
public:
	unsigned int GetInternalRefCount() const;
	unsigned int rva006D3750() const;
	void rva006D3470();
};

struct StringNode0070D9F0
{
	void *m_vtbl;
	int m_flags;
	EAStringC m_str;
	StringNode0070D9F0 *m_next;
};
extern int g_00E1836C;
// g_00E1836C: matched references place it at VA 0xe1836c (zero-filled .bss).
int g_00E1836C;
// g_00E18368: matched references place it at VA 0xe18368 (retail .data initial value 0).
StringNode0070D9F0 ** g_00E18368 = 0;
extern int g_00E18374;
// g_00E18374: matched references place it at VA 0xe18374 (zero-filled .bss).
int g_00E18374;
extern EAStringC saConstantAtE18388[];
// g_00E18650: matched references place it at VA 0xe18650 (zero-filled; a plain-data view).
EAStringC g_00E18650;

void Rva0070D9F0Shutdown()
{
	for (int i = 0; i < g_00E1836C; ++i) {
		StringNode0070D9F0 *node = g_00E18368[i];
		if (!node)
			continue;
		do {
			if (((BfmeAptValue006DCD20 *)node)->getGCRootCount() != 0x7F) {
				g_bfmeAptAssertAtE17734("pString->getGCRoot() == AptValue::MAX_GCROOT", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\StringPool.cpp", 0x129);
				if (g_bfmeAptBreakOnAssertAtDDC01C) {
					__asm int 3
				}
			}
			if (((AptValue *)node)->getRefCount() != 1) {
				g_bfmeAptAssertAtE17734("pString->getRefCount() == 1", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\StringPool.cpp", 0x12A);
				if (g_bfmeAptBreakOnAssertAtDDC01C) {
					__asm int 3
				}
			}
			StringNode0070D9F0 *next = node->m_next;
			EAStringC *s = &node->m_str;
			g_00E18374 += ((s->rva006D3750() + 10) & ~3) + 8;
			unsigned int a = (s->rva006D3750() + 12) & ~3;
			unsigned int b = (s->rva006D3750() + 10) & ~3;
			g_00E18374 += a - b + 8;
			((AptValue *)node)->Release();
			node = next;
		} while (node);
		g_releaseVectorAtE17710->ReleaseValues();
	}
	if (g_00E18374 != 0) {
		g_bfmeAptAssertAtE17734("sCurrentMemorySaved == 0", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\StringPool.cpp", 0x143);
		if (g_bfmeAptBreakOnAssertAtDDC01C) {
			__asm int 3
		}
	}
	g_pChainBlockAllocator->freeBlock(g_00E18368, g_00E1836C * 4);
	g_00E1836C = 0;
	EAStringC *p = saConstantAtE18388;
	do {
		if (p->GetInternalRefCount() != 1) {
			g_bfmeAptAssertAtE17734("saConstant[i].GetInternalRefCount() == 1", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\StringPool.cpp", 0x14C);
			if (g_bfmeAptBreakOnAssertAtDDC01C) {
				__asm int 3
			}
		}
		p->rva006D3470();
		++p;
	} while ((int)p < (int)&g_00E18650);
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?saConstantAtE18388@@3PAVEAStringC@@A=_bfmeObjDAE")
