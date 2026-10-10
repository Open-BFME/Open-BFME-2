// cl: /O1 /EHs-c-
//
// ?bfmeAskBIC@BfmeSubBIC@@QAEHXZ, retail 0x00290fc9, 183 bytes. Banked partial (score 0.93) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Evidence: pin bfmeAskBIC, callers 0x000B329B 0x00468FAC Drawable_rva00275545, rowed getControllingPlayer 0x0028AFA9 rva0028F4BC 0x0028F4BC getRelationship 0x002AD0C6 bfmeAskRV 0x002AA231 getNthPlayer 0x002A7A29 getIndicatorColor 0x0028B026, ThePlayerList 0x009FEEE8.
class Team;
enum Relationship
{
	REL_ENEMY = 0,
	REL_NEUTRAL = 1,
	REL_ALLY = 2
};
class Player;
class BfmeMemberRV
{
public:
	bool bfmeAskRV();
};
class PlayerList
{
public:
	Player *getNthPlayer(int i);
	char m_pad00[0x10];
	Player *m_local10;
};
class Rva00373EC6
{
public:
	char m_pad00[0x38];
	int m_38;
	int m_3c;
};
class ObjectInner
{
public:
	char m_pad00[0x113];
	unsigned char m_113;
};
class Slot250
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual Player *slot4C(Player *p);
};
class Player
{
public:
	Relationship getRelationship(const Team *other) const;
	char m_pad00[0x280];
	int m_color280;
	char m_pad284[0x2EC - 0x284];
	const Team *m_team2EC;
};
extern PlayerList *ThePlayerList;
class Object
{
public:
	Player *getControllingPlayer() const;
	Rva00373EC6 *rva0028F4BC();
	int getIndicatorColor() const;
	char m_pad00[4];
	ObjectInner *m_inner04;
	char m_pad08[0x250 - 8];
	Slot250 *m_slot250;
};
class BfmeSubBIC : public Object
{
public:
	int bfmeAskBIC();
};
int BfmeSubBIC::bfmeAskBIC()
{
	Player *local = ThePlayerList->m_local10;
	Player *controller = getControllingPlayer();
	Player *candidate = controller;
	bool useFallback = true;
	if (m_inner04->m_113 & 1) {
		Rva00373EC6 *p = rva0028F4BC();
		// Codegen: same-valued PHI receiver on the player list closes the native register roles.
		if (p != 0 && p->m_3c != 0 && controller != 0 && local != 0 && controller->getRelationship(local->m_team2EC) != REL_ALLY && ((BfmeMemberRV *)local)->bfmeAskRV() && (candidate = (ThePlayerList?ThePlayerList:ThePlayerList)->getNthPlayer(p->m_38)) != 0) {
			useFallback = false;
		}
	}
	Slot250 *s = m_slot250;
	if (s != 0) {
		candidate = s->slot4C(local);
		if (candidate != 0) {
			useFallback = false;
		}
	}
	if (!useFallback && candidate != 0) {
		return candidate->m_color280;
	}
	return getIndicatorColor();
}
