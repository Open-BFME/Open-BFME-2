// cl: /MD
//
// ?rva0057FD6E@Rva0057FD6E@@QAEXXZ, retail 0x0057FD6E, 13 bytes.
// Forwards to rowed 0x005AFC92 when +0x64 non-null, else return.
// Evidence: chain packet calls just-landed 0x005AFC92; caller 0x0057FF87
// ignores return; tail-jmp shape.
class Rva005AFC92
{
public:
	bool rva005AFC92();
	void rva005AFCFF();
	bool rva005AFD2E();
};

class Rva005AFCEC
{
public:
	void rva005AFCB4(int arg);
};

class ChatWindowsInGame
{
public:
	bool rva005B00C8(int arg0, unsigned int arg1, unsigned int arg2);
};

class Rva0057FD6E
{
public:
	void rva0057FD6E();
	void rva0057FD94();
	bool rva0057FDA1();
	void rva0057FDB0(bool arg);
	bool rva0057FD7B(unsigned int arg0, unsigned int arg1, unsigned int arg2);
private:
	char m_pad[100];
	Rva005AFC92 *m_64;
	unsigned char m_68;
};

void Rva0057FD6E::rva0057FD6E()
{
	if (m_64 != 0) {
		m_64->rva005AFC92();
	}
}

// ?rva0057FD94@Rva0057FD6E@@QAEXXZ, retail 0x0057FD94, 13 bytes. Same
// forward shape to rowed 0x005AFCFF. Evidence: chain packet; caller
// 0x0043DCB2; same +0x64 class.
void Rva0057FD6E::rva0057FD94()
{
	if (m_64 != 0) {
		m_64->rva005AFCFF();
	}
}

// ?rva0057FDA1@Rva0057FD6E@@QAE_NXZ, retail 0x0057FDA1, 15 bytes. Same
// +0x64 forward to rowed bool 0x005AFD2E with false on null. Evidence:
// chain packet; caller 0x00511660.
bool Rva0057FD6E::rva0057FDA1()
{
	if (m_64 == 0) {
		return false;
	}
	return m_64->rva005AFD2E();
}

void Rva0057FD6E::rva0057FDB0(bool arg)
{
	if (m_64 != 0) {
		reinterpret_cast<Rva005AFCEC *>(m_64)->rva005AFCB4(*reinterpret_cast<int *>(&arg));
	}
}

// ?rva0057FD7B@Rva0057FD6E@@QAE_NIII@Z, retail 0x0057FD7B, 25 bytes.
// Forwards to recovered 0x005B00C8 when +0x64 non-null and +0x68 non-zero,
// else false. Evidence: gap packet; caller 0x00442CD4 passes three
// message args; ChatWindowsInGame.cpp now owns the callee.
bool Rva0057FD6E::rva0057FD7B(unsigned int arg0, unsigned int arg1, unsigned int arg2)
{
	if (m_64 == 0) {
		return false;
	}
	if (m_68 != 0) {
		return reinterpret_cast<ChatWindowsInGame *>(m_64)->rva005B00C8(arg0, arg1, arg2);
	}
	return false;
}
