// ?rva0005634C@MilesAudioManager@@QAEXHMH@Z
// partial score=0.85 date=2026-10-07
// cl: /O1 /G7 /arch:SSE /EHsc /MD
// Ghidra 0005634C..000563FE, 178B, RET12. Target evidence establishes
// the three argument slots and the manager receiver, already called by
// verified 00057530. Lookup returns a borrowed pointer and an owning
// four-byte reference. Only the measured fields below are modelled;
// the original method and record identities remain unknown.
class OpaqueRefCounted
{
public:
    virtual ~OpaqueRefCounted();
    void Release_Ref();
private:
    long refs;
};

class Rva0005634CPlaying : public OpaqueRefCounted
{
public:
    char at08[0x3c - 8];
    float value;
    float clock;
    char at44[0x4f - 0x44];
    bool dirty;
};

struct Rva0005634CReference
{
    Rva0005634CPlaying *value;
    Rva0005634CReference() : value(0) {}
    ~Rva0005634CReference()
    {
        if (value)
            value->Release_Ref();
    }
};

class Rva00481FAFFloatSlot
{
public:
    __declspec(noinline) void store(float value);
private:
    char at00[0x2c];
    float value;
};

struct Rva0005634CSettings
{
    char at00[0x78];
    int clock;
};

class MilesAudioManager
{
public:
    void rva0005634C(int key, float value, int mode);
    // Existing ledger ABI exposes the third dword as int. This call's
    // native LEA passes an owning-reference address in that slot.
    bool rva00055FCA(int key, void **borrowed, int ownerAddress);
private:
    char at00[0x10];
    Rva0005634CSettings *settings;
};

// ?rva0005634C@MilesAudioManager@@QAEXHMH@Z present-unmatched
void MilesAudioManager::rva0005634C(int key, float value, int mode)
{
    Rva00481FAFFloatSlot *borrowed = 0;
    Rva0005634CReference owner;
    bool found = rva00055FCA(key, reinterpret_cast<void **>(&borrowed), reinterpret_cast<int>(&owner));
    Rva0005634CPlaying *playing = owner.value;
    if (found) {
        if (mode == 1) {
            if (borrowed) {
                borrowed->store(value);
                if (playing) {
                    playing->dirty = true;
                    playing->value = value;
                    playing->clock = 0.0f;
                }
            }
        } else if (playing) {
            playing->value = value;
            playing->clock = static_cast<float>(settings->clock);
        } else if (borrowed) {
            borrowed->store(value);
        }
    }
}
