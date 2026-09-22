// cl: /O1 /DNDEBUG /MD
//
// ?rva007FBE70@Rva007FBC60Game@@QAEPADXZ @0x668370 (15B):
// Rva007FBC60Game platform-buffer accessor used by the FESL game-browser
// record measurement. Returns the +0x190 buffer when its lead byte is set,
// otherwise null. Byte-true via the branchless ternary select.

class Rva007FBC60Game
{
public:
	char *rva007FBE70();
	char m_pad[0x190];
	unsigned char m_platformLead;
};

// ?rva007FBE70@Rva007FBC60Game@@QAEPADXZ
char *Rva007FBC60Game::rva007FBE70()
{
	return m_platformLead ? m_pad + 0x190 : 0;
}
