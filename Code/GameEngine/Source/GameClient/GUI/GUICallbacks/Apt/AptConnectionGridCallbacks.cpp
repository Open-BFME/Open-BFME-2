// cl: /DNDEBUG /MD
//
// The online connection grid's Apt callbacks "Connection::RedrawGrid",
// 0x005DB647, and "Connection::OnRetryConnections", 0x005DB36A, bound as
// member pointers by the grid's constructor 0x005DB6E2; that binding is
// their only reference. GameNetwork already has a Connection class, so the
// class keeps the name the ledger gives the grid's rowed per-player setter
// 0x005DB3B3 (Rva005DB3B3Method.cpp).

// The global at 0x00E063F8 (name unknown) the grid registers in; its
// unrowed 0x005A6D47 retries the connections and +0x28 is the state the
// grid draws.
class Rva005A6D47
{
public:
	void rva005A6D47();

	unsigned char m_pad00[0x28];
	unsigned char m_28; // +0x28
};

extern Rva005A6D47 *g_Va00E063F8;

class Rva005DB3B3
{
public:
	void RedrawGrid(const char *unused);
	void OnRetryConnections(const char *unused);
	void rva005DB630();

	// Rowed 0x005DB3B3 refreshes one player's name and number.
	void rva005DB3B3(int player);
	// Unrowed 0x005DB512 redraws one cell, pinned by address.
	void rva005DB512(void *state, int row, int column);
};

// Retail 0x005DB36A, 18 bytes: "Connection::OnRetryConnections".
void Rva005DB3B3::OnRetryConnections(const char *unused)
{
	if (g_Va00E063F8)
		g_Va00E063F8->rva005A6D47();
}

// Retail 0x005DB630, 23 bytes. Name unknown. Refreshes all eight players.
void Rva005DB3B3::rva005DB630()
{
	for (int player = 0; player < 8; ++player)
		rva005DB3B3(player);
}

// Retail 0x005DB647, 58 bytes: "Connection::RedrawGrid" redraws every
// cell, then every player.
void Rva005DB3B3::RedrawGrid(const char *unused)
{
	Rva005A6D47 *connections = g_Va00E063F8;
	if (connections)
	{
		void *state = &connections->m_28;
		for (int row = 0; row < 8; ++row)
			for (int column = 0; column < 8; ++column)
				rva005DB512(state, row, column);
		rva005DB630();
	}
}
