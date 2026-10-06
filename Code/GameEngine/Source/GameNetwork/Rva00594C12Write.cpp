// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// ?rva00594C12@Rva00594C12@@QAEHPBDHKG@Z @0x00594C12 109B UDP::Write donor shape via wsock32 sendto
// Evidence: IAT htons htonl sendto WSAGetLastError; callers 0x004D4CC0 0x00595208 0x005952B0; donor udp.cpp Write with retval=-1 giving or edi eax.
extern "C" __declspec(dllimport) unsigned short __stdcall htons(unsigned short hostshort);
extern "C" __declspec(dllimport) unsigned long __stdcall htonl(unsigned long hostlong);
extern "C" __declspec(dllimport) int __stdcall sendto(unsigned int s, const char *buf, int len, int flags, const void *to, int tolen);
extern "C" __declspec(dllimport) int __stdcall WSAGetLastError(void);

typedef int SOCKET;

struct SockAddrIn
{
	short sin_family;
	unsigned short sin_port;
	unsigned long sin_addr;
	char sin_zero[8];
};

class Rva00594C12
{
public:
	int rva00594C12(const char *buf, int len, unsigned long addr, unsigned short port);
private:
	SOCKET m_socket;
	char m_pad[0x1C - 4];
	int m_lastError;
};
int Rva00594C12::rva00594C12(const char *buf, int len, unsigned long addr, unsigned short port)
{
	if (addr == 0 || port == 0)
		return -7;
	SockAddrIn sa;
	sa.sin_port = htons(port);
	sa.sin_addr = htonl(addr);
	sa.sin_family = 2;
	m_lastError = 0;
	int ret = sendto(m_socket, buf, len, 0, &sa, 16);
	if (ret == -1) {
		ret = -1;
		m_lastError = WSAGetLastError();
	}
	return ret;
}
