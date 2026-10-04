// ?rva003A10FE@Team@@QAEX_N@Z
// partial score=0.94 date=2026-10-05
// ?rva003A10FE@Team@@QAEX_N@Z
// ?rva003A10FE@Team@@QAEX_N@Z
// cl: /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva003A10FE@Team@@QAEX_N@Z, retail 0x003A10FE (259 bytes).
// Team::rva003A10FE(bool): if this is the controlling player's current team
// (Player+0x2EC) builds a local list<int> of member Objects whose +0x250
// inner returns >0 via virtual +0x114, notifies each entry's inner via
// virtual +0xA8 with 0, then destroys remaining members via rowed
// GameLogic::destroyObject unless flag is set and Object+0x438 bit0 is set.
// Follows sibling TeamRva003A1C3A list<int> pattern (rowed iterate
// 0x00263864, pinned advance 0x00263526, rowed list insert 0x005925E2,
// rowed List_base ctor/dtor, rowed getControllingPlayer 0x0039D7CF, rowed
// destroyObject 0x00242C09, TheGameLogic 0x00DFE78C). Honest Team method name.
#include <list>

class Team;
class Object;
class Player;
class GameLogic;

template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	// Retail's frame is 0x28 and ours is 0x24 at this size; the iterator
	// view is padded to the width that makes both agree. m_targetAbiState is
	// never read here -- it exists only so the DLINK_ITERATOR occupies the
	// frame space retail gives it.
	unsigned char m_targetAbiState[24];

public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Rva003A10FEInner
{
public:
	virtual void v00();
	virtual void v01();
	virtual int v02();
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
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42(int a);
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual void v67();
	virtual void v68();
	virtual unsigned int v69(int a);
};

class Object
{
public:
	unsigned char m_pad00[0x94];
	unsigned char m_flag94;
	unsigned char m_pad95[0x250 - 0x95];
	Rva003A10FEInner *m_inner250;
	unsigned char m_pad254[0x438 - 0x254];
	unsigned char m_flag438;
};

class Player
{
public:
	unsigned char m_pad00[0x2EC];
	Team *m_team2EC;
};

class GameLogic
{
public:
	void destroyObject(Object *obj);
};

extern GameLogic *TheGameLogic;

class Team
{
public:
	Player *getControllingPlayer() const;
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
// ?rva003A10FE@Team@@QAEX_N@Z present-unmatched
	void rva003A10FE(bool flag);
};

void Team::rva003A10FE(bool flag)
{
	Player *player = getControllingPlayer();
	if (player->m_team2EC == this) {
		_STL::list<int> tmp;
		for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
			Object *cur = iter.cur();
			int curVal = (int)cur;
			if (cur == 0)
				continue;
			Rva003A10FEInner *inner = cur->m_inner250;
			if (inner == 0)
				continue;
			if (inner->v69(0) <= 0)
				continue;
			tmp.push_back(curVal);
		}
		for (_STL::list<int>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
			Object *obj = (Object *)(*it);
			Rva003A10FEInner *inner = obj->m_inner250;
			if (inner == 0)
				continue;
			inner->v42(0);
		}
	}
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *cur = iter.cur();
		if (!flag || (cur->m_flag438 & 1) == 0)
			TheGameLogic->destroyObject(cur);
	}
}
