// ?update@GarrisonContain@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.97 date=2026-10-11
// cl: /O1 /arch:SSE /G7 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// GarrisonContain::update (0x00479643, 217 bytes), after the BFME1/ZH
// GarrisonContain.cpp body: slot 0 of the +0x10 UpdateModuleInterface vftable
// 0x00C46560 (this at +0x10). WB 0x011A3E00 is GarrisonContain::update
// (GarrisonContain.cpp:1023 mobile assert, compiled out).
//
// Target facts: the module data is read before the base update (rowed
// 0x004640BE, called with the +0x10 this, result ignored). The contained
// list is copied by value (pair 0x0046247D, then 0x0036AE51) and destroyed
// at the end (0x004EC395, the only EH state). Each effectively dead occupant
// (Object +0x438 bit 0) is removed through the +0x20 Contain interface slot
// 41 (Object, false) and its safe-occlusion frame (+0x428) set to the logic
// frame (TheGameLogic +0x40) plus 1000 times the frame-rate global 0x009BA4E4.
// Then, on the primary: removeInvalidObjectsFromGarrisonPoints (pinned
// 0x0047933C), addValidObjectsToGarrisonPoints 0x0047894C, trackTargets
// 0x00478ADB, the healing helper 0x00478BE0 and, when module data +0xA0 is
// set and the Object is mobile (pinned isMobile 0x002907A1), the movement
// helper 0x00478FD7. Returns 1.
//
// Carried from the donor: the method name, the order of the calls, the
// removal/occlusion loop and the m_mobileGarrison test. BFME 2 adds the
// removeInvalid/addValid/trackTargets sequence ZH commented out.
#include "../../../../Include/GameLogic/ContainmentListView.h"

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class Object
{
public:
	bool isMobile() const;	// pinned 0x002907A1
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	void setSafeOcclusionFrame(unsigned int frame) { m_428 = frame; }
private:
	unsigned char m_pad000[0x428];
	unsigned int m_428; // +0x428
	unsigned char m_pad42C[0x438 - 0x42C];
	unsigned char m_438; // +0x438
};

class GameLogic;
extern GameLogic *TheGameLogic;
struct GameLogicFrameView
{
	unsigned char m_pad00[0x40];
	unsigned int m_frame; // +0x40
};
extern int g_Va00DBA4E4;	// logic frames per second

struct GarrisonContainModuleData
{
	unsigned char m_pad00[0xA0];
	bool m_mobileGarrison; // +0xA0
};

// The rowed base update 0x004640BE (OpenContain's, with the +0x10 this).
class Rva004640BE
{
public:
	int rva004640BE();
};

// The pinned pair writer 0x0046247D: returns its argument.
struct Rva0046247DPair
{
	void *m00;
	void *m04;
};
class Rva0046247D
{
public:
	void *rva0046247D(Rva0046247DPair &p);
};

class GarrisonContainModule
{
public:
	virtual void moduleSlot0();
	const GarrisonContainModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	void *m_0C;
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
	// OpenContain's update (rowed 0x004640BE) takes this same +0x10 this.
	int openContainUpdate() { return ((Rva004640BE *)this)->rva004640BE(); }
};

class GarrisonContainUpdateModule : public GarrisonContainModule, public UpdateModuleInterface
{
public:
	unsigned char m_pad14[0x20 - 0x14];
};

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();
class ContainModuleInterface
{
public:
	SLOT08(s00,s01,s02,s03,s04,s05,s06,s07)
	SLOT08(s08,s09,s0A,s0B,s0C,s0D,s0E,s0F)
	SLOT08(s10,s11,s12,s13,s14,s15,s16,s17)
	SLOT08(s18,s19,s1A,s1B,s1C,s1D,s1E,s1F)
	SLOT08(s20,s21,s22,s23,s24,s25,s26,s27)
	virtual void s28();
	virtual void removeFromContain(Object *obj, bool exposeStealthUnits) = 0;	// slot 41
};
#undef SLOT08

class GarrisonContain : public GarrisonContainUpdateModule, public ContainModuleInterface
{
public:
	virtual UpdateSleepTime update();
	void rva00478BE0();	// rowed healing helper
	void rva00478FD7();	// rowed movement helper
protected:
	void removeInvalidObjectsFromGarrisonPoints();
	void addValidObjectsToGarrisonPoints();
	void trackTargets();
	const GarrisonContainModuleData *getGarrisonContainModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }
};

UpdateSleepTime GarrisonContain::update()
{
	const GarrisonContainModuleData *modData = getGarrisonContainModuleData();

	// extend functionality
	openContainUpdate();

	// remove effectively dead objects from this garrison container
	Rva0046247DPair pair;
	ContainmentList containList = ((Rva0036AE51ListView *)((Rva0046247D *)(GarrisonContainModule *)this)->rva0046247D(pair))->rva0036AE51();
	Object *contained;
	for (ContainmentList::const_iterator it = containList.begin(); it != containList.end(); /*empty*/)
	{
		// get object
		contained = (Object *)containmentFirstWord(*it);

		// increment iterator, we may delete the object
		++it;

		// remove if dead
		if (contained->isEffectivelyDead())
		{
			// remove from container
			removeFromContain(contained, false);

			// set the safe occlusion frame to way way way in the future so we never see it during death
			contained->setSafeOcclusionFrame(((GameLogicFrameView *)TheGameLogic)->m_frame + g_Va00DBA4E4 * 1000);
		}
	}

	removeInvalidObjectsFromGarrisonPoints();
	addValidObjectsToGarrisonPoints();
	trackTargets();
	rva00478BE0();

	if (modData->m_mobileGarrison && getObject()->isMobile() == true)
		rva00478FD7();

	return UPDATE_SLEEP_NONE;
}
