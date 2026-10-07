// Ghidra 0x000562FA..0x0005634C, 82B, thiscall RET8.
// Position-result layout is shared with the verified 0x0005160F provider.
// The query and receiver relationship are target facts; the original
// method and validity-flag meanings remain unresolved.
struct BfmeEventPositionView {
    float x, y, z;
    BfmeEventPositionView() {}
    BfmeEventPositionView(float a, float b, float c) : x(a), y(b), z(c) {}
};
class AudioEventRTS;
class MilesAudioManager {
public:
    bool rva0005623E(int, void **, int);
    BfmeEventPositionView Rva0005160FGet(AudioEventRTS *, bool &);
    bool rva000562FA(int, BfmeEventPositionView *);
};

bool MilesAudioManager::rva000562FA(int key, BfmeEventPositionView *output)
{
    void *event = 0;
    if (rva0005623E(key, &event, 0) && event != 0) {
        bool valid;
        *output = Rva0005160FGet(static_cast<AudioEventRTS *>(event), valid);
        if (valid)
            return true;
    }
    return false;
}
