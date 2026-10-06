// cl: /EHs /MD
// ??1Rva002E1F42@@UAE@XZ retail 0x002E1F42 65 bytes.
// Unlock-lane dtor: vptr store 0x00804A84 at +0, frees +0x0C via rowed
// _free 0x00030830 when non-null, then rowed GameEngineDeletingBase dtor
// 0x001B4E74. Evidence: unlock lane (unblocks 0x002E21B5); caller 0x002E21B8
// passes this in ecx; same vptr-plus-free-plus-base shape as dtor lane;
// neighbours carry /O1.
class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
};

extern "C" void free(void *p);

class Rva002E1F42 : public GameEngineDeletingBase
{
public:
	virtual ~Rva002E1F42();
private:
	char m_pad[8];
	char *m_c;
};

Rva002E1F42::~Rva002E1F42()
{
	if (m_c)
		free(m_c);
}
