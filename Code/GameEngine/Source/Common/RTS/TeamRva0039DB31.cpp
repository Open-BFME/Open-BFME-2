// cl: /O1 /DNDEBUG /MD
//
// ?rva0039DB31@Team@@QAEXPBX@Z @0x0039DB31 (88B): hands an argument to every
// member: through the member's contain interface (slot 31 of the Object
// +0x250 provider, the interface the rowed Object::rva0028C197 returns;
// its slot 46 with a zero second argument) when it has one, else to the
// rowed Object::rva00293077. Same member walk as TeamRva0039DDC2.cpp
// (rowed iterate_TeamMemberList 0x00263864, pinned advance 0x00263526),
// directly before Team::countObjectsByThingTemplate 0x0039DB89.

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

class Rva0039DB31Contain
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45();
	virtual void slot46(const void *arg, int flag);
};

class Rva0039DB31Provider
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30();
	virtual Rva0039DB31Contain *slot31();
};

class Object
{
public:
	void rva00293077(const void *arg);

	unsigned char m_pad[0x250];
	Rva0039DB31Provider *m_provider250; // +0x250
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	void rva0039DB31(const void *arg);
};

void Team::rva0039DB31(const void *arg)
{
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		Rva0039DB31Provider *provider = obj->m_provider250;
		Rva0039DB31Contain *contain = provider ? provider->slot31() : 0;
		if (contain)
			contain->slot46(arg, 0);
		else
			obj->rva00293077(arg);
	}
}
