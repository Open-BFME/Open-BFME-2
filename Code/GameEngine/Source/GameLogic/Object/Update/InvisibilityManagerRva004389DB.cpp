// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfmelist /D_STLP_USE_MALLOC /D_BFME_RETAIL_TREE_INSERT_LAYOUT /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common /ICode/Libraries/Include/Lib /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
// stlport
//
// ?rva004389DB@Rva00439E0C@@QAEXPAVObject@@PAURva004389DBInfo@@H@Z, retail
// 0x004389DB (657 bytes); called from 0x004397F6 and 0x00439F24 with the
// receiver Rva00439E0C (TheGameLogic's +0x178 manager, whose 0x00439E0C is
// WorldBuilder's InvisibilityManager::detected), so the method stays
// address-named on that view.  WorldBuilder twin 0x01281820 is unnamed
// (callgraph lead) and agrees on every branch.
// Detection feedback for a revealed stealth object: if the object's +0x94
// set holds the record's +0x10 entry and the local player controls it, its
// drawable's +0x358 opacity is set to 1.  Then, with a drawable and a
// feedback level: the owner gets the "StealthNeutralized" radar event,
// sound, message and Eva event (level 2 only); an enemy viewer gets the
// "StealthDiscovered" radar event and, given a detector in the record, the
// sound, message and Eva event at the detector; an ally gets the discovered
// sound and Eva event (level 2 only).  The Eva events come from the
// object's template (+0x5C8 enemy, +0x5CC ally, +0x5D0 owner).  The same
// feedback, driven by module data, is StealthUpdate::markAsDetected's tail
// in StealthUpdateLogic.cpp, whose views this unit follows.
#include "GameLogicObjectLookupView.h"
#include "Coord3D.h"
#include <list>
#include <map>
#include "ascii_string.h"
#include "unicode_string.h"
#include "Common/BfmeAudioEventPrefix136.h"

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

template <int N> class Rva004389DBSlots : public Rva004389DBSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004389DBSlots<0>
{
};

class Player
{
public:
	Relationship getRelationship(const Object *that) const;	// 0x002AD11E
	Int getPlayerIndex() const { return m_playerIndex; }
private:
	char m_pad00[0x54];
	Int m_playerIndex;	// +0x54
};

class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_local; }
private:
	char m_pad00[0x10];
	Player *m_local;	// +0x10
};
extern PlayerList *ThePlayerList;

enum RadarEventType
{
	RADAR_EVENT_STEALTH_DISCOVERED = 8,
	RADAR_EVENT_STEALTH_NEUTRALIZED = 9
};

class Radar
{
public:
	void createEvent(const Coord3D *pos, RadarEventType type, Real secondsToLive = 4.0f);	// 0x002D88A4
};
extern Radar *TheRadar;

struct MiscAudio
{
	char m_pad00[0x30];
	OpaqueRefElement4 m_stealthDiscoveredSound;	// +0x30
	OpaqueRefElement4 m_stealthNeutralizedSound;	// +0x34
};

class AudioManager : public Rva004389DBSlots<25>
{
public:
	virtual UnsignedInt addAudioEvent(const BfmeAudioEventPrefix136 *event);	// slot 25
	virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35(); virtual void slot36(); virtual void slot37();
	virtual void slot38(); virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44(); virtual void slot45();
	virtual void slot46(); virtual void slot47(); virtual void slot48(); virtual void slot49();
	virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55(); virtual void slot56(); virtual void slot57();
	virtual void slot58(); virtual void slot59(); virtual void slot60(); virtual void slot61();
	virtual void slot62(); virtual void slot63(); virtual void slot64(); virtual void slot65();
	virtual void slot66(); virtual void slot67(); virtual void slot68(); virtual void slot69();
	virtual void slot70(); virtual void slot71(); virtual void slot72(); virtual void slot73();
	virtual void slot74(); virtual void slot75(); virtual void slot76(); virtual void slot77();
	virtual const MiscAudio *getMiscAudio();	// slot 78
};
extern AudioManager *TheAudio;

// AudioEventRTS::setPlayerIndex (+0x6C), rowed under an address-derived name.
class Rva0033F15DDwordSlot
{
public:
	void set(int value);
};

