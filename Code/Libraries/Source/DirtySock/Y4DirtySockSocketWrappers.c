// cl: /Od /GZ /GS /MD /DNDEBUG
/* EA DirtySock socket wrappers, ported verbatim from BFME1
 * Y4DirtySockSocket.c. Retail 0x006699E0 (41B), 0x00669A10 (126B)
 * and 0x0066AB90 (180B).
 *
 * The bind wrapper hands its result to the Winsock error translator,
 * which maps WSAE* failures onto the library's small negative vocabulary.
 * The bounded compare selects unbounded form on negative length; both
 * operands read unsigned, so high-bit differences stay non-negative.
 */

struct Rva007FD4E0Socket
{
	struct Rva007FD4E0Socket *m_next; /* +0x00 */
	struct Rva007FD4E0Socket *m_killNext; /* +0x04 */
	int m_family; /* +0x08 */
	int m_type; /* +0x0C */
	int m_protocol; /* +0x10 */
	char m_opened; /* +0x14 */
	char m_reserved15; /* +0x15 */
	short m_shutdownFlags; /* +0x16 */
	unsigned int m_socket; /* +0x18 */
	char m_gap[0x20];
	void *m_callback; /* +0x3C */
	unsigned int m_lastTick; /* +0x40 */
	unsigned int m_rate; /* +0x44 */
	void *m_callbackData; /* +0x48 */
	void (__cdecl *m_callbackProc)(struct Rva007FD4E0Socket *socket,
		int reason, void *data); /* +0x4C */
};

int __stdcall bind(unsigned int socket, const void *address, int addressLength);
int __stdcall WSAGetLastError(void);
int __stdcall shutdown(unsigned int socket, int how);
int __stdcall listen(unsigned int socket, int backlog);

int Rva007FD540(int result)
{
	if (result < 0)
	{
		result = WSAGetLastError();

		if (result == 10035 || result == 10054)
			result = 0;
		else if (result == 10051 || result == 10065)
			result = -5;
		else if (result == 10057)
			result = -2;
		else if (result == 10061)
			result = -6;
		else
			result = -7;
	}

	return result;
}

int Rva007FD510(struct Rva007FD4E0Socket *socket, const void *address,
	int addressLength)
{
	return Rva007FD540(bind(socket->m_socket, address, addressLength));
}

int Rva007FD4E0(struct Rva007FD4E0Socket *socket, int how)
{
	socket->m_shutdownFlags |= how;
	shutdown(socket->m_socket, how);
	return 0;
}

int Rva007FD7A0(struct Rva007FD4E0Socket *socket, int backlog)
{
	return Rva007FD540(listen(socket->m_socket, backlog));
}

void *g_Rva0130AB60;
int g_Rva0130AB64;

int Rva007FDEB0(int control, int value, void *pointer)
{
	if (control == 'xmap')
		g_Rva0130AB60 = pointer;
	if (control == 'xdns')
		g_Rva0130AB64 = value;
	return -1;
}

int Rva007FE200(const int *value)
{
	return *value;
}

int Rva007FDE80(struct Rva007FD4E0Socket *socket, void *callback,
	unsigned int rate, void *data,
	void (__cdecl *proc)(struct Rva007FD4E0Socket *, int, void *))
{
	socket->m_rate = rate;
	socket->m_callback = callback;
	socket->m_callbackData = data;
	socket->m_callbackProc = proc;
	return 0;
}

struct Rva0130AB68List
{
	unsigned int m_ownerThread; /* +0x00 */
	unsigned int m_depth; /* +0x04 */
	int m_state; /* +0x08 */
	char m_body[4]; /* +0x0C */
};

// g_Rva0130AB68Default: VA 0x00E0A580 (.data zero-fill); five matched DIR32
// witnesses establish this address. Retail initializes the declared 0x10-byte
// structure to zero.
struct Rva0130AB68List g_Rva0130AB68Default = { 0 };

void __declspec(dllimport) __stdcall LeaveCriticalSection(void *body);

void Rva007FECB0(struct Rva0130AB68List *list)
{
	struct Rva0130AB68List *node = list ? list : &g_Rva0130AB68Default;

	if (node->m_depth > 1)
	{
		node->m_depth = node->m_depth - 1;
	}
	else
	{
		node->m_ownerThread = 0;
		node->m_depth = 0;
		node->m_state = 0;
		LeaveCriticalSection(node->m_body);
	}
}

