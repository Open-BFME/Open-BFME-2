// ?rva00052662@MilesAudioManager@@QAEPAXPAX@Z
// partial score=0.7 date=2026-10-07
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Native Ghidra52662..52696 RET4 (52B). The served5BB52 body calls
// this manager helper before the native Miles 3D sample APIs. The same
// call ABI is established by rowed5C931. Target facts: indirect playing
// reference; selector14; handle/index word08; manager arrayBD4 of48-byte
// records; validity byte02 and handle04. These are opaque measured views;
// original enum and record names are unknown. Existing address-derived pin
// retained rather than promoting the semantic get3D alias to a target fact.
struct PlayingWord00052662 {
    char unknown00[8];
    union { void *handle; int index; } word;
    char unknown0C[8];
    int kind;
};
struct SampleSlot00052662 {
    char unknown00[2];
    bool used;
    char unknown03;
    void *handle;
    char unknown08[0x40];
};
class MilesAudioManager {
public:
    void *rva00052662(void *reference);
private:
    char unknown00[0xBD4];
    SampleSlot00052662 *samples;
};
void *MilesAudioManager::rva00052662(void *reference)
{
    PlayingWord00052662 *playing = *reinterpret_cast<PlayingWord00052662 **>(reference);
    void *result = 0;
    switch (playing->kind) {
    case 2:
        result = playing->word.handle;
        break;
    case 3: {
        SampleSlot00052662 *begin = samples;
        SampleSlot00052662 &sample = begin[playing->word.index];
        if (sample.used) result = sample.handle;
        break;
    }
    case 4: break;
    default: break;
    }
    return result;
}
