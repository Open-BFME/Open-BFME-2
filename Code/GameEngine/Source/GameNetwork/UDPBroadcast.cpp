// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// ?rva00594B2E@UDP@@QAE_N_N@Z @ 0x00594B2E 40B evidence: UDP setsockopt SOL_SOCKET SO_BROADCAST via IAT wsock32; neighbours UDPErrorMap Rva00594C12Write share flags; caller 0x004D5120 forwards arg
extern "C" __declspec(dllimport) int __stdcall setsockopt(unsigned int s, int level, int optname, const char *optval, int optlen);

class UDP
{
public:
	bool rva00594B2E(bool on);
private:
	unsigned int m_socket;
};

bool UDP::rva00594B2E(bool on)
{
	int val = on;
	return setsockopt(m_socket, 0xffff, 0x20, (const char *)&val, 4) == 0;
}