unsigned int __declspec(dllimport) __stdcall GetCurrentThreadId(void);
void __declspec(dllimport) __stdcall EnterCriticalSection(void *body);
long __declspec(dllimport) __stdcall InterlockedExchange(long *target, long value);

int Rva007FEB00(struct Rva0130AB68List *list)
{
	struct Rva0130AB68List *node = list ? list : &g_Rva0130AB68Default;

	if (node->m_ownerThread == GetCurrentThreadId())
	{
		node->m_depth = node->m_depth + 1;
		return 1;
	}

	if (InterlockedExchange((long *)&node->m_state, 1))
		return 0;

	EnterCriticalSection(node->m_body);

	node->m_ownerThread = GetCurrentThreadId();
	node->m_depth = node->m_depth + 1;
	return 1;
}

void __declspec(dllimport) __stdcall Sleep(int interval);

void Rva007FEBD0(struct Rva0130AB68List *list)
{
	struct Rva0130AB68List *node = list ? list : &g_Rva0130AB68Default;

	while (!Rva007FEB00(list))
	{
		EnterCriticalSection(node->m_body);

		if (!InterlockedExchange((long *)&node->m_state, 1))
		{
			node->m_ownerThread = GetCurrentThreadId();
			node->m_depth = node->m_depth + 1;
			return;
		}

		LeaveCriticalSection(node->m_body);
		Sleep(1);
	}
}

void __declspec(dllimport) __stdcall DeleteCriticalSection(void *body);
void __declspec(dllimport) __stdcall InitializeCriticalSection(void *body);

void Rva007FEAA0(struct Rva0130AB68List *list)
{
	struct Rva0130AB68List *node = list ? list : &g_Rva0130AB68Default;

	node->m_state = 0;
	DeleteCriticalSection(node->m_body);
}

void Rva007FEA20(struct Rva0130AB68List *list)
{
	struct Rva0130AB68List *node = list ? list : &g_Rva0130AB68Default;

	node->m_ownerThread = 0;
	node->m_depth = 0;
	node->m_state = 0;
	InitializeCriticalSection(node->m_body);
}

// g_Rva0130AC90: matched references place it at VA 0xe0a6a8 (zero-filled .bss).
int g_Rva0130AC90 = 0;

void Rva007FEE10(void)
{
	Rva007FEBD0(&g_Rva0130AC90);
	Rva007FECB0(&g_Rva0130AC90);
}

// g_Rva0130AB58Head: matched references place it at VA 0xe0a570 (retail .data initial value 0).
void *g_Rva0130AB58Head = 0;
// g_Rva0130AB5CKillList: matched references place it at VA 0xe0a574 (retail .data initial value 0).
struct Rva007FD4E0Socket *g_Rva0130AB5CKillList = 0;
// g_Rva012C3C88Format: matched references place it at VA 0xdd83e0; retail contents, sized to the
// 0x58-byte gap before the next known global there.
char g_Rva012C3C88Format[88] = {
	100, 105, 114, 116, 121, 110, 101, 116,
	119, 105, 110, 58, 32, 119, 97, 114,
	110, 105, 110, 103, 44, 32, 116, 114,
	121, 105, 110, 103, 32, 116, 111, 32,
	99, 108, 111, 115, 101, 32, 115, 111,
	99, 107, 101, 116, 32, 48, 120, 37,
	48, 56, 120, 32, 116, 104, 97, 116,
	32, 105, 115, 32, 110, 111, 116, 32,
	105, 110, 32, 116, 104, 101, 32, 115,
	111, 99, 107, 101, 116, 32, 108, 105,
	115, 116, 10, 0, -1, -1, -1, -1,
};
int Rva007FE780(const char *format, ...);
int __stdcall closesocket(unsigned int socket);

int Rva007FD3F0(struct Rva007FD4E0Socket *socket)
{
	struct Rva007FD4E0Socket **link;
	unsigned char found;

	found = 0;
	Rva007FEBD0(0);
	for (link = (struct Rva007FD4E0Socket **)&g_Rva0130AB58Head;
		*link != 0;
		link = &(*link)->m_next)
	{
		if (*link == socket)
		{
			*link = socket->m_next;
			found = 1;
			break;
		}
	}
	Rva007FECB0(0);

	if (!found)
	{
		Rva007FE780(g_Rva012C3C88Format, socket);
		return -1;
	}

	Rva007FEE10();

	if (socket->m_socket >= 0)
	{
		shutdown(socket->m_socket, 2);
		closesocket(socket->m_socket);
	}
	socket->m_socket = 0xFFFFFFFF;
	socket->m_opened = 0;

	Rva007FEBD0(0);
	socket->m_killNext = g_Rva0130AB5CKillList;
	g_Rva0130AB5CKillList = socket;
	Rva007FECB0(0);
	return 0;
}

