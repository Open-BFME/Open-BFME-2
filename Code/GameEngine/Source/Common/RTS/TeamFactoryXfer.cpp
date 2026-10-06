// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /DNDEBUG /MD /EHsc
// ?xfer@TeamFactory@@MAEXPAVXfer@@@Z, retail 0x003A308A (527 bytes).
// Identity (target): WorldBuilder's debug Team.cpp TeamFactory::DoXfer
// (callgraph lead) and Zero Hour's TeamFactory::xfer share retail's order:
// the unique team id, the prototype count checked against the map size
// (XferException(5, 0) on mismatch), then on save each prototype's id and
// snapshot over the map (rowed _M_increment 0x00024250), on load
// findTeamPrototypeByID (0x0039F72C) with the same throw when missing.
// Layout (target): the method runs on the Snapshot base at TeamFactory+0x0C,
// so the prototype map (+0xB0) and its count (+0xB4) read at +0xA4/+0xA8 and
// m_uniqueTeamID (+0xC0) at +0xB4; prototypes carry their id at +0x0C.
// BFME 2 deltas (target): a light-CRC early out and Version(1, 3); from
// version 2 a flag (whether the first of 40 prototype slots at +0x10 is
// set) and, when set, each slot's name (+0x14), owner player index (+0x08,
// -1 for none) and singleton bit (+0x18 bit 0); a slot with an owner is
// re-set up on load through 0x003A2C0D (owner, name, singleton, no Dict)
// and, from version 3, moved as a snapshot. Zero Hour's unused
// prototypeName local survives as the constructed-and-released string.
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



namespace _STL
{
struct _Rb_tree_node_base
{
	bool _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class Dummy> class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
};
}

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};

class Player
{
public:
	int getPlayerIndex() const { return m_playerIndex; }

private:
	unsigned char m_pad00[0x54];
	int m_playerIndex; // +0x54
};

class PlayerList
{
public:
	Player *getNthPlayer(int index);
};

extern PlayerList *ThePlayerList;

class Dict;

class TeamPrototype : public Snapshot
{
public:
	unsigned int getID() const { return m_id; }
	Player *getControllingPlayer() const { return m_owningPlayer; }
	const AsciiString &getName() const { return m_name; }
	bool getIsSingleton() const { return (m_flags & 1) != 0; }
	void rva003A2C0D(Player *owner, const AsciiString &name, bool isSingleton, Dict *d);

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	unsigned char m_pad04[0x08 - 0x04];
	Player *m_owningPlayer; // +0x08
	unsigned int m_id; // +0x0C
	unsigned char m_pad10[0x14 - 0x10];
	AsciiString m_name; // +0x14
	int m_flags; // +0x18
};

struct TeamPrototypeKey
{
	int m_first;
	int m_second;
};

struct TeamPrototypeMapNode : public _STL::_Rb_tree_node_base
{
	TeamPrototypeKey m_key; // +0x10
	TeamPrototype *m_value; // +0x18
};

struct TeamPrototypeMap
{
	_STL::_Rb_tree_node_base *m_header; // +0x00
	unsigned int m_nodeCount; // +0x04
	unsigned int size() const { return m_nodeCount; }
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	unsigned char m_pad04[0x0C - 0x04];
};

enum { TEAM_FACTORY_PROTOTYPE_SLOTS = 40 };

class TeamFactory : public SubsystemInterface, public Snapshot
{
public:
	TeamPrototype *findTeamPrototypeByID(unsigned int id);

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	TeamPrototype *m_prototypeSlots[TEAM_FACTORY_PROTOTYPE_SLOTS]; // +0x10
	TeamPrototypeMap m_prototypes; // +0xB0
	unsigned char m_padB8[0xC0 - 0xB8];
	unsigned int m_uniqueTeamID; // +0xC0
};

void TeamFactory::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 3);
	*xfer == version;

	*xfer == m_uniqueTeamID;

	unsigned short prototypeCount = (unsigned short)m_prototypes.size();
	*xfer == prototypeCount;
	if (prototypeCount != m_prototypes.size())
		throw XferException(5, 0);

	unsigned int teamPrototypeID;
	TeamPrototype *teamPrototype;
	AsciiString prototypeName;
	if (xfer->IsStoring())
	{
		for (_STL::_Rb_tree_node_base *it = m_prototypes.m_header->_M_left; it != m_prototypes.m_header;
			it = _STL::_Rb_global<bool>::_M_increment(it))
		{
			teamPrototype = ((TeamPrototypeMapNode *)it)->m_value;
			teamPrototypeID = teamPrototype->getID();
			*xfer == teamPrototypeID;
			*xfer == *teamPrototype;
		}
	}
	else
	{
		for (unsigned short i = 0; i < prototypeCount; ++i)
		{
			*xfer == teamPrototypeID;
			teamPrototype = findTeamPrototypeByID(teamPrototypeID);
			if (teamPrototype == 0)
				throw XferException(5, 0);
			*xfer == *teamPrototype;
		}
	}

	if (version.m_minimum >= 2)
	{
		bool hasSlots = m_prototypeSlots[0] != 0;
		*xfer == hasSlots;
		if (hasSlots)
		{
			for (int i = 0; i < TEAM_FACTORY_PROTOTYPE_SLOTS; ++i)
			{
				TeamPrototype *slot = m_prototypeSlots[i];
				AsciiString name(slot->getName());
				*xfer == name;
				int playerIndex = slot->getControllingPlayer() ? slot->getControllingPlayer()->getPlayerIndex() : -1;
				*xfer == playerIndex;
				bool isSingleton = slot->getIsSingleton();
				*xfer == isSingleton;
				if (playerIndex != -1)
				{
					if (xfer->IsLoading())
					{
						Player *owner = ThePlayerList->getNthPlayer(playerIndex);
						slot->rva003A2C0D(owner, name, isSingleton, 0);
					}
					if (version.m_minimum >= 3)
						*xfer == *slot;
				}
			}
		}
	}
}
