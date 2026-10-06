// ?rva002AB5C7@Rva002AB5C7Player@@QAEXXZ
// partial score=0.93 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
//
// ?rva002AB5C7@Rva002AB5C7Player@@QAEXXZ, retail 0x002AB5C7, 118 bytes.
// Player team scan: walk +0x32C prototype list, for each team iterate its
// members calling g_00A027B8 slot26, then follow +0x40 chain via rowed
// disp8 getter. Evidence: callers 0x003BB30E, LINK BONUS, all callees rowed.
// Prev/next share /O1 /DNDEBUG /MD.
#pragma pointers_to_members(full_generality, multiple_inheritance)
class Object;
class Rva005C4AF5DwordField
{
public:
	int get() const;
};
template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[28];
public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};
template<class OBJCLASS>
class Rva001705A0DlinkIterator
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[28];
public:
	void advance();
};
class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};
class Rva00A027B8
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26(void *arg);
};
extern Rva00A027B8 *g_00A027B8;
struct PlayerTeamNode
{
	PlayerTeamNode *m_next;
	PlayerTeamNode *m_prev;
	void *m_value;
};
struct TeamProtoView
{
	char m_pad[0x334];
	Team *m_team;
};
class Rva002AB5C7Player
{
public:
	void rva002AB5C7();
private:
	char m_pad[0x32C];
	PlayerTeamNode *m_list;
};
typedef int (Rva005C4AF5DwordField::*GetMemFn)() const;
void Rva002AB5C7Player::rva002AB5C7()
{
	PlayerTeamNode *node = m_list->m_next;
	if (node == m_list)
		return;
	GetMemFn fn = &Rva005C4AF5DwordField::get;
	int delta = 0;
	for (; node != m_list; node = node->m_next) {
		Team *team = ((TeamProtoView *)node->m_value)->m_team;
		while (team != 0) {
			for (DLINK_ITERATOR<Object> it = team->iterate_TeamMemberList(); !it.done(); ((Rva001705A0DlinkIterator<Object> *)&it)->advance()) {
				g_00A027B8->slot26(it.cur());
			}
			Rva005C4AF5DwordField *f = (Rva005C4AF5DwordField *)((char *)team + delta);
			team = (Team *)(f->*fn)();
		}
	}
}
