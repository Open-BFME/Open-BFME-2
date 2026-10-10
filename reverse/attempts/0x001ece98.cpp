// ?restartCurrentCampaignMission@LinearCampaign@@QAEXXZ
// partial score=0.8 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// WB AF8520 names restartCurrentCampaignMission; native 1ECE98..1ECEF6.
// The 172-byte element and three-word vector storage are target observations.
// insertRange's receiver ABI still needs reconciliation with the old free
// Rva001ECD19 forward and its ECX-reading worker at 1EC1B4. No admission.
#include <vector>
struct BfmeAssignRecord172 {
    ~BfmeAssignRecord172();
    unsigned char bytes[172];
};
class LinearCampaignHistoryView : public _STL::vector<BfmeAssignRecord172> {
public:
    void insertRange(BfmeAssignRecord172 *, BfmeAssignRecord172 *, BfmeAssignRecord172 *);
};
class Rva001EB6FE { public: void rva001EB68A(); };
class Rva001EB456 { public: void rva001EB456(int, int); };
class LinearCampaign {
public:
    void restartCurrentCampaignMission();
private:
    unsigned char unknown00[0xA4];
    LinearCampaignHistoryView current;
    unsigned unknownB0;
    _STL::vector<BfmeAssignRecord172> previous;
    bool won, restarting, unknownC2, advanced;
};
void LinearCampaign::restartCurrentCampaignMission() {
    if (won || advanced) {
        reinterpret_cast<Rva001EB6FE *>(this)->rva001EB68A();
    } else {
    restarting = false;
    current.insertRange(current.end(), previous.begin(), previous.end());
    previous.erase(previous.begin(), previous.end());
    reinterpret_cast<Rva001EB456 *>(this)->rva001EB456(1, 0);
    }
}
