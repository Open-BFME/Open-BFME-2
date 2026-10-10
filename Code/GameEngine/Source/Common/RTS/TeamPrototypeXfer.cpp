// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /DNDEBUG /MD /GX
// ?xfer@TeamPrototype@@MAEXPAVXfer@@@Z @0x003A3E74 473B: slot 3 of vtable 0x0081AE94 (class of ??1TeamPrototype). Evidence: donor BFME1 Team.cpp xfer plus TeamPrototypeInstanceWalks xfer plus rowed getNthPlayer 0x002A7A29 plus pins 0x0039F761 0x003A3DBE plus disp8 getter 0x005C4AF5.
// Slot 3 is TeamPrototype::xfer, retyped protected (MAE) from retail IsLightCRC early-out and Version(1,2) plus int player index plus Ascii plus bool plus Snapshot plus ushort count plus bool plus floats plus version-gated bools plus uint plus team save/load walks.
#include "ascii_string.h"
#include "Common/Snapshot.h"

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

class MemoryPoolObject
{
public:
	virtual ~MemoryPoolObject();
};

class Player
{
public:
	int getPlayerIndex() const { return m_playerIndex; }
private:
	char m_pad00[0x54];
	int m_playerIndex;
};

class PlayerList
{
public:
	Player *getNthPlayer(int i);
};
extern PlayerList *ThePlayerList;

class Team : public Snapshot, public MemoryPoolObject
{
public:
	Team *dlink_next_TeamInstanceList() const;
private:
	char m_pad08[0x34 - 0x08];
public:
	unsigned int m_id;
private:
	char m_pad38[0x40 - 0x38];
	Team *m_next;
};

template <class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance()
	{
		if (m_cur)
			m_cur = ((*m_cur).*(m_getNextFunc))();
	}
	bool done() const { return m_cur == 0; }
	OBJCLASS* cur() const { return m_cur; }
};

class Script;
class TeamTemplateInfo : public Snapshot
{
public:
	virtual ~TeamTemplateInfo();
protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
private:
	unsigned char m_data[0x318 - 0x12C - 4];
};

class TeamFactory;
struct Rva003A2FD4Proto;
class TeamFactory
{
public:
	Team *findTeamByID(unsigned int id);
	Team *rva003A3DBE(Rva003A2FD4Proto *proto, int n);
};
extern TeamFactory *TheTeamFactory;

class TeamPrototype : public Snapshot
{
public:
	DLINK_ITERATOR<Team> iterate_TeamInstanceList() const
	{
		return DLINK_ITERATOR<Team>(m_teamInstanceListHead, &Team::dlink_next_TeamInstanceList);
	}
protected:
	virtual void xfer(Xfer *xfer);
private:
	TeamFactory *m_factory;
	Player *m_owningPlayer;
	unsigned int m_id;
	AsciiString m_name;
	AsciiString m_ownerName;
	int m_flags;
	bool m_productionConditionAlwaysFalse;
	unsigned char m_pad1D[3];
	AsciiString m_productionConditionName;
	Script *m_productionConditionScript;
	bool m_retrievedGenericScripts;
	unsigned char m_pad29[3];
	Script *m_genericScriptsToRun[32];
	AsciiString m_genericScriptNames[32];
	TeamTemplateInfo m_teamTemplate;
	AsciiString m_attackPriorityName;
	bool m_31C;
	bool m_31D;
	bool m_31E;
	unsigned int m_320;
	bool m_324;
	float m_328;
	float m_32C;
	float m_330;
	Team *m_teamInstanceListHead;
};

void TeamPrototype::xfer(Xfer *xfer)
{
	unsigned int teamID;
	if (xfer->IsLightCRC())
		return;
	Xfer::Version version(1, 2);
	*xfer == version;
	int owningPlayerIndex;
	if (xfer->IsStoring())
		owningPlayerIndex = m_owningPlayer->getPlayerIndex();
	*xfer == owningPlayerIndex;
	m_owningPlayer = ThePlayerList->getNthPlayer(owningPlayerIndex);
	*xfer == m_attackPriorityName;
	*xfer == m_productionConditionAlwaysFalse;
	*xfer == (Snapshot &)m_teamTemplate;
	unsigned short teamInstanceCount = 0;
	for (DLINK_ITERATOR<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
		teamInstanceCount++;
	*xfer == teamInstanceCount;
	*xfer == m_324;
	*xfer == m_328;
	*xfer == m_32C;
	*xfer == m_330;
	if (version.m_minimum >= 2)
	{
		*xfer == m_31C;
		*xfer == m_31D;
		*xfer == m_31E;
		*xfer == m_320;
	}
	if (xfer->IsStoring())
	{
		for (DLINK_ITERATOR<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
		{
			teamID = iter.cur()->m_id;
			*xfer == teamID;
			*xfer == (Snapshot &)*iter.cur();
		}
	}
	else
	{
		for (unsigned short i = 0; i < teamInstanceCount; ++i)
		{
			*xfer == teamID;
			Team *teamInstance = TheTeamFactory->findTeamByID(teamID);
			if (teamInstance == 0)
			{
				teamInstance = TheTeamFactory->rva003A3DBE((Rva003A2FD4Proto *)this, 1);
				if (teamInstance)
					teamInstance->m_id = teamID;
			}
			*xfer == (Snapshot &)*teamInstance;
		}
	}
}
