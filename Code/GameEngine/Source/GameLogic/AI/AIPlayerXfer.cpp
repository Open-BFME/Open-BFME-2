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

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *value);
void XferGameDifficulty(Xfer *xfer, int *value);

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};

class TeamInQueue;

class GameWindow
{
public:
	unsigned int winGetStatus();
};

class Rva001DB09DDwordField
{
public:
	int get() const;
	char m_lead[0x10];
	int m_value;
};

class Rva00161220
{
public:
	Rva00161220() throw();
private:
	void *m_vptr;
	char m_pad[0x30 - 4];
};

class Player
{
public:
	char m_pad[0x54];
	int m_playerIndex;
};

class Rva004F040F
{
public:
	void rva004EF383(void *arg);
private:
	char m_pad00[4];
	void *m_04;
	void *m_08;
};

class Rva00160A00
{
	char m_pad[8];
	void *m_08;
public:
	void flip();
};

class AIPlayer
{
public:
	void prependTo_TeamBuildQueue(TeamInQueue *o);
	void reverse_TeamBuildQueue();
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
			void *p = new Rva00161220;
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
			void *p = new Rva00161220;
			((Rva004F040F *)this)->rva004EF383(p);
			*xfer == *(Snapshot *)p;
		}
		((Rva00160A00 *)this)->flip();
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