class Eva
{
public:
	void reportEvaEvent(Int event, const Coord3D *pos, Int flag);	// 0x001DE2DA
};
extern Eva *TheEva;

class GameTextInterface : public Rva004389DBSlots<15>
{
public:
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;	// slot 15
};
extern GameTextInterface *TheGameText;

class InGameUI : public Rva004389DBSlots<16>
{
public:
	virtual void message(UnicodeString format, ...);	// slot 16
};
extern InGameUI *TheInGameUI;

class Drawable
{
public:
	void setSecondMaterialPassOpacity(Real op) { m_secondMaterialPassOpacity = op; }
	bool rva004389DBFlag440() const { return m_440 != 0; }
private:
	char m_pad000[0x358];
	Real m_secondMaterialPassOpacity;	// +0x358
	char m_pad35C[0x440 - 0x35C];
	unsigned char m_440;	// +0x440
};

struct Rva004389DBTemplate
{
	char m_pad000[0x115];
 unsigned char m_kind115;
 char m_pad116[0x5C8-0x116];
	Int m_evaEventDetectedEnemy;	// +0x5C8
	Int m_evaEventDetectedAlly;	// +0x5CC
	Int m_evaEventDetectedOwner;	// +0x5D0
};

// The +0x94 holder's test (0x00331682), rowed under an address-derived name.
class Rva00331682Holder
{
public:
	bool test(const void *key) const;
};

class Object
{
public:
	Object *rva002931F5(bool);
 Player *getControllingPlayer() const;	// 0x0028AFA9
	Drawable *getDrawable() const;	// 0x005508E2
	const Rva004389DBTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	ObjectID getID() const { return m_id; }
	const Rva00331682Holder &rva004389DBHolder() const { return m_holder94; }
private:
	void *m_vtable;
	const Rva004389DBTemplate *m_template;	// +0x04
	char m_pad08[0x38 - 0x08];
	Coord3D m_position;	// +0x38
	char m_pad44[0x74 - 0x44];
	ObjectID m_id;	// +0x74
	char m_pad78[0x94 - 0x78];
	Rva00331682Holder m_holder94;	// +0x94
};

struct Rva004389DBInfo
{
	Object *m_detector;	// +0x00
	char m_pad04[0x0C];
	char m_key10[4];	// +0x10
};

class Rva00439E0C
{
public:
	void rva004389DB(Object *obj, Rva004389DBInfo *info, Int feedback);
};

void Rva00439E0C::rva004389DB(Object *obj, Rva004389DBInfo *info, Int feedback)
{
	if (obj->rva004389DBHolder().test(info->m_key10))
	{
		if (obj->getControllingPlayer() == ThePlayerList->getLocalPlayer())
		{
			Drawable *draw = obj->getDrawable();
			if (draw)
				draw->setSecondMaterialPassOpacity(1.0f);
		}
	}

	Drawable *draw = obj->getDrawable();
	if (!draw || !feedback)
		return;

	Player *localPlayer = ThePlayerList->getLocalPlayer();
	if (localPlayer == obj->getControllingPlayer())
	{
		if (feedback == 2)
		{
			TheRadar->createEvent(obj->getPosition(), RADAR_EVENT_STEALTH_NEUTRALIZED);
			BfmeAudioEventPrefix136 neutralizedSound(TheAudio->getMiscAudio()->m_stealthNeutralizedSound, obj->getID());
			((Rva0033F15DDwordSlot *)&neutralizedSound)->set(localPlayer->getPlayerIndex());
			TheAudio->addAudioEvent(&neutralizedSound);
			TheInGameUI->message(TheGameText->fetch("MESSAGE:StealthNeutralized"));
			Int message = obj->getTemplate()->m_evaEventDetectedOwner;
			TheEva->reportEvaEvent(message, obj->getPosition(), 0);
		}
	}
	else if (localPlayer->getRelationship(obj) != ALLIES)
	{
		if (!draw->rva004389DBFlag440())
		{
			TheRadar->createEvent(obj->getPosition(), RADAR_EVENT_STEALTH_DISCOVERED);
			if (info->m_detector)
			{
				BfmeAudioEventPrefix136 discoveredSound(TheAudio->getMiscAudio()->m_stealthDiscoveredSound, info->m_detector->getID());
				((Rva0033F15DDwordSlot *)&discoveredSound)->set(localPlayer->getPlayerIndex());
				TheAudio->addAudioEvent(&discoveredSound);
				TheInGameUI->message(TheGameText->fetch("MESSAGE:StealthDiscovered"));
				Int message = obj->getTemplate()->m_evaEventDetectedEnemy;
				TheEva->reportEvaEvent(message, info->m_detector->getPosition(), (Int)obj->getPosition());
			}
		}
	}
	else if (feedback == 2)
	{
		BfmeAudioEventPrefix136 discoveredSound(TheAudio->getMiscAudio()->m_stealthDiscoveredSound, obj->getID());
		((Rva0033F15DDwordSlot *)&discoveredSound)->set(localPlayer->getPlayerIndex());
		TheAudio->addAudioEvent(&discoveredSound);
		Int message = obj->getTemplate()->m_evaEventDetectedAlly;
		TheEva->reportEvaEvent(message, obj->getPosition(), 0);
	}
}

