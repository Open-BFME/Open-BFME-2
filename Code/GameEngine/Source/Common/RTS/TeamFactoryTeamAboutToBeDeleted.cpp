// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?teamAboutToBeDeleted@TeamFactory@@QAEXPAVTeam@@@Z, retail 0x003A3048,
// 65 bytes.
//
// Zero Hour Team.cpp TeamFactory::teamAboutToBeDeleted: every prototype in
// the factory's map hears about the team, then ThePlayerList does.
// Target evidence: TheTeamFactory (0x00E028BC) is the receiver at both
// teardown call sites (deleteTeamCallback 0x003A33A7 and
// TeamPrototype::updateState 0x003A34AC); the body walks the +0xB0
// prototype map from header->left through the rowed _M_increment
// 0x00024250 like the rowed TeamFactory finds (TeamFactoryFindById.cpp),
// calling 0x003A2CA5 on each node's +0x18 prototype with the team (pinned
// as TeamPrototype::teamAboutToBeDeleted: it walks the prototype's +0x334
// team list), and tail-calls ThePlayerList (0x00DFEEE8) member 0x002A7AFE
// when the list exists.
namespace _STL
{
struct _Rb_tree_node_base
{
	bool _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class Dummy> class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
};
}

class Team;

class TeamPrototype
{
public:
	void teamAboutToBeDeleted(Team *team);
};

struct TeamPrototypeMapKey
{
	int m_first;
	int m_second;
};

struct TeamPrototypeMapNode : public _STL::_Rb_tree_node_base
{
	TeamPrototypeMapKey m_key; // +0x10
	TeamPrototype *m_value; // +0x18
};

class PlayerList
{
public:
	void rva002A7AFE(void *team);
};

extern PlayerList *ThePlayerList;

class TeamFactory
{
public:
	void teamAboutToBeDeleted(Team *team);

private:
	unsigned char m_pad00[0xB0];
	TeamPrototypeMapNode *m_prototypes; // +0xB0, map header
};

void TeamFactory::teamAboutToBeDeleted(Team *team)
{
	for (TeamPrototypeMapNode *it = (TeamPrototypeMapNode *)m_prototypes->_M_left; it != m_prototypes;
		it = (TeamPrototypeMapNode *)_STL::_Rb_global<bool>::_M_increment(it))
	{
		it->m_value->teamAboutToBeDeleted(team);
	}
	if (ThePlayerList)
		ThePlayerList->rva002A7AFE(team);
}
