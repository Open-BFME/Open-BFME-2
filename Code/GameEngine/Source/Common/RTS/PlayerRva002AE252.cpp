// cl: /MD /GX- /Ireference/shims/bfme2_ascii
// ?rva002AE252@Player@@QAEXXZ @0x002AE252 (155B): Player science init.
// Resets sciences via rowed rva002AC673, assigns the science vector from the
// template at +0x34 (0x120 vs 0x12C via rowed bfmeCall939D gate and rowed
// vector assign dup 0x0021C21B), grants starting sciences from Store configs
// via pinned get 0x002000D7 and pinned addScience 0x002AD661, then notifies
// ScriptEngine via rowed notify 0x00357F43. Callers at 0x001EC6DA 0x0040F90D.
extern class RankInfoStore *TheRankInfoStore;

extern class GameLogic *TheGameLogic;

enum ScienceType
{
	SCIENCE_INVALID = -1
};

namespace _STL
{
template <class T> class allocator
{
};

template <class T, class A = allocator<T> > class vector
{
public:
	vector &operator=(const vector &other);
	T *m_start;
	T *m_finish;
	T *m_end;
};
}

typedef _STL::vector<int> IntVec;

// The retail assignment target is the rowed four-byte record specialization
// at 0x0021C21B. Keep the science vector's storage and call ABI unchanged.
struct Rva0021C21BElement { char bytes[4]; };
typedef _STL::vector<Rva0021C21BElement> RetailAssignVector;

class BfmeGlob939D
{
public:
	char bfmeCall939D();
};

#define TheBfmeGlob (*(BfmeGlob939D **)&TheGameLogic)

struct PlayerTemplate
{
	char m_pad[0x120];
	IntVec m_vecA;
	IntVec m_vecB;
};

struct Rva002000D7Config
{
	char m_pad[0x38];
	ScienceType *m_start;
	ScienceType *m_finish;
};

class Rva002000D7Store
{
public:
	Rva002000D7Config *get(int index);
};

#define TheStore (*(Rva002000D7Store **)&TheRankInfoStore)

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;


class Player
{
public:
	void rva002AE252();
	void rva002AC673();
	void rva002AE2ED(Player *other);
	void rva002AE475(void *userData);
	int iterateObjects(int (*func)(class Object *, void *), void *userData) const;
private:
	bool addScience(ScienceType science);
	char m_pad00[0x1C];
	int m_count;
	char m_pad20[0x34 - 0x20];
	PlayerTemplate *m_template;
	char m_pad38[0x54 - 0x38];
	int m_playerIndex;
	char m_pad58[0x2F0 - 0x58];
	IntVec m_sciences;
};

void Player::rva002AE252()
{
	rva002AC673();
	if (m_template != 0) {
		bool gate = TheBfmeGlob->bfmeCall939D() != 0;
		if (gate)
			*(RetailAssignVector *)&m_sciences = *(const RetailAssignVector *)&m_template->m_vecB;
		else
			*(RetailAssignVector *)&m_sciences = *(const RetailAssignVector *)&m_template->m_vecA;
	}
	for (int i = 1; i <= m_count; ++i) {
		Rva002000D7Config *cfg = TheStore->get(i);
		if (cfg != 0) {
			for (ScienceType *it = cfg->m_start; it != cfg->m_finish; ++it)
				addScience(*it);
		}
	}
	for (int *it = m_sciences.m_start; it != m_sciences.m_finish; ++it)
		TheScriptEngine->notifyOfAcquiredScience(m_playerIndex, (ScienceType)*it);
}

void Player::rva002AE2ED(Player *other)
{
	IntVec *vec = &other->m_sciences;
	int *start = vec->m_start;
	int *finish = vec->m_finish;
	for (int *it = start; it != finish; ++it)
		addScience((ScienceType)*it);
}

// Native callback 0x002AE435 has a rowed definition with this signature.
class Thing;
class Drawable;
namespace _STL { template <class T, class A> class list; }
int rva002AE435(const Thing *, _STL::list<Drawable *, _STL::allocator<Drawable *> > *);
void Player::rva002AE475(void *userData)
{
	iterateObjects((int (*)(Object *, void *))rva002AE435, userData);
}