int Rva007FE6C0(const char *string1, const char *string2, int length)
{
	int difference;
	const unsigned char *first;
	const unsigned char *second;

	first = (const unsigned char *)string1;
	second = (const unsigned char *)string2;
	if (length < 0)
	{
		for (; *first != 0; first++, second++)
		{
			if (*first != *second)
				return *first - *second;
		}
		return 0;
	}
	for (; length > 0; first++, second++, length--)
	{
		difference = *first - *second;
		if (difference != 0)
			return difference;
	}
	return 0;
}

struct Rva007FD920IpHeader
{
	unsigned char m_versionAndLength; /* +0x00, low nibble is IHL */
	unsigned char m_skip[7];
	unsigned char m_timeToLive; /* +0x08 */
};

int __stdcall setsockopt(unsigned int socket, int level, int option,
	const void *value, int valueLength);
int __stdcall send(unsigned int socket, const char *buffer, int length,
	int flags);
int __stdcall sendto(unsigned int socket, const char *buffer, int length,
	int flags, const void *to, int toLength);
void *Rva007FD660(char *temp, void *address);

int Rva007FD920(struct Rva007FD4E0Socket *socket, const char *buffer,
	int length, int flags, void *to, int toLength)
{
	int result;
	char scratch[0x10];
	const struct Rva007FD920IpHeader *header;
	int timeToLive;

	if (socket->m_type == 3)
	{
		header = (const struct Rva007FD920IpHeader *)buffer;
		timeToLive = header->m_timeToLive;
		setsockopt(socket->m_socket, 0, 4, &timeToLive, 4);

		length -= (header->m_versionAndLength & 0x0F) * 4;
		buffer = buffer + (header->m_versionAndLength & 0x0F) * 4;
		if (length < 0)
			length = 0;
	}

	if (to == 0)
		result = send(socket->m_socket, buffer, length, 0);
	else
		result = sendto(socket->m_socket, buffer, length, 0,
			Rva007FD660(scratch, to), toLength);

	return Rva007FD540(result);
}

int __stdcall recv(unsigned int socket, char *buffer, int length, int flags);
int __stdcall recvfrom(unsigned int socket, char *buffer, int length,
	int flags, char *from, int *fromLength);
unsigned int __declspec(dllimport) __stdcall GetTickCount(void);

unsigned int Rva007FEA00(void)
{
	return GetTickCount();
}

long __cdecl time(long *timer);

unsigned int Rva007FEF60(void)
{
	return time(0);
}

int Rva007FDA50(struct Rva007FD4E0Socket *socket, char *buffer, int length,
	int flags, char *from, int *fromLength)
{
	int result;
	unsigned int tick;
	int translated;

	if (from == 0)
	{
		result = recv(socket->m_socket, buffer, length, 0);
	}
	else
	{
		result = recvfrom(socket->m_socket, buffer, length, 0, from,
			fromLength);
		if (result > 0)
		{
			tick = Rva007FEA00();
			from[11] = (char)tick; tick >>= 8;
			from[10] = (char)tick; tick >>= 8;
			from[9] = (char)tick; tick >>= 8;
			from[8] = (char)tick;
		}
	}

	if (result == 0)
		translated = -1;
	else
		translated = Rva007FD540(result);
	result = translated;

	if (flags & 0x20)
	{
		if (result == -1)
			result = 0;
		else if (result == 0)
			result = -1;
	}
	return result;
}

int __stdcall connect(unsigned int socket, const void *address,
	int addressLength);

int Rva007FD5C0(struct Rva007FD4E0Socket *socket, const void *address,
	int addressLength)
{
	char temp[0x10];

	socket->m_opened = 0;
	return Rva007FD540(connect(socket->m_socket,
		Rva007FD660(temp, (void *)address), addressLength));
}

unsigned int __stdcall socket(int family, int type, int protocol);
int __stdcall ioctlsocket(unsigned int socket, long command,
	unsigned long *argument);
void *Rva007F0000(int size);
void *__cdecl memset(void *destination, int value, unsigned int count);

struct Rva007FD4E0Socket *Rva007FD2D0(int family, int type, int protocol)
{
	unsigned int handle;
	struct Rva007FD4E0Socket *socketObject;
	unsigned long nonblock = 1;

	handle = socket(family, type, protocol);
	if (handle == 0xFFFFFFFF)
		return 0;

