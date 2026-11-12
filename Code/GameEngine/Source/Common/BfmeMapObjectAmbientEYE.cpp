// cl: /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
//
// ?bfmeRunEYE@BfmeNodeEYE@@QAEXXZ, retail 0x0030DEAE..0x0030E09A (492 B, RET0):
// the map-object ambient sound refresh that bfmeGoEYE (BfmeConv888.cpp) runs
// on every map object after storing the mode in g_bfmeCurEYE, and that the
// +0x44 bit-0x10 setters 0x0030E2EC/0x0030E2F5 tail into.
// Target evidence: the existing donor_sweep pin names this address; WB
// 0x00A7DDB0 (string " MapObjectAmb %d %s") is the same body with the
// reference-count helpers inline. No ZH or BFME 1 body; the map-object twin of
// GameClient::rva0023B383 (GameClientDrawableTOC.cpp), whose views are reused:
// TranslateAudioProperties (0x00433796) on the property Dict (+0x24) and
// template (+0x18) gives forced-off, a customized info and enabled; a
// customized info is renamed " MapObjectAmb %d %s" under a global counter and
// handed to TheAudio (slot 74); otherwise the template's ambient slot 0x25.
// The mode (1 always, 2 the enabled property, 3 the info's 0x001D9781 test)
// decides whether the sound should play; handles from 5 up count as playing.
// Starting stores the customized info at +0x58 and the slot-25 handle at
// +0x54 from an event at the object position (0x0030D631); stopping is the
// rowed 0x0030D606. Field and method names are address- or role-derived.
#include "ascii_string.h"
#include "../../Include/Common/BfmeAudioEventPrefix136.h"

class Dict;
class Drawable;
class ThingTemplate;
class AudioEventInfo;

class Rva004EC166
{
public:
	void rva00433403(const AsciiString &name);

	char m_pad00[8];
	AsciiString m_audioName; // +0x08
};

class AudioManager
{
public:
	virtual void vf00(); virtual void vf01(); virtual void vf02(); virtual void vf03(); virtual void vf04();
	virtual void vf05(); virtual void vf06(); virtual void vf07(); virtual void vf08(); virtual void vf09();
	virtual void vf10(); virtual void vf11(); virtual void vf12(); virtual void vf13(); virtual void vf14();
	virtual void vf15(); virtual void vf16(); virtual void vf17(); virtual void vf18(); virtual void vf19();
	virtual void vf20(); virtual void vf21(); virtual void vf22(); virtual void vf23(); virtual void vf24();
	virtual unsigned int addAudioEvent(const BfmeAudioEventPrefix136 *event); // slot 25 (+0x64)
	virtual void vf26(); virtual void vf27(); virtual void vf28(); virtual void vf29(); virtual void vf30();
	virtual void vf31(); virtual void vf32(); virtual void vf33(); virtual void vf34(); virtual void vf35();
	virtual void vf36(); virtual void vf37(); virtual void vf38(); virtual void vf39(); virtual void vf40();
	virtual void vf41(); virtual void vf42(); virtual void vf43(); virtual void vf44(); virtual void vf45();
	virtual void vf46(); virtual void vf47(); virtual void vf48(); virtual void vf49(); virtual void vf50();
	virtual void vf51(); virtual void vf52(); virtual void vf53(); virtual void vf54(); virtual void vf55();
	virtual void vf56(); virtual void vf57(); virtual void vf58(); virtual void vf59(); virtual void vf60();
	virtual void vf61(); virtual void vf62(); virtual void vf63(); virtual void vf64(); virtual void vf65();
	virtual void vf66(); virtual void vf67(); virtual void vf68(); virtual void vf69(); virtual void vf70();
	virtual void vf71(); virtual void vf72(); virtual void vf73();
	virtual void addAudioEventInfo(Rva004EC166 *info); // slot 74 (+0x128)
};
extern AudioManager *TheAudio;

// The 4-byte owning reference; release is inlined at each scope exit.
struct Rva00239057Ref : OpaqueRefElement4
{
	Rva004EC166 *get() const { return (Rva004EC166 *)referent; }
};

