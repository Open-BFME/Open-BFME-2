// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?rva002A7461@Rva002A7461@@QAEHXZ @0x002A7461 98B.
// Capped sum over 0xC-byte entries: total = +0xC + +0x4 plus entry value
// when filter invalid or player check passes, capped at +0x10.
// Evidence: unlock lane, neighbours Rva002A7400Ctor/Rva002A74C3 share /O1,
// callees getNthPlayer/isValid/Player::rva002AB2D9 rowed, ThePlayerList global.
class BfmeTab1026;
class ObjectFilter
{
public:
	bool isValid() const;
private:
	int m_index;
};
class Player
{
public:
	bool rva002AB2D9(BfmeTab1026 *tab, bool flag) const;
};
class PlayerList
{
public:
	Player *getNthPlayer(int i);
};
extern PlayerList *ThePlayerList;
struct Rva002A7461Entry
{
	int m_value;
	int m_pad4;
	ObjectFilter m_filter;
};
class Rva002A7461
{
public:
	int rva002A7461();
private:
	int m_pad0;
	int m_base4;
	int m_base8;
	int m_baseC;
	int m_limit10;
	int m_playerIndex14;
	char m_pad18[8];
	Rva002A7461Entry *m_begin20;
	Rva002A7461Entry *m_end24;
};
int Rva002A7461::rva002A7461()
{
	int total = m_baseC + m_base4;
	Player *player = ThePlayerList->getNthPlayer(m_playerIndex14);
	for (Rva002A7461Entry *it = m_begin20; it != m_end24; ++it)
	{
		if (it->m_filter.isValid())
		{
			if (!player->rva002AB2D9((BfmeTab1026 *)&it->m_filter, true))
				continue;
		}
		total += it->m_value;
	}
	total = total > m_limit10 ? m_limit10 : total;
	return total;
}