	socketObject = (struct Rva007FD4E0Socket *)Rva007F0000(0x50);
	memset(socketObject, 0, 0x50);
	socketObject->m_socket = handle;

	ioctlsocket(handle, 0x8004667E, &nonblock);
	if (type == 2)
		setsockopt(handle, 0xFFFF, 0x20, &nonblock, 4);

	socketObject->m_family = family;
	socketObject->m_type = type;
	socketObject->m_protocol = protocol;

	Rva007FEBD0(0);
	socketObject->m_next = (struct Rva007FD4E0Socket *)g_Rva0130AB58Head;
	g_Rva0130AB58Head = socketObject;
	Rva007FECB0(0);

	return socketObject;
}

unsigned int __stdcall accept(unsigned int socket, void *address,
	unsigned int *addressLength);

struct Rva007FD4E0Socket *Rva007FD7D0(struct Rva007FD4E0Socket *listenSocket,
	void *address, unsigned int *addressLength)
{
	struct Rva007FD4E0Socket *acceptedSocket;
	unsigned int clientHandle;
	unsigned long nonblock;

	acceptedSocket = 0;
	nonblock = 1;

	if (listenSocket->m_socket == 0xFFFFFFFF)
		return 0;

	if (address != 0 && *addressLength < 0x10)
		return 0;

	if (listenSocket->m_family == 2)
	{
		clientHandle = accept(listenSocket->m_socket, address, addressLength);
		if (clientHandle != 0xFFFFFFFF)
		{
			ioctlsocket(clientHandle, 0x8004667E, &nonblock);

			acceptedSocket = (struct Rva007FD4E0Socket *)Rva007F0000(0x50);
			memset(acceptedSocket, 0, 0x50);
			acceptedSocket->m_socket = clientHandle;
			acceptedSocket->m_family = listenSocket->m_family;
			acceptedSocket->m_type = listenSocket->m_type;
			acceptedSocket->m_protocol = listenSocket->m_protocol;
			acceptedSocket->m_opened = 1;

			Rva007FEBD0(0);
			acceptedSocket->m_next = (struct Rva007FD4E0Socket *)g_Rva0130AB58Head;
			g_Rva0130AB58Head = acceptedSocket;
			Rva007FECB0(0);
		}
	}

	return acceptedSocket;
}

// g_Rva0130AB54Version: matched references place it at VA 0xe0a56c (zero-filled .bss).
int g_Rva0130AB54Version = 0;

void *__cdecl memcpy(void *destination, const void *source,
	unsigned int count);
int __stdcall getsockname(unsigned int socket, void *name, int *nameLength);
int __stdcall WSAIoctl(unsigned int socket, unsigned int code,
	const void *inBuffer, int inLength, void *outBuffer, int outLength,
	int *bytesReturned, void *overlapped, void *completion);

#define SOCKET_ADDR_BYTES( p ) \
	( ( ( ( ( (const unsigned char *)( p ) )[ 4 ] << 8 ) \
	| ( (const unsigned char *)( p ) )[ 5 ] ) << 8 \
	| ( (const unsigned char *)( p ) )[ 6 ] ) << 8 \
	| ( (const unsigned char *)( p ) )[ 7 ] )

int Rva007FE310(void *dest, int destLength, const void *src, int srcLength)
{
	unsigned int probeSocket;
	char queryBuffer[0x10];
	int lastError;

	if (destLength != srcLength)
		return -1;

	if (*(const unsigned short *)src == 2)
	{
		memcpy(dest, src, destLength);
		((unsigned char *)dest)[7] = 0;
		((unsigned char *)dest)[6] = 0;
		((unsigned char *)dest)[5] = 0;
		((unsigned char *)dest)[4] = 0;

		probeSocket = socket(2, 2, 0);
		if (probeSocket != 0xFFFFFFFF)
		{
			if (g_Rva0130AB54Version >= 0x200)
			{
				if (WSAIoctl(probeSocket, 0xC8000014, src, srcLength, queryBuffer,
					0x10, &destLength, 0, 0) < 0)
				{
					lastError = WSAGetLastError();
				}
				memcpy((char *)dest + 4, queryBuffer + 4, 4);

				if (SOCKET_ADDR_BYTES(dest) == 0x7F000001)
					memcpy((char *)dest + 4, (const char *)src + 4, 4);
			}

			if (SOCKET_ADDR_BYTES(dest) == 0
				&& connect(probeSocket, src, srcLength) == 0
				&& getsockname(probeSocket, queryBuffer, &destLength) == 0)
			{
				memcpy((char *)dest + 4, queryBuffer + 4, 4);
			}

			closesocket(probeSocket);
		}
		return 0;
	}

	memset(dest, 0, destLength);
	return -3;
}

