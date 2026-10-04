// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva00335FE1@BfmeObjectEventDispatch@@QAEXPBVWeaponTemplateSetHead@@0PAX@Z retail 0x00335FE1 122B
// Dispatch loop over 0x9C stride array from +0xBC to +0xC0. Each element is the
// rowed Rva003317B0 check class (int plus WeaponTemplateSetHead plus 19-int
// mask equals 0x9C). Filter is check(a) true and check(b) false then invoke
// event with object and a stack DelayedLuaEventList. Evidence: ecx is the
// dispatch this for rowed invoke pin 0x00334634; caller 0x00264069 passes two
// WeaponTemplateSetHead pointers plus object; dtor pin 0x00B6DD2 and ctor row
// 0x000B6D8B both exist for struct BfmeDelayedLuaEventList.
class WeaponTemplateSetHead;

class Rva003317B0
{
public:
	bool rva003317B0(const WeaponTemplateSetHead *arg);
private:
	char m_data[0x9C];
};

struct BfmeDelayedLuaEvent
{
	unsigned char m_data[0x18];
};

struct BfmeDelayedLuaEventList
{
	BfmeDelayedLuaEventList();
	~BfmeDelayedLuaEventList();
	void *m_vtable;
	BfmeDelayedLuaEvent m_events[3];
};

struct BfmeObjectEventDispatch
{
	void invoke(void *event, void *object, BfmeDelayedLuaEventList *eventList);
	void rva00335FE1(const WeaponTemplateSetHead *a, const WeaponTemplateSetHead *b, void *obj);
private:
	char m_pad[0xBC];
	Rva003317B0 *m_begin;
	Rva003317B0 *m_end;
};

void BfmeObjectEventDispatch::rva00335FE1(const WeaponTemplateSetHead *a, const WeaponTemplateSetHead *b, void *obj)
{
	for (Rva003317B0 *p = m_begin; p != m_end; ++p) {
		if (!p->rva003317B0(a))
			continue;
		if (p->rva003317B0(b))
			continue;
		BfmeDelayedLuaEventList list;
		invoke(p, obj, &list);
	}
}
