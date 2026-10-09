// cl: /O1 /Oy- /G7 /arch:SSE /DNDEBUG /MD
// Semantic guide: BFME1 9cbfb551 ControlBar_bfmeQueryWD.cpp. BFME2's
// WB C2A210 and native31DFD1..31E068 retain the three output flags but
// delegate command-set lookup and the combined prerequisite/cost test.
// Native31E068..31E09E and WB C2A3B0 prove the adjacent availability test.
enum ScienceType { SCIENCE_INVALID = -1 };

class Rva0043D3A8;
class Player
{
public:
    bool hasScience(ScienceType) const;
};

// Native science range is +A4/+A8/+AC. Only this consumed prefix is
// represented; neither the full CommandButton extent nor container spelling
// is inferred from the BFME1 +84 range. Value access follows the donor.
struct PurchaseScienceRange
{
    ScienceType *first, *last, *capacity;
    bool empty() const { return first == last; }
    ScienceType operator[](int index) const { return first[index]; }
};
class CommandButton
{
public:
    char opaque00[0xA4];
    PurchaseScienceRange science;
    const PurchaseScienceRange &getScienceVec() const { return science; }
};
class CommandSet
{
public:
    const CommandButton *getCommandButton(int) const;
};
class Rva0031D5F8
{
public:
    void *rva0031DF89(const void *);
};
class ScienceStore
{
public:
    bool playerHasRootPrereqsForScience(const Player *, ScienceType) const;
    bool rva001FF4D3(Rva0043D3A8 *, ScienceType) const;
};
extern ScienceStore *TheScienceStore;

class ControlBar
{
public:
    void GetPurchaseScienceStatus(Player *, int, const CommandButton **,
        bool *, bool *, bool *);
    bool rva0031E068(Player *, int);
};

void ControlBar::GetPurchaseScienceStatus(Player *player, int index,
    const CommandButton **buttonOut, bool *found, bool *canPurchase,
    bool *hasScience)
{
    *found = false;
    *canPurchase = false;
    *hasScience = false;
    const CommandSet *set = static_cast<const CommandSet *>(
        reinterpret_cast<Rva0031D5F8 *>(this)->rva0031DF89(player));
    if (!set) return;
    *buttonOut = set->getCommandButton(index);
    if (!*buttonOut) return;
    *found = true;
    const CommandButton *button = *buttonOut;
    if (button->getScienceVec().empty()) return;
    ScienceType science = button->getScienceVec()[0];

    // Native passes the nullable player+4 holder to both science predicates.
    // The root provider retains a legacy Player-spelled argument; the cast
    // expresses its existing pointer ABI, not a new nominal holder identity.
    Rva0043D3A8 *holder = player ? reinterpret_cast<Rva0043D3A8 *>(
        reinterpret_cast<char *>(player) + 4) : 0;
    if (!TheScienceStore->playerHasRootPrereqsForScience(
            reinterpret_cast<const Player *>(holder), science)) return;
    if (!player->hasScience(science)) {
        if (TheScienceStore->rva001FF4D3(holder, science)) *canPurchase = true;
    } else {
        *hasScience = true;
    }
}

bool ControlBar::rva0031E068(Player *player, int index)
{
    const CommandButton *button;
    bool found, canPurchase, hasScience;
    GetPurchaseScienceStatus(player, index, &button, &found, &canPurchase,
        &hasScience);
    return found && canPurchase && !hasScience;
}
