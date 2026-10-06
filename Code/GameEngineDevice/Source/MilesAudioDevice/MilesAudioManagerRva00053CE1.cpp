// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX-
// ?rva00053CE1@Rva00053CE1@@QAEXMHH@Z @0x00053CE1 69B: thiscall volume flags idx.
// Locks MilesMutexGuard over +0x9D4 then calls row 0x000523A0
// ?setVolumes@Rva00699180Owner@@QAEXME@Z on array elem at +0x12C stride 0x1C4.
// Layout mirrors Code/GameEngine/Source/Common/Rva00059A25Method.cpp which
// proves +0x12C stride 0x1C4 with guard over +0x9D4; mutex at +0x9D4 also
// target-measured for MilesAudioManager in StopAudio TU. Chain from 0x000523A0.
class Rva00699180Owner
{
public:
    void setVolumes(float volume, unsigned char flags);
};

class MilesMutexGuard
{
public:
    MilesMutexGuard(void *obj, int flags);
    ~MilesMutexGuard();
private:
    void *m_obj;
    int m_flags;
};

struct Elem1C4
{
    char data[0x1C4];
};

class Rva00053CE1
{
public:
    void rva00053CE1(float volume, int flags, int idx);
private:
    char m_pad[0x12C];
    Elem1C4 m_arr[1];
    char m_padAfter[0x9D4 - 0x12C - 0x1C4];
    int m_9D4;
};

void Rva00053CE1::rva00053CE1(float volume, int flags, int idx)
{
    MilesMutexGuard guard(&m_9D4, 0);
    ((Rva00699180Owner *)&m_arr[idx])->setVolumes(volume, (unsigned char)flags);
}
