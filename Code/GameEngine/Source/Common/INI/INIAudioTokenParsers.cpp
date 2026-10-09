// cl: /O1 /G7 /arch:SSE /EHsc /MD /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception /ICode/GameEngine/Include
//
// Three FieldParse procs that read one token and hand it, with the store, to
// a cdecl audio-event token parser (each parser checks "NoSound"; the 0x339235
// family also takes "EVA:" and "+SOUND:" prefixes, and 0x33939F rejects EVA
// sounds with "This is not a valid place to use the EVA: sound syntax: %s").
// Referenced from 73 / 46 / 35 FieldParse rows. Original names unproven, so
// the procs and helpers keep their address names:
//
// ?Rva003393DFParse@@YAXPAVINI@@PAX1PBX@Z 24B @0x003393DF -> 0x00339235
// ?Rva003393F7Parse@@YAXPAVINI@@PAX1PBX@Z 24B @0x003393F7 -> 0x0033939F
// ?Rva00339900Parse@@YAXPAVINI@@PAX1PBX@Z 24B @0x00339900 -> 0x00339184

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
};

void Rva00339235(const char *token, void *store);
void Rva0033939F(const char *token, void *store);
void Rva00339184(const char *token, void *store);

void Rva003393DFParse(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	Rva00339235(token, store);
}

void Rva003393F7Parse(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	Rva0033939F(token, store);
}

void Rva00339900Parse(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	Rva00339184(token, store);
}

// Native token parsers 0x00339184..0x00339234 and 0x00339235..0x0033939E.
// WorldBuilder e645d0/e647a0 and the FieldParse wrappers 0x339900/0x3393DF
// establish cdecl (token, store), not an INI callback ABI. Names stay opaque.
// BFME1 INIAudioEventInfo's lookup/clear algorithm is the semantic lead;
// BFME1 donor revision 9cbfb551fe20dae985f91f2319d8997287b6a705.
// Target proves NoSound, EVA: and +SOUND: branches, the 8-byte output record,
// audio slot 0x12C, owning-handle assignment 0x239099 and release 0x50ED3.
// Keep the owning return and AsciiString in a full expression: a named return
// local adds a LEA and changes both the frame and temporary cleanup schedule.
// Rva00339184Ref models just the observed owning return; its original name
// and the audio-manager lookup's original name remain unestablished.
#include "ascii_string.h"
#include "Common/INIException.h"
#include "Common/BfmeAudioEventPrefix136.h"
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *,const char *);
struct Rva00339184Ref : OpaqueRefElement4 {
 ~Rva00339184Ref(){if(referent)referent->Release_Ref();}
};
class Rva00339184Audio {
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
 virtual void slot0A();
 virtual void slot0B();
 virtual void slot0C();
 virtual void slot0D();
 virtual void slot0E();
 virtual void slot0F();
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
 virtual void slot1A();
 virtual void slot1B();
 virtual void slot1C();
 virtual void slot1D();
 virtual void slot1E();
 virtual void slot1F();
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
 virtual void slot2A();
 virtual void slot2B();
 virtual void slot2C();
 virtual void slot2D();
 virtual void slot2E();
 virtual void slot2F();
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
 virtual void slot3A();
 virtual void slot3B();
 virtual void slot3C();
 virtual void slot3D();
 virtual void slot3E();
 virtual void slot3F();
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
 virtual void slot4A();
 virtual Rva00339184Ref find(const AsciiString &name);
};
class AudioManager; extern AudioManager *TheAudio;
void Rva00339184(const char *token,void *store)
{
 if(_strcmpi(token,"NoSound")==0) {((Rva000A8C9B*)store)->clear();return;}
 *(OpaqueRefElement4*)store=((Rva00339184Audio*)TheAudio)->find(AsciiString(token));

 if(!((OpaqueRefElement4*)store)->referent) throw INIException(3,"Invalid Sound '%s'",token);
}

extern "C" __declspec(dllimport) int __cdecl _strnicmp(const char *,const char *,unsigned int);
class Eva {public:int rva001DE78E(const AsciiString *name);};extern Eva *TheEva;
struct Rva00339235Value {int eventID;OpaqueRefElement4 sound;};
void Rva00339235(const char *token,void *store)
{
 Rva00339235Value *value=(Rva00339235Value*)store;
 if(_strcmpi(token,"NoSound")==0) {
  ((Rva000A8C9B*)&value->sound)->clear();value->eventID=-1;return;
 }
 if(_strnicmp(token,"EVA:",4)==0) {
  if(!TheEva) throw INIException(8,"Error: Attempting to parse special EVA: sound before EVA system initialized ('%s')",token);
  token+=4;
  {AsciiString name(token);value->eventID=TheEva->rva001DE78E(&name);}
  if(value->eventID==-1) throw INIException(3,"Unknown EVA event in EVA:%s",token);
 } else {
  bool dynamic=false;
  if(_strnicmp(token,"+SOUND:",7)==0) {dynamic=true;token+=7;}
  value->sound=((Rva00339184Audio*)TheAudio)->find(AsciiString(token));

  if(!dynamic)value->eventID=-1;
  if(!value->sound.referent) throw INIException(3,"Invalid Sound '%s'",token);
 }
}
