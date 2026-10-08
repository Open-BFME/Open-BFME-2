// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?findTeamByID@TeamFactory@@QAEPAVTeam@@I@Z @0x0039F761 68B
// Zero Hour TeamFactory::findTeamByID: a null id returns null; otherwise walk
// the prototype map at +0xB0 (header->left begin, rowed _M_increment
// 0x00024250, 8-byte key at +0x10, TeamPrototype at +0x18 as in the sibling
// TeamFactoryFindById.cpp) and return the first non-null
// TeamPrototype::findTeamByID (0x0039D92A). Callers: getTeamNamed 0x003584E9,
// the CaveContain/GarrisonContain/TurretAI xfers and
// AIGuardAttackAggressorState::update with ecx = TheTeamFactory.
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
struct TeamFactoryFindTeamByIDKey
{
	int m_first;
	int m_second;
};
class TeamPrototype
{
public:
	Team *findTeamByID(unsigned int id);
};
struct TeamFactoryFindTeamByIDNode : public _STL::_Rb_tree_node_base
{
	TeamFactoryFindTeamByIDKey m_key10;
	TeamPrototype *m_value18;
};
class TeamFactory
{
public:
	Team *findTeamByID(unsigned int id);
private:
	unsigned char m_pad00[0xB0];
	TeamFactoryFindTeamByIDNode *m_mapB0;
};
Team *TeamFactory::findTeamByID(unsigned int id)
{
	if (id == 0)
		return 0;
	TeamFactoryFindTeamByIDNode *node = (TeamFactoryFindTeamByIDNode *)m_mapB0->_M_left;
	if (node != m_mapB0) {
		do {
			Team *team = node->m_value18->findTeamByID(id);
			if (team)
				return team;
			node = (TeamFactoryFindTeamByIDNode *)_STL::_Rb_global<bool>::_M_increment(node);
		} while (node != m_mapB0);
	}
	return 0;
}
