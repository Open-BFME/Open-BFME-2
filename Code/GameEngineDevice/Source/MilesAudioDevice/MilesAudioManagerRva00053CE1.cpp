// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX-
// ?rva00053CE1@Rva00053CE1@@QAEXMHH@Z @0x00053CE1 69B: thiscall volume flags idx.
// Locks MilesMutexGuard over +0x9D4 then calls row 0x000523A0
// ?setVolumes@GlobalVolumeData@MilesAudioManager@@QAEXME@Z on array elem at +0x12C stride 0x1C4.
// Layout mirrors Code/GameEngine/Source/Common/Rva00059A25Method.cpp which
// proves +0x12C stride 0x1C4 with guard over +0x9D4; mutex at +0x9D4 also
// target-measured for MilesAudioManager in StopAudio TU. Chain from 0x000523A0.
#include "../../Include/MilesAudioDevice/MilesMutexGuard.h"

#include "../../../GameEngine/Include/Common/Elem1C4.h"

class MilesAudioManager
{
public:
	class GlobalVolumeData;
    virtual void rva00053CE1(float volume, int flags, int idx);
private:
    char m_pad[0x128];
    Elem1C4 m_arr[1];
    char m_padAfter[0x9D4 - 0x12C - 0x1C4];
    int m_9D4;
};

class MilesAudioManager::GlobalVolumeData
{
public:
    void setVolumes(float volume, unsigned char flags);
};

void MilesAudioManager::rva00053CE1(float volume, int flags, int idx)
{
    MilesMutexGuard guard(&m_9D4, 0);
    ((MilesAudioManager::GlobalVolumeData *)&m_arr[idx])->setVolumes(volume, (unsigned char)flags);
}
