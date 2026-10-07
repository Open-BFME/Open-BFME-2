// ?rva002A8E7B@Rva002A8E7B@@QAEXXZ
// partial score=0.98 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
#include <map>
#include <vector>

enum ObjectID { ObjectIDInvalid = 0 };

class Object;
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	char m_pad[0x40];
	unsigned int m_frame;
};
extern GameLogic *TheGameLogic;

class Rva004F95DOwner
{
public:
	void rva004F95D();
};

class AIGameTeam
{
public:
	void update();
};

class Rva002A8E7B
{
public:
	void rva002A8E7B();

private:
	char m_pad908[0x908];
	_STL::map<int, int> m_map;
	_STL::vector<AIGameTeam *> m_teams;
	char m_pad920[0x14];
	_STL::vector<ObjectID> m_objectIDs;
};

void Rva002A8E7B::rva002A8E7B()
{
	if (m_teams.begin() == m_teams.end() || TheGameLogic->m_frame < 10)
		return;

	for (_STL::map<int, int>::iterator it = m_map.begin(); it != m_map.end(); ++it)
		((Rva004F95DOwner *)it->second)->rva004F95D();

	_STL::vector<ObjectID>::iterator id = m_objectIDs.begin();
	_STL::vector<ObjectID>::iterator idsEnd = m_objectIDs.end();
	while (id != idsEnd) {
		if (TheGameLogic->findObjectByID(*id) == 0)
		{
			_STL::vector<ObjectID>::iterator nextID = m_objectIDs.erase(id);
			idsEnd = m_objectIDs.end();
			id = nextID;
		}
		else
			++id;
	}

	_STL::vector<AIGameTeam *>::iterator team = m_teams.begin();
	_STL::vector<AIGameTeam *>::iterator *teamsEnd =
		(_STL::vector<AIGameTeam *>::iterator *)((char *)this + 0x918);
	while (team != *teamsEnd) {
		(*team)->update();
		++team;
	}
}
