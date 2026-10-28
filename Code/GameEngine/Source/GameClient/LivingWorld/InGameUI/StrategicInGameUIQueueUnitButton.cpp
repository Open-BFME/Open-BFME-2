// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /DNDEBUG /MD /EHsc
//
// StrategicInGameUIQueueUnitButton.cpp -- StrategicInGameUI::QueueUnitButton
// members at their WorldBuilder home (reverse/wb_name_leads.csv); retail
// supplies the bytes. Target facts: the button keeps the region id at +0x18
// and the queued unit's id at +0x20; the region's virtual slot 13 (+0x34)
// gives its build queue of ids.

#include "ascii_string.h"
#include "unicode_string.h"

// Existing counted-help ABI: the holder is four bytes and the pointee's
// reference count is at +4. Original template spelling is not established.
struct TargetRef00217D4C
{
	void *m_vtbl;
	int m_refCount;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);
struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C(TargetRef00217D4C *ptr) : m_ptr(ptr)
	{
		if (m_ptr)
			++m_ptr->m_refCount;
	}
	~TreeHintRef00217D4C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
	TargetRef00217D4C *m_ptr;
};
class InGameSimpleHelp
{
public:
	InGameSimpleHelp(const UnicodeString &title, const UnicodeString &text);
private:
	char m_opaque[12];
};

class Image;
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;
class SpawnArmy
{
public:
	UnicodeString rva004E25AF(int playerID);
	UnicodeString GetButtonHelp(int playerID);
	unsigned char m_pad00[0x48];
	int m_48;
	int m_4c;
	const Image *GetButtonImage(int playerID);
};

struct QueueUnitButtonIds
{
	int *m_start;
	int *m_finish;

	unsigned int size() const { return m_finish - m_start; }
};

class QueueUnitButtonRegion
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual bool canQueue(int);
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual int getBuildProgress();
	virtual const QueueUnitButtonIds *getBuildQueue();
};

// The region lookup by id (rowed 0x005F88F4, address-named).
int Rva005F88F4Get(int regionID);

class Keyboard
{
public:
	bool isShift();
};
extern Keyboard *TheKeyboard;

class GameMessage
{
public:
	void appendIntegerArgument(int arg);
};

class MessageStream
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual GameMessage *appendMessage(int type);
};
extern MessageStream *TheMessageStream;

// The last position before start (the whole queue when start is out of
// range) holding id, or -1 (inlined in retail).
static inline int FindQueuedBefore(const QueueUnitButtonIds *queue, int id, int start)
{
	int i = (start >= 0 && (unsigned int)start < queue->size()) ? start : queue->size();
	while (i > 0)
	{
		--i;
		if (queue->m_start[i] == id)
			return i;
	}
	return -1;
}

namespace StrategicInGameUI
{
// WB1633D30 names GetButtonImage and its BuildingNoArt fallback. Native
//5F8BD4..5F8C48 is116B: playerID first then the existing208B SpawnArmy
// image-provider receiver. Its EH states prove a dynamic local-static
// initializer with temporary AsciiString; retain that native lifetime.
// Receiver spelling remains the existing address-derived access view.
const Image *GetButtonImage(int playerID, SpawnArmy *army)
{
	static const Image *noArtImage = TheMappedImageCollection->findImageByName(AsciiString("BuildingNoArt"));
	const Image *image = army->GetButtonImage(playerID);
	return image ? image : noArtImage;
}
}

// The spawnable unit's rowed title and description getters (0x004E25AF,
// pinned 0x004E265F) and its +0x48/+0x4C words.

// ??0Rva005E8908@@QAE@HHPAVSpawnArmy@@@Z, native 5F8C48..5F8CAE (104B,
// RET 0xC; caller 0x005E8B66, the army spawn button list): a button record
// holding its first argument and player id, the unit's button image
// (GetButtonImage above), the unit's +0x4C and +0x48 words and its title
// and description for that player. Address-derived names.
class Rva005E8908
{
public:
	Rva005E8908(int value, int playerID, SpawnArmy *unit);

	int m_value;					// +0x00
	int m_playerID;					// +0x04
	const Image *m_image;			// +0x08
	int m_0c;						// +0x0C
	int m_10;						// +0x10
	UnicodeString m_title;			// +0x14
	UnicodeString m_description;	// +0x18
};

Rva005E8908::Rva005E8908(int value, int playerID, SpawnArmy *unit)
	: m_value(value), m_playerID(playerID),
	  m_image(StrategicInGameUI::GetButtonImage(playerID, (SpawnArmy *)unit)),
	  m_0c(unit->m_4c), m_10(unit->m_48),
	  m_title(unit->rva004E25AF(playerID)), m_description(unit->GetButtonHelp(playerID))
{
}

