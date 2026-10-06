// cl: /EHs /MD
// ??1Rva004209CC@@UAE@XZ, retail 0x004209CC, 65 bytes.
// Virtual dtor: installs vtable 0x0083BD40, frees heap pointer at +0x0C via
// rowed _free 0x00030830, calls rowed base GameEngineDeletingBase dtor
// 0x001B4E74, with __EH_prolog frame 0x00629188. Same EH plus free shape as
// Rva0053FB33Dtor (66B). Evidence: vtable store plus free branch plus base
// call; caller at 0x00420A10; unblocks 0x00420A0D.
extern "C" void __cdecl free(void *block);

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[8];
};

struct Rva004209CCHolder
{
	~Rva004209CCHolder() { if (m_ptr != 0) free(m_ptr); }
	void *m_ptr;
};

class Rva004209CC : public GameEngineDeletingBase
{
public:
	virtual ~Rva004209CC();
private:
	Rva004209CCHolder m_0C;
};

Rva004209CC::~Rva004209CC()
{
}
