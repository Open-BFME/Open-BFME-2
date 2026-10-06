// cl: /DNDEBUG /MD /EHsc

// Open-BFME: PingThread ICMP ping helper, retail 0x0054F99E, 234 bytes.
// ZH donor is GeneralsMD/Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PingThread.cpp
// (PingThreadClass::doPing). The body measures round-trip time via ICMP.DLL:
// LoadLibrary, resolve IcmpCreateFile/IcmpCloseHandle/IcmpSendEcho, open a
// handle, fill a printable-ASCII request buffer, send one echo and return the
// reply time clamped to the timeout, or -1 on any failure.

typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef int Int;
typedef int BOOL;
typedef void *HMODULE;
typedef void *HANDLE;
typedef unsigned long DWORD;
typedef unsigned short WORD;

extern "C"
{
	__declspec(dllimport) HMODULE __stdcall LoadLibraryA(const char *fileName);
	__declspec(dllimport) void *__stdcall GetProcAddress(HMODULE module, const char *procName);
	__declspec(dllimport) BOOL __stdcall FreeLibrary(HMODULE module);
}

struct PingIpOptionInfo
{
	UnsignedByte ttl;
	UnsignedByte tos;
	UnsignedByte flags;
	UnsignedByte optionsSize;
	void *optionsData;
};

struct PingEchoReply
{
	UnsignedInt sourceAddress;
	UnsignedInt roundTripTime;
	WORD replyDataSize;
	WORD reserved;
	void *replyData;
	PingIpOptionInfo replyOptions;
};

typedef HANDLE (__stdcall *IcmpCreateFileProc)(void);
typedef BOOL (__stdcall *IcmpCloseHandleProc)(HANDLE handle);
typedef DWORD (__stdcall *IcmpSendEchoProc)(HANDLE handle, UnsignedInt destAddress,
	void *requestData, WORD requestSize, void *requestOptions,
	void *replyBuffer, DWORD replySize, DWORD timeoutMs);

// Measure the ICMP round-trip time to an IPv4 address, in milliseconds.
// Returns the reply time clamped to timeoutMs, or -1 when the host cannot
// be pinged through ICMP.DLL.
Int __stdcall MeasureIcmpPing(UnsignedInt destAddress, Int timeoutMs)
{
	Int pingTime = -1;
	Int requestLen = 32;
	Int fillSeed = 32;

	char replyBuffer[sizeof(PingEchoReply) + 8192];
	char requestBuffer[8192];

	HMODULE icmpLib = LoadLibraryA("ICMP.DLL");
	if (icmpLib == 0) {
		goto cleanupDone;
	}

	IcmpCreateFileProc createFile = (IcmpCreateFileProc)GetProcAddress(icmpLib, "IcmpCreateFile");
	IcmpCloseHandleProc closeHandle = (IcmpCloseHandleProc)GetProcAddress(icmpLib, "IcmpCloseHandle");
	IcmpSendEchoProc sendEcho = (IcmpSendEchoProc)GetProcAddress(icmpLib, "IcmpSendEcho");
	if (createFile == 0 || closeHandle == 0 || sendEcho == 0) {
		goto cleanupLib;
	}

	HANDLE icmpHandle = createFile();
	if (icmpHandle == (HANDLE)-1) {
		goto cleanupLib;
	}

	for (Int i = 0, fillValue = fillSeed; i < requestLen; ++i, ++fillValue) {
		fillValue = fillValue >= 126 ? fillSeed : fillValue;
		requestBuffer[i] = (char)fillValue;
	}

	PingIpOptionInfo requestOptions;
	requestOptions.ttl = 64;
	requestOptions.tos = 0;
	requestOptions.flags = 0;
	requestOptions.optionsSize = 0;
	requestOptions.optionsData = 0;

	DWORD replyCount = sendEcho(icmpHandle, destAddress,
		requestBuffer, (WORD)requestLen,
		&requestOptions,
		replyBuffer, sizeof(replyBuffer),
		(DWORD)timeoutMs);
	if (replyCount != 0) {
		pingTime = *(UnsignedInt *)&replyBuffer[8];
		if (pingTime > timeoutMs) {
			pingTime = timeoutMs;
		}
	} else {
		pingTime = -1;
		goto cleanupLib;
	}

cleanupHandle:
	closeHandle(icmpHandle);
cleanupLib:
	FreeLibrary(icmpLib);
cleanupDone:
	return pingTime;
}