namespace StrategicInGameUI
{

class QueueUnitButton
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	// Slot 4 (pointer at 0x00879CDC).
	virtual void OnRightClicked();
	virtual void v05(); virtual void v06(); virtual void v07();
	// Slot 8 (pointer at 0x00879CEC); hidden four-byte result, RET4.
	virtual TreeHintRef00217D4C CreateHelp();

private:
	unsigned char m_pad04[0x18 - 0x04];
	int m_regionID; // +0x18
	unsigned char m_pad1c[0x20 - 0x1C];
	int m_unitID; // +0x20
	unsigned char m_pad24[4];
	UnicodeString m_helpTitle; // +0x28
	UnicodeString m_helpText; // +0x2C
};
}

// StrategicInGameUI::QueueUnitButton::OnRightClicked, retail 0x005F8B1C
// (184 bytes; WorldBuilder lines 243..263, wb-name-unverified): dequeues one
// (five with shift) of this unit from the region's build queue, newest
// first, by message 0x6AD (region, unit).
void StrategicInGameUI::QueueUnitButton::OnRightClicked()
{
	QueueUnitButtonRegion *region = (QueueUnitButtonRegion *)Rva005F88F4Get(m_regionID);
	if (!region)
		return;

	int count = TheKeyboard->isShift() ? 5 : 1;
	int index = -1;
	for (; count > 0; --count)
	{
		index = FindQueuedBefore(region->getBuildQueue(), m_unitID, index);
		if (index < 0)
			break;
		GameMessage *msg = TheMessageStream->appendMessage(0x6AD);
		msg->appendIntegerArgument(m_regionID);
		msg->appendIntegerArgument(m_unitID);
	}
}

// WB1634790 names CreateHelp; native5F8D07..5F8D5C builds the existing
// 12-byte help object from these two stored strings and acquires one reference.
TreeHintRef00217D4C StrategicInGameUI::QueueUnitButton::CreateHelp()
{
	return TreeHintRef00217D4C((TargetRef00217D4C *)new InGameSimpleHelp(m_helpTitle, m_helpText));
}

// Native 5F8986..5F89A4 counts queued IDs; 5F89A4..5F89CA finds the
// first index. WB 16341E0 and 16342B0 independently prove their loops.
// Progress 5F8A0C..5F8A7E is WB 1634230; update 5F8A7E..5F8B1C
// is WB 1634080. The visible static float helper lets MSVC select
// the native XMM0 return without an artificial vector return type.
// The update's original class name is unproven; it holds region/unit/build
// time at 20/28/2C and updates its button subobject at +8.
class Rva005E1160Flag {public:void rva005E1160(bool);};
class Rva005E1168 {public:void rva005E1168(int);};
class Rva005E1178 {public:void ShowTimerOverlay(float);};
class Rva005F8A7ESub;
void __fastcall hideProductionCount(Rva005F8A7ESub*);
void __fastcall HideTimerOverlay(Rva005F8A7ESub*);
static inline int CountQueuedUnits(const QueueUnitButtonIds*queue,int id) {
 int count=0;
 int*end=queue->m_finish;
 for(int*p=queue->m_start;p!=end;++p)if(*p==id)++count;
 return count;
}
static inline int FindQueuedUnit(const QueueUnitButtonIds*queue,int id) {
 int size=queue->m_finish-queue->m_start;
 for(int i=0;i<size;++i)if(queue->m_start[i]==id)return i;
 return -1;
}
static float GetQueuedUnitProgress(int regionID,int unitID,int buildTime) {
 QueueUnitButtonRegion*region=(QueueUnitButtonRegion*)Rva005F88F4Get(regionID);
 if(region) {
  int index=FindQueuedUnit(region->getBuildQueue(),unitID);
  if(index==0) {
   if(buildTime>0)return (float)region->getBuildProgress()/(float)buildTime;
   return 0.0f;
  }
  if(index>0)return 0.0f;
 }
 return 1.0f;
}
class Rva005F8A7E {public:void rva005F8A7E();char prefix[0x20];int regionID;int unknown24;int unitID;int buildTime;};
// ?Rva005F8A7E::rva005F8A7E present-unmatched
void Rva005F8A7E::rva005F8A7E() {
 QueueUnitButtonRegion*region=(QueueUnitButtonRegion*)Rva005F88F4Get(regionID);
 ((Rva005E1160Flag*)((char*)this+8))->rva005E1160(region&&region->canQueue(unitID));
 int count=region?CountQueuedUnits(region->getBuildQueue(),unitID):0;
 if(count>0)((Rva005E1168*)((char*)this+8))->rva005E1168(count);
 else hideProductionCount((Rva005F8A7ESub*)((char*)this+8));
 if(count>0)((Rva005E1178*)((char*)this+8))->ShowTimerOverlay(GetQueuedUnitProgress(regionID,unitID,buildTime));
 else HideTimerOverlay((Rva005F8A7ESub*)((char*)this+8));
}
