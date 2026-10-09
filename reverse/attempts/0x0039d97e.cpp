// ?setControllingPlayer@Team@@QAEXPAVPlayer@@@Z
// partial score=0.970297 date=2026-10-09
// Donor Team.cpp setControllingPlayer plus BFME2 capture notification path.
// Native39D97E..39D9E1 and WB EF4800 establish identity and receiver.
// Target prototype30/controller8; member template115 bit20 suppresses
// notification; old/new Player arguments forwarded through owned290DBB.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
class Player;
class BfmeOwnerCFF;
class BfmeThingCFF
{
public:
	void bfmeGoCFF(BfmeOwnerCFF *owner);
	unsigned char m_head[8];
	BfmeOwnerCFF *m_owner;
};
class Object;
class ThingTemplate
{
public:
	unsigned char m_pad[0x115];
	unsigned char m_115;
};
struct Rva002A9B58;
class Object
{
public:
	void makeDirty();
	void rva00290DBB(Rva002A9B58 *a, Rva002A9B58 *b);
	unsigned char m_pad0[4];
	ThingTemplate *m_template;
};
template<class OBJCLASS> class DLINK_ITERATOR
{
public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
private:
	OBJCLASS *m_cur;
	unsigned char m_rest[20];
};
class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	void setControllingPlayer(Player *player);
	unsigned char m_pad00[0x30];
	BfmeThingCFF *m_proto;
};
void Team::setControllingPlayer(Player *player)
{
 BfmeOwnerCFF *owner=(BfmeOwnerCFF*)player;
	BfmeThingCFF *proto = m_proto;
	if (!proto)
		return;
	BfmeOwnerCFF *curOwner = proto->m_owner;
	proto->bfmeGoCFF(owner);
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *obj = iter.cur();
		obj->makeDirty();
		if ((obj->m_template->m_115 & 0x20) == 0) {
			if (curOwner && curOwner != owner)
				obj->rva00290DBB((Rva002A9B58 *)curOwner, (Rva002A9B58 *)owner);
		}
	}
}