struct SocketFdSet
{
	unsigned int fd_count;
	unsigned int fd_array[64];
};

struct SocketTimeVal
{
	long tv_sec;
	long tv_usec;
};

#define SOCKET_FD_SET(handle, set) \
	do { \
		unsigned int slotIndex; \
		for (slotIndex = 0; slotIndex < (set)->fd_count; slotIndex++) \
		{ \
			if ((set)->fd_array[slotIndex] == (handle)) \
				break; \
		} \
		if (slotIndex == (set)->fd_count) \
		{ \
			if ((set)->fd_count < 64) \
			{ \
				(set)->fd_array[slotIndex] = (handle); \
				(set)->fd_count++; \
			} \
		} \
	} while (0)

int __stdcall select(int nfds, struct SocketFdSet *readfds,
	struct SocketFdSet *writefds, struct SocketFdSet *exceptfds,
	const struct SocketTimeVal *timeout);
int __stdcall getpeername(unsigned int socket, void *name, int *nameLength);

int Rva007FDB60(struct Rva007FD4E0Socket *socket, int selector, void *buffer,
	int bufferLength)
{
	int queryResult;
	struct SocketFdSet writableSet;
	struct SocketFdSet exceptSet;
	struct SocketTimeVal timeout;
	char peerAddress[0x10];

	if (buffer != 0)
		memset(buffer, 0, bufferLength);

	if (socket->m_socket == 0xFFFFFFFF)
		return -7;

	if (selector == 'conn')
	{
		getpeername(socket->m_socket, buffer, &bufferLength);
		return 0;
	}

	if (selector == 'bind')
	{
		getsockname(socket->m_socket, buffer, &bufferLength);
		return 0;
	}

	if (selector == 'peer')
	{
		getpeername(socket->m_socket, buffer, &bufferLength);
		return 0;
	}

	if (selector == 'stat')
	{
		if (socket->m_opened == 0)
		{
			writableSet.fd_count = 0;
			exceptSet.fd_count = 0;
			SOCKET_FD_SET(socket->m_socket, &writableSet);
			SOCKET_FD_SET(socket->m_socket, &exceptSet);

			timeout.tv_sec = timeout.tv_usec = 0;

			if (select(1, 0, &writableSet, &exceptSet, &timeout) != 0)
			{
				if (exceptSet.fd_count > 0)
					socket->m_opened = -1;
				if (writableSet.fd_count > 0)
					socket->m_opened = 1;
			}
		}

		if (socket->m_opened > 0)
		{
			bufferLength = 0x10;
			queryResult = Rva007FD540(getpeername(socket->m_socket, peerAddress,
				&bufferLength));
			if (queryResult == -2)
				socket->m_opened = -1;
		}

		return socket->m_opened > 0;
	}

	return -1;
}

struct IdleCallbackEntry
{
	void *callbackFunction;
	void *callbackRef;
};

struct IdleCallbackEntry g_Rva0130AB90[64];
int g_Rva0130ACB4;

void Rva007FED40(void *callback, void *ref)
{
	if (callback == 0 || ref == 0)
		return;
	g_Rva0130AB90[g_Rva0130ACB4].callbackFunction = callback;
	g_Rva0130AB90[g_Rva0130ACB4].callbackRef = ref;
	g_Rva0130ACB4++;
}

void Rva007FED90(void *callback, void *ref)
{
	int slotIndex;

	if (callback == 0 || ref == 0)
		return;
	for (slotIndex = 0; slotIndex < g_Rva0130ACB4; slotIndex++)
	{
		if (g_Rva0130AB90[slotIndex].callbackFunction == callback &&
			g_Rva0130AB90[slotIndex].callbackRef == ref)
		{
			g_Rva0130AB90[slotIndex].callbackFunction = 0;
			g_Rva0130AB90[slotIndex].callbackRef = 0;
			break;
		}
	}
}

