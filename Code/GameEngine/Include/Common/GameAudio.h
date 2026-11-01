// AudioManager: canonical BFME2 abstract audio interface.
// Target facts (code addresses are RVAs; table addresses are VAs):
// Constructor 0x0005107D calls SubsystemInterface's 0x001B4E63 at 0x00051080, stores Snapshot's 0x00BBB554 at +0xC (0x00051085), then installs its own primary 0x00BC5148 (0x0005108C) and secondary 0x00BC5138 (0x00051092). SubsystemInterface is +0 and Snapshot is +0xC; the complete base occupies 0x10 bytes. MilesAudioManager's constructor 0x0005CF5F calls this constructor at 0x0005CF74 and initializes its first own member at +0x10 (0x0005CF93).
// Destructor 0x0005109D, rowed under Rva005109D, restores Snapshot's 0x00BBB554 at +0xC (0x000510A8) and tail-calls SubsystemInterface's 0x001B4E74 (0x000510AE). That parent restores 0x00BD77A0. These are base teardown tables, not competing AudioManager tables. The secondary deleting-destructor thunk 0x00051C9A subtracts 0xC and jumps to primary deleting destructor 0x000510B3.
// Primary table 0x00BC5148 contains 105 slots. Slots 0..13 retain the SubsystemInterface order; 1, 9, 10 and all 14..104 are __purecall (0x0003B810). Secondary table 0x00BC5138 contains the destructor thunk and three __purecall slots. Unknown primary slots keep neutral names. No data members extend the two bases.
// MilesAudioManager's primary table 0x00BC55B0 proves slot 15 stopAudio (0x00054284), 20 setViewFocus (0x0005DAFC), 25 addAudioEvent (0x0005DABB), 27 removeAudioEvent (0x00057787), 28 killAudioEventImmediately (0x000615DA), 31 isValidAudioEvent (0x000527E2), 52 isCurrentlyPlaying (0x000572DC), 57 setOn (0x0005168C), 60 setVolume (0x0005C8BB), 77 getAudioSettings (0x001DB09D), 78 getMiscAudio (0x0057E556), 83 isMusicAlreadyLoaded (0x0005B017), and 88 xferAudioHandle (0x000596E9). Zero Hour supplies the playback, volume and settings getter names; retail callers fix their BFME2 slot indices and argument shapes. Slot 88 transfers the unsigned handle through Xfer, as called by 0x0033FF2B.
// Slot 25 forwards its event pointer at 0x0005DAC3 to 0x0005D734 and preserves the returned handle in EAX. Slot 31 tests the event's +8 info pointer (0x000527F0); slot 52 returns a boolean after looking up the unsigned handle. The settings and misc getters read +0x10 and +0x14 in the concrete MilesAudioManager, not fields of this interface.
// Slots 98, 99, 101 and 102 are pure in AudioManager. The Miles table's corresponding targets are the rowed onAudioLODChanged 0x000607BB (void), 0x000531F6 (bool in AL, ret), 0x00053281 and 0x0005329C (void, ret). Only the first has a proved semantic name. Slot 103 is the rowed friend_xferSubAudioEventRTS (0x0005987D, Xfer* and BfmePoolRef10*, ret 8).
// Out-of-line AudioManager rows: constructor 0x0005107D, regainFocus 0x0035D2F7, regainFocusThunk 0x0035D326. Lifetime declarations have no inline bodies.
#ifndef BFME2_GAMEAUDIO_H
#define BFME2_GAMEAUDIO_H

#if defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#error Include GameAudio.h before the short SubsystemInterface definition.
#endif
#ifndef BFME_SUBSYSTEM_SLOTS
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

struct BfmeAudioEventPrefix136;
class BfmePoolRef10;
struct AudioSettings;
class MiscAudio;
enum AudioAffect;

class AudioManager : public SubsystemInterface, public Snapshot {
public:
    AudioManager();
    virtual ~AudioManager();

