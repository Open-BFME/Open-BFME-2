// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /Ireference/shims/moduledata
//
// ??1GameInfo@@UAE@XZ @0x00400A7F 121B: GameInfo virtual dtor (formerly the address name
// Rva00382FA7; name from ctor 0x00400A07 and the shared vtable); installs vtable
// 0x008193C8 then destroys owned TreeHint ptr at +0xC8 via delete plus null,
// Version at +0x90 via rowed 0x00002152, AsciiString at +0x40 via narrow
// 0x00036410, UnicodeString at +0x04 via wide 0x00036E70, then inline Snapshot
// base restoring 0x00BBB554. Layout from rowed copy 0x00382FA7 and ctor
// 0x00400A07 plus GameInfoReset reset 0x003FFF8F; EH states 3-0.
#include "ascii_string.h"
#include "unicode_string.h"

#include "../../Include/Common/VersionClass.h"

#include "../../Include/GameClient/TreeHintOpaque0043671B.h"

class Xfer;
class Image;
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"

class GameInfo : public Snapshot
{
public:
	virtual ~GameInfo();
	// Retail table 0x00C193C8 (23 slots), spelled as Include/GameNetwork/GameInfo.h
	// spells them, so every unit's copy of the table names the same functions.
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
	virtual void *vslot04();
	virtual void *vslot05();
	virtual const Image *rva00401015(int);
	virtual int vslot07();
	virtual int vslot08();
	virtual int vslot09();
	virtual void reset(); // slot 10
	virtual void startGame(int gameID);
	virtual bool amIHost() const;
	virtual int getLocalSlotNum() const;
	virtual void resetAccepted();
	virtual void resetStartSpots();
	virtual void adjustSlotsForMap();
	virtual void closeOpenSlots();
	virtual bool isSkirmish();
	virtual bool isMultiPlayer();
	virtual bool isSandbox();
	virtual void *vslot21();
	virtual UnicodeString vslot22() const;
private:
	UnicodeString m_04;
	int m_08;
	int m_0C;
	unsigned char m_10;
	unsigned char m_11;
	unsigned char m_12;
	char m_pad13;
	int m_14;
	int m_18[8];
	int m_38;
	int m_3C;
	AsciiString m_40;
	int m_44;
	int m_48;
	int m_4C;
	int m_50;
	int m_54;
	int m_58;
	int m_5C;
	int m_60[10];
	int m_88;
	unsigned char m_8C;
	char m_pad8D[3];
	Version m_90;
	int m_C0;
	int m_C4;
	TreeHintOpaque0043671B *m_C8;
	int m_CC[4];
};

GameInfo::~GameInfo()
{
	if (m_C8 != 0)
	{
		delete m_C8;
		m_C8 = 0;
	}
}
