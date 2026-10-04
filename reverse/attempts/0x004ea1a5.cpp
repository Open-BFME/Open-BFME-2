// ?rva004EA1A5@Rva004EA1A5@@QAEXPAX@Z
// partial score=0.95 date=2026-10-04
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva004EA1A5@Rva004EA1A5@@QAEXPAX@Z retail 0x004EA1A5 191B: chain calls landed 0x0055ADBA plus testStatus and float checks plus hero find erase; evidence callees rowed plus globals g_00E04494 g_00E04498
#include <vector>
#include <algorithm>

enum ObjectStatusTypes
{
	STATUS_0 = 0,
	STATUS_1 = 1,
	STATUS_2 = 2
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes s) const;
	char m_pad00[4];
	void *m_04;
	char m_pad08[0x6C];
	int m_74;
	char m_pad78[0x208];
	float m_280;
};

class Rva004E9378
{
public:
	bool rva004E9378();
};

class Rva00506FE9Hit
{
public:
	void rva0055ADBA(void *x);
};

class CreateAHeroData
{
public:
	char m_pad00[0x10];
	int m_10;
	char m_pad14[0x10];
	int m_24;
	char m_pad28[0x3C];
	unsigned char m_64;
	char m_pad65[3];
	int m_68;
	int m_6C;
};

extern void *g_00E04494;
extern void *g_00E04498;

class Rva004EA1A5
{
public:
	void rva004EA1A5(void *x);
	char m_pad00[0x14];
	void *m_14;
	int m_18;
	char m_pad1C[8];
	_STL::vector<void *, _STL::allocator<void *> > m_vec24;
};

// ?rva004EA1A5@Rva004EA1A5@@QAEXPAX@Z present-unmatched
void Rva004EA1A5::rva004EA1A5(void *x)
{
	Rva004EA1A5 *self = this;
	register const Object *obj = (const Object *)x;
	if (!(0.0f > obj->m_280)) {
		if (!obj->testStatus(STATUS_2))
			return;
	}
	void *flagPtr = *(void **)((char *)obj + 4);
	if ((*(unsigned char *)((char *)flagPtr + 0x10E) & 4) != 0)
		return;
	if (0.0f > obj->m_280)
		--self->m_18;
	void **beg = (void **)g_00E04494;
	void **end = (void **)g_00E04498;
	if (beg == end)
		return;
	for (void **p = beg; p != end; ++p) {
		CreateAHeroData *t = (CreateAHeroData *)*p;
		*(CreateAHeroData **)&x = t;
		if (t->m_64 != 0) {
			if (t->m_68 != *(int *)((char *)self + 0x14))
				continue;
			if (t->m_24 != obj->m_74)
				continue;
		}
		if (!((Rva004E9378 *)t)->rva004E9378()) {
			CreateAHeroData **vbeg = (CreateAHeroData **)self->m_vec24.begin();
			CreateAHeroData **vend = (CreateAHeroData **)self->m_vec24.end();
			CreateAHeroData **found = _STL::find(vbeg, vend, t);
			if (found != vend)
				self->m_vec24.erase((void **)found);
			((Rva00506FE9Hit *)t)->rva0055ADBA(self->m_14);
		}
		++t->m_6C;
		t->m_64 = 0;
		return;
	}
}
