// cl: /DNDEBUG /MD /EHsc

typedef unsigned int SOCKET;

extern "C" __declspec(dllimport) int __stdcall shutdown(SOCKET socket, int how);
extern "C" __declspec(dllimport) int __stdcall recvfrom(
	SOCKET socket, char *buffer, int length, int flags, void *from, int *fromLength);
extern "C" __declspec(dllimport) int __stdcall closesocket(SOCKET socket);

// ??1UDP@@QAE@XZ, retail 0x00594918 (69 B): the UDP socket destructor (shutdown, drain
// recvfrom, closesocket). Transport slot clear 0x004D5133 deletes its UDP through it (REL32 0x004D5176).
class UDP
{
public:
	~UDP();

private:
	SOCKET fd;
};

UDP::~UDP()
{
	char pending[1024];
	if (fd != static_cast<SOCKET>(-1)) {
		shutdown(fd, 2);
		while (recvfrom(fd, pending, sizeof(pending), 0, 0, 0) > 0) {
		}
		closesocket(fd);
	}
}
