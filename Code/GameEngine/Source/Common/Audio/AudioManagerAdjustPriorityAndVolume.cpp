// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/Common/Audio
//
// ?find@Rva006AD590Entry@@QAEPATRva006AD590Slot@@H@Z
// retail 0x00059238, 33 bytes. Dedicated TU holding the donor preamble plus
// this ONE body, ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/Audio/AudioManagerAdjustPriorityAndVolume.cpp.
// Recompiled /Os the donor body is byte-identical to retail once relocations
// are masked (unique hit on unclaimed .text).
//
// The donor's Rva006AD590Owner::bfmeAdjustPriorityAndVolume is carried here
// too, though it is NOT the placed body: find() is defined in-class and is
// only emitted out of line because the donor's owner calls it. Deleting the
// owner makes the class's only member unreferenced, and MSVC 7.1 then declines
// to emit it at all -- the object has no code section and the row cannot be
// verified. That is what makes this a dedicated TU rather than a trimmed one.
//
// The map lookup goes through the same pinned ?bfmeFindPE@BfmeSubPE@@QAEPAHH@Z
// that BfmeThingPE::bfmeGoPE (BfmeConv906.cpp) already calls, reached through
// the donor's member-function-pointer thunk at retail 0x001F7A47.
#define BfmeZeroRange 0.0f

enum AudioPriority { AP_RVA006AD590_PLACEHOLDER };

union Rva006AD590Slot
{
	int m_asInt;
	float m_asFloat;
};

// Same pinned lookup used by BfmeThingPE::bfmeGoPE (BfmeConv906.cpp).
struct BfmeSubPE
{
	int *m_bfmeFirst;
};

// Retail 0x001F7A47: the member-function-pointer thunk the map lookup goes
// through. Carried from the donor source; the body at the address remains
// unrecovered.
extern void j_00025cca();

struct AudioManagerBfmeFindPECallView
{
	int *find(int key);
};

class Rva006AD590Info
{
public:
	virtual ~Rva006AD590Info();
	virtual int getNameKey() const;

	char m_pad04[0x0c];
	Rva006AD590Slot m_priority;	// +0x10
	char m_pad14[4];
	float m_defaultVolume;			// +0x18
};

class AudioEventRTS
{
public:
	void setAudioPriority(AudioPriority newPriority);
	void setVolume(float vol);

	char m_pad00[8];
	Rva006AD590Info *m_eventInfo;	// +0x08
	char m_pad0c[0x1c];
	int m_timeOfDay;				// +0x28
};

class Rva006AD590Entry
{
public:
	Rva006AD590Slot *find(int key)
	{
		union
		{
			void *asVoid;
			int *(AudioManagerBfmeFindPECallView::*asMember)(int);
		} call;
		call.asVoid = reinterpret_cast<void *>(j_00025cca);
		int *r = (reinterpret_cast<AudioManagerBfmeFindPECallView *>(
			&m_map)->*call.asMember)(key);
		if (r == m_map.m_bfmeFirst)
			return 0;
		return (Rva006AD590Slot *)((char *)r + 0x14);
	}

	char m_pad[0x1b8];
	BfmeSubPE m_map;				// +0x1b8
	char m_tail[0x1c4 - 0x1b8 - 4];
};

class Rva006AD590Owner
{
public:
	void bfmeAdjustPriorityAndVolume(AudioEventRTS *event);

private:
	char m_padb8[0xb8];
	Rva006AD590Entry m_entries[3];
};

void Rva006AD590Owner::bfmeAdjustPriorityAndVolume(AudioEventRTS *event)
{
	int timeOfDay = event->m_timeOfDay;
	int key = event->m_eventInfo->getNameKey();

	Rva006AD590Slot *slot = m_entries[timeOfDay].find(key);
	if (slot)
	{
		event->setAudioPriority((AudioPriority)slot->m_asInt);
		Rva006AD590Info *info = event->m_eventInfo;
		float priority = info->m_priority.m_asFloat;
		if (priority > BfmeZeroRange)
		{
			float ratio = slot->m_asFloat / priority;
			event->setVolume(ratio * info->m_defaultVolume);
		}
	}
	else
	{
		event->setAudioPriority((AudioPriority)event->m_eventInfo->m_priority.m_asInt);
		event->setVolume(event->m_eventInfo->m_defaultVolume);
	}
}

class Rva000588DA
{
public:
	~Rva000588DA();
};

class Rva00059259
{
public:
	void rva00059259();
};

void Rva00059259::rva00059259()
{
	((Rva000588DA *)this)->~Rva000588DA();
}