    virtual void slot14() = 0;
    virtual void stopAudio(AudioAffect affect) = 0;
    virtual void slot16() = 0;
    virtual void slot17() = 0;
    virtual void slot18() = 0;
    virtual void slot19() = 0;
    virtual void setViewFocus(int viewType) = 0;
    virtual void slot21() = 0;
    virtual void slot22() = 0;
    virtual void slot23() = 0;
    virtual void slot24() = 0;
    virtual int addAudioEvent(const BfmeAudioEventPrefix136 *event) = 0;
    virtual void slot26() = 0;
    virtual void removeAudioEvent(unsigned int handle) = 0;
    virtual bool killAudioEventImmediately(unsigned int handle) = 0;
    virtual void slot29() = 0;
    virtual void slot30() = 0;
    virtual bool isValidAudioEvent(const BfmeAudioEventPrefix136 *event) const = 0;
    virtual void slot32() = 0;
    virtual void slot33() = 0;
    virtual void slot34() = 0;
    virtual void slot35() = 0;
    virtual void slot36() = 0;
    virtual void slot37() = 0;
    virtual void slot38() = 0;
    virtual void slot39() = 0;
    virtual void slot40() = 0;
    virtual void slot41() = 0;
    virtual void slot42() = 0;
    virtual void slot43() = 0;
    virtual void slot44() = 0;
    virtual void slot45() = 0;
    virtual void slot46() = 0;
    virtual void slot47() = 0;
    virtual void slot48() = 0;
    virtual void slot49() = 0;
    virtual void slot50() = 0;
    virtual void slot51() = 0;
    virtual bool isCurrentlyPlaying(unsigned int handle) = 0;
    virtual void slot53() = 0;
    virtual void slot54() = 0;
    virtual void slot55() = 0;
    virtual void slot56() = 0;
    virtual void setOn(bool turnOn, int whichToAffect) = 0;
    virtual void slot58() = 0;
    virtual void slot59() = 0;
    virtual void setVolume(float volume, int whichToAffect) = 0;
    virtual void slot61() = 0;
    virtual void slot62() = 0;
    virtual void slot63() = 0;
    virtual void slot64() = 0;
    virtual void slot65() = 0;
    virtual void slot66() = 0;
    virtual void slot67() = 0;
    virtual void slot68() = 0;
    virtual void slot69() = 0;
    virtual void slot70() = 0;
    virtual void slot71() = 0;
    virtual void slot72() = 0;
    virtual void slot73() = 0;
    virtual void slot74() = 0;
    virtual void slot75() = 0;
    virtual void slot76() = 0;
    virtual const AudioSettings *getAudioSettings() const = 0;
    virtual const MiscAudio *getMiscAudio() const = 0;
    virtual void slot79() = 0;
    virtual void slot80() = 0;
    virtual void slot81() = 0;
    virtual void slot82() = 0;
    virtual bool isMusicAlreadyLoaded() const = 0;
    virtual void slot84() = 0;
    virtual void slot85() = 0;
    virtual void slot86() = 0;
    virtual void slot87() = 0;
    virtual void xferAudioHandle(Xfer *xfer, unsigned int *handle) = 0;
    virtual void slot89() = 0;
    virtual void slot90() = 0;
    virtual void slot91() = 0;
    virtual void slot92() = 0;
    virtual void slot93() = 0;
    virtual void slot94() = 0;
    virtual void slot95() = 0;
    virtual void slot96() = 0;
    virtual void slot97() = 0;
    virtual void onAudioLODChanged() = 0;
    virtual bool slot99() = 0;
    virtual void slot100() = 0;
    virtual void slot101() = 0;
    virtual void slot102() = 0;
    virtual void friend_xferSubAudioEventRTS(Xfer *xfer, BfmePoolRef10 *eventRef) = 0;
    virtual void slot104() = 0;

    void regainFocus();
    void regainFocusThunk();
};

extern AudioManager *TheAudio;

#endif
