// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva002AABBC@Player@@QAEXXZ @0x002AABBC (50B): with a current selection
// (+0x730, the Squad view rowed as Rva0018BB10Roster/Gen_0018BC70), rebuild
// its object cache through rowed 0x004D6CAC and hand each object's id
// (Object +0x74) to the AiOrdersManager snapshot at VA 0x00E01E18
// (GameStateInit's g_Va00E01E18) via rowed rva003551EA. Called from the
// unclaimed 0x00377613. Names are address-derived.
#include <vector>

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class Object
{
public:
	char m_pad[0x74];
	int m_id;
};

typedef _STL::vector<Object *> VecObjectPtr;

class Rva0018BB10Roster
{
public:
	const VecObjectPtr &rva004D6CAC();
};

class Rva0035516C
{
public:
	void rva003551EA(NameKeyType key) const;
};

extern void *g_Va00E01E18;

class Player
{
public:
	void rva002AABBC();

private:
	char m_pad[0x730];
	Rva0018BB10Roster *m_currentSelection;
};

void Player::rva002AABBC()
{
	if (m_currentSelection)
	{
		const VecObjectPtr &objects = m_currentSelection->rva004D6CAC();
		for (VecObjectPtr::const_iterator it = objects.begin(); it != objects.end(); ++it)
			((Rva0035516C *)g_Va00E01E18)->rva003551EA((NameKeyType)(*it)->m_id);
	}
}
