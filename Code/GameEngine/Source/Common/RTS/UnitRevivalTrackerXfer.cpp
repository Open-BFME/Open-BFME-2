// cl: /Ireference/shims/moduledata /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// UnitRevivalTracker::xfer, retail 0x0037F39E (290 bytes):
// ?xfer@UnitRevivalTracker@@MAEXPAVXfer@@@Z
// Identity (target): WorldBuilder's debug UnitRevivalTracker.cpp
// UnitRevivalTracker::DoXfer calls, in retail's order, the entry transfer
// (0x0037E473), the entry vector's range erase, UnitRevivalEntry's
// constructor (0x0037E352), push_back, the entry destructor and
// PlayerList::getNthPlayer; retail's only reference is a vtable slot
// (0x00818DF0).
// Body (target): Version(1, 1); the entry count (vector at +0x04, 0xD8-byte
// entries) as an unsigned int; on save each entry then the owner's player
// index (+0x10, -1 for none); on load the vector is emptied and refilled
// one transferred entry at a time, then the owner is looked up by index.
// The vector members are the folded STLport bodies already rowed for this
// element (push_back 0x002E2D10, range erase 0x002E2690).
#include "Common/Snapshot.h"
#include <vector>

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

class UnitRevivalEntry
{
public:
	UnitRevivalEntry();
	UnitRevivalEntry(const UnitRevivalEntry &that);
	~UnitRevivalEntry();
	UnitRevivalEntry &operator=(const UnitRevivalEntry &that);
	void rva0037E473(Xfer *xfer);

private:
	char m_bytes[0xD8];
};

typedef _STL::vector<UnitRevivalEntry> UnitRevivalEntryVector;

class UnitRevivalTracker : public Snapshot
{
protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	UnitRevivalEntryVector m_entries; // +0x04
	Player *m_player; // +0x10
};

void UnitRevivalTracker::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;

	unsigned int count = m_entries.size();
	*xfer == count;

	if (xfer->IsStoring())
	{
		for (UnitRevivalEntryVector::iterator it = m_entries.begin(); it != m_entries.end(); ++it)
			it->rva0037E473(xfer);
		int playerIndex;
		if (m_player)
			playerIndex = m_player->getPlayerIndex();
		else
			playerIndex = -1;
		*xfer == playerIndex;
	}
	else
	{
		m_entries.clear();
		for (unsigned int i = 0; i < count; ++i)
		{
			UnitRevivalEntry entry;
			entry.rva0037E473(xfer);
			m_entries.push_back(entry);
		}
		int playerIndex;
		*xfer == playerIndex;
		if (playerIndex != -1)
			m_player = ThePlayerList->getNthPlayer(playerIndex);
		else
			m_player = 0;
	}
}
