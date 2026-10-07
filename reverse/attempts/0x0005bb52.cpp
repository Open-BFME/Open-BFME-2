// ?rva0005BB52@MilesAudioManager@@QAEXPAXPBUCoord3D@@@Z
// partial score=0.95 date=2026-10-07
// ?rva0005BB52@MilesAudioManager@@QAEXPAXPBUCoord3D@@@Z
// cl: /O1 /arch:SSE /G7 /Oy- /DNDEBUG /DWIN32 /MD /EHsc /ICode/Libraries/Include/Lib
// Ghidra 0005BB52..0005BBE2, 144B, RET8. MilesAudioManager receiver is
// established by the same-this 52662/5A9F8 neighbours. PlayingAudio event
// +1C and the three Miles imports are read directly from the target.
// ZH initFilters3D and BFME1 Rva006B3F90InitFilters3D.cpp (ba7ddda7e8)
// provide the volume/pitch semantic lead; three final helper names remain
// unresolved and retain their addresses. The target has no sample null guard.
#include "Coord3D.h"
typedef void *H3DSAMPLE;
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_volume(H3DSAMPLE, float);
extern "C" __declspec(dllimport) int __stdcall AIL_3D_sample_playback_rate(H3DSAMPLE);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_playback_rate(H3DSAMPLE, int);
class Rva002D94DD
{
public:
    float rva002D94DD() const;
};
struct Rva0005BB52Playing
{
    char unknown00[0x1C];
    Rva002D94DD *event;
};
class MilesAudioManager
{
public:
    void rva0005BB52(void *ref, const Coord3D *position);
    void *get3DSampleHandleForPlayingAudio(void *ref);
    float rva0005A9F8(void *ref, int apply, int fade);
    void rva000545C1(void *ref, const Coord3D *position);
    void rva00055C5D(void *ref, unsigned char *result);
    void rva00052FA0(void *ref);
};
void MilesAudioManager::rva0005BB52(void *ref, const Coord3D *position)
{
    void *reference = ref;
    H3DSAMPLE &sample = ref;
    Rva0005BB52Playing *playing;
    sample = get3DSampleHandleForPlayingAudio(reference);
    playing = *reinterpret_cast<Rva0005BB52Playing **>(reference);
    AIL_set_3D_sample_volume(sample, rva0005A9F8(reference, 1, 1));
    float pitch = playing->event->rva002D94DD();
    if (pitch == 0.0f)
    {
    }
    else
        AIL_set_3D_sample_playback_rate(sample,
            static_cast<int>(AIL_3D_sample_playback_rate(sample) * pitch));
    rva000545C1(reference, position);
    rva00055C5D(reference, reinterpret_cast<unsigned char *>(&sample) + 3);
    rva00052FA0(reference);
}
