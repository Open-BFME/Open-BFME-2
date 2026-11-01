// cl: /DNDEBUG /MD /Ob2
// Readable out-of-line body of ??0TexBufferClass@@QAE@HPBD@Z (retail 0x0015D080, 62B).
// Ported from reference/open-bfme-1/.../TexBufferClassCtorThunk.cpp: unlike its
// MatBufferClass sibling (header-inline over the ShareBufferClass template),
// BFME's TexBufferClass derives straight from ShareBufferClassBase and clears
// its pointer array inline with add-add Count*4 (/G7) instead of calling Clear.
// Member names follow Code/.../ShareBufferClassBaseCtor.cpp, which owns the
// full layout (RefCountClass NumRefs plus raw/aligned buffer, count, alignment);
// only the members this ctor touches are declared here.

#include <new.h>
#include <string.h>

#include "../WWLib/RefCountData.h"

class ShareBufferClassBase : public RefCountClass
{
public:
	ShareBufferClassBase(int count, const char *name, int flags);
	virtual ~ShareBufferClassBase();

protected:
	void *m_rawBuffer;
	void *m_array;
	int m_count;
};

class TexBufferClass : public ShareBufferClassBase
{
public:
	TexBufferClass(int count, const char *name);
	virtual ~TexBufferClass();
};

// ??0TexBufferClass@@QAE@HPBD@Z
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline TexBufferClass::TexBufferClass(int count, const char *name)
	: ShareBufferClassBase(count, name, 0)
{
	int bytes = m_count;
	bytes += bytes;
	bytes += bytes;
	memset(m_array, 0, bytes);
}

// ?bfmeAnchorTexBufferClassCtor absent-from-retail
void *bfmeAnchorTexBufferClassCtor(void *where, int count, const char *name)
{
	return ::new (where) TexBufferClass(count, name);
}