void Rva007FEE40(void)
{
	int tableIndex;
	void (__cdecl *idleCallback)(void *ref);
	void *callbackRef;

	if (Rva007FEB00(&g_Rva0130AC90) != 0)
	{
		for (tableIndex = 0; tableIndex < g_Rva0130ACB4; tableIndex++)
		{
			idleCallback = (void (__cdecl *)(void *))
				g_Rva0130AB90[tableIndex].callbackFunction;
			callbackRef = g_Rva0130AB90[tableIndex].callbackRef;

			if (idleCallback == 0 || callbackRef == 0)
			{
				g_Rva0130AB90[tableIndex].callbackFunction =
					g_Rva0130AB90[g_Rva0130ACB4 - 1].callbackFunction;
				g_Rva0130AB90[tableIndex].callbackRef =
					g_Rva0130AB90[g_Rva0130ACB4 - 1].callbackRef;
				g_Rva0130AB90[g_Rva0130ACB4 - 1].callbackFunction = 0;
				g_Rva0130AB90[g_Rva0130ACB4 - 1].callbackRef = 0;
				g_Rva0130ACB4 = g_Rva0130ACB4 - 1;
				tableIndex = tableIndex - 1;
				continue;
			}

			idleCallback(callbackRef);
		}

		Rva007FECB0(&g_Rva0130AC90);
	}
}

// g_Rva012C3CDCDraining: matched references place it at VA 0xdd8434 (retail .data initial value -1).
int g_Rva012C3CDCDraining = -1;
// g_Rva0130ACB8Thread: matched references place it at VA 0xe0a6d0 (zero-filled .bss).
int g_Rva0130ACB8Thread = 0;

void Rva007FE620(void)
{
	g_Rva012C3CDCDraining = 1;

	while (g_Rva0130ACB8Thread != 0)
	{
		Rva007FEE40();
		Sleep(0x32);
	}

	g_Rva012C3CDCDraining = 0;
}

void Rva007FE670(void)
{
	g_Rva0130ACB8Thread = 0;

	while (g_Rva012C3CDCDraining > 0)
		Sleep(1);

	Rva007FEAA0(0);
	Rva007FEAA0((struct Rva0130AB68List *)&g_Rva0130AC90);
}

void Rva007F0030(void *object);

void Rva007FD170(struct Rva007FD4E0Socket *listHead)
{
	struct Rva007FD4E0Socket *scanSocket;
	struct Rva007FD4E0Socket *socketList;
	unsigned int nowTick;

	socketList = listHead;
	nowTick = Rva007FEA00();
	Rva007FEBD0(0);

	for (scanSocket = socketList->m_next; scanSocket != 0; scanSocket = scanSocket->m_next)
	{
		if (scanSocket->m_rate != 0 && scanSocket->m_callbackProc != 0
			&& scanSocket->m_lastTick != 0xFFFFFFFF
			&& nowTick - scanSocket->m_lastTick > scanSocket->m_rate)
		{
			scanSocket->m_lastTick = 0xFFFFFFFF;
			scanSocket->m_callbackProc(scanSocket, 0, scanSocket->m_callbackData);
			nowTick = Rva007FEA00();
			scanSocket->m_lastTick = nowTick;
		}
	}

	while ((scanSocket = g_Rva0130AB5CKillList) != 0)
	{
		g_Rva0130AB5CKillList = scanSocket->m_killNext;
		Rva007F0030(scanSocket);
	}

	Rva007FECB0(0);
}

void Rva0081BDE4(void);

void Rva007FD270(void)
{
	Rva007FED90((void *)Rva007FD170, &g_Rva0130AB58Head);
	Rva007FEE10();

	while (g_Rva0130AB58Head != 0)
		Rva007FD3F0((struct Rva007FD4E0Socket *)g_Rva0130AB58Head);

	Rva007FD170(&g_Rva0130AB58Head);
	Rva007FE670();
	Rva0081BDE4();
}

struct WsaStartupData
{
	unsigned short requestedVersion;
	unsigned short highVersion;
	char description[257];
	char systemStatus[129];
	unsigned short maxSockets;
	unsigned short maxUdpDatagrams;
	char *vendorInfo;
};

int __stdcall WSAStartup(unsigned short versionRequested,
	struct WsaStartupData *startupData);
void Rva007FE520(int priority);

void Rva007FD080(int startupPriority)
{
	struct WsaStartupData startupData;
	int startupResult;

	Rva007FE520(startupPriority);
	Rva007FED40((void *)Rva007FD170, &g_Rva0130AB58Head);

	g_Rva0130AB60 = 0;
	g_Rva0130AB64 = 0;

	memset(&startupData, 0, sizeof startupData);
	startupResult = WSAStartup(2, &startupData);

	g_Rva0130AB54Version = ((unsigned char)(startupData.requestedVersion & 0xFF) << 8)
		| (unsigned char)((unsigned int)startupData.requestedVersion >> 8);
}

