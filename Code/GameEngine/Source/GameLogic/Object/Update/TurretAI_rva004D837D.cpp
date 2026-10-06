// cl: /DNDEBUG /MD
// ?rva004D837D@TurretAI@@QAEIXZ, retail 0x004D837D, 29 bytes.
// Evidence: unlock lane; +0x10 m_owner (TurretAI_setTurretTargetObject layout);
// +0x258 ptr then +0x21c val else TheGameLogic+0x40 frame; callers 0x4D83D1 0x4D8448 0x4D88AC;
// neighbours TurretAI_rva004D82F6 + OpaqueScalarDeletingDtors.
class GameLogic
{
	char m_pad[0x40];
	unsigned m_frame;
public:
	unsigned getFrame() const { return m_frame; }
};

extern GameLogic *TheGameLogic;

struct Rva004D837DInner
{
	char m_pad[0x21C];
	unsigned m_val21C;
};

struct Rva004D837DOuter
{
	char m_pad[0x258];
	Rva004D837DInner *m_ptr258;
};

class TurretAI
{
	char m_pad[0x10];
	Rva004D837DOuter *m_owner;
public:
	unsigned rva004D837D();
};

unsigned TurretAI::rva004D837D()
{
	Rva004D837DInner *x = m_owner->m_ptr258;
	if (x != 0)
		return x->m_val21C;
	return TheGameLogic->getFrame();
}
