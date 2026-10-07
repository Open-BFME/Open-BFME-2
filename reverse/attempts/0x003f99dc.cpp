// ?processFrame@LivingWorldEyeTower@@AAEXXZ
// partial score=0.9 date=2026-10-07
// cl: /DNDEBUG /MD /GX-
// BFME1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f:
// game/GameEngine/Source/GameClient/LivingWorldEyeTowerProcessFrame.cpp.
// Native Ghidra3F99DC..3F9A2B RET0; rowed updateState3F9BED tailcalls
// this method. Target establishes singleton+8C source and slot38 snapshot,
// target pair5C/60 copied to24/28, and the two targets1C/20. Donor supplies
// processFrame purpose; helper3F962F remains address-named. Helper3F936E
// unused receiver ABI is established by the ECX=this setup at both calls.
class Rva002D3627Host;
extern Rva002D3627Host *g_00DFEF18;
struct FrameScratch { unsigned int values[3]; };
class FrameState {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void snapshot(void *source, FrameScratch *point);
};
class Rva003F936EHost;
struct FramePair { volatile unsigned int first; volatile unsigned int second; };
class LivingWorldEyeTower {
    void processFrame();
    void rva003F962F();
    void rva003F936E(unsigned int target, float *point);
    char head[0x1C];
    unsigned int firstTarget;
    unsigned int secondTarget;
    FramePair framePoint;
    char gap[0x30];
    FramePair targetPoint;
};
void LivingWorldEyeTower::processFrame()
{
    FrameScratch scratch;
    FrameState *state = reinterpret_cast<FrameState *>(g_00DFEF18);
    state->snapshot(reinterpret_cast<char *>(state) + 0x8C, &scratch);
    framePoint.first = targetPoint.first;
    framePoint.second = targetPoint.second;
    rva003F962F();
    rva003F936E(firstTarget, reinterpret_cast<float *>(&framePoint));
    rva003F936E(secondTarget, reinterpret_cast<float *>(&framePoint));
}