struct AudioEventInfoRef : OpaqueRefElement4
{
	AudioEventInfoRef(const AudioEventInfo *info);
};

// 8-byte template audio slot, returned by value; the info reference is at +4.
class Rva002390CB
{
public:
	int m_00;
	OpaqueRefElement4 m_info; // +0x04
};

class Rva00239435
{
public:
	Rva002390CB rva00239435(int index) throw();
};

#include "../../../GameEngineDevice/Include/Rva001D98BD.h"

class BfmeRetBWF;
#include "../../Include/Common/Rva0030D631.h"
#include "../../Include/Common/Rva0030D606.h"

void TranslateAudioProperties(Dict *props, Drawable *draw, ThingTemplate *tmpl, bool *soundOff,
	Rva000A8C9B *customInfo, bool *soundEnabled);

// Mode stored by bfmeGoEYE (declared as there).
extern void *g_bfmeCurEYE;
// Rename counter for customized map-object infos (retail 0x00E00948, no owner).
extern int g_00E00948;
// Both are zero-initialised .data (VA 0x00E00938 and 0x00E00948) and owned here;
// bfmeGoEYE (BfmeConv888.cpp) is the mode's only writer.
void *g_bfmeCurEYE;
int g_00E00948;

struct BfmeNodeEYE
{
	void bfmeRunEYE();

	unsigned char m_pad00[0x18];
	ThingTemplate *m_template; // +0x18
	unsigned char m_pad1C[0x24 - 0x1C];
	unsigned char m_properties[4]; // +0x24 Dict
	unsigned char m_pad28[0x44 - 0x28];
	unsigned int m_flags; // +0x44
	// Retail tests bit 4 as mov/shr 4/test al,1: a by-bit inline test, not a mask.
	bool testFlag(int bit) const { return (m_flags & (1 << bit)) != 0; }
	unsigned char m_pad48[0x54 - 0x48];
	unsigned int m_ambientHandle; // +0x54
	OpaqueRefElement4 m_customAmbientInfo; // +0x58
};

void BfmeNodeEYE::bfmeRunEYE()
{
	if (!TheAudio || !m_template)
		return;

	bool shouldPlay = false;
	bool forcedOff = false;
	Rva00239057Ref customInfo;
	bool enabled = false;
	TranslateAudioProperties((Dict *)m_properties, 0, m_template, &forcedOff,
		(Rva000A8C9B *)&customInfo, &enabled);
	if (customInfo.referent)
	{
		AsciiString name;
		name.format(" MapObjectAmb %d %s", g_00E00948, customInfo.get()->m_audioName.str());
		g_00E00948++;
		customInfo.get()->rva00433403(name);
		TheAudio->addAudioEventInfo(customInfo.get());
	}

	Rva00239057Ref info;
	if (!forcedOff && g_bfmeCurEYE && testFlag(4))
	{
		if (!customInfo.referent)
			(OpaqueRefElement4 &)info = ((Rva00239435 *)m_template)->rva00239435(0x25).m_info;
		else
			(OpaqueRefElement4 &)info = AudioEventInfoRef((const AudioEventInfo *)customInfo.referent);

		if (!info.referent)
			shouldPlay = false;
		else
		{
			switch ((int)g_bfmeCurEYE)
			{
			case 1:
				shouldPlay = true;
				break;
			case 2:
				shouldPlay = enabled;
				break;
			case 3:
				shouldPlay = false;
				if (((Rva001D98BD *)info.referent)->rva001D9781())
					shouldPlay = true;
				break;
			}
		}
	}
	else
		shouldPlay = false;

	bool playing = m_ambientHandle >= 5;
	if (shouldPlay != playing)
	{
		if (shouldPlay)
		{
			m_customAmbientInfo = customInfo;
			if (info.referent)
			{
				BfmeAudioEventPrefix136 event(info,
					*(const BfmeEventPositionView *)((Rva0030D631 *)this)->rva0030D631(), 0);
				m_ambientHandle = TheAudio->addAudioEvent(&event);
			}
		}
		else
			((Rva0030D606 *)this)->rva0030D606();
	}
}
