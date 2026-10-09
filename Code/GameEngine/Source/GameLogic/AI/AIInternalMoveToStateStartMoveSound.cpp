// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// AIInternalMoveToState::startMoveSound, retail 0x00347225 (383 bytes), and
// the file-static start-sound helper it calls, retail 0x0034712E (247 bytes).
//
// Target facts: startMoveSound is pinned from AIInternalMoveToState::onEnter
// (REL32 at 0x0034C6E3) and sits between AIDeadState::onExit (0x00347110) and
// AIInternalMoveToState::onExit (0x003473A4). The owner comes from the state
// machine (+0x18, owner +0x14), its drawable from Thing::getDrawable
// (0x005508E2) and its body module from +0x254, whose vslot 8 is the damage
// state (> 1 picks the damaged sound). The sounds are the Drawable keyed
// lookups 0x21/0x22 (start, damaged start: helper) and 0x23/0x24 (loop,
// damaged loop: startMoveSound), each assigned into a four-byte owning handle
// (0x00239099) from the returned record's +4. A loop sound first removes the
// still-playing handle (+0x40) through TheAudio vslot 27 when TheAudio exists
// and the handle is at least 5, then stores the vslot 25 addAudioEvent result
// there. Finally every member of the object's contain list (Object
// 0x0028C197, vslot 66 (?, list) pair) gets the helper. The helper is
// file-static: retail passes the drawable on the stack, the object in ESI and
// the body module in ECX (the compiler's custom convention).
//
// Donor: Zero Hour AIStates.cpp AIInternalMoveToState::startMoveSound and the
// BFME 1 row of the same name (start/loop pairs with a damaged variant, the
// >= 5 handle removal); BFME 2 moved the sounds to the drawable lookups and
// added the contained-member pass. Names of the helper and the views are
// structural.
#include "Common/BfmeAudioEventPrefix136.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef UnsignedInt AudioHandle;

enum BodyDamageType
{
	BODY_PRISTINE,
	BODY_DAMAGED,
	BODY_REALLYDAMAGED,
	BODY_RUBBLE
};

class Rva002D9531
{
public:
	void rva002D9531(int v); // AudioEventRTS::setObjectID
};

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
class AudioManager : public VSlots<25>
{
public:
	virtual AudioHandle addAudioEvent(const BfmeAudioEventPrefix136 *eventToAdd) = 0;
	virtual void slot26() = 0;
	virtual void removeAudioEvent(AudioHandle handle) = 0;
};
extern AudioManager *TheAudio;

// Owning sound handle: zeroed on entry, released on exit.
struct MoveSoundRef : public OpaqueRefElement4
{
	MoveSoundRef() { referent = 0; }
	~MoveSoundRef()
	{
		if (referent != 0)
			referent->Release_Ref();
	}
	using OpaqueRefElement4::operator=;
};

// Keyed-lookup record returned by the Drawable wrappers; +4 owns the sound.
class Rva002390CB
{
public:
	Rva002390CB(const Rva002390CB &other);
	~Rva002390CB()
	{
		if (m_ref.referent != 0)
			m_ref.referent->Release_Ref();
	}
	int m_00;
	OpaqueRefElement4 m_ref;
};

class Drawable
{
public:
	Rva002390CB rva00346C79(); // key 0x21
	Rva002390CB rva00346C92(); // key 0x22
	Rva002390CB rva00346CAB(); // key 0x23
	Rva002390CB rva00346CC4(); // key 0x24
};

class BodyModuleInterface : public VSlots<8>
{
public:
	virtual BodyDamageType getDamageState() const = 0;
};

class Object;
struct MoveSoundMemberNode
{
	MoveSoundMemberNode *m_next;
	MoveSoundMemberNode *m_prev;
	Object *m_object;
};
struct MoveSoundMemberList
{
	MoveSoundMemberNode *m_head;
};
struct MoveSoundMemberRange
{
	int m_00;
	const MoveSoundMemberList *m_list;
};
// Interface returned by Object::rva0028C197: slot 66 fills a (?, list) pair.
class MoveSoundContain : public VSlots<66>
{
public:
	virtual void rva0028C197Slot66(MoveSoundMemberRange *out) = 0;
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

class Object : public Thing
{
public:
	void *rva0028C197() const;
	ObjectID getID() const { return m_id; }
	static __forceinline BodyModuleInterface *getBodyModule(const Object *object) { return object->m_body; }
private:
	unsigned char m_pad00[0x74];
	ObjectID m_id; // +0x74
	unsigned char m_pad78[0x254 - 0x78];
	BodyModuleInterface *m_body; // +0x254
};

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
};

class State
{
public:
	virtual ~State();
	Object *getMachineOwner() const { return m_machine->getOwner(); }
private:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class AIInternalMoveToState : public State
{
private:
	unsigned char m_pad1C[0x40 - 0x1C];
	AudioHandle m_ambientPlayingHandle; // +0x40
	void startMoveSound();
};

static inline void setObjectID(BfmeAudioEventPrefix136 &sound, ObjectID id)
{
	((Rva002D9531 *)&sound)->rva002D9531(id);
}

static void playMoveStartSound(Drawable *draw, Object *obj, BodyModuleInterface *body)
{
	if (draw == 0 || obj == 0)
		return;

	MoveSoundRef sound;
	if (body != 0 && body->getDamageState() > BODY_DAMAGED)
		sound = draw->rva00346C92().m_ref;
	if (sound.referent == 0)
		sound = draw->rva00346C79().m_ref;
	if (sound.referent != 0)
	{
		BfmeAudioEventPrefix136 soundEvent(sound, 0);
		setObjectID(soundEvent, obj->getID());
		TheAudio->addAudioEvent(&soundEvent);
	}
}

void AIInternalMoveToState::startMoveSound()
{
	Object *obj = getMachineOwner();
	Drawable *draw = obj->getDrawable();
	BodyModuleInterface *body = Object::getBodyModule(obj);
	if (draw != 0)
	{
		playMoveStartSound(draw, obj, body);

		MoveSoundRef sound;
		if (body != 0 && body->getDamageState() > BODY_DAMAGED)
			sound = draw->rva00346CC4().m_ref;
		if (sound.referent == 0)
			sound = draw->rva00346CAB().m_ref;
		if (sound.referent != 0)
		{
			if (TheAudio != 0 && m_ambientPlayingHandle >= 5)
				TheAudio->removeAudioEvent(m_ambientPlayingHandle);
			BfmeAudioEventPrefix136 soundEvent(sound, 0);
			setObjectID(soundEvent, obj->getID());
			m_ambientPlayingHandle = TheAudio->addAudioEvent(&soundEvent);
		}
	}

	MoveSoundContain *contain = (MoveSoundContain *)obj->rva0028C197();
	if (contain != 0)
	{
		MoveSoundMemberRange range;
		contain->rva0028C197Slot66(&range);
		MoveSoundMemberNode *head = range.m_list->m_head;
		for (MoveSoundMemberNode *node = head->m_next; node != head; node = node->m_next)
		{
			Object *member = node->m_object;
			if (member != 0)
				playMoveStartSound(member->getDrawable(), member, Object::getBodyModule(member));
		}
	}
}
