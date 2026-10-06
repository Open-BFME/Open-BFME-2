// ?rva0047CAEB@Rva0047CAEB@@QAEPAVBfmeObject872Header@@PAV2@PAVObject@@@Z
// partial score=0.93 date=2026-10-06
// cl: /DNDEBUG /MD /Oy-
//
// ?rva0047CAEB@Rva0047CAEB@@QAEPAVBfmeObject872Header@@PAV2@PAVObject@@@Z retail 0x0047CAEB 84 bytes.
// Ref lane: address stored in 3 data table slots next to SlaughterHordeContain
// and HordeSiegeEngineContain rows. Calls rowed getControllingPlayer 0x28AFA9
// and Rva2225E0Filter::accepts 0x362437 then copies header at base+0x1A4 via
// rowed copy ctor 0x2CF108 else falls back to SlaughterHordeContain::rva00462CE1.
// Honest address name: method identity unproven.

class Player;
class Object
{
public:
	Player *getControllingPlayer() const throw();
};

class BfmeObject872Header
{
public:
	__declspec(nothrow) BfmeObject872Header(const BfmeObject872Header &other);
};

struct Rva2225E0Filter
{
	bool accepts(Object *obj, Player *ctx) throw();
};

class SlaughterHordeContain
{
public:
	virtual BfmeObject872Header *rva00462CE1(BfmeObject872Header *out, int unused) throw();
};

class Rva0047CAEB
{
public:
	BfmeObject872Header *rva0047CAEB(BfmeObject872Header *out, Object *obj);
};

#include <new>

BfmeObject872Header *Rva0047CAEB::rva0047CAEB(BfmeObject872Header *out, Object *obj)
{
	__assume(out != 0);
	Object *outerObj = *(Object **)((char *)this - 0x18);
	if (obj != 0) {
		if (((Rva2225E0Filter *)((char *)*(void **)((char *)this - 0x1c) + 0x18c))->accepts(obj, outerObj->getControllingPlayer())) {
			new (out) BfmeObject872Header(*(BfmeObject872Header *)((char *)*(void **)((char *)this - 0x1c) + 0x1a4));
			return out;
		}
	}
	return ((SlaughterHordeContain *)this)->SlaughterHordeContain::rva00462CE1(out, (int)obj);
}
