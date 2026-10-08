// cl: /DNDEBUG /MD
//
// ?rva0039E8EB@Team@@QAEPAVObject@@XZ @0x0039E8EB (20B).
// Team::rva0039E8EB(): returns the first member of the team or null. Retail
// creates the 24-byte iterator via the pinned iterate_TeamMemberList at
// 0x263864 and returns its m_cur. Callers such as 0x003C02D6 pass Team ECX
// from getTeamNamed and null-check the returned Object*.

class Object;

template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];

public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	Object *rva0039E8EB();
	Object *rva0039E968(int bit);
	bool rva0039E8FF(int val);
};

Object *Team::rva0039E8EB()
{
	DLINK_ITERATOR<Object> iter = iterate_TeamMemberList();
	return iter.cur();
}

// ?rva0039E968@Team@@QAEPAVObject@@H@Z @0x0039E968 57B chain lane: first
// member whose rowed 0x0028D8EB test is 1 else null; 0x18B iterator via
// rowed iterate plus rowed DLINK_ITERATOR<Object> advance; cmp al,1. The
// test class Rva0028D8EB is the honest placeholder for what reads
// as Object+0x3A4 at the call site.
class Rva0028D8EB
{
public:
	int rva0028D8EB(int bit);
};
Object *Team::rva0039E968(int bit)
{
	DLINK_ITERATOR<Object> iter = iterate_TeamMemberList();
	while (!iter.done()) {
		if ((char)((Rva0028D8EB *)iter.cur())->rva0028D8EB(bit) == 1)
			return iter.cur();
		iter.advance();
	}
	return 0;
}

// ?rva0039E8FF@Team@@QAE_NH@Z @0x0039E8FF 105B unlock Team method iterating members via rowed iterate plus rowed DLINK_ITERATOR<Object> advance plus virtual 0x7c and 0xac plus pinned bfmeHas985C; caller 0x003C4A28
struct Rva0039E8FFMid
{
	virtual void f00(); virtual void f01(); virtual void f02(); virtual void f03();
	virtual void f04(); virtual void f05(); virtual void f06(); virtual void f07();
	virtual void f08(); virtual void f09(); virtual void f10(); virtual void f11();
	virtual void f12(); virtual void f13(); virtual void f14(); virtual void f15();
	virtual void f16(); virtual void f17(); virtual void f18(); virtual void f19();
	virtual void f20(); virtual void f21(); virtual void f22(); virtual void f23();
	virtual void f24(); virtual void f25(); virtual void f26(); virtual void f27();
	virtual void f28(); virtual void f29(); virtual void f30(); virtual void *f31();
};
struct Rva0039E8FFTarget
{
	virtual void g00(); virtual void g01(); virtual void g02(); virtual void g03();
	virtual void g04(); virtual void g05(); virtual void g06(); virtual void g07();
	virtual void g08(); virtual void g09(); virtual void g10(); virtual void g11();
	virtual void g12(); virtual void g13(); virtual void g14(); virtual void g15();
	virtual void g16(); virtual void g17(); virtual void g18(); virtual void g19();
	virtual void g20(); virtual void g21(); virtual void g22(); virtual void g23();
	virtual void g24(); virtual void g25(); virtual void g26(); virtual void g27();
	virtual void g28(); virtual void g29(); virtual void g30(); virtual void g31();
	virtual void g32(); virtual void g33(); virtual void g34(); virtual void g35();
	virtual void g36(); virtual void g37(); virtual void g38(); virtual void g39();
	virtual void g40(); virtual void g41(); virtual void g42(); virtual bool g43(int val);
};
class BfmeArg985
{
public:
	char bfmeHas985C(int v);
};
class Object
{
public:
	char m_pad[0x250];
	Rva0039E8FFMid *m_mid;
};
bool Team::rva0039E8FF(int val)
{
	if (val == 0)
		return false;
	DLINK_ITERATOR<Object> iter = iterate_TeamMemberList();
	while (!iter.done()) {
		Object *cur = iter.cur();
		Rva0039E8FFMid *mid = cur->m_mid;
		void *res = mid ? mid->f31() : 0;
		if (res != 0) {
			if (((Rva0039E8FFTarget *)res)->g43(val))
				return true;
		} else {
			if ((char)((BfmeArg985 *)cur)->bfmeHas985C(val) == 1)
				return true;
		}
		iter.advance();
	}
	return false;
}