// Native 439CF7..439E0C and WB 127FEA0 identify the record-add operation.
// The address-derived public owner retains the existing caller pin.
class Rva002542F3Member {
public:
 int rva00438268(const Rva002542F3Member&) const;
 char m_prefix[0x18]; int m_kind; char m_tail[0xB8-0x1C];
};
class Rva004382FC {
public:
 Rva004382FC(const Rva002542F3Member&,int);
 Rva002542F3Member m_nugget;
 int m_frame,m_duration; unsigned char m_flag;
};
struct BfmePod196 { int a[49]; };
struct Rva004393D6 : public _STL::list<BfmePod196> {
 int m_04,m_08,m_0c;
 Rva004393D6(); ~Rva004393D6();
 Rva004393D6&operator=(const Rva004393D6&);
};
typedef _STL::map<int,Rva004393D6,_STL::less<int>,
 _STL::allocator<_STL::pair<const int,Rva004393D6> > > InvisibilityRecordMap;
template<> Rva004393D6& InvisibilityRecordMap::operator[](const int&);
class Rva00388F63Map { public: void *find(int*); };
// The existing push wrapper only forwards this value address to insert.
// No value of its old unconstrained element view is constructed here.
struct Rva004390F7Element;
template<> void _STL::list<Rva004390F7Element>::push_back(const Rva004390F7Element&);
struct InvisibilityNode { InvisibilityNode *next,*prev; Rva004382FC value; };
struct InvisibilityTreeNode {
 unsigned color; void *parent,*left,*right; int key; Rva004393D6 record;
};
class Rva00439CF7 {
public:
 void rva00439CF7(Object*,int,const void*);
 bool rva0043979D(Object*,Rva004393D6*);
 void *m_vtable; InvisibilityRecordMap m_records;
};
void Rva00439CF7::rva00439CF7(Object *object,int duration,const void *data) {
 if(!object) return;
 if(!(object->getTemplate()->m_kind115&0x20) && object->rva002931F5(false)) return;
 const Rva002542F3Member &nugget=*(const Rva002542F3Member*)data;
 if(nugget.m_kind>=2) return;
 int id=(int)object->getID();
 InvisibilityTreeNode *node=(InvisibilityTreeNode*)((Rva00388F63Map*)&m_records)->find(&id);
 if(node==*(InvisibilityTreeNode**)&m_records) {
  Rva004393D6 empty;
  m_records[id]=empty;
  node=(InvisibilityTreeNode*)((Rva00388F63Map*)&m_records)->find(&id);
 }
 Rva004393D6 *record=&node->record;
 InvisibilityNode *head=*(InvisibilityNode**)record;
 for(InvisibilityNode *it=head->next;it!=*(InvisibilityNode**)record;it=it->next) {
  Rva004382FC &entry=it->value;
  if(entry.m_frame && (unsigned char)entry.m_nugget.rva00438268(nugget)) {
   entry.m_duration+=duration; return;
  }
 }
 Rva004382FC entry(nugget,duration);
 ((_STL::list<Rva004390F7Element>*)record)->push_back(*(const Rva004390F7Element*)&entry);
 rva0043979D(object,record);
}
