// cl: /Ireference/shims/moduledata /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Native37F27B..37F2C0 RET4 and Player constructor2B0F3C establish identity.
// Owner+10 and the D8 vector+4 are established by UnitRevivalTrackerXfer.cpp.
// Retail table 0x00C18DF0 contains only the rowed xfer at 0x0037F39E.
// The vector has the constructor's sole cleanup action.
// The constructor has a single unwind action for its D8-entry vector;
// field layout agrees with the existing Xfer provider.
class Xfer;
#include <vector>
class Player;
class UnitRevivalEntry {
public:
 UnitRevivalEntry();UnitRevivalEntry(const UnitRevivalEntry&);~UnitRevivalEntry();
 UnitRevivalEntry&operator=(const UnitRevivalEntry&);
private:char m_bytes[0xD8];
};
class UnitRevivalTracker {
public:
 UnitRevivalTracker(Player*);void rva0037F26D();
protected:virtual void xfer(Xfer*);
private:_STL::vector<UnitRevivalEntry>m_entries;Player*m_player;
};
UnitRevivalTracker::UnitRevivalTracker(Player*owner):m_player(owner) {rva0037F26D();}
