// cl: /O1
// ?rva002D36AE@Rva002D36AEHost@@QAEXHH@Z, retail 0x002D36AE 21B chain via rowed 0x005260FC.
// Null-guarded forwarder: inner = m_mid->m_c4; if inner call rowed setter with same args; tail jmp.
// Evidence: callee ?rva005260FC@Rva005260FC@@QAEXPBVAsciiString@@H@Z rowed; caller 0x003BD285; prev 0x002D368E next 0x002D36C3 same /O1.
class AsciiString;

class Rva005260FC
{
public:
	void rva005260FC(const AsciiString *name, int value);
};

struct Rva002D36AEMid
{
	char m_pad[0xC4];
	Rva005260FC *m_c4;
};

class Rva002D36AEHost
{
public:
	void rva002D36AE(int a, int b);
private:
	char m_pad[0x10];
	Rva002D36AEMid *m_mid;
};

void Rva002D36AEHost::rva002D36AE(int a, int b)
{
	Rva005260FC *inner = m_mid->m_c4;
	if (inner != 0)
		inner->rva005260FC((const AsciiString *)a, b);
}
