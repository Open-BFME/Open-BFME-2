// ?Rva00339184@@YAXPBDPAX@Z
// partial score=0.4 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/iniexception
// stlport
// Audit: worldbuilder-callback-leads.json, 2026-10-05-openbfme2.
// Names are carried from WB diagnostics and associated through matching parser
// keys; the PC bodies independently confirm their corresponding behavior.
// PC table7D9D68: Sounds/Attack/Decay ->1DAD3E with stores50/60/70;
// PC table7D9F1C: Subsounds ->1DAD68 with store80. All offsets were reread in PC.
// The 42-byte wrapper passes the event name at+8 and optional weight-total
// offset to the shared weighted-token parser1DABB6. The 329-byte resolver
// builds name/weight pairs, resolves owning references through audio slot12C,
// rejects missing names except NoSound and direct self-reference, then appends.
// Reference guide: BFME1 AudioEventRTSParseSoundsList.cpp at
// 6583b3c1ff21db4a561285717028fdafc780b7db (weighted list and offset getter).
// Subsound flow, layouts, diagnostics and calls are recovered from PC bytes.
// Existing address-derived STL element and reference names are retained;
// their application-level typedef names are not inferred from byte equality.
// The 329-byte boundary includes both cold throws; the compiler terminal INT3
// is alignment, not part of the body. Existing parser1DABB6 remains banked.
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);
#include "ascii_string.h"
#include "Common/INIException.h"
#include <vector>
class INI;
struct SoundWeightOffset { int value; int get() const { return value; } };
class OpaqueRefCounted { public: void Release_Ref(); };
class Rva0036CA00Str {
public:
 OpaqueRefCounted *m_item;
 __declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &);
 ~Rva0036CA00Str() { if(m_item) m_item->Release_Ref(); }
};
class BfmeStringTailRecord156 {
public:
 Rva0036CA00Str ref; int weight;
 BfmeStringTailRecord156(const Rva0036CA00Str &r,int w): ref(r),weight(w) {}
};
struct RvaPair001D9F62 { AsciiString m_key; int m_value; ~RvaPair001D9F62(); };
namespace _STL {
 template<> vector<RvaPair001D9F62>::~vector();
 template<> void vector<BfmeStringTailRecord156>::reserve(unsigned int);
 template<> void vector<BfmeStringTailRecord156>::push_back(const BfmeStringTailRecord156 &);
}
class AudioManager {
public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot0a();
 virtual void slot0b();
 virtual void slot0c();
 virtual void slot0d();
 virtual void slot0e();
 virtual void slot0f();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot1a();
 virtual void slot1b();
 virtual void slot1c();
 virtual void slot1d();
 virtual void slot1e();
 virtual void slot1f();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot2a();
 virtual void slot2b();
 virtual void slot2c();
 virtual void slot2d();
 virtual void slot2e();
 virtual void slot2f();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot3a();
 virtual void slot3b();
 virtual void slot3c();
 virtual void slot3d();
 virtual void slot3e();
 virtual void slot3f();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot4a();
 virtual Rva0036CA00Str rvaSlot12C(const AsciiString &name);
};
extern AudioManager *TheAudio;

class Rva000A8C9B
{
public:
 void clear();
};

class PlayingAudioRef
{
public:
 OpaqueRefCounted *m_item;
 PlayingAudioRef &operator=(const PlayingAudioRef &);
};

// BFME1 INIAudioEventInfo.cpp supplies the name-to-audio lookup flow. Target
// evidence at 0x00339184 adds the NoSound clear, TheAudio slot 0x12C counted
// return, and Invalid Sound diagnostic; the sibling sound-list parser above
// confirms the BFME2 audio-manager and handle view.
void Rva00339184(const char *token, void *store)
{
 if (_strcmpi(token, "NoSound") == 0) {
  ((Rva000A8C9B *)store)->clear();
  return;
 }

 {
  AsciiString name(token);
  {
   Rva0036CA00Str sound = TheAudio->rvaSlot12C(name);
   ((PlayingAudioRef *)store)->operator=(*(const PlayingAudioRef *)&sound);
  }
 }

 if (!((PlayingAudioRef *)store)->m_item)
  throw INIException(3, "Invalid Sound '%s'", token);
}

void Rva001DABB6Parse(INI *,void *,int *,void *);
class AudioEventInfo {
public:
 static void parseSoundsList(INI *,void *,void *,const void *);
 static void parseSubsoundsList(INI *,void *,void *,const void *);
};
void AudioEventInfo::parseSoundsList(
    INI *ini, void *instance, void *store, const void *userData)
{
    int *total = userData ?
        (int *)((char *)instance + ((const SoundWeightOffset *)userData)->get()) : 0;
    Rva001DABB6Parse(ini, store, total, (char *)instance + 8);
}

void AudioEventInfo::parseSubsoundsList(
    INI *ini, void *instance, void *store, const void *userData)
{
    int *total = userData ?
        (int *)((char *)instance + ((const SoundWeightOffset *)userData)->get()) : 0;
    _STL::vector<RvaPair001D9F62> names;
    AsciiString &eventName = *(AsciiString *)((char *)instance + 8);
    Rva001DABB6Parse(ini, &names, total, &eventName);
    _STL::vector<BfmeStringTailRecord156> *sounds =
        (_STL::vector<BfmeStringTailRecord156> *)store;
    sounds->reserve(names.size());

    for (_STL::vector<RvaPair001D9F62>::iterator i = names.begin(), end = names.end();
        i != end; ++i)
    {
        Rva0036CA00Str sound = TheAudio->rvaSlot12C(i->m_key);
        if (!sound.m_item && i->m_key.compareNoCase("NoSound"))
            throw INIException(3, "Unknown subsound '%s' in multisound", i->m_key.str());
        if (sound.m_item == instance)
            throw INIException(3, "Multisound '%s' cannot use itself as a subsound", eventName.str());
        sounds->push_back(BfmeStringTailRecord156(sound, i->m_value));
    }
}
