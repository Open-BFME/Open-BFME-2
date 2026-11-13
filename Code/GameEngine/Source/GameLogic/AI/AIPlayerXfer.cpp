// cl: /O1 /DNDEBUG /MD /EHsc
// ?xfer@AIPlayer@@MAEXPAVXfer@@@Z @0x004F0DDE 740B: AIPlayer::xfer slot 3 of 0x00862DC8 via ctor 0x004F04FC
// Evidence: pin plus LINK BONUS plus ZH AIPlayer.cpp donor plus BFME1 AIPlayer.cpp version comments.

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;

#include "../../../Include/Common/BfmeXfer.h"

#include "../../../Include/Common/XferVersion.h"

#include "../../../../Libraries/Include/Lib/Coord3DBase.h"

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *value);
void XferGameDifficulty(Xfer *xfer, int *value);

#include "../../../Include/Common/XferException.h"

class TeamInQueue;

#include "../../../Include/GameClient/Bfme2GameWindow.h"

#include "../../../Include/GameLogic/Rva001DB09DDwordField.h"

// TeamInQueue: the build-queue record ctor 0x004EF5CE (new 0x30).
#include "TeamInQueue.h"

#include "../../../Include/Common/Player.h"

class AIPlayer
{
public:
	void prependTo_TeamBuildQueue(TeamInQueue *o);
	void prependTo_TeamReadyQueue(TeamInQueue *o);
	void reverse_TeamBuildQueue();
	void flip();	// ZH reverse_TeamReadyQueue, rowed at 0x004F04C0
protected:
	virtual void xfer(Xfer *xfer);
private:
	void *m_teamBuildQueue;
	void *m_teamReadyQueue;
	Player *m_player;
	bool m_readyToBuildTeam;
	bool m_readyToBuildStructure;
	char m_pad12[2];
	int m_teamTimer;
	int m_structureTimer;
	int m_teamSeconds;
	int m_buildDelay;
	int m_teamDelay;
	int m_frameLastBuildingBuilt;
	int m_difficulty;
	int m_skillsetSelector;
	Coord3DBase m_baseCenter;
	bool m_baseCenterSet;
	char m_pad41[3];
	float m_44;
	ObjectID m_48;
	ObjectID m_4C;
	ObjectID m_50;
	Coord3DBase m_54;
	int m_60;
	bool m_64;
	bool m_65;
	char m_pad66[2];
	int m_68;
	unsigned int m_6C;
	ObjectID m_70;
	ObjectID m_74;
};

void AIPlayer::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 2);
	*xfer == version;

	XferObjectID(xfer, &m_70);

	typedef unsigned short UnsignedShort;
	UnsignedShort teamBuildQueueCount = 0;
	for (void *p = m_teamBuildQueue; p;) {
		teamBuildQueueCount++;
		if (!p)
			break;
		p = (void *)((GameWindow *)p)->winGetStatus();
	}
	*xfer == teamBuildQueueCount;

	if (xfer->IsStoring()) {
		for (void *p = m_teamBuildQueue; p;) {
			*xfer == *(Snapshot *)p;
			if (!p)
				break;
			p = (void *)((GameWindow *)p)->winGetStatus();
		}
	} else {
		if (m_teamBuildQueue != 0)
			throw XferException(5, 0);
		for (UnsignedShort i = 0; i < teamBuildQueueCount; ++i) {
			void *p = new TeamInQueue;
			prependTo_TeamBuildQueue((TeamInQueue *)p);
			*xfer == *(Snapshot *)p;
		}
		reverse_TeamBuildQueue();
	}

	UnsignedShort teamReadyQueueCount = 0;
	for (void *p = m_teamReadyQueue; p;) {
		teamReadyQueueCount++;
		if (!p)
			break;
		p = (void *)((Rva001DB09DDwordField *)p)->get();
	}
	*xfer == teamReadyQueueCount;

	if (xfer->IsStoring()) {
		for (void *p = m_teamReadyQueue; p;) {
			*xfer == *(Snapshot *)p;
			if (!p)
				break;
			p = (void *)((Rva001DB09DDwordField *)p)->get();
		}
	} else {
		if (m_teamReadyQueue != 0)
			throw XferException(5, 0);
		for (UnsignedShort i = 0; i < teamReadyQueueCount; ++i) {
			void *p = new TeamInQueue;
			prependTo_TeamReadyQueue((TeamInQueue *)p);
			*xfer == *(Snapshot *)p;
		}
		flip();
	}

	int playerIndex = m_player->m_playerIndex;
	*xfer == playerIndex;
	if (playerIndex != m_player->m_playerIndex)
		throw XferException(5, 0);

	*xfer == m_readyToBuildTeam;
	*xfer == m_readyToBuildStructure;
	*xfer == m_teamTimer;
	*xfer == m_structureTimer;
	*xfer == m_buildDelay;
	*xfer == m_teamDelay;
	*xfer == m_teamSeconds;
	XferObjectID(xfer, &m_74);
	*xfer == m_frameLastBuildingBuilt;
	XferGameDifficulty(xfer, &m_difficulty);
	*xfer == m_skillsetSelector;
	*xfer == m_baseCenter;
	*xfer == m_baseCenterSet;
	*xfer == m_44;
	ObjectID *repairIDs = &m_48;
	int repairLeft = 2;
	do {
		XferObjectID(xfer, repairIDs++);
	} while (--repairLeft != 0);
	XferObjectID(xfer, &m_50);
	*xfer == m_60;
	*xfer == m_64;
	*xfer == m_65;
	*xfer == m_68;
	*xfer == m_54;
	if (version.m_minimum >= 2) {
		*xfer == m_6C;
	}
}
