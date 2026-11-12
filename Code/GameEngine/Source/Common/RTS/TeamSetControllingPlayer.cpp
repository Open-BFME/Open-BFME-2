// Team::setControllingPlayer, retail 0x0039D97E..0x0039D9E3 (101 bytes).
// Identity: named WorldBuilder EF4800 Team.cpp definition and native caller ABI.
// Reference: Open-BFME-1 9e3be919b10ae956e3c8a13995e0d62f2be1d016,
// game/GameEngine/Source/Common/RTS/Team.cpp control-transfer loop.
// Native evidence supplies Team prototype+30, member head+38, controller+8,
// Object template+4 and kind byte+115 bit20. The two Player values are
// forwarded through the existing Object transfer provider 00290DBB.
// The iterator's virtual-inheritance Object/member-pointer layout is the
// existing proven TeamDidAllEnter.cpp contract. Its visible advance and
// factory definitions retain the native caller register allocation.
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
#include "../../../Include/Common/ThingTemplate.h"
class Player;
#include "../../../Include/Common/BfmeObjectVirtualTail.h"

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

#include "../../../Include/Common/BfmeObjectVtbl.h"

#include "../../../Include/Common/BfmeObjectDlinkBase.h"

class BfmeObjectDlinkPad
{
public:
	ThingTemplate *m_template;	// +0x04
	unsigned char m_pad[0x60];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
    public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier {
public:
    void makeDirty();
    void rva00290DBB(Player *a, Player *b);
};
template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance() { if (m_cur) m_cur = ((*m_cur).*(m_getNextFunc))(); }
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const { return DLINK_ITERATOR<Object>(m_head, &Object::dlink_next_TeamMemberList); }
	void setControllingPlayer(Player *player);
	unsigned char m_pad00[0x30];
	BfmeThingCFF *m_proto;
    char pad34[4];
    Object *m_head;
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
		if ((obj->m_template->m_kindof[3] & (1U << 13)) == 0) {
			if (curOwner && curOwner != owner)
				obj->rva00290DBB((Player *)curOwner, (Player *)owner);
		}
	}
}
