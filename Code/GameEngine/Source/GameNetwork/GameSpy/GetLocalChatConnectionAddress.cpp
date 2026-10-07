// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /O1 /G7
// stlport
//
// GetLocalChatConnectionAddress, retail 0x004FE987 (942 bytes): which local
// address talks to the chat server. PeerThreadClass::connectCallback calls it
// at 0x0038BA8F with "peerchat.gamespy.com" and 6667. Identity: the
// "inetmib1.dll", "snmpapi.dll" and four SnmpExtension/SnmpUtilMem
// GetProcAddress literals and the SNMP tcpConnTable walk are Zero Hour's
// StagingRoomGameInfo.cpp helper line for line (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). The AsciiString is BFME's (8-byte
// header), so it cannot share a unit with the Zero Hour headers.
//
// Read from the retail bytes, like BFME 1's port
// (reference/open-bfme-1/game/.../GetLocalChatConnectionAddress.cpp): no
// DEBUG_LOG, the first query is SNMP_PDU_GET and every later one
// SNMP_PDU_GETNEXT, the bind is reached through bind_list_ptr->list and the
// OID buffer is allocated into it; one wsock32 import slot serves both of
// Zero Hour's ntohl calls (htonl). Unlike BFME 1's port it keeps Zero Hour's
// byte arrays and temp, and a failed query frees the OID buffer too.
//
// The connection record is spelled BfmePod20, the ledger's size-only name for
// the folded 20-byte POD vector instantiation whose push_back retail calls
// (0x0059B8C6); Zero Hour's tag is tConnInfoStruct.
//
// Built /EHs rather than /EHsc: retail stores EH state 0 before each inline
// free of the vector, which /EHsc drops because extern "C" free is then
// assumed not to throw. /D_CRTIMP= gives the direct call to _free (0x00430830).

#include <string.h>
#include <vector>
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef unsigned char BYTE;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef int BOOL;
typedef long AsnInteger32;
typedef long AsnInteger;
typedef void *HANDLE;
typedef void *LPVOID;
typedef struct HINSTANCE__ *HINSTANCE;
typedef int (__stdcall *FARPROC)();

#define NULL 0
#define SNMP_PDU_GET 0xA0
#define SNMP_PDU_GETNEXT 0xA1
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

struct hostent
{
	char *h_name;
	char **h_aliases;
	short h_addrtype;
	short h_length;
	char **h_addr_list;
};

extern "C" __declspec(dllimport) struct hostent * __stdcall gethostbyname(const char *name);
extern "C" __declspec(dllimport) unsigned long __stdcall htonl(unsigned long hostlong);
extern "C" __declspec(dllimport) HINSTANCE __stdcall LoadLibraryA(const char *name);
extern "C" __declspec(dllimport) BOOL __stdcall FreeLibrary(HINSTANCE module);
extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(HINSTANCE module, const char *name);
extern "C" __declspec(dllimport) DWORD __stdcall GetTickCount(void);

typedef struct {
	UINT idLength;
	UINT *ids;
} AsnObjectIdentifier;

typedef struct {
	BYTE *stream;
	UINT length;
	BOOL dynamic;
} AsnOctetString;

typedef struct {
	BYTE asnType;
	union {
		AsnInteger32 number;
		AsnOctetString address;
	} asnValue;
} AsnAny;

typedef struct {
	AsnObjectIdentifier name;
	AsnAny value;
} SnmpVarBind;

typedef struct {
	SnmpVarBind *list;
	UINT len;
} SnmpVarBindList;

typedef SnmpVarBind RFC1157VarBind;
typedef SnmpVarBindList RFC1157VarBindList;

/*
** Function definitions for the MIB-II entry points.
*/

BOOL (__stdcall *SnmpExtensionInitPtr)(DWORD dwUpTimeReference, HANDLE *phSubagentTrapEvent, AsnObjectIdentifier *pFirstSupportedRegion);
BOOL (__stdcall *SnmpExtensionQueryPtr)(BYTE bPduType, RFC1157VarBindList *pVarBindList, AsnInteger32 *pErrorStatus, AsnInteger32 *pErrorIndex);
LPVOID (__stdcall *SnmpUtilMemAllocPtr)(DWORD bytes);
void (__stdcall *SnmpUtilMemFreePtr)(LPVOID pMem);

