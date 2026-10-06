// cl: -Oy- -GR- -EHsc-
// ?Probe@Rva005B6E32Box@@SAHXZ @0x005B6E32 159B: localhost connectivity probe.
// WSAs up 2.2 into a 416-byte buffer, bails unless both version bytes read
// 2, opens an AF_INET socket, zeroes a sockaddr tail-reusing the buffer,
// sets family/loopback via htonl, connects, closes on success, always
// WSACleanups, and returns 1 unless startup or version failed. Imports
// declared dllimport explicitly (direct slot calls); memset via extern C
// to the thunk row. The sockaddr overlays the buffer tail by union.
extern "C" __declspec(dllimport) int __stdcall WSAStartup(unsigned short v, void *data);
extern "C" __declspec(dllimport) int __stdcall socket(int a, int t, int p);
extern "C" __declspec(dllimport) int __stdcall closesocket(int s);
extern "C" __declspec(dllimport) int __stdcall connect(int s, void *a, int n);
extern "C" __declspec(dllimport) unsigned long __stdcall htonl(unsigned long v);
extern "C" __declspec(dllimport) int __stdcall WSACleanup();
extern "C" void *__cdecl memset(void *dst, int val, unsigned int n);

struct Rva005B6E32Addr
{
	short family;
	unsigned char port[2];
	unsigned long addr;
	char pad[8];
};

union Rva005B6E32Buf
{
	char data[0x1a0];
	struct
	{
		char _p[0x190];
		Rva005B6E32Addr sa;
	} o;
};

struct Rva005B6E32Box
{
	static int Probe();
};

int Rva005B6E32Box::Probe()
{
	Rva005B6E32Buf u;
	if (WSAStartup(0x202, &u.data) != 0)
		return 0;
	int rc;
	if (u.data[0] != 2 || u.data[1] != 2)
		rc = 0;
	else {
		int s = socket(2, 2, 0);
		memset(&u.o.sa, 0, 0x10);
		u.o.sa.family = 2;
		u.o.sa.port[1] = 0;
		u.o.sa.port[0] = 0;
		u.o.sa.addr = 0x7f000001;
		u.o.sa.addr = htonl(0x7f000001);
		if (s != -1) {
			connect(s, &u.o.sa, 0x10);
			closesocket(s);
		}
		rc = 1;
	}
	WSACleanup();
	return rc;
}
