// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs
//
// ??0Rva005C1A36@@QAE@PAXH@Z
// Retail 0x005C19B6..0x005C1A36 (128 bytes), __thiscall, ret 8.
//
// Constructor of the 0x30-byte AptStats subclass whose vtable is 0x008743DC
// (its destructor ??1Rva005C1A36@@UAE@XZ at 0x005C1A36 follows directly).
// Runs the rowed base ctor ??0AptStats@@QAE@PAX@Z (0x005DD609; AptStats is
// 0x2C bytes) then clears the held object at +0x2C and creates it by kind:
// kind 1 builds the 0x1C-byte Rva005C18F0 (rowed ctor 0x005C1896) and kind 0
// or any other value builds the 0x1C-byte Rva005C1980 (ctor 0x005C1926; its
// destructor is rowed at 0x005C1980). Caller: 0x00522B0E.
//
// Retail lowers the switch with an explicit case 0 test and a default branch
// that both land on the Rva005C1980 block (sub eax,0 / je / dec eax / jne);
// a merged `default: case 0:` label drops the case 0 test so the default
// reaches the shared block through a label. EH states: Rva005C1980 new is
// state 1 and Rva005C18F0 new is state 2.
class AptStats
{
public:
	AptStats(void *host);
	virtual ~AptStats();
	char m_pad[0x28];
};

struct HeldSlot0
{
	virtual void *heldSlot0(int flags);
};

class Rva005C1A36 : public AptStats
{
public:
	Rva005C1A36(void *owner, int kind);
	virtual ~Rva005C1A36();
	HeldSlot0 *m_2c;
};

class Rva005C18F0
{
public:
	Rva005C18F0();
	char opaque_size[0x1c];
};

class Rva005C1980
{
public:
	Rva005C1980();
	char opaque_size[0x1c];
};

Rva005C1A36::Rva005C1A36(void *owner, int kind) : AptStats(owner), m_2c(0)
{
	switch (kind) {
	case 0:
	createDefault:
		m_2c = (HeldSlot0 *)new Rva005C1980;
		break;
	case 1:
		m_2c = (HeldSlot0 *)new Rva005C18F0;
		break;
	default:
		goto createDefault;
	}
}
