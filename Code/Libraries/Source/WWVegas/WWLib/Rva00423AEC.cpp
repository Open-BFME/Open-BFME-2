// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?getValidSelectedObjectsForPlayer@FormationAssistant@@QAE_NPAVPlayer@@PAVRva0029FB3BMember@@@Z @0x00423AEC 147B.
// Unlock: collects matching roster Objects into out list via rowed reset/append
// and filter at this+0x20. Evidence: callees 0x0026549E 0x004D6CAC 0x0028AFA9
// 0x00362437 0x002A1B6F, Player+0x730 roster, Object+0x74 id +0x438 flag.
#include <vector>

class Object;
class Player;
class Squad;
class Rva0029FB3BMember;
class Rva002A1B6FNativeList;
class Rva2225E0Filter;

typedef _STL::vector<Object *> VecObjectPtr;

class Object
{
public:
	virtual ~Object();
	Player *getControllingPlayer() const;
private:
	char m_pad04[0x74 - 0x04];
public:
	void *m_74;
private:
	char m_pad78[0x438 - 0x78];
public:
	unsigned char m_438;
};

class Squad
{
public:
	const VecObjectPtr &rva004D6CAC();
};

class Player
{
public:
	char m_pad[0x730];
	Squad *m_roster;
};

class Rva0029FB3BMember
{
public:
	void *m_head;
	void reset();
};

class Rva002A1B6FNativeList
{
public:
	void append(void *const &value);
};

class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);
};

class FormationAssistant
{
public:
	bool getValidSelectedObjectsForPlayer(Player *player, Rva0029FB3BMember *out);
private:
	char m_pad[0x20];
	Rva2225E0Filter m_filter;
};

bool FormationAssistant::getValidSelectedObjectsForPlayer(Player *player, Rva0029FB3BMember *out)
{
	out->reset();
	if (!player)
		return false;
	Squad *roster = player->m_roster;
	if (!roster)
		return false;
	const VecObjectPtr &objects = roster->rva004D6CAC();
	for (VecObjectPtr::const_iterator it = objects.begin(); it != objects.end(); ++it)
	{
		Object *obj = *it;
		if (!obj)
			continue;
		if (obj->getControllingPlayer() != player)
			continue;
		if (!m_filter.accepts(obj, player))
			continue;
		if (obj->m_438 & 1)
			continue;
		void *val = obj->m_74;
		((Rva002A1B6FNativeList *)out)->append(val);
	}
	void *head = out->m_head;
	return *(void **)head != head;
}