__declspec(dllimport) int __stdcall CreateThread(
	void *security, unsigned int stackSize, void *start, void *parameter,
	unsigned int flags, unsigned int *identifier);
__declspec(dllimport) void __stdcall SetThreadPriority(int thread, int priority);
__declspec(dllimport) int __stdcall CloseHandle(int object);

// g_Rva012C3CE0Message: matched references place it at VA 0xdd8438; retail contents, sized to the
// 0x24-byte gap before the next known global there.
char g_Rva012C3CE0Message[36] = {
	87, 97, 114, 110, 105, 110, 103, 58,
	32, 78, 101, 116, 67, 114, 105, 116,
	84, 32, 105, 115, 32, 116, 111, 111,
	32, 115, 109, 97, 108, 108, 33, 10,
	0, 0, 0, 0,
};
int Rva007FE780(const char *format, ...);

void Rva007FE520(int priority)
{
	unsigned int pid;

	g_Rva0130ACB4 = 0;
	g_Rva012C3CDCDraining = -1;

	Rva007FEA20(0);
	Rva007FEA20((struct Rva0130AB68List *)&g_Rva0130AC90);

	g_Rva0130ACB8Thread = 1;
	g_Rva0130ACB8Thread = CreateThread(0, 0, (void *)Rva007FE620,
		0, 0, &pid);

	if (g_Rva0130ACB8Thread != 0)
	{
		SetThreadPriority(g_Rva0130ACB8Thread, priority);
		CloseHandle(g_Rva0130ACB8Thread);
	}

	if (0)
		Rva007FE780(g_Rva012C3CE0Message);
}

void Rva007FE210(void *requestObject)
{
	if (InterlockedExchange((long *)((char *)requestObject + 0x54), 1))
		Rva007F0030(requestObject);
}

struct HostLookupRecord
{
	char header[0x0C];
	unsigned char **addressList;
};

struct ResolveRequest
{
	int status;
	unsigned int resolvedAddress;
	char gap[8];
	char hostname[0x44];
	int state;
};

struct HostLookupRecord *__stdcall gethostbyname(const char *name);

int Rva007FE250(struct ResolveRequest *request)
{
	unsigned char *addressBytes;
	struct HostLookupRecord *lookupRecord;

	lookupRecord = gethostbyname(request->hostname);

	if (lookupRecord != 0)
	{
		addressBytes = *lookupRecord->addressList;
		request->resolvedAddress = (addressBytes[0] << 24) | (addressBytes[1] << 16)
			| (addressBytes[2] << 8) | addressBytes[3];
		request->status = 1;
	}
	else
	{
		request->status = -1;
	}

	if (InterlockedExchange((long *)&request->state, 1))
		Rva007F0030(request);

	return 0;
}

int __cdecl Rva007FF080(const char *text)
{
	int charIndex;
	int hashValue;
	int carryBits;

	for (charIndex = 0, hashValue = 0; text[charIndex] != 0; charIndex++)
	{
		carryBits = hashValue & 0xF8000000;
		hashValue = hashValue << 5;
		hashValue = (carryBits >> 27) ^ hashValue;
		hashValue = text[charIndex] ^ hashValue;
	}
	return hashValue;
}

int __cdecl sprintf(char *buffer, const char *format, ...);
// g_Rva0130ACBCGroupMask: matched references place it at VA 0xe0a6d4 (zero-filled .bss).
int g_Rva0130ACBCGroupMask = 0;
// g_Rva012C3D04Format: matched references place it at VA 0xdd845c; retail contents, sized to the
// 0x8-byte gap before the next known global there.
char g_Rva012C3D04Format[8] = {
	37, 48, 52, 120, 0, 0, 0, 0,
};
// g_Rva012C3D0CFormat: matched references place it at VA 0xdd8464; retail contents, sized to the
// 0x8-byte gap before the next known global there.
char g_Rva012C3D0CFormat[8] = {
	37, 48, 50, 120, 0, 0, 0, 0,
};
// g_Rva012C3D14Format: matched references place it at VA 0xdd846c; retail contents, sized to the
// 0x8-byte gap before the next known global there.
char g_Rva012C3D14Format[8] = {
	37, 115, 58, 32, 37, 115, 10, 0,
};
// g_Rva012C3D1CFormat: VA 0x00DD8474 (.data), witnessed by a matched DIR32
// relocation; the 8 retail bytes end at g_Rva012C3D24Offset at 0x00DD847C.
char g_Rva012C3D1CFormat[8] = { 37, 115, 58, 32, 37, 115, 10, 0 };

