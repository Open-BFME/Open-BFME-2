// ?rva0033605B@BfmeObjectEventDispatch@@QAEXPBVBfmeObject872Header@@0PAX@Z
// partial score=1.0 date=2026-10-07
// Native 33605B..3360D2 is complete RET12. Existing sibling 335FE1 and
// predicate 3317F9 establish this compatible dispatch prefix: table words
// +C8/+CC and 24-byte stride. Both predicate tests and list lifetime/invoke
// call order reproduce 119 bytes exactly under the recorded flags.
// This is banked evidence, not recovered/linkable progress. After refreshing
// the real predicate/list constructor/destructor objects, link preview still
// refuses the BfmeDelayedLuaEventList ctor/dtor aliases and unrowed invoke
// 334634. Earlier converted log entry did not establish a landed source row.
// No alias pins or linker escape hatches were added.
// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /EHsc
// ?rva00335FE1@BfmeObjectEventDispatch@@QAEXPBVWeaponTemplateSetHead@@0PAX@Z retail 0x00335FE1 122B
// Dispatch loop over 0x9C stride array from +0xBC to +0xC0. Each element is the
// rowed Rva003317B0 check class (int plus WeaponTemplateSetHead plus 19-int
// mask equals 0x9C). Filter is check(a) true and check(b) false then invoke
// event with object and a stack DelayedLuaEventList. Evidence: ecx is the
// dispatch this for rowed invoke pin 0x00334634; caller 0x00264069 passes two
// WeaponTemplateSetHead pointers plus object; dtor pin 0x00B6DD2 and ctor row
// 0x000B6D8B both exist for struct BfmeDelayedLuaEventList.
class WeaponTemplateSetHead;
class BfmeObject872Header;
class Rva003317F9 { public: bool rva003317F9(const BfmeObject872Header *arg); private: char data[0x24]; };

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
    void rva0033605B(const BfmeObject872Header *a,const BfmeObject872Header *b,void *obj);
private:
	char m_pad[0xBC];
	Rva003317B0 *m_begin;
	Rva003317B0 *m_end;
    char padc4[4];
    Rva003317F9 *beginC8;
    Rva003317F9 *endCC;
};



void BfmeObjectEventDispatch::rva0033605B(const BfmeObject872Header *a,const BfmeObject872Header *b,void *obj) {
 for(Rva003317F9 *p=beginC8;p!=endCC;++p) {
  if(!p->rva003317F9(a))continue;
  if(p->rva003317F9(b))continue;
  BfmeDelayedLuaEventList list;
  invoke(p,obj,&list);
 }
}
