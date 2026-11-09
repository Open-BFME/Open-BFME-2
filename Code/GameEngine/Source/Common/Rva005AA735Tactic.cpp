// cl: /MD /GX /DNDEBUG
//
// The "SimpleDefense" skirmish-AI tactic (vtable 0x00871FBC; ctor 0x005AA7DF
// in Rva004ECECDTacticCtors.cpp, dtor 0x005AA735 and ??_G, slot 9 in
// Rva004ECECDTacticCreate.cpp). Base chain, all address-derived: AITacticDefensive
// over AITacticOffensive over the AITactic.cpp object AITactic.
//
//   0x005AA740  slot 3: send the team (0x0039D7A6) to the +0x20 record's
//               point and size it by the record's kind (+0x2C): 1, 3, or
//               half of the owner's objects when there is more than one
#include <stddef.h>

struct Rva0039D7A6Src
{
	int m00;
	int m04;
	int m08;
};

class Rva0039D7A6Setter
{
public:
	void set(const Rva0039D7A6Src *src);
	char m_pad000[0x2D0];
	int m_2D0;		// +0x2D0
};

class Player;

namespace _STL
{
template <class T1, class T2> struct pair
{
	T1 first;
	T2 second;
};
template <class T> struct hash
{
};
template <class T> struct equal_to
{
};
template <class T> class allocator
{
};
template <class K, class V, class H, class E, class A> class hash_map
{
public:
	unsigned int bucket_count() const;
};
}

typedef _STL::hash_map<int, int, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, int> > > IntMap;

#include "../../Include/GameLogic/Rva002A8F24.h"
extern Rva002A8F24 *TheSkirmishAIManager;

struct Rva005AA735Record
{
	char m_pad00[0x0C];
	Rva0039D7A6Src m_point0C;	// +0x0C
	char m_pad18[0x2C - 0x18];
	int m_kind;			// +0x2C
};

#include "../../Include/Common/AITactic.h"
#include "../../Include/Common/AITacticOffensive.h"

class Rva005AA735 : public AITacticOffensive
{
public:
	virtual ~Rva005AA735();
	virtual bool initializeTeamTemplate(Rva0039D7A6Setter *team, void *unused);
};

bool Rva005AA735::initializeTeamTemplate(Rva0039D7A6Setter *team, void *)
{
	team->set(&((Rva005AA735Record *)m_field20)->m_point0C);
	switch (((Rva005AA735Record *)m_field20)->m_kind) {
	case 0:
		team->m_2D0 = 1;
		break;
	case 1:
		team->m_2D0 = 3;
		break;
	case 2: {
		unsigned int count = (*(IntMap **)TheSkirmishAIManager->rva002A8F24(((Player *)m_field24)))->bucket_count();
		if (count > 1)
			team->m_2D0 = (int)(count * 0.5f);
		break;
	}
	}
	return true;
}
