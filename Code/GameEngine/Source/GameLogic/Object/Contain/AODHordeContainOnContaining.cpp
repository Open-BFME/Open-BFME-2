// cl: /DNDEBUG /MD
//
// Target evidence: the AODHordeContain constructor in AODHordeContainCtor.cpp
// installs primary vftable 0x00C46570; its entry at 0x00C46C08 is this body at
// 0x0047A3CB. The body takes an Object pointer and a one-byte selection flag,
// fades in the object's drawable for five logic seconds, calls the int-taking
// method pinned at 0x0039B28F on Object+0x264, then forwards both arguments to
// 0x0046FA46. That base routine is a HordeContain vtable body and calls the
// rowed HordeContain routine at 0x0046A893.
//
// Identity inference: the same entry/argument shape is `onContaining(Object *,
// Bool)` in the BFME1 contain interface and its derived contain implementations.
// The target vtable relation supports AODHordeContain as the overriding class;
// the experience-tracker and helper names remain address-derived.

extern const int g_00DBA4E4;

class Drawable
{
public:
	void fadeIn(unsigned int frames);
};

class Rva003BD306Target
{
public:
	void rva0039B28F(int value);
};

class Object
{
public:
	Drawable *getDrawable() const;
	unsigned char m_pad000[0x264];
	Rva003BD306Target *m_experienceTracker;
};

class HordeContain
{
public:
	virtual void onContaining(Object *object, bool wasSelected);
};

class AODHordeContain : public HordeContain
{
public:
	virtual void onContaining(Object *object, bool wasSelected);
};

// ?onContaining@AODHordeContain@@UAEXPAVObject@@_N@Z
void AODHordeContain::onContaining(Object *object, bool wasSelected)
{
	if (object->getDrawable())
		object->getDrawable()->fadeIn(g_00DBA4E4 * 5);

	object->m_experienceTracker->rva0039B28F(1);
	HordeContain::onContaining(object, wasSelected);
}
