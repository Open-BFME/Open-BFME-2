// cl: /MD /GX-
// ?rva002AC673@Player@@QAEXXZ @0x002AC673 (62B): Player science reset.
// Iterates the ScienceType vector at +0x2F0..+0x2F4, notifying ScriptEngine
// via rowed ?rva00357A03@ScriptEngine@@QAEXHW4ScienceType@@@Z at 0x00357A03
// with player index at +0x54, then clears the range through rowed
// vector<ScienceType>::erase at 0x00532803. Caller at 0x002AE258. Prev
// PlayerRva002AC629 next PlayerRva002ACD09.

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
	T *erase(T *first, T *last);
	T *m_start;
	T *m_finish;
	T *m_end;
};
}

class ScriptEngine
{
public:
	void rva00357A03(int playerIndex, ScienceType science);
};
extern ScriptEngine *TheScriptEngine;


class Player
{
public:
	void rva002AC673();
private:
	char m_pad00[0x54];
	int m_playerIndex;
	char m_pad58[0x2F0 - 0x58];
	_STL::vector<ScienceType> m_sciences;
};

void Player::rva002AC673()
{
	ScienceType *end = m_sciences.m_finish;
	_STL::vector<ScienceType> *vec = &m_sciences;
	for (ScienceType *it = vec->m_start; it != end; ++it) {
		TheScriptEngine->rva00357A03(m_playerIndex, *it);
	}
	vec->erase(vec->m_start, vec->m_finish);
}
