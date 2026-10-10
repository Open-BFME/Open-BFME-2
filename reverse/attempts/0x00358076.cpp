// ?rva00358076@ScriptEngine@@QAE_NABVAsciiString@@_N@Z
// partial score=0.98 date=2026-10-11
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/GameEngine/Include
// stlport
// ?rva00358076@ScriptEngine@@QAE_NABVAsciiString@@_N@Z @0x00358076 280B
// Retail audio-complete twin of 0x00357F5E: CRC find in m_list1A25C, else OpaqueRef via TheAudio slot 0x12c,
// BfmeAudioEventPrefix136 in inner scope so its dtor runs before Release_Ref, length via slot 0x140 / g_00DBA4F0,
// insert via 0x357DF8, frame check at +0x40 with conditional int erase.
// Evidence: LINK BONUS name, CRC 0x3ECA13, insert 0x357DF8, Bfme ctor 0x2D97D6, tail dtor 0x2D9A43,
// Release_Ref 0x50ED3, list erase 0x438539, TheAudio 0x009FE6E8, TheGameLogic 0x009FE78C,
// layout +0x1A25C from ScriptEngine_dtor, donor ZH isAudioComplete plus BFME1 IsAudioComplete, HEAD START from banked 0x00357F5E 0.93 stash.
// 2026-10-11: slot 75 returns the handle BY VALUE (AudioRef with a releasing dtor; hidden return slot reuses
// the name arg at [ebp+8]) - this alone fixes the EH state-0 store after the call, the ev state 1/0 pair and
// the 280B extent. Only gap left (5 lines at +0x48): retail loads the vtable (mov eax,[ecx]) right after
// TheAudio and stores the zeroed timer after push edx; ours schedules xor/stores before the vtable load.
// Tried with no change: timer ctor/aggregate/pair/value-init, zeroing in arg or object comma expr, audio
// local, /G5 /G6 /GB /G7 /arch:SSE /EHs /Oy- /Os-split; timer at function scope or after call is worse.
#include <list>
#include "Common/BfmeAudioEventPrefix136.h"
#include "ascii_string.h"

unsigned long __cdecl Rva003ECA13Get(const AsciiString &s);

struct BfmeSpecialPowerTimer8
{
	unsigned int m_templateID;
	unsigned int m_readyFrame;
};

class Rva00357DF8
{
public:
	void rva00357DF8(const BfmeSpecialPowerTimer8 &rec);
private:
	_STL::list<BfmeSpecialPowerTimer8, _STL::allocator<BfmeSpecialPowerTimer8> > m_list;
};

extern float g_00DBA4F0;

class GameLogic
{
public:
	char m_pad[0x40];
	unsigned int m_frame;
};
extern GameLogic *TheGameLogic;

// The audio event handle slot 75 returns by value: a ref-counted pointer
// released on destruction (the hidden return slot reuses the name argument).
struct AudioRef
{
	OpaqueRefCounted *referent;
	~AudioRef() { if (referent != 0) referent->Release_Ref(); }
};

class AudioManagerView
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03(); virtual void slot04();
	virtual void slot05(); virtual void slot06(); virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23(); virtual void slot24();
	virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34();
	virtual void slot35(); virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual void slot45(); virtual void slot46(); virtual void slot47(); virtual void slot48(); virtual void slot49();
	virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53(); virtual void slot54();
	virtual void slot55(); virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63(); virtual void slot64();
	virtual void slot65(); virtual void slot66(); virtual void slot67(); virtual void slot68(); virtual void slot69();
	virtual void slot70(); virtual void slot71(); virtual void slot72(); virtual void slot73(); virtual void slot74();
	virtual AudioRef getAudioRef(const AsciiString &name);
	virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79();
	virtual float getLength(const BfmeAudioEventPrefix136 *ev);
};
class AudioManager;
extern AudioManager *TheAudio;

class ScriptEngine
{
public:
	bool rva00358076(const AsciiString &s, bool remove);
private:
	char m_pad[0x1A25C];
	_STL::list<BfmeSpecialPowerTimer8, _STL::allocator<BfmeSpecialPowerTimer8> > m_list1A25C;
};

bool ScriptEngine::rva00358076(const AsciiString &s, bool remove)
{
	unsigned long crc = Rva003ECA13Get(s);
	_STL::list<BfmeSpecialPowerTimer8, _STL::allocator<BfmeSpecialPowerTimer8> > &lst = m_list1A25C;
	_STL::list<BfmeSpecialPowerTimer8, _STL::allocator<BfmeSpecialPowerTimer8> >::iterator it;
	for (it = lst.begin(); it != lst.end(); ++it) {
		if (it->m_templateID == crc)
			break;
	}
	if (it == lst.end()) {
		BfmeSpecialPowerTimer8 timer;
		timer.m_templateID = 0;
		timer.m_readyFrame = 0;
		AudioRef ref = ((AudioManagerView *)TheAudio)->getAudioRef(s);
		if (ref.referent == 0)
			return true;
		{
			BfmeAudioEventPrefix136 ev(*(const OpaqueRefElement4 *)&ref, 0);
			float len = ((AudioManagerView *)TheAudio)->getLength(&ev);
			int frames = (int)(len / g_00DBA4F0);
			timer.m_readyFrame = TheGameLogic->m_frame + frames;
			timer.m_templateID = crc;
			((Rva00357DF8 *)&lst)->rva00357DF8(timer);
			it = lst.begin();
		}
	}
	if (TheGameLogic->m_frame >= it->m_readyFrame) {
		if (remove) {
			((_STL::list<int, _STL::allocator<int> > *)&lst)->erase((_STL::list<int, _STL::allocator<int> >::iterator &)it);
		}
		return true;
	}
	return false;
}