void Rva007FE880(int group, const unsigned char *buffer, int length)
{
	int i;
	char *pOut;
	char addr[0x10];
	char line[0x80];

	pOut = 0;

	for (i = 0; i < length; i++)
	{
		if (pOut == 0)
		{
			sprintf(addr, g_Rva012C3D04Format, i);
			pOut = line;
		}

		sprintf(pOut, g_Rva012C3D0CFormat, buffer[i]);
		pOut += 2;

		if ((i + 0x11) % 32 == 0)
		{
			*pOut = ' ';
			pOut += 1;
		}

		if ((i + 1) % 32 == 0)
		{
			if (group & g_Rva0130ACBCGroupMask)
				Rva007FE780(g_Rva012C3D14Format, addr, line);
			pOut = 0;
		}
	}

	if (pOut != 0)
	{
		if (group & g_Rva0130ACBCGroupMask)
			Rva007FE780(g_Rva012C3D1CFormat, addr, line);
	}
}

struct Rva007FEF80Tm
{
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};

struct Rva007FEF80Tm *__cdecl gmtime(const long *timer);
struct Rva007FEF80Tm *__cdecl localtime(const long *timer);
// g_Rva012C3D24Offset: matched references place it at VA 0xdd847c (retail .data initial value -1).
int g_Rva012C3D24Offset = -1;

int Rva007FEF80(void)
{
	int iGmt;
	int iLocal;
	long uTime;
	struct Rva007FEF80Tm *pTm;

	if (g_Rva012C3D24Offset == -1)
	{
		uTime = time(0);

		pTm = gmtime(&uTime);
		iGmt = pTm->tm_mday * 86400 + pTm->tm_hour * 3600
			+ pTm->tm_min * 60 + pTm->tm_sec;

		pTm = localtime(&uTime);
		iLocal = pTm->tm_mday * 86400 + pTm->tm_hour * 3600
			+ pTm->tm_min * 60 + pTm->tm_sec;

		g_Rva012C3D24Offset = iLocal - iGmt;
	}

	return g_Rva012C3D24Offset;
}

/* Callers elsewhere reach bodies in this unit through spellings pinned to the same
   retail address (same cdecl/thiscall ABI); bind them here. */
#pragma comment(linker, "/alternatename:?Rva007FEA00Tick@@YAIXZ=_Rva007FEA00")
#pragma comment(linker, "/alternatename:?Rva007FD3F0SocketClose@@YAXPAX@Z=_Rva007FD3F0")
#pragma comment(linker, "/alternatename:?Rva007FD510Bind@@YAHPAXPBXH@Z=_Rva007FD510")
#pragma comment(linker, "/alternatename:?Rva007FD920Send@@YAHPAXPBDHH1H@Z=_Rva007FD920")
#pragma comment(linker, "/alternatename:?Rva007FD2D0SocketOpen@@YAPAXHHH@Z=_Rva007FD2D0")
#pragma comment(linker, "/alternatename:?Rva007FD4E0SocketShutdown@@YAXPAXH@Z=_Rva007FD4E0")
#pragma comment(linker, "/alternatename:?Rva007FDB60SocketInfo@@YAXPAXH0H@Z=_Rva007FDB60")
#pragma comment(linker, "/alternatename:?Rva007FE310SocketHost@@YAXPAURva00804440SockAddr@@H0H@Z=_Rva007FE310")

// Retail's call sites in this unit's matched rows land on bodies rowed under
// other spellings at the same addresses (same ABI). Bind the spellings used here.
#pragma comment(linker, "/alternatename:_Rva0081BDE4=?ji_006556ac@@YAXXZ")
#pragma comment(linker, "/alternatename:?Rva007FDA50Recv@@YAHPAXPADHH1PAH@Z=_Rva007FDA50")
#pragma comment(linker, "/alternatename:?Rva007FDE80SetCallback@@YAHPAXHI00@Z=_Rva007FDE80")
#pragma comment(linker, "/alternatename:?Rva007FEA20ListInit@@YAXPAX@Z=_Rva007FEA20")
#pragma comment(linker, "/alternatename:?Rva007FEAA0ListReset@@YAXPAX@Z=_Rva007FEAA0")
#pragma comment(linker, "/alternatename:?Rva007FEBD0Lock@@YAXPAX@Z=_Rva007FEBD0")
#pragma comment(linker, "/alternatename:?Rva007FECB0Unlock@@YAXPAX@Z=_Rva007FECB0")
