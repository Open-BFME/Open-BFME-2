// cl: /O1 /Oy- /G7 /arch:SSE /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// WB F45310 names Palantir::Impl::UpdatePlayerStats. Native2D4BDB..2D4DD0
// proves the cache/flag offsets and20 science buttons. All callees already
// have verified providers. Unobserved portions of the objects remain opaque.
#include <algorithm>
namespace _STL {
template <> bool *find(bool *, bool *, const bool &);
}

class Player;
class PlayerList;
class BfmeMemberRV;
class BfmeThingRV
{
public:
    BfmeMemberRV *bfmePickRV();
};
class ControlBar
{
public:
    bool rva0031E068(Player *, int);
};
extern PlayerList *ThePlayerList;
extern ControlBar *TheControlBar;
void playPlayerLevelUpEffect();
bool Rva003FEE43SetPlayerRank(int);
void setPlayerMagicProgress(int);
int Rva0043C99AGet();
unsigned char Rva0043CCD1Get();
void highlightPlayerMagicButton(bool);
void setPlayerButtonsState(bool);
void enablePlayerMagicButton(bool);

struct PalantirPlayerTemplateView
{
    char unknown00[0x1BC];
    bool ring;
};
struct PalantirPlayerView
{
    char unknown00[0x14];
    float experience;
    char unknown18[4];
    int level;
    char unknown20[4];
    int rank, nextExperience, currentExperience;
    char unknown30[4];
    PalantirPlayerTemplateView *playerTemplate;
};

// Native2D2EBC..2D2EEF is a separate51-byte extent, immediately after the
// completely rowed ComputeFrameState2D2E57..2D2EBC and before the next
// PUSH ESI/PUSH EDI entry. The emitted static helper consumes EAX, matching
// retail's compiler-private ABI. WB F456C0 supplies the same arithmetic as
// the named update's helper; its original spelling remains unasserted.
static inline int Rva002D2EBCProgress(const PalantirPlayerView *player)
{
    int range = player->nextExperience - player->currentExperience;
    if (range == 0) return 1;
    int percent = int(player->experience - player->currentExperience) * 100 / range;
    if (percent < 1) percent = 1;
    else if (percent > 100) percent = 100;
    return percent;
}

namespace Palantir {
class Impl
{
public:
    void UpdatePlayerStats();
private:
    char unknown00[0x7E];
    bool rankValid : 1;
    bool buttonsValid : 1;
    bool buttonsState : 1;
    bool magicEnabled : 1;
    bool magicHighlighted : 1;
    bool unknownFlag : 1;
    unsigned char unusedBits : 2;
    char unknown7F;
    int lastLevel, lastRank, lastProgress;
    char unknown8C[0x44];
    bool previousAvailability[20];
    bool highlighted;
};
}

void Palantir::Impl::UpdatePlayerStats()
{
    Player *localPlayer = reinterpret_cast<Player *>(
        reinterpret_cast<BfmeThingRV *>(ThePlayerList)->bfmePickRV());
    PalantirPlayerView *player = reinterpret_cast<PalantirPlayerView *>(localPlayer);
    int level = player->level;
    if (level != lastLevel) {
        if (lastLevel >= 0 && level > lastLevel) playPlayerLevelUpEffect();
        lastLevel = level;
    }
    if (!rankValid || player->rank != lastRank) {
        if (Rva003FEE43SetPlayerRank(player->rank)) {
            rankValid = true;
            lastRank = player->rank;
        }
    }
    int percent = Rva002D2EBCProgress(player);
    if (percent != lastProgress) {
        setPlayerMagicProgress(percent);
        lastProgress = percent;
    }

    bool available[20];
    for (int i = 0; i < 20; ++i)
        available[i] = TheControlBar->rva0031E068(localPlayer, i);
    if (!highlighted) {
        for (int i = 0; i < 20; ++i) {
            if (available[i] && !previousAvailability[i]) {
                highlighted = true;
                break;
            }
        }
    } else if (static_cast<unsigned char>(Rva0043C99AGet()) || !Rva0043CCD1Get() ||
        _STL::find(available, available + 20, true) == available + 20) {
        highlighted = false;
    }
    _STL::copy(available, available + 20, previousAvailability);
    if (magicHighlighted != highlighted) {
        highlightPlayerMagicButton(highlighted);
        magicHighlighted = highlighted;
    }

    bool enabled;
    // The existing getter is byte-spelled. WB's Bool result and native's
    // unchanged AL store establish a bool representation here; copying that
    // byte preserves the existing provider ABI without a new return-type pin.
    reinterpret_cast<unsigned char &>(enabled) = Rva0043CCD1Get();
    PalantirPlayerTemplateView *playerTemplate = player->playerTemplate;
    if (playerTemplate) {
        bool ring = playerTemplate->ring;
        if (!buttonsValid || ring != buttonsState) {
            setPlayerButtonsState(ring);
            buttonsValid = true;
            buttonsState = ring;
            magicEnabled = false;
            magicHighlighted = false;
            unknownFlag = false;
            enabled = magicEnabled;
        }
    }
    if (magicEnabled != enabled) {
        enablePlayerMagicButton(enabled);
        magicEnabled = enabled;
    }
}
