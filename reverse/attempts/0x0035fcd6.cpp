// ??0Rva0035FCD6@@QAE@XZ
// partial score=0.95 date=2026-10-06
// ??0Rva0035FCD6@@QAE@XZ
// partial score=0.95 date=2026-10-01
// ??0Rva0035FCD6@@QAE@XZ
// partial score=0.95 date=2026-10-01
// cl: /O1 /MD
// ??0Rva0035FCD6@@QAE@XZ @0x0035FCD6 (52B): ctor storing vtable 0x008166BC,
// same vtable as dtor ??1Rva0035FD0A at 0x0035FD0A. Calls base ??0Rva001DBAA4
// at 0x001DBAA4, zeroes +0x2C/+0x30/+0x10/+0xC/+0x34, sets +0x28=-1,
// +0x14/+0x4=0x1E, byte +9=1. Caller at 0x0035FD95 unblocks 0x0035FD73.
// Same shape as Rva0035F4A6Ctor/Rva0035E2E6Ctor; base layout from Rva001DBAA4Ctor.
class Rva001DBAA4
{
public:
	virtual ~Rva001DBAA4();
	Rva001DBAA4();
	int m_4;
	bool m_8;
	bool m_9;
	bool m_A;
	int m_C;
};
struct Rva0035FCD6Slot
{
	int m_index;
	int m_a;
	int m_b;
	Rva0035FCD6Slot() : m_index(-1), m_a(0), m_b(0) {}
};

class Rva0035FCD6 : public Rva001DBAA4
{
public:
	virtual ~Rva0035FCD6();
	Rva0035FCD6();
	int m_10;
	int m_14;
	char m_pad18[0x28 - 0x18];
	Rva0035FCD6Slot m_28;
	int m_34;
};
// ??0Rva0035FCD6@@QAE@XZ present-unmatched
Rva0035FCD6::Rva0035FCD6()
{
	m_14 = 0x1E;
	m_4 = 0x1E;
	m_10 = 0;
	m_C = 0;
	m_9 = true;
	m_34 = 0;
}
