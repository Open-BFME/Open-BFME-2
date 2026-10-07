// cl: /EHsc /MD /Ireference/shims/bfme2_ascii
//
#include "unicode_string.h"
// ?rva006007A5@Rva006007A5@@QAEXPAX@Z @0x006007A5 45B. Recursive list/tree
// free helper: if node null return else loop over siblings at +8 recursing
// on child at +0x0C with the same this then freeing via rowed _free
// 0x00030830. Same recipe as AnimationSoundTree::rva004CA167 without the
// payload dtor. Evidence: self-call at 0x006007B7; callers at 0x00600839
// (clear checking count +4) and self; ret 4.

extern "C" void free(void *);

class Rva006007A5
{
public:
	void rva006007A5(void *node);
	void rva0060082B();

private:
	void *m_header;
	unsigned m_count;
};

void Rva006007A5::rva006007A5(void *nodeIn)
{
	if (!nodeIn)
		return;
	char *cur = (char *)nodeIn;
	do
	{
		char *child = *(char **)(cur + 0x0C);
		rva006007A5(child);
		char *next = *(char **)(cur + 8);
		free(cur);
		cur = next;
	} while (cur);
}

void Rva006007A5::rva0060082B()
{
	if (m_count == 0)
		return;
	void *first = *(void **)((char *)m_header + 4);
	rva006007A5(first);
	*(void **)((char *)m_header + 8) = m_header;
	*(unsigned *)((char *)m_header + 4) = 0;
	*(void **)((char *)m_header + 0x0C) = m_header;
	m_count = 0;
}

class ArchiveFileSystem
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void *openFile(const UnicodeString &s, void *a, void *b, void *c, void *d);
};

extern ArchiveFileSystem *TheArchiveFileSystem;

// ?Rva006007DAOpen@@YGXPAX000@Z @0x006007DA 81B. Archive open with empty UnicodeString plus four args via slot 0x1c; prev 0x006007A5 next 0x0060082B same TU; callees strlen? no, StringBase ctor 0x00037E30 releaseBuffer 0x00036E70 EH_prolog; callers 0x0021F32E etc.; address-derived honest free name.
void __stdcall Rva006007DAOpen(void *a, void *b, void *c, void *d)
{
	UnicodeString empty(L"");
	TheArchiveFileSystem->openFile(empty, a, b, c, d);
}
