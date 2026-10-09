// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// Retail 0038ADE2..0038AF29: aggregate teardown preceding the WB-named
// PeerThreadClass::pushStatsToRoom. Constructor38AAEB installs C1989C;
// slot0 deleting wrapper38ADC6 calls this virtual destructor. The outer
// address-derived identity is retained because WB F69A90 is unnamed.
// Native teardown proves lifetime members at54..490: eight strings atD0;
// two PlayerStatMap trees at98/A4; record dtors at278/298; ThreadClass base
// teardown last. All gaps derive from native member addresses. This is a
// destructor-only view: novtable suppresses the own-vptr reset absent from
// retail, following SkirmishGameInfoDtor.cpp's established virtual ABI pattern.
// STLport semantics: BFME1 donor0bef414b52a39a3ab1ec98dca60d8a214de4260e.
// Existing callee names are retained; opaque record names preserve uncertainty.
#include <string>
#include <map>
class ThreadClass { public: virtual ~ThreadClass(); private: char pad[0x50]; };
struct BfmeOpaqueOwnedRecord492 { ~BfmeOpaqueOwnedRecord492(); char bytes[492]; };
struct Rva00388EAE { ~Rva00388EAE(); char bytes[12]; };
class __declspec(novtable) Rva0038ADE2 : public ThreadClass {
public: virtual ~Rva0038ADE2();
private:
 std::string s54,s60,s6c,s78;
 char gap84[0x14];
 std::map<std::string,int> m98,ma4;
 char gapb0[4]; std::string sb4;
 char gapc0[4]; std::string sc4;
 std::string names[8];
 char gap130[0x30]; std::string s160,s16c;
 char gap178[0x100]; Rva00388EAE record278;
 std::string s284; char gap290[8];
 BfmeOpaqueOwnedRecord492 record298; char gap484[12];
 std::string s490;
};
Rva0038ADE2::~Rva0038ADE2() {}
