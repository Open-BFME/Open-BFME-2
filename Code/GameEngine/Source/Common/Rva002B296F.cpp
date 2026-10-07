// cl: /O1 /DNDEBUG /MD /DWIN32 /D_WINDOWS
//
// ?rva002B296F@Rva002B296F@@QAEXXZ @0x002B296F 29B. Flag init plus
// frames-per-second-derived field: clears +0xE8, sets +0x169 and
// stores g_00DBA4E8 (FramesPerSecond) times 4 at +0x16C. No calls.
//
// Target evidence (game.dat, read-only, capstone): frameless thiscall
// (mov byte [ecx+0xE8],0; mov byte [ecx+0x169],1; mov eax,[0xDBA4E8];
// shl eax,2; mov [ecx+0x16C],eax; ret). Holder and identities
// unproven: honest address-derived names; the g_00DBA4E8 spelling
// follows Rva000806F3BasesParams.cpp.
extern int g_00DBA4E8;

class Rva002B296F
{
public:
	void rva002B296F();
	void rva002B35DF();
private:
	unsigned char m_pad00[0xE4];
	int m_E4;
	unsigned char m_E8;
	unsigned char m_padE9[0x169 - 0xE9];
	unsigned char m_169;
	unsigned char m_pad16A[0x16C - 0x16A];
	int m_16C;
};

// ?rva002B296F@Rva002B296F@@QAEXXZ
void Rva002B296F::rva002B296F()
{
	m_E8 = 0;
	m_169 = 1;
	m_16C = g_00DBA4E8 * 4;
}

// ?rva002B35DF@Rva002B296F@@QAEXXZ @0x002B35DF 24B. Same-class
// refresh over rva002B296F above: re-runs it, then sets +0xE8 and
// stores FramesPerSecond raw at +0xE4.
void Rva002B296F::rva002B35DF()
{
	rva002B296F();
	m_E8 = 1;
	m_E4 = g_00DBA4E8;
}
