// cl: /Oy- /DNDEBUG /MD
// ?rva003F3159@Rva003F3159@@QAEPAUDynamicPortalLink@@PAU2@0@Z @0x003F3159 51B:
// __thiscall copy-destroy tail over DynamicPortalLink ranges: rowed copy
// 0x003F2460 with a __false_type tag temp, then rowed _Destroy 0x003F29F8
// over [mid m_finish), update m_finish, return first arg. Caller 0x003F3AE3
// unblocks 0x003F3AB5. Call stays external via dup cast and declared-only
// _Destroy template per LivingWorldRegionConnectionHelpers precedent.
// The copy's by-reference dummy is the dead-arg-slot address [ebp+0xb]
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
void __cdecl Rva003F2460Copy(char *first, char *last, char *result);
typedef char *(__cdecl *Rva003F2460Copy4Fn)(char *, char *, char *, void *);
class Rva003F3159
{
public:
	DynamicPortalLink *rva003F3159(DynamicPortalLink *a, DynamicPortalLink *b);
private:
	char m_pad04[4];
	DynamicPortalLink *m_finish;
};
DynamicPortalLink *Rva003F3159::rva003F3159(DynamicPortalLink *a, DynamicPortalLink *b)
{
	DynamicPortalLink *mid = (DynamicPortalLink *)((Rva003F2460Copy4Fn)&Rva003F2460Copy)((char *)b, (char *)m_finish, (char *)a, (char *)&a + 3);
	_STL::_Destroy(mid, m_finish);
	m_finish = mid;
	return a;
}
