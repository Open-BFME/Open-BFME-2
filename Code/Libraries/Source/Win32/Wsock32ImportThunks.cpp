// cl: /O2 /G7 /Oy /Ob1 /MD /I"reference/open-bfme-1/inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include"
// wsock32.dll import thunks: typed C++ forwarding through the genuine PE
// import-pointer symbols, as Kernel32ImportThunks.cpp and
// User32ImportThunks.cpp do. VS2003 __identifier names the actual decorated
// __imp__ symbol; no alias, address pin, inline assembly, emitted bytes or
// replacement datum is used.
// Signatures: the VS2003 Platform SDK WinSock.h, included through windows.h;
// its declarations carry no dllimport. WinSock.h leaves __WSAFDIsSet's
// parameters unnamed; the documented names are used.
// Each retail six-byte thunk's IAT slot names the export (row notes), except
// ntohl and ntohs: game.dat's rebuilt import table spells their slots htonl
// and htons (reverse/attempt_support/wsock32_ntohl_ntohs_import_slots.md).
#include <windows.h>
extern "C" {
// _ntohl@4
typedef u_long (PASCAL FAR *PFN_ntohl)(u_long);
extern PFN_ntohl __identifier("_imp__ntohl@4");
u_long PASCAL FAR ntohl(u_long netlong) {
 return __identifier("_imp__ntohl@4")(netlong);
}

// _recvfrom@24
typedef int (PASCAL FAR *PFN_recvfrom)(SOCKET, char FAR *, int, int, struct sockaddr FAR *, int FAR *);
extern PFN_recvfrom __identifier("_imp__recvfrom@24");
int PASCAL FAR recvfrom(SOCKET s, char FAR * buf, int len, int flags, struct sockaddr FAR * from, int FAR * fromlen) {
 return __identifier("_imp__recvfrom@24")(s, buf, len, flags, from, fromlen);
}

// _select@20
typedef int (PASCAL FAR *PFN_select)(int, fd_set FAR *, fd_set FAR *, fd_set FAR *, const struct timeval FAR *);
extern PFN_select __identifier("_imp__select@20");
int PASCAL FAR select(int nfds, fd_set FAR * readfds, fd_set FAR * writefds, fd_set FAR * exceptfds, const struct timeval FAR * timeout) {
 return __identifier("_imp__select@20")(nfds, readfds, writefds, exceptfds, timeout);
}

// _htonl@4
typedef u_long (PASCAL FAR *PFN_htonl)(u_long);
extern PFN_htonl __identifier("_imp__htonl@4");
u_long PASCAL FAR htonl(u_long hostlong) {
 return __identifier("_imp__htonl@4")(hostlong);
}

// _closesocket@4
typedef int (PASCAL FAR *PFN_closesocket)(SOCKET);
extern PFN_closesocket __identifier("_imp__closesocket@4");
int PASCAL FAR closesocket(SOCKET s) {
 return __identifier("_imp__closesocket@4")(s);
}

// _bind@12
typedef int (PASCAL FAR *PFN_bind)(SOCKET, const struct sockaddr FAR *, int);
extern PFN_bind __identifier("_imp__bind@12");
int PASCAL FAR bind(SOCKET s, const struct sockaddr FAR * addr, int namelen) {
 return __identifier("_imp__bind@12")(s, addr, namelen);
}

// _htons@4
typedef u_short (PASCAL FAR *PFN_htons)(u_short);
extern PFN_htons __identifier("_imp__htons@4");
u_short PASCAL FAR htons(u_short hostshort) {
 return __identifier("_imp__htons@4")(hostshort);
}

// _socket@12
typedef SOCKET (PASCAL FAR *PFN_socket)(int, int, int);
extern PFN_socket __identifier("_imp__socket@12");
SOCKET PASCAL FAR socket(int af, int type, int protocol) {
 return __identifier("_imp__socket@12")(af, type, protocol);
}

// _send@16
typedef int (PASCAL FAR *PFN_send)(SOCKET, const char FAR *, int, int);
extern PFN_send __identifier("_imp__send@16");
int PASCAL FAR send(SOCKET s, const char FAR * buf, int len, int flags) {
 return __identifier("_imp__send@16")(s, buf, len, flags);
}

// _WSAGetLastError@0
typedef int (PASCAL FAR *PFN_WSAGetLastError)(void);
extern PFN_WSAGetLastError __identifier("_imp__WSAGetLastError@0");
int PASCAL FAR WSAGetLastError(void) {
 return __identifier("_imp__WSAGetLastError@0")();
}

// _connect@12
typedef int (PASCAL FAR *PFN_connect)(SOCKET, const struct sockaddr FAR *, int);
extern PFN_connect __identifier("_imp__connect@12");
int PASCAL FAR connect(SOCKET s, const struct sockaddr FAR * name, int namelen) {
 return __identifier("_imp__connect@12")(s, name, namelen);
}

// _gethostbyname@4
typedef struct hostent FAR * (PASCAL FAR *PFN_gethostbyname)(const char FAR *);
extern PFN_gethostbyname __identifier("_imp__gethostbyname@4");
struct hostent FAR * PASCAL FAR gethostbyname(const char FAR * name) {
 return __identifier("_imp__gethostbyname@4")(name);
}

// _inet_addr@4
typedef unsigned long (PASCAL FAR *PFN_inet_addr)(const char FAR *);
extern PFN_inet_addr __identifier("_imp__inet_addr@4");
unsigned long PASCAL FAR inet_addr(const char FAR * cp) {
 return __identifier("_imp__inet_addr@4")(cp);
}

// _WSACleanup@0
typedef int (PASCAL FAR *PFN_WSACleanup)(void);
extern PFN_WSACleanup __identifier("_imp__WSACleanup@0");
int PASCAL FAR WSACleanup(void) {
 return __identifier("_imp__WSACleanup@0")();
}

// _WSAStartup@8
typedef int (PASCAL FAR *PFN_WSAStartup)(WORD, LPWSADATA);
extern PFN_WSAStartup __identifier("_imp__WSAStartup@8");
int PASCAL FAR WSAStartup(WORD wVersionRequired, LPWSADATA lpWSAData) {
 return __identifier("_imp__WSAStartup@8")(wVersionRequired, lpWSAData);
}

// _ntohs@4
typedef u_short (PASCAL FAR *PFN_ntohs)(u_short);
extern PFN_ntohs __identifier("_imp__ntohs@4");
u_short PASCAL FAR ntohs(u_short netshort) {
 return __identifier("_imp__ntohs@4")(netshort);
}

// _gethostname@8
typedef int (PASCAL FAR *PFN_gethostname)(char FAR *, int);
extern PFN_gethostname __identifier("_imp__gethostname@8");
int PASCAL FAR gethostname(char FAR * name, int namelen) {
 return __identifier("_imp__gethostname@8")(name, namelen);
}

// _shutdown@8
typedef int (PASCAL FAR *PFN_shutdown)(SOCKET, int);
extern PFN_shutdown __identifier("_imp__shutdown@8");
int PASCAL FAR shutdown(SOCKET s, int how) {
 return __identifier("_imp__shutdown@8")(s, how);
}

// _ioctlsocket@12
typedef int (PASCAL FAR *PFN_ioctlsocket)(SOCKET, long, u_long FAR *);
extern PFN_ioctlsocket __identifier("_imp__ioctlsocket@12");
int PASCAL FAR ioctlsocket(SOCKET s, long cmd, u_long FAR * argp) {
 return __identifier("_imp__ioctlsocket@12")(s, cmd, argp);
}

// _setsockopt@20
typedef int (PASCAL FAR *PFN_setsockopt)(SOCKET, int, int, const char FAR *, int);
extern PFN_setsockopt __identifier("_imp__setsockopt@20");
int PASCAL FAR setsockopt(SOCKET s, int level, int optname, const char FAR * optval, int optlen) {
 return __identifier("_imp__setsockopt@20")(s, level, optname, optval, optlen);
}

// _getsockopt@20
typedef int (PASCAL FAR *PFN_getsockopt)(SOCKET, int, int, char FAR *, int FAR *);
extern PFN_getsockopt __identifier("_imp__getsockopt@20");
int PASCAL FAR getsockopt(SOCKET s, int level, int optname, char FAR * optval, int FAR * optlen) {
 return __identifier("_imp__getsockopt@20")(s, level, optname, optval, optlen);
}

// _getsockname@12
typedef int (PASCAL FAR *PFN_getsockname)(SOCKET, struct sockaddr FAR *, int FAR *);
extern PFN_getsockname __identifier("_imp__getsockname@12");
int PASCAL FAR getsockname(SOCKET s, struct sockaddr FAR * name, int FAR * namelen) {
 return __identifier("_imp__getsockname@12")(s, name, namelen);
}

// _sendto@24
typedef int (PASCAL FAR *PFN_sendto)(SOCKET, const char FAR *, int, int, const struct sockaddr FAR *, int);
extern PFN_sendto __identifier("_imp__sendto@24");
int PASCAL FAR sendto(SOCKET s, const char FAR * buf, int len, int flags, const struct sockaddr FAR * to, int tolen) {
 return __identifier("_imp__sendto@24")(s, buf, len, flags, to, tolen);
}

// _recv@16
typedef int (PASCAL FAR *PFN_recv)(SOCKET, char FAR *, int, int);
extern PFN_recv __identifier("_imp__recv@16");
int PASCAL FAR recv(SOCKET s, char FAR * buf, int len, int flags) {
 return __identifier("_imp__recv@16")(s, buf, len, flags);
}

// ___WSAFDIsSet@8
typedef int (PASCAL FAR *PFN___WSAFDIsSet)(SOCKET, fd_set FAR *);
extern PFN___WSAFDIsSet __identifier("_imp____WSAFDIsSet@8");
int PASCAL FAR __WSAFDIsSet(SOCKET fd, fd_set FAR * set) {
 return __identifier("_imp____WSAFDIsSet@8")(fd, set);
}

// _inet_ntoa@4
typedef char FAR * (PASCAL FAR *PFN_inet_ntoa)(struct in_addr);
extern PFN_inet_ntoa __identifier("_imp__inet_ntoa@4");
char FAR * PASCAL FAR inet_ntoa(struct in_addr in) {
 return __identifier("_imp__inet_ntoa@4")(in);
}
}
