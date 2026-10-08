// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE
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

#include "ascii_string.h"

// The port negotiation grid (Common/Rva005DB98EGet.cpp): per cell state
// 0x005DB9BC and ping record 0x005DB98E (falloff 0x005A66BF and estimate
// 0x005DB95B rowed in Common/Elem005DB98EFalloff.cpp).
struct Elem005DB98E
{
	float rva005DB95B();
	float rva005A66BF();
};

class PortNegotiationSchema
{
public:
	void *peekPing(unsigned short x, unsigned short y);
	int GetConnectionState(unsigned short x, unsigned short y);
};

extern class GameSpyConfigInterface *TheGameSpyConfig;
int __cdecl Rva005DB335Get(int ping); // ping band 0..3 against TheGameSpyConfig

class Rva00222A8BTarget
{
public:
	int invoke(void *level, const char *name, int count, const char *arg, void *a4, void *a5, void *a6, void *a7);
};
extern Rva00222A8BTarget *TheRva00222A8BTarget;

class AptConnectionScreen
{
public:
	void RedrawGrid(const char *unused);
	void OnRetryConnections(const char *unused);
	void rva005DB630();

	// Rowed 0x005DB3B3 refreshes one player's name and number.
	void UpdateSlotName(int player);
	void UpdateGrid(PortNegotiationSchema *schema, int row, int column);
	static int GetPingImageEnum(Elem005DB98E *ping);

private:
	unsigned char m_pad00[0x5C];
	void *m_level; // +0x5C
};

// Retail 0x005DB36A, 18 bytes: "Connection::OnRetryConnections".
void AptConnectionScreen::OnRetryConnections(const char *unused)
{
	if (g_Va00E063F8)
		g_Va00E063F8->rva005A6D47();
}

// Retail 0x005DB630, 23 bytes. Name unknown. Refreshes all eight players.
void AptConnectionScreen::rva005DB630()
{
	for (int player = 0; player < 8; ++player)
		UpdateSlotName(player);
}

// Retail 0x005DB647, 58 bytes: "Connection::RedrawGrid" redraws every
// cell, then every player.
void AptConnectionScreen::RedrawGrid(const char *unused)
{
	Rva005A6D47 *connections = g_Va00E063F8;
	if (connections)
	{
		PortNegotiationSchema *state = (PortNegotiationSchema *)&connections->m_28;
		for (int row = 0; row < 8; ++row)
			for (int column = 0; column < 8; ++column)
				UpdateGrid(state, row, column);
		rva005DB630();
	}
}

// Retail 0x005DB37C, 53 bytes (WorldBuilder AptConnectionScreen::
// GetPingImageEnum, asserting TheGameSpyConfig): no image without a config
// or a measured ping, else the config's band for the estimate.
int AptConnectionScreen::GetPingImageEnum(Elem005DB98E *ping)
{
	if (TheGameSpyConfig == 0)
		return 0;
	else if (0.0f == ping->rva005A66BF())
		return 0;
	else
		return Rva005DB335Get((int)ping->rva005DB95B());
}

// Retail 0x005DB512, 224 bytes (WorldBuilder AptConnectionScreen::
// UpdateGrid): plays the cell's "UpdateConnection_<row>_<column>" Apt
// function with the frame suffix for its state (retail strings).
void AptConnectionScreen::UpdateGrid(PortNegotiationSchema *schema, int row, int column)
{
	AsciiString function;
	function.format("UpdateConnection_%d_%d", row, column);
	const char *frame = "_empty";
	switch (schema->GetConnectionState(row, column))
	{
	case 1:
		frame = "_waiting";
		break;
	case 2:
		frame = "_connecting";
		break;
	case 3:
	{
		Elem005DB98E *ping = (Elem005DB98E *)schema->peekPing(row, column);
		if (!ping)
			break;
		switch (GetPingImageEnum(ping))
		{
		case 0:
			frame = "_connecting";
			break;
		case 1:
			frame = "_good";
			break;
		case 2:
			frame = "_warning";
			break;
		case 3:
			frame = "_bad";
			break;
		}
		break;
	}
	case 4:
		frame = "_failed";
		break;
	}
	TheRva00222A8BTarget->invoke(m_level, function.str(), 1, frame, 0, 0, 0, 0);
}
