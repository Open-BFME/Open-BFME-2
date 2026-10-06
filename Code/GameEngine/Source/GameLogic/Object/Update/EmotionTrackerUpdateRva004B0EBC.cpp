// cl: /EHsc /DNDEBUG /MD
// ?rva004B0EBC@EmotionTrackerUpdate@@QAE_NXZ, retail 0x004B0EBC, 41 bytes.
// Honest-address method of EmotionTrackerUpdate proven by vector offsets:
// +0x90/+0x94 are m_emotions begin/end (EmotionTrackerUpdateDtor.cpp has
// EmotionTrackerVecHolder at +0x90). Iterates 4-byte pointer array,
// double-derefs +4 then tests byte at +0x18C, returns bool.
extern class GameLogic *TheGameLogic;

class GameLogic
{
public:
    int getFrame() const { return m_frame; }

private:
    char m_pad[0x40];
    int m_frame;
};

class EmotionTrackerUpdate
{
public:
    bool rva004B0EBC();
    void rva004B0D4C(int index, void *p);
    void PulseEmotion(int index, void *p, int delay);

private:
    char m_pad0[0x24];
    bool m_active[12];
    int m_array30[12];
    int m_array60[12];
    void *m_begin;
    void *m_end;
};

struct Rva004B0EBCInner
{
    char m_pad[4];
    void *m_ptr;
};

struct Rva004B0EBCOuter
{
    char m_pad[0x18C];
    bool m_flag;
};

bool EmotionTrackerUpdate::rva004B0EBC()
{
    void **it = (void **)m_begin;
    void **end = (void **)m_end;
    goto cond;
loop:
    {
        Rva004B0EBCInner *inner = *(Rva004B0EBCInner **)it;
        Rva004B0EBCOuter *outer = *(Rva004B0EBCOuter **)((char *)inner + 4);
        if (*(bool *)((char *)outer + 0x18C)) {
            return true;
        }
        ++it;
    }
cond:
    if (it != end) {
        goto loop;
    }
    return false;
}

// ?rva004B0D4C@EmotionTrackerUpdate@@QAEXHPAX@Z, retail 0x004B0D4C (36B):
// the undelayed sibling directly before PulseEmotion - same active flag and
// +0x74 source ID, frame slot cleared to 0. Object+0x24C forwards to it
// through its outermost container (0x0028EC48).
void EmotionTrackerUpdate::rva004B0D4C(int index, void *p)
{
    m_active[index] = true;
    m_array30[index] = 0;
    int v = (p != 0) ? *(int *)((char *)p + 0x74) : 0;
    m_array60[index] = v;
}

void EmotionTrackerUpdate::PulseEmotion(int index, void *p, int delay)
{
    m_active[index] = true;
    m_array30[index] = TheGameLogic->getFrame() + delay;
    int v = (p != 0) ? *(int *)((char *)p + 0x74) : 0;
    m_array60[index] = v;
}
