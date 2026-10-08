// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /arch:SSE /ICode/Libraries/Include/Lib
#include "ascii_string.h"
#include "Coord2D.h"
// Whole-file recovery from retail's QueuedIconSlot ctor 0x005F7B25 and
// WorldBuilder 0x0162EB00, StrategicHUDBuildQueueDetailsMovieClip.cpp:685.
// Its seven command-map bindings capture this and prove the callback owners.
// The callback argument is unused; void* records the observed one-word RET4
// ABI, not a recovered argument type. Method names remain address-qualified.
class BuildQueueOwnerView {public:virtual void unknown0();virtual void onBack();};
namespace StrategicHUD {
class BuildQueueDetailsMovieClip {
public: class Impl { public: class QueuedIconSlot; class InProgressIconSlot; void rva005F68FE(void*); void rva005F6916(void*); void rva005F691D(void*); private: BuildQueueOwnerView *owner; char unknown[0x63]; bool backHover; };
};
}
class StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot {
public:
 void rva005F688B(void*);
 void rva005F6892(void*);
 void rva005F6A90(void*);
 void rva005F6A98(void*);
 void rva005F6AA0(void*);
 void rva005F6AA8(void*);
 void rva005F6AE8(void*);
private:
 char unknown[0x28];
 bool turnsHover;
};
// RET4 at 0x005F688F closes this 7B body; the ctor binds its address under
// _OnQueuedIconSlotTurnsRemainingRollOut. The following callback starts6892.
void StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot::rva005F688B(void*) {
 turnsHover=false;
}


// Constructor binding: _OnQueuedIconSlotTurnsRemainingRollOver.
void StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot::rva005F6892(void*) { turnsHover=true; }


class Rva005F6A30 {public:void rva005F6A30();};
// Constructor binding: _OnQueuedIconSlotRollOut.
void StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot::rva005F6A90(void*) { ((Rva005F6A30*)this)->rva005F6A30(); }


class Rva005F6A44 {public:void rva005F6A44();};
// Constructor binding: _OnQueuedIconSlotRollOver.
void StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot::rva005F6A98(void*) { ((Rva005F6A44*)this)->rva005F6A44(); }


class Rva005F69A0 {public:void rva005F69A0();};
// Constructor binding: _OnQueuedIconSlotTypeRollOut.
void StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot::rva005F6AA0(void*) { ((Rva005F69A0*)this)->rva005F69A0(); }


class Rva005F69B2 {public:void rva005F69B2();};
// Constructor binding: _OnQueuedIconSlotTypeRollOver.
void StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot::rva005F6AA8(void*) { ((Rva005F69B2*)this)->rva005F69B2(); }


// Click binding in ctor5F7B25; native RET4 closes5F6AE8..5F6B0B.
class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
struct QueuedAptModeView { char unknown[0x318]; int mode; };
class GameWindow { public:void winDrawBorder(); };
class Rva005F698E { public:void rva005F698E(); };
void StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot::rva005F6AE8(void*) {
 int mode=((QueuedAptModeView*)g_bfmeAptWindowManager)->mode;
 if(mode==0) ((GameWindow*)this)->winDrawBorder();
 else if(mode==2) ((Rva005F698E*)this)->rva005F698E();
}


// Native81B state setter; WB owner and vtable8797F4 slot24 agree.
extern const char *g_00C78D64[];
int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget*,void*,const char*,const char*,const char**);
struct IconOwner { char unknown[4]; void *level; AsciiString name; char unknownC[4]; int overlayArg; };
class StrategicHUD::BuildQueueDetailsMovieClip::Impl::InProgressIconSlot {
public:virtual void DoSetState(int); void rva005F6899(const Coord2D*,const Coord2D*,void*,void*);
private:char unknown[0x10];int state;char gap[4];IconOwner *owner; int total,remaining;
};
void StrategicHUD::BuildQueueDetailsMovieClip::Impl::InProgressIconSlot::DoSetState(int index) {
 if(index==state)return;
 const char *icon=g_00C78D64[index];
 IconOwner *parent=owner;
 Rva0050E9FEAptCall((Rva00222A8BTarget*)g_bfmeAptWindowManager,parent->level,parent->name.str(),"SetInProgressIconSlotState",&icon);
 state=index;
}


class Display;
extern Display *TheDisplay;
class Rva000A4826 {public:void rva000A4875(float,float,float,float,float,int);};
// Ctor5F775E binds this receiver under _ProgressOverlay. Native101B RET16.
void StrategicHUD::BuildQueueDetailsMovieClip::Impl::InProgressIconSlot::rva005F6899(const Coord2D *position,const Coord2D *size,void*,void*) {
 float progress;
 if(total) progress=(float)(total-remaining)/(float)total;
 else progress=0.0f;
 ((Rva000A4826*)TheDisplay)->rva000A4875(position->x,position->y,size->x,size->y,progress*100.0f,owner->overlayArg);
}

// Ctor5F7F21 binding: _OnBackButtonClicked.
void StrategicHUD::BuildQueueDetailsMovieClip::Impl::rva005F68FE(void*) { if(((QueuedAptModeView*)g_bfmeAptWindowManager)->mode==0)owner->onBack(); }

// Ctor5F7F21 binding: _OnBackButtonRollOver.
void StrategicHUD::BuildQueueDetailsMovieClip::Impl::rva005F6916(void*) { backHover=true; }
