// ?rva004639D5@SlaughterHordeContain@@UAEHH@Z
// partial score=0.72 date=2026-10-05
// cl: /Os /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva004639D5@SlaughterHordeContain@@UAEHH@Z, retail 0x004639D5, 120 bytes.
// Virtual slot 3 (cell base+0xC) in 17-table family (e.g. 0x8433F0..0x848F08),
// window [47A699,46294E,B3FD0,4639D5,464FC7,46322C]. Map<int,int> at this+0xD0
// via rowed _M_find 0x388F63 (int-int exact provider); owner at *(this-0x1C)
// with limit at owner+0x94; node timestamp at found+0x14 (pair second);
// TheGameLogic frame at +0x40; ratio (frame-start)/limit*100.0f via x87 with
// 2^32 bias + __ftol2 0x629228; miss->100, over-limit->100, zero-delta->0,
// zero-limit->100. Evidence: slot cells + OpenContain map precedent + BFME1
// GarrisonContain frame vocabulary (donor facts only); method identity still
// anonymous, honest address name.
#include <map>

class GameLogic
{
public:
	char m_pad00[0x40];
	unsigned m_frame40;
};
extern GameLogic *TheGameLogic;

struct Owner004639D5 {
	char m_pad00[0x94];
	unsigned m_limit94;
};

class SlaughterHordeContain
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual int rva004639D5(int key);
	virtual void s4();
	virtual void s5();
	char m_pad04[0xD0 - 4];
	_STL::map<int, int> m_mapD0;
};

int SlaughterHordeContain::rva004639D5(int key)
{
	Owner004639D5 *owner = *(Owner004639D5 **)((char *)this - 0x1C);
	_STL::map<int, int>::iterator it = m_mapD0.find(key);
	if (it == m_mapD0.end())
		return 100;
	unsigned frame = TheGameLogic->m_frame40;
	unsigned start = (unsigned)(*it).second;
	unsigned delta = frame - start;
	unsigned limit = owner->m_limit94;
	if (delta > limit)
		return 100;
	if (delta == 0)
		return 0;
	if (limit == 0)
		return 100;
	return (int)((float)delta / (float)limit * 100.0f);
}