typedef struct BfmePod20 {
	unsigned int State;
	unsigned long LocalIP;
	unsigned short LocalPort;
	unsigned long RemoteIP;
	unsigned short RemotePort;
} ConnInfoStruct;

Bool GetLocalChatConnectionAddress(AsciiString serverName, UnsignedShort serverPort, UnsignedInt& localIP)
{
	/*
	** Local defines.
	*/
	enum {
		CLOSED = 1,
		LISTENING,
		SYN_SENT,
		SEN_RECEIVED,
		ESTABLISHED,
		FIN_WAIT,
		FIN_WAIT2,
		CLOSE_WAIT,
		LAST_ACK,
		CLOSING,
		TIME_WAIT,
		DELETE_TCB
	};

	enum {
		tcpConnState = 1,
		tcpConnLocalAddress,
		tcpConnLocalPort,
		tcpConnRemAddress,
		tcpConnRemPort
	};

	/*
	** Locals.
	*/
	unsigned char serverAddress[4];
	unsigned char remoteAddress[4];
	HANDLE trap_handle;
	AsnObjectIdentifier first_supported_region;
	std::vector<ConnInfoStruct> connectionVector;
	int last_field;
	int index;
	AsnInteger error_status;
	AsnInteger error_index;
	int conn_entry_type;
	Bool found;

	/*
	** Get the address of the chat server.
	*/
	struct hostent *host_info = gethostbyname(serverName.str());

	if (!host_info) {
		return(false);
	}

	memcpy(serverAddress, &host_info->h_addr_list[0][0], 4);
	unsigned long temp = *((unsigned long*)(&serverAddress[0]));
	temp = htonl(temp);
	*((unsigned long*)(&serverAddress[0])) = temp;

	/*
	** Load the MIB-II SNMP DLL.
	*/
	HINSTANCE mib_ii_dll = LoadLibraryA("inetmib1.dll");
	if (mib_ii_dll == NULL) {
		return(false);
	}

	HINSTANCE snmpapi_dll = LoadLibraryA("snmpapi.dll");
	if (snmpapi_dll == NULL) {
		FreeLibrary(mib_ii_dll);
		return(false);
	}

	/*
	** Get the function pointers into the .dll
	*/
	SnmpExtensionInitPtr = (int (__stdcall *)(unsigned long,void ** ,AsnObjectIdentifier *)) GetProcAddress(mib_ii_dll, "SnmpExtensionInit");
	SnmpExtensionQueryPtr = (int (__stdcall *)(unsigned char,SnmpVarBindList *,long *,long *)) GetProcAddress(mib_ii_dll, "SnmpExtensionQuery");
	SnmpUtilMemAllocPtr = (void *(__stdcall *)(unsigned long)) GetProcAddress(snmpapi_dll, "SnmpUtilMemAlloc");
	SnmpUtilMemFreePtr = (void (__stdcall *)(void *)) GetProcAddress(snmpapi_dll, "SnmpUtilMemFree");
	if (SnmpExtensionInitPtr == NULL || SnmpExtensionQueryPtr == NULL || SnmpUtilMemAllocPtr == NULL || SnmpUtilMemFreePtr == NULL) {
		FreeLibrary(snmpapi_dll);
		FreeLibrary(mib_ii_dll);
		return(false);
	}

	RFC1157VarBindList *bind_list_ptr = (RFC1157VarBindList *) SnmpUtilMemAllocPtr(sizeof(RFC1157VarBindList));
	bind_list_ptr->list = (RFC1157VarBind *) SnmpUtilMemAllocPtr(sizeof(RFC1157VarBind));
	bind_list_ptr->len = 1;

	/*
	** OK, here we go. Try to initialise the .dll
	*/
	int ok = SnmpExtensionInitPtr(GetTickCount(), &trap_handle, &first_supported_region);

	if (!ok) {
		SnmpUtilMemFreePtr(bind_list_ptr->list);
		SnmpUtilMemFreePtr(bind_list_ptr);
		FreeLibrary(snmpapi_dll);
		FreeLibrary(mib_ii_dll);
		return(false);
	}

	/*
	** Name of mib_ii object we want to query. See RFC 1213.
	**
	** iso.org.dod.internet.mgmt.mib-2.tcp.tcpConnTable.TcpConnEntry.tcpConnState
	**  1   3   6      1      2     1   6        13          1             1
	*/
	unsigned int mib_ii_name[] = {1,3,6,1,2,1,6,13,1,1};
	bind_list_ptr->list->name.idLength = ARRAY_SIZE(mib_ii_name);
	bind_list_ptr->list->name.ids = (unsigned int *) SnmpUtilMemAllocPtr(sizeof(mib_ii_name));
	memcpy(bind_list_ptr->list->name.ids, mib_ii_name, sizeof(mib_ii_name));

	/*
	** We start with the tcpConnLocalAddress field.
	*/
	last_field = 1;

	/*
	** First connection.
	*/
	index = 0;

	BYTE pdu_type = SNMP_PDU_GET;

	/*
	** Suck out that tcp connection info....
	*/
	while (true) {

		if (!SnmpExtensionQueryPtr(pdu_type, bind_list_ptr, &error_status, &error_index)) {
			SnmpUtilMemFreePtr(bind_list_ptr->list->name.ids);
			SnmpUtilMemFreePtr(bind_list_ptr->list);
			SnmpUtilMemFreePtr(bind_list_ptr);
			FreeLibrary(snmpapi_dll);
			FreeLibrary(mib_ii_dll);
			return(false);
		}

		/*
		** If this is something new we aren't looking for then we are done.
		*/
		if (bind_list_ptr->list->name.idLength < ARRAY_SIZE(mib_ii_name)) {
			break;
		}

		if (pdu_type == SNMP_PDU_GET) {
			pdu_type = SNMP_PDU_GETNEXT;
		}

		/*
		** Get the type of info we are looking at. See RFC1213.
		*/
		conn_entry_type = bind_list_ptr->list->name.ids[ARRAY_SIZE(mib_ii_name) - 1];

		if (last_field != conn_entry_type) {
			index = 0;
			last_field = conn_entry_type;
		}

		switch (conn_entry_type) {

			case tcpConnState:
			{
				ConnInfoStruct new_conn;
				new_conn.State = bind_list_ptr->list->value.asnValue.number;
				connectionVector.push_back(new_conn);
				break;
			}

			case tcpConnLocalAddress:
				connectionVector[index].LocalIP = *((unsigned long*)bind_list_ptr->list->value.asnValue.address.stream);
				index++;
				break;

			case tcpConnLocalPort:
				connectionVector[index].LocalPort = bind_list_ptr->list->value.asnValue.number;
				index++;
				break;

			case tcpConnRemAddress:
				connectionVector[index].RemoteIP = *((unsigned long*)bind_list_ptr->list->value.asnValue.address.stream);
				index++;
				break;

			case tcpConnRemPort:
				connectionVector[index].RemotePort = bind_list_ptr->list->value.asnValue.number;
				index++;
				break;
		}
	}

	SnmpUtilMemFreePtr(bind_list_ptr->list->name.ids);
	SnmpUtilMemFreePtr(bind_list_ptr->list);
	SnmpUtilMemFreePtr(bind_list_ptr);

	/*
	** Right, we got the lot. Lets see if any of them have the same address as the chat
	** server we think we are talking to.
	*/
	found = false;
	for (Int i=0; i<connectionVector.size(); ++i) {
		ConnInfoStruct connection = connectionVector[i];

		temp = htonl(connection.RemoteIP);
		memcpy(remoteAddress, (unsigned char*)&temp, 4);

		/*
		** See if this connection has the same address as our server.
		*/
		if (!found && memcmp(remoteAddress, serverAddress, 4) == 0) {

			if (serverPort == 0 || serverPort == (unsigned int)connection.RemotePort) {

				/*
				** Make sure the connection is current.
				*/
				if (connection.State == ESTABLISHED) {
					localIP = connection.LocalIP;
					found = true;
				}
			}
		}
	}

	FreeLibrary(snmpapi_dll);
	FreeLibrary(mib_ii_dll);
	return(found);
}
