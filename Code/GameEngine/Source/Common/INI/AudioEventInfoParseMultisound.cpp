// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// platformsdk
// stlport
// ?parseMultisoundDefinition@AudioEventInfo@@SAXPAVINI@@@Z, retail 0x001DA4DE, 374 B
// (WorldBuilder twin 0x00AC05E0). Map-ini rejection, newAudioEventInfo through the
// audio manager's slot 73, subsound vector reset, field parse and the PLAY_ONE /
// LOOP / music-track checks. The reference-counted handle's assignment
// (rowed 0x00239099) is defined here as in its owner unit so cl sees that it
// does not keep the handle's address: retail then keeps the referent in ESI and
// releases it at scope end without reloading the handle.
#include <windows.h>
#include "ascii_string.h"
#include <vector>
#include "../../../Include/Common/INI/FieldParse.h"

struct FieldParse;

#include "../../../Include/Common/INI/INI.h"

extern const struct FieldParse g_00BD9D68[];
extern const float g_00BDA3E4;

class OpaqueRefCounted
{
public:
	virtual ~OpaqueRefCounted();
	void Add_Ref() { InterlockedIncrement(&refs); }
	void Release_Ref();
private:
	long refs;
};

struct OpaqueRefElement4
{
	OpaqueRefCounted *referent;
	OpaqueRefElement4() : referent(0) {}
	~OpaqueRefElement4() { if (referent) referent->Release_Ref(); }
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};

inline __declspec(noinline) OpaqueRefElement4 &OpaqueRefElement4::operator=(const OpaqueRefElement4 &other)
{
	if (this != &other) {
		if (other.referent)
			other.referent->Add_Ref();
		if (referent)
			referent->Release_Ref();
		referent = other.referent;
	}
	return *this;
}

class AudioManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72();
	virtual OpaqueRefElement4 newAudioEventInfo(const AsciiString &name, int create);
	virtual void slot74();
	virtual OpaqueRefElement4 findAudioEventInfo(const AsciiString &name) const;
};

extern AudioManager *TheAudio;


class BfmeStringTailRecord156 {public:OpaqueRefElement4 ref;int weight;};
namespace _STL {template<> BfmeStringTailRecord156 *vector<BfmeStringTailRecord156>::erase(BfmeStringTailRecord156*,BfmeStringTailRecord156*);}
extern const FieldParse g_00BD9F1C[];
class AudioEventInfo : public OpaqueRefCounted {public:
 AsciiString name;char pad0c[0x4c-0x0c];unsigned control;
 char pad50[0x80-0x50];_STL::vector<BfmeStringTailRecord156> subsounds;int totalWeight;
 char pad90[0xb0-0x90];int type;
 static void parseMultisoundDefinition(INI*);
};
void AudioEventInfo::parseMultisoundDefinition(INI *ini)
{
 int allow=1;
 if(ini->getLoadType()==2) throw INIException(3,"You cannot define or override a Multisound in map.ini");
 if(ini->getLoadType()==5) allow=0;
 AsciiString name;
 OpaqueRefElement4 track;
 name=ini->getNextToken(0);
 track=TheAudio->newAudioEventInfo(name,allow);
 AudioEventInfo *info=static_cast<AudioEventInfo*>(track.referent);
 if(!info) return;
 info->subsounds.clear();
 info->totalWeight=0;
 info->name=name;
 info->type=5;
 ini->initFromINI(info,g_00BD9F1C);
 if(info->control & ~0x81) throw INIException(1,"PLAY_ONE and LOOP are the only valid control flags for Multisounds");
 if(info->control & 1) {
  if(!(info->control & 0x80)) throw INIException(1,"Multisound control flag \"LOOP\" is supported only in conjunction with flag PLAY_ONE. See me if you need this changed.");
  BfmeStringTailRecord156 *end=info->subsounds.end();
  for(BfmeStringTailRecord156 *i=info->subsounds.begin();i!=end;++i) {
   AudioEventInfo *sub = static_cast<AudioEventInfo*>(i->ref.referent);
   if(sub && sub->type!=0) throw INIException(1,"Multisound control flag \"LOOP\" is supported only when all subsounds are MusicTracks. See me if you need this changed.");
  }
 }
}
