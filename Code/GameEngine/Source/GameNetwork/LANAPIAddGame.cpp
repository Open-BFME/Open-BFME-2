// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1
//
// LANAPI::addGame, retail 0x0044B2EA (290 bytes): insert a game into the
// LANAPI game list (+0x10) ordered by case-insensitive name. Ported verbatim
// from Zero Hour's GameEngine/Source/GameNetwork/LANAPI.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference).
// Target evidence: LANAPI::RequestGameCreate (0x0044B55A) calls it with the
// new current game; the body keeps Zero Hour's empty-list, new-head and
// sorted-walk cases over the next link at +0xF5C (the field
// RequestGameCreate clears through setNext) and compares names from
// LANGameInfo vslot 23 (getName, by value) with the rowed
// StringBase<unsigned short>::compareNoCase.

#include <stddef.h>
#include "unicode_string.h"

// Retail registers no unwind state for the compared name temporaries:
// StringBase<unsigned short>::compareNoCase is taken not to throw (as in
// AptSkirmishCallbacks.cpp).
template <> int StringBase<unsigned short>::compareNoCase(const StringBase<unsigned short> &str) const throw();

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap( char (*)[N] ) = 0;
};
template <> class VSlots<0>
{
};

class LANGameInfo : public VSlots<23>
{
public:
	virtual UnicodeString getName( void ) = 0;
	LANGameInfo *getNext( void ) { return m_next; }
	void setNext( LANGameInfo *next ) { m_next = next; }

private:
	unsigned char m_preF5C[0xF5C - 4];
	LANGameInfo *m_next;				// +0xF5C
};

class LANAPI
{
public:
	virtual ~LANAPI( void );

protected:
	void addGame( LANGameInfo *game );

	unsigned char m_pre10[0x10 - 4];
	LANGameInfo *m_games;				// +0x10
};

void LANAPI::addGame( LANGameInfo *game )
{
	if (!m_games)
	{
		m_games = game;
		game->setNext(NULL);
		return;
	}
	else
	{
		if (game->getName().compareNoCase(m_games->getName()) < 0)
		{
			game->setNext(m_games);
			m_games = game;
			return;
		}
		else
		{
			LANGameInfo *g = m_games;
			while (g->getNext() && g->getNext()->getName().compareNoCase(game->getName()) > 0)
			{
				g = g->getNext();
			}
			game->setNext(g->getNext());
			g->setNext(game);
			return;
		}
	}
}
