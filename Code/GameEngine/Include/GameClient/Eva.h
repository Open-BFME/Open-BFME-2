/* Target facts (code addresses are RVAs; tables are VAs): Eva is polymorphic. Constructor 0x001DF91B calls SubsystemInterface's constructor 0x001B4E63 at 0x001DF930, installs Snapshot's base table 0x00BBB554 at +0x0C at 0x001DF939, then installs Eva's primary 0x00BDC5B8 at +0 and secondary 0x00BDC5A8 at +0x0C at 0x001DF947/0x001DF94D. Destructor 0x001DF057 installs the same Eva tables at 0x001DF068/0x001DF06E, restores Snapshot's base table at 0x001DF0D8 and calls the SubsystemInterface destructor at 0x001DF0DF; that base restores 0x00BD77A0 at 0x001B4E74. These tables describe successive subobject lifetimes. Allocation 0x0022E6F9 pushes 0x98 before operator new 0x0002FDA0 and constructor call 0x0022E711, proving sizeof 0x98 and bases SubsystemInterface +0, Snapshot +0x0C.
   Primary table 0x00BDC5B8 has fourteen slots: 0=001DF3D5 (deleting destructor calling 001DF057), 1=init 001DF0F9, 2=001B5384, 3/8/12=000B3FD0 (ret), 4/11=005CB9FF (false, ret 4), 5=0047A699 (false), 6=000D43D0 (zero), 7/13=0047A69C (ret 4), 9=reset 001DF1A4, 10=update 001DE156. Slots 2-8/11-13 equal the registered parent's table 0x00BD77A0. Secondary table 0x00BDC5A8 has four slots: 0=001DF0F1 (this -= 0x0C, jump to 001DF3D5), 1=000B3FD0 (loadPostProcess), 2=GetSnapshotName 001DD02B (returns the Eva literal at 0x00BDC4FC), 3=xfer 001DD031. Constructor calls establish storage at +10 (001DDBC6), +1C/+28/+5C (00211E58), +34/+48 (001DED2B), +68 (002049AD), and +80 (001DCF82). Stores at 001DF9AB/001DF9BA/001DF9BD/001DF9C4/001DF9CB prove dwords +6C/+70/+74/+78 and byte +7C. Setup 001DCF82 writes float +80/+94 and dwords +84/+88/+8C/+90; update 001DE156 reads +8C, and 001DD3DD reads +90. Unspecified container storage stays opaque.
   Out-of-line method spellings follow ledger rows: constructor 001DF91B, destructor 001DF057, init 001DF0F9, reset 001DF1A4, update 001DE156, GetSnapshotName 001DD02B, xfer 001DD031, reportEvaEvent 001DE2DA, internalReportEvaEvent 001DD468, countEvaEventAsPlayed 001DD4E3, isEventBlockedByTimeout 001DD53D, isEventAboutToPlay 001DD5A0, getLastReallyPlayedFrameForEvaEvent 001DD604, rva001DD670 001DD670, rva001DD3DD 001DD3DD, rva001DDF04 001DDF04, rva001DE78E 001DE78E, rva001DCFC9 001DCFC9, iniScanEvaEventID 001DE9C4, messageToName 001DEB8A, rva001debf6 001DEBF6, xferEvaEventID 001DEC48, iniParsePredefinedEvaEvent 001DEA96, iniParseNewEvaEvent 001DF42D, iniParseEvaEventForwardReference 001DF6A8. Zero Hour Eva.h supplies init/reset/update names; BFME2's additional Snapshot base and event API follow retail and the ledger. */
#ifndef BFME2_EVA_H
#define BFME2_EVA_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

class AsciiString;
class INI;
class Xfer;
struct Coord3D;
struct EvaEventReport;
struct Vec001DCDAF;
enum EvaEventID;
namespace _STL {
template <class T> class allocator;
template <class T, class A> class vector;
}

class Eva : public SubsystemInterface, public Snapshot
{
public:
    Eva();
    virtual ~Eva();
    virtual void init();
#ifndef BFME_SUBSYSTEM_SLOTS
    virtual bool loadIniFilesFromLegend();
    virtual void postProcessLoad();
    virtual bool vslot04(int);
    virtual bool vslot05();
    virtual int vslot06();
    virtual void vslot07(int);
    virtual void vslot08();
#endif
    virtual void reset();
    virtual void update();
#ifndef BFME_SUBSYSTEM_SLOTS
    virtual bool vslot11(int);
    virtual void vslot12();
    virtual void vslot13(int);
#endif

#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif

    bool reportEvaEvent(EvaEventID eventID, const Coord3D *position, const Coord3D *secondPosition);
    bool internalReportEvaEvent(const EvaEventReport *report);
    void countEvaEventAsPlayed(EvaEventID eventID);
    bool isEventBlockedByTimeout(EvaEventID eventID) const;
    bool isEventAboutToPlay(EvaEventID eventID) const;
    bool getLastReallyPlayedFrameForEvaEvent(EvaEventID eventID, unsigned int *frame) const;
    bool rva001DD670(EvaEventID eventID, Vec001DCDAF *position) const;
    void rva001DD3DD();
    void rva001DDF04();
    int rva001DE78E(const AsciiString *name);
    void rva001DCFC9(INI *ini, void *info);
    int iniScanEvaEventID(const char *name);
    AsciiString messageToName(int message);
    void rva001debf6(_STL::vector<AsciiString, _STL::allocator<AsciiString> > *out);
    void xferEvaEventID(Xfer *xfer, int *eventID);
    static void iniParsePredefinedEvaEvent(INI *ini);
    static void iniParseNewEvaEvent(INI *ini);
    static void iniParseEvaEventForwardReference(INI *ini);

protected:
    virtual void loadPostProcess();
    virtual void xfer(Xfer *xfer);

public:
    unsigned char m_storage10[0x5C];
    unsigned int m_word6C;
    int m_word70;
    unsigned int m_word74;
    int m_word78;
    bool m_byte7C;
    unsigned char m_pad7D[3];
    float m_float80;
    unsigned int m_word84;
    int m_word88;
    unsigned int m_word8C;
    unsigned int m_word90;
    float m_float94;
};

extern Eva *TheEva;

#endif
