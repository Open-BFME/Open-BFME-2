// cl: /Ireference/shims/moduledata /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Native37F27B..37F2C0 RET4 and Player constructor2B0F3C establish identity.
// Owner+10 and the D8 vector+4 are established by UnitRevivalTrackerXfer.cpp.
// Base inheritance spelling is unknown; use the proven four-slot ABI view.
// Retail four-slot Snapshot ABI without a separate base-cleanup state.
// The constructor has a single unwind action for its D8-entry vector;
// field layout and virtual order agree with the existing Xfer provider.
class Xfer;
#include <vector>
class Player;
class UnitRevivalEntry {
public:
 UnitRevivalEntry();UnitRevivalEntry(const UnitRevivalEntry&);~UnitRevivalEntry();
 UnitRevivalEntry&operator=(const UnitRevivalEntry&);
private:char bytes[0xD8];
};
class UnitRevivalTracker {
public:
 UnitRevivalTracker(Player*);virtual ~UnitRevivalTracker();void rva0037F26D();
protected:virtual void loadPostProcess();virtual void crc(Xfer*);virtual void xfer(Xfer*);
private:_STL::vector<UnitRevivalEntry>entries;Player*player;
};
UnitRevivalTracker::UnitRevivalTracker(Player*owner):player(owner) {rva0037F26D();}
