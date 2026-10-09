// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ZH audio pause actions guide the purpose; target slots and integer ABI
// are measured independently at 0x003BBCB3 and its caller.
template<int N> class Rva003BBCB3Slots : public Rva003BBCB3Slots<N - 1>
{
public:
    virtual void gap(char (*)[N]);
};
template<> class Rva003BBCB3Slots<0> {};
class Rva003BBCB3Audio : public Rva003BBCB3Slots<34>
{
public:
    virtual void pauseSound(int, int, int, int);
    virtual void gap35();
    virtual void pauseMusic(int, int, int);
    virtual void pauseSpeech(int, int, int, int);
};
class AudioManager;
extern AudioManager *TheAudio;
void __stdcall Rva003BBCB3Set(bool enabled)
{
    int pause = !enabled;
    int *pausePtr = &pause;
    ((Rva003BBCB3Audio *)TheAudio)->pauseMusic(0, 1, *pausePtr);
}

void __stdcall Rva003BBCD2Set(bool enabled, bool otherEnabled)
{
    int pause = !enabled;
    int otherPause = !otherEnabled;
    int *pausePtr = &pause;
    int *otherPausePtr = &otherPause;
    ((Rva003BBCB3Audio *)TheAudio)->pauseSpeech(0, 1, *pausePtr, *otherPausePtr);
}
void __stdcall Rva003BBC81Set(bool enabled, bool otherEnabled, int kind)
{
    int pause = !enabled;
    int otherPause = !otherEnabled;
    int *pausePtr = &pause;
    int *otherPausePtr = &otherPause;
    ((Rva003BBCB3Audio *)TheAudio)->pauseSound(0, kind, *pausePtr, *otherPausePtr);
}
