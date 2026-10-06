// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// ?rva00594976@UDP@@QAEHH@Z @ 0x00594976 53B evidence: UDP ioctlsocket FIONBIO 0x8004667e via IAT wsock32; neighbours udp UDPErrorMap share flags; caller 0x00594C05 pushes 0
extern "C" __declspec(dllimport) int __stdcall ioctlsocket(unsigned int s, long cmd, unsigned long *argp);

class UDP
{
public:
	int rva00594976(int on);
private:
	unsigned int m_socket;
};

int UDP::rva00594976(int on)
{
	unsigned long mode = 1;
	if (on)
		mode = 0;
	if (ioctlsocket(m_socket, 0x8004667e, &mode) == -1)
		return -1;
	return 0;
}
