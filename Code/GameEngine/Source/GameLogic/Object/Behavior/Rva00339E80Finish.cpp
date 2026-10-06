// cl: /Oy- /DNDEBUG /MD
// ?rva00339E80@Rva00339E80@@QAEPAUDynamicPortalLink@@PAU2@0@Z @0x00339E80 51B:
// __thiscall copy-destroy tail over DynamicPortalLink ranges: rowed copy
// 0x001FFC38 with a dummy tag temp, then rowed _Destroy 0x003F29F8
// over [mid m_finish), update m_finish, return first arg. Callers 0x00339F6A
// 0x0033A2A4 0x0033A3DA unblock 0x0033A310. Call stays external via
// declared-only _Destroy template per LivingWorldRegionConnectionHelpers
// precedent. Same 51B shape as 0x003F3159 (Rva003F3159Finish.cpp).
// The copy's dummy is the dead-arg-slot address [ebp+0xb]
// (Rva002983DAEraseRange precedent); /Oy- keeps the ebp frame retail uses.
struct DynamicPortalLink
{
	void *m_owned;
	int m_second;
	int m_third;
	~DynamicPortalLink();
};
namespace _STL
{
struct __false_type {};
template <class T> void _Destroy(T first, T last);
}
void *__cdecl Rva001FFC38Copy(void *a, void *b, void *c, void *d);
class Rva00339E80
{
public:
	DynamicPortalLink *rva00339E80(DynamicPortalLink *a, DynamicPortalLink *b);
private:
	char m_pad04[4];
	DynamicPortalLink *m_finish;
};
DynamicPortalLink *Rva00339E80::rva00339E80(DynamicPortalLink *a, DynamicPortalLink *b)
{
	DynamicPortalLink *mid = (DynamicPortalLink *)Rva001FFC38Copy((void *)b, (void *)m_finish, (void *)a, (void *)((char *)&a + 3));
	_STL::_Destroy(mid, m_finish);
	m_finish = mid;
	return a;
}
