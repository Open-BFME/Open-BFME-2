// cl: /O1 /DNDEBUG /MD /EHsc
// Whole-file recovery from retail's QueuedIconSlot ctor 0x005F7B25 and
// WorldBuilder 0x0162EB00, StrategicHUDBuildQueueDetailsMovieClip.cpp:685.
// Its seven command-map bindings capture this and prove the callback owners.
// The callback argument is unused; void* records the observed one-word RET4
// ABI, not a recovered argument type. Method names remain address-qualified.
namespace StrategicHUD {
class BuildQueueDetailsMovieClip {
public: class Impl { public: class QueuedIconSlot; };
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

