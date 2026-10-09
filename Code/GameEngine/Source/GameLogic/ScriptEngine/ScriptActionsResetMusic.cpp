// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// BF1f989 original music reset body and WB target doResetMusicScripting.
#include "ascii_string.h"
template<int N> class Rva003C0532Slots : public Rva003C0532Slots<N - 1>
{
public:
    virtual void gap(char (*)[N]);
};
template<> class Rva003C0532Slots<0> {};
class ClientSubsystem : public Rva003C0532Slots<38>
{
public:
    virtual void pauseAudio(int first, int second, int third);
};

class ScriptEngine
{
public:
	void *rva0020881A(AsciiString name);
};

class AudioManager;
extern AudioManager *TheAudio;
#define TheAudioClientUpdate ((ClientSubsystem *)TheAudio)
// BFME2 data owns TheScriptEngine at VA 0x00DFE16C; this view retains
// the rowed neutral flag-lookup signature at 0x0020881A.
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doResetMusicScripting(bool fadeout);
};

void ScriptActions::doResetMusicScripting(bool fadeout)
{
	int pause = !fadeout;
	int *pausePtr = &pause;
	TheAudioClientUpdate->pauseAudio(0, 0, *pausePtr);
	char text[] = "/___MusicScript_Init";
	bool *flag = (bool *)((ScriptEngine *)TheScriptEngine)->rva0020881A(
		AsciiString(text));
	if (flag != 0)
		*flag = true;
}
