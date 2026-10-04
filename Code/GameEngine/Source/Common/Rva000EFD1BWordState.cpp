// Donor:1281192f682ce6f29b8f06b7daea4b5e8fdfbb24 game/GameEngine/Source/Common/Rva007B8100Set.cpp.
// Target EFD1B/14 independently proves word writes at+8/+10 and ret4 ABI.
// Original names and full receiver layout unknown; other bytes are opaque.
// cl: /O1 /G7 /arch:SSE2 /GX- /MD

class Rva000EFD1BWordState
{
public:
	void rva000EFD1B(unsigned int value);

	unsigned char m_unknown00[8];
	unsigned int m_08;
	unsigned char m_unknown0c[4];
	unsigned int m_10;
};

void Rva000EFD1BWordState::rva000EFD1B(unsigned int value)
{
	m_08 = value;
	m_10 = 0;
}
