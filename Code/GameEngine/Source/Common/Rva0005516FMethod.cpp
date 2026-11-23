// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /Oi /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// ?rva0005516F@Rva0005516F@@QAEXPAUHolder@@H@Z @0x0005516F 83B.
// Outer array at +0x12C stride 0x1C4 of MilesAudioManager::GlobalVolumeData; first calls elem[key] then if key==2 fans out to elems 0,1 with key 2.
// The array layout agrees with MilesAudioManager::rva00053CE1 and MilesAudioManager::rva00059A25.
// The callee is 0x000550F7 and the caller is 0x0005FDCA.
struct Holder;
#include "../../../GameEngineDevice/Include/MilesAudioDevice/MilesAudioManager.h"

class MilesAudioManager::GlobalVolumeData
{
public:
    void volumeAdjustingSoundStopping(Holder *o, int key);
};
#include "../../Include/Common/Elem1C4.h"
class Rva0005516F
{
public:
    void rva0005516F(Holder *o, int key);
private:
    char m_pad[0x12C];
    Elem1C4 m_arr[3];
};
void Rva0005516F::rva0005516F(Holder *holder, int key)
{
    ((MilesAudioManager::GlobalVolumeData *)&m_arr[key])->volumeAdjustingSoundStopping(holder, key);
    if (key == 2)
    {
        for (int i = 0; i < 3; ++i)
        {
            if (i != 2)
                ((MilesAudioManager::GlobalVolumeData *)&m_arr[i])->volumeAdjustingSoundStopping(holder, 2);
        }
    }
}
