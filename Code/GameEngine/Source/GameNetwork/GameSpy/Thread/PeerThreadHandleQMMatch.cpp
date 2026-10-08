// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?handleQMMatch@PeerThreadClass@@QAEXPAXHHQAPAD11111@Z @0x0038B6C1 502B: quickmatch matched path leaves group room notifies others and posts QM status with IP/port/side/color/nat/extra. Evidence: donor BFME1 PeerThread.cpp handleQMMatch plus PeerHandleQMMatch.cpp 6-field plus port 8088; strings "We're matched!" plus empty g_Rva0107301CEmptyString; callees row peerLeaveRoomA 0x69A2C0 peerMessagePlayerA 0x698F70 ctor 0x389F77 dtor 0x38A063 basic_string assign 0x1B790 atoi strcmpi IAT; global g_00A02340 slot 0x20; QM_WORKING 4 to QM_MATCHED 7.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <string>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <stddef.h>
#include "ascii_string.h"

typedef void *PEER;
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
static const Int MAX_SLOTS = 8;

enum MessageType
{
	NormalMessage,
	ActionMessage
};

enum QMStatus
{
	QM_IDLE,
	QM_JOININGQMCHANNEL,
	QM_LOOKINGFORBOT,
	QM_SENTINFO,
	QM_WORKING,
	QM_POOLSIZE,
	QM_WIDENINGSEARCH,
	QM_MATCHED,
	QM_INCHANNEL,
	QM_NEGOTIATINGFIREWALLS,
	QM_STARTINGGAME,
	QM_COULDNOTFINDBOT,
	QM_COULDNOTFINDCHANNEL,
	QM_COULDNOTNEGOTIATEFIREWALLS,
	QM_STOPPED
};

enum RoomType
{
	TitleRoom,
	GroupRoom,
	StagingRoom
};

struct PeerResponse {
	PeerResponse();
	~PeerResponse();
	int unknown_00;
	std::string unknown_04;
	std::string unknown_10;
	std::string unknown_1c;
	std::wstring unknown_28;
	std::string unknown_34;
	std::string unknown_40;
	std::wstring unknown_4c;
	std::string unknown_58;
	std::string unknown_64;
	std::string unknown_70;
	std::string unknown_7c;
	std::string unknown_88[8];
	std::string unknown_e8;
	std::string unknown_f4;
	_STL::vector<AsciiString> unknown_100;
	int qm_status;
	int qm_pool;
	int qm_mapIdx;
	int qm_seed;
	UnsignedInt qm_IP[8];
	unsigned short qm_port[8];
	Int qm_side[8];
	Int qm_color[8];
	Int qm_nat[8];
	Int qm_extra[8];
	char qm_pad[0x348 - 0x1CC];
};

struct Global003EF728V6;
extern Global003EF728V6 *g_00A02340;
class QMResponseQueueView {
public:
	virtual void unused0();
	virtual void unused1();
	virtual void unused2();
	virtual void unused3();
	virtual void unused4();
	virtual void unused5();
	virtual void unused6();
	virtual void unused7();
	virtual void addResponse(const PeerResponse &resp);
};


extern "C" void peerLeaveRoomA(PEER peer, int roomType, const char *msg);
extern "C" void peerMessagePlayerA(PEER peer, const char *nick, const char *msg, int type);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *s);
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

class PeerThreadClass
{
	char prefix[0x54];
	std::string m_loginName;
	char gap[0x294 - 0x54 - 12];
	QMStatus m_qmStatus;
public:
	void handleQMMatch(PEER peer, Int mapIndex, Int seed,
		char *playerName[MAX_SLOTS], char *playerIP[MAX_SLOTS],
		char *playerSide[MAX_SLOTS], char *playerColor[MAX_SLOTS],
		char *playerNAT[MAX_SLOTS], char *playerExtra[MAX_SLOTS]);
};

void PeerThreadClass::handleQMMatch(PEER peer, Int mapIndex, Int seed,
	char *playerName[MAX_SLOTS], char *playerIP[MAX_SLOTS], char *playerSide[MAX_SLOTS],
	char *playerColor[MAX_SLOTS], char *playerNAT[MAX_SLOTS], char *playerExtra[MAX_SLOTS])
{
	if (m_qmStatus == QM_WORKING) {
		m_qmStatus = QM_MATCHED;
		peerLeaveRoomA(peer, GroupRoom, "");
		for (Int i = 0; i < MAX_SLOTS; ++i) {
			if (playerName[i] && _strcmpi(playerName[i], m_loginName.c_str()))
				peerMessagePlayerA(peer, playerName[i], "We're matched!", NormalMessage);
		}
		PeerResponse resp;
		resp.qm_status = QM_MATCHED;
		resp.unknown_00 = 17;
		for (i = 0; i < MAX_SLOTS; ++i) {
			if (playerName[i]) {
				resp.unknown_88[i] = playerName[i];
				resp.qm_IP[i] = atoi(playerIP[i]);
				resp.qm_port[i] = (unsigned short)(8088 + i);
				resp.qm_side[i] = atoi(playerSide[i]);
				resp.qm_color[i] = atoi(playerColor[i]);
				resp.qm_nat[i] = atoi(playerNAT[i]);
				resp.qm_extra[i] = atoi(playerExtra[i]);
			} else {
				resp.unknown_88[i] = "";
				resp.qm_IP[i] = 0;
				resp.qm_side[i] = 0;
				resp.qm_color[i] = 0;
				resp.qm_nat[i] = 0;
				resp.qm_extra[i] = -1;
			}
		}
		resp.qm_seed = seed;
		resp.qm_mapIdx = mapIndex;
		((QMResponseQueueView *)g_00A02340)->addResponse(resp);
	}
}
