// ?rva000562FA@MilesAudioManager@@QAE_NHPAUBfmeEventPositionView@@@Z
// partial score=0.8 date=2026-10-07
// Target 0x000562FA, 82 bytes, from the boundary/xref record.
// The matched call at 0x0005160F returns a BfmeEventPositionView and sets
// validity; 0x0005623E is an existing call-site-admitted MilesAudioManager
// pin. This preserves the supported call relationship while the exact
// source signature and target-specific register shape remain open.
struct BfmeEventPositionView { float x, y, z; };
class AudioEventRTS;
BfmeEventPositionView __stdcall Rva0005160FGet(AudioEventRTS *, bool &);
class MilesAudioManager {
public:
    bool rva0005623E(int key, void **result, int flags);
    bool rva000562FA(int key, BfmeEventPositionView *output);
};
bool MilesAudioManager::rva000562FA(int key, BfmeEventPositionView *output)
{
    void *event = 0;
    if (rva0005623E(key, &event, 0) && event != 0) {
        bool valid;
        BfmeEventPositionView position = Rva0005160FGet(
            reinterpret_cast<AudioEventRTS *>(event), valid);
        *output = position;
        return valid;
    }
    return false;
}
