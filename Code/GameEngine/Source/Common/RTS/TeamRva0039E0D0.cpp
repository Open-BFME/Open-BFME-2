// cl: /DNDEBUG /MD
//
// ?rva0039E0D0@Team@@QAE_NXZ @0x0039E0D0 (141B).
// Team::rva0039E0D0(): returns true when the Team gate byte at +0x112 is clear
// or every considered member passes dead/status/template/AI/virtual filters.
// Retail evidence: gate byte at Team+0x112, iterate_TeamMemberList at 0x263864
// plus DLINK advance pinned at 0x263526, Object::testStatus at 0x4E536 with
// arg 2, template at Object+0x04 with kind byte at +0x115 bit 0x20, AI ptr at
// Object+0x250 with virtual +0x7c returning sub, sub virtuals +0x180(takes 0)
// +0xA4 +0x9C, caller at 0x39F131, prev 0x39E042 TeamHasAnyObjects next
// 0x39E20D TeamDidPartialEnter share Team iteration and DLINK layout.

typedef unsigned int UnsignedInt;

enum ObjectStatusTypes
{
	ObjectStatus_Dummy0 = 0,
	ObjectStatus_Dummy1 = 1,
	ObjectStatus_Two = 2
};

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

struct ThingTemplate
{
	unsigned char m_pad[0x115];
	unsigned char m_byte115;
};

class Rva0039E0D0AI
{
public:
	virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
	virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
	virtual void d08(); virtual void d09(); virtual void d10(); virtual void d11();
	virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
	virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
	virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
	virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
	virtual void d28(); virtual void d29(); virtual void d30();
	virtual void *getSub();
};

class Rva0039E0D0Sub
{
public:
	virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
	virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
	virtual void d08(); virtual void d09(); virtual void d10(); virtual void d11();
	virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
	virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
	virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
	virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
	virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
	virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35();
	virtual void d36(); virtual void d37(); virtual void d38();
	virtual bool check9C();
	virtual void d40();
	virtual bool checkA4();
	virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45();
	virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49();
	virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53();
	virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57();
	virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61();
	virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65();
	virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69();
	virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73();
	virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77();
	virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81();
	virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85();
	virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89();
	virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93();
	virtual void d94(); virtual void d95();
	virtual void *check180(int);
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;

public:
	unsigned char m_pad0[4];
	ThingTemplate *m_template;
	unsigned char m_pad1[0x250 - 0x8];
	Rva0039E0D0AI *m_ai250;
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	bool rva0039E0D0();

private:
	unsigned char m_pad[0x112];
	unsigned char m_byte112;
};

bool Team::rva0039E0D0()
{
	if (m_byte112 != 0) {
		for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
			Object *cur = iter.cur();
			if (cur->testStatus(ObjectStatus_Two))
				return false;
			ThingTemplate *tmpl = cur->m_template;
			if ((tmpl->m_byte115 & 0x20) == 0)
				continue;
			Rva0039E0D0AI *ai = cur->m_ai250;
			if (ai == 0)
				continue;
			Rva0039E0D0Sub *sub = (Rva0039E0D0Sub *)ai->getSub();
			if (sub == 0)
				continue;
			if (sub->check180(0) == 0)
				return false;
			if (!sub->checkA4())
				continue;
			if (!sub->check9C())
				return false;
		}
	}
	return true;
}
