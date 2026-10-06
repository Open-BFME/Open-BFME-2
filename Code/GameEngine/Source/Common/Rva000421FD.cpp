// cl: /MD

// ?rva000421FD@Rva000421FD@@QAEXXZ @0x000421FD 21B
// Unlock: missing callee of 2; counter at +0x1B4 with setFPMode on first use.
// Callees rowed: ?setFPMode@@YAXXZ. Prev/next are disp trivials with TU defaults.

void __cdecl setFPMode();

class Rva000421FD
{
	char _pad0[0x1b4];
	int m_1b4;
public:
	void rva000421FD();
};

void Rva000421FD::rva000421FD()
{
	if (m_1b4 == 0)
		setFPMode();
	++m_1b4;
}
