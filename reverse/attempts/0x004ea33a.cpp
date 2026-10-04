// ?rva004EA33A@Rva004EA33A@@QAEXXZ
// partial score=0.96 date=2026-10-04
// ?rva004EA33A@Rva004EA33A@@QAEXXZ
// partial score=0.91 date=2026-09-30
// cl: /O1 /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva004EA33A@Rva004EA33A@@QAEXXZ @0x004EA33A (106B): hero vector cleanup plus fields.
// Deletes virtual slot 0 result of each entry in global vector<void*> at
// 0x00A04494 via rowed operator delete at 0x0002FD60, erases range via rowed
// erase at 0x0031BD55, zeroes +0xc, fetches via rowed rva002A8F24 at
// 0x002A8F24 with Player at +8, then rowed rva004DFB55 at 0x004DFB55 with
// this-0xc as CreateAHeroData. Caller at 0x004EA3E2. Prev Disp8 getters.
#include <vector>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Iface004EA33A
{
	virtual void *virt0(int x);
};

class Player;
class CreateAHeroData;
class Rva002A8F24
{
public:
	void *rva002A8F24(Player *p);
};
class Rva004DFB55
{
public:
	void rva004DFB55(CreateAHeroData *p);
};

extern _STL::vector<void *> g_00E04494;
extern Rva002A8F24 *g_00DFEEF8;

class Rva004EA33A
{
	char m_pad0[8];
	Player *m_player;
	int m_fieldC;
public:
	void rva004EA33A();
};

// ?rva004EA33A@Rva004EA33A@@QAEXXZ present-unmatched
void Rva004EA33A::rva004EA33A()
{
	Rva004EA33A *self = this;
	void **end = ((void ***)&g_00E04494)[1];
	void **beg = ((void ***)&g_00E04494)[0];
	if (beg != end) {
		void **it = beg;
		_ReadWriteBarrier();
		do {
			void *p = *it;
			void *q = p ? ((Iface004EA33A *)p)->virt0(0) : 0;
			::operator delete(q);
			++it;
		} while (it != end);
	}
	g_00E04494.erase((void **)g_00E04494.begin(), (void **)g_00E04494.end());
	self->m_fieldC = 0;
	void *res = g_00DFEEF8->rva002A8F24(self->m_player);
	((Rva004DFB55 *)res)->rva004DFB55((CreateAHeroData *)((char *)self - 12));
}
