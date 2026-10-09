// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX-
// ?rva000530DF@MilesAudioManager@@QAEXXZ @ 0x000530DF 52B: guard over +0x9D4 then zero +0xBE4 then call row 0x000512C4 with 0. Evidence: same MilesMutexGuard ctor/dtor rows as 0x00052917; mutex +0x9D4 proven by StopAudio; callee row Code/GameEngine/Source/Common/Rva000512C4.cpp.
class MilesMutexGuard
{
public:
    MilesMutexGuard(void *mutex, int defer);
    ~MilesMutexGuard();
private:
    void *m_mutex;
    bool m_held;
};

class MilesAudioManager
{
public:
    void rva000530DF();
    void internalSetReverbRoomType(int roomType);
private:
    char m_pad0[0x9d4];
    int m_mutex9D4;
    char m_pad9D8[0xbe4 - 0x9d8];
    int m_0BE4;
};

void MilesAudioManager::rva000530DF()
{
    MilesMutexGuard guard(&m_mutex9D4, 0);
    m_0BE4 = 0;
    internalSetReverbRoomType(0);
}
