// cl: /O1 /G7 /ICode/GameEngine/Source/Common /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD /EHsc
//
// ?rva00438D58@Rva00439E0C@@QAEXPAVObject@@@Z, retail 0x00438D58, 197 bytes.
// Member of the invisibility manager view taking an Object (`this` unread, so
// the former free __stdcall spelling had identical bytes; 0x0043979D calls it
// with ECX preserved): Drawable via Thing::getDrawable, gates via
// Object::rva002933CD plus Object::isLocallyControlled, sound ref via
// Drawable::rva00374389 returning Rva002390CB, audio event via shared
// BfmeAudioEventPrefix136 plus setObjectID 0x002D9531 plus addAudioEvent
// slot 0x64, statuses 0x5f/0x60 via rowed setStatus. Layout from retail
// offsets; caller is 0x0043982F in 0x0043979D.
#include "Common/BfmeAudioEventPrefix136.h"

class Drawable;
class Thing
{
public:
	Drawable *getDrawable() const;
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

class Object : public Thing
{
public:
	int rva002933CD();
	bool isLocallyControlled() const;
	void setStatus(ObjectStatusTypes bit, bool flag);
	int getID() const { return m_id; }
private:
	char m_pad00[0x74];
	int m_id;
};

class Rva002390CB
{
public:
	Rva002390CB(const Rva002390CB &other);
	~Rva002390CB() { if (m_04.referent != 0) m_04.referent->Release_Ref(); }
	char m_pad00[4];
	OpaqueRefElement4 m_04;
};

class Drawable
{
public:
	Rva002390CB rva00374389();
	Rva002390CB rva003743A2();
};

class Rva002D9531
{
public:
	void rva002D9531(int v);
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
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *eventToAdd) = 0;
};
extern AudioManager *TheAudio;

static inline void setObjectID(BfmeAudioEventPrefix136 &sound, int id)
{
	((Rva002D9531 *)&sound)->rva002D9531(id);
}

class Rva00439E0C
{
public:
	void rva00438D58(Object *obj);
};

void Rva00439E0C::rva00438D58(Object *obj)
{
	bool zero = false;
	Drawable *draw = obj->getDrawable();
	if (draw == (Drawable *)(int)zero)
		goto noAudio;
	if ((unsigned char)obj->rva002933CD() == (unsigned char)zero)
		goto noAudio;
	if (!obj->isLocallyControlled())
		goto noAudio;
	{
		Rva002390CB tmp = draw->rva00374389();
		if (tmp.m_04.referent != (OpaqueRefCounted *)(int)zero) {
			BfmeAudioEventPrefix136 evt(tmp.m_04, zero);
			setObjectID(evt, obj->getID());
			TheAudio->addAudioEvent(&evt);
		}
	}
noAudio:
	obj->setStatus((ObjectStatusTypes)0x5f, zero);
	obj->setStatus((ObjectStatusTypes)0x60, zero);
}

// Native438C6C..438D58/236B. Existing sibling supplies the event lifetime
// structure; native RET16 establishes four stdcall arguments. Deadline at
// payload+8 and statuses5F/60 are target facts; function identity stays neutral.
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
extern void __stdcall Rva004381C4Iterate(const Object *);
struct UpdateFrameView { char pad[8]; unsigned frame; };
void __stdcall Rva00438C6CUpdate(Object *obj, void *payload, int duration, bool flag)
{
 Rva004381C4Iterate(obj);
 UpdateFrameView *data=(UpdateFrameView*)payload;
 unsigned deadline=TheGameLogic->getFrame()+duration;
 if (deadline>data->frame) data->frame=deadline;
 bool zero=false;
 Drawable *draw=obj->getDrawable();
 if(draw==(Drawable*)(int)zero)goto noSound;
 if((unsigned char)obj->rva002933CD()!=(unsigned char)zero)goto noSound;
 {
  Rva002390CB tmp=draw->rva003743A2();
  if(tmp.m_04.referent!=(OpaqueRefCounted*)(int)zero)
  {
   BfmeAudioEventPrefix136 evt(tmp.m_04,zero);
   setObjectID(evt,obj->getID());
   TheAudio->addAudioEvent(&evt);
  }
 }
noSound:
 obj->setStatus((ObjectStatusTypes)0x60,zero);
 obj->setStatus((ObjectStatusTypes)0x5f,zero);
 if (flag) obj->setStatus((ObjectStatusTypes)0x5f,true); else obj->setStatus((ObjectStatusTypes)0x60,true);
}
