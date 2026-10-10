// ?parseObjectDefinition@ThingFactory@@SAXPAVINI@@ABVAsciiString@@11@Z
// partial score=0.9835 date=2026-10-10
// ?parseObjectDefinition@ThingFactory@@SAXPAVINI@@ABVAsciiString@@11@Z
// partial score=0.98352 date=2026-10-09
// ?parseObjectDefinition@ThingFactory@@SAXPAVINI@@ABVAsciiString@@11@Z
// partial score=0.95 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception /ICode/GameEngine/Include
#include "ascii_string.h"
#include "unicode_string.h"
#include "Common/INIException.h"
#include "Common/BfmeAudioEventPrefix136.h"
class MultiIniFieldParse { public: MultiIniFieldParse(); const void *entries[16]; unsigned int offsets[16]; int count; };
class Rva0033A8FC { public: static void buildFieldParse(MultiIniFieldParse &); };
class INI { public: void initFromINIMulti(void *,const MultiIniFieldParse &); char pad[8]; int loadType; };
class ThingTemplate { public: void copyFrom(const ThingTemplate *); void setCopiedFromDefault(); void validate(); char pad[8]; bool isOverride; };
struct Rva0033E06AArg;
class Rva0033E06A { public: void rva0033E06A(Rva0033E06AArg *); };

class ThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &); bool rva002D06AA(const AsciiString &); ThingTemplate *newOverride(ThingTemplate *); static void parseObjectDefinition(INI *,const AsciiString &,const AsciiString &,const AsciiString &); private: ThingTemplate *newTemplate(const AsciiString &); };
extern ThingFactory *TheThingFactory;
class InGameUI; extern InGameUI *TheInGameUI;
class ParserUI { public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void __cdecl message(UnicodeString format,...);
};
class AudioManager; extern AudioManager *TheAudio;
class ParserAudio { public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
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
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual unsigned int addEvent(const BfmeAudioEventPrefix136 *);
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
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
virtual void slot50();
virtual void slot51();
virtual void slot52();
virtual void slot53();
virtual void slot54();
virtual void slot55();
virtual void slot56();
virtual void slot57();
virtual void slot58();
virtual void slot59();
virtual void slot60();
virtual void slot61();
virtual void slot62();
virtual void slot63();
virtual void slot64();
virtual void slot65();
virtual void slot66();
virtual void slot67();
virtual void slot68();
virtual void slot69();
virtual void slot70();
virtual void slot71();
virtual void slot72();
virtual void slot73();
virtual void slot74();
virtual void slot75();
virtual void slot76();
virtual void slot77();
virtual char *settings();
};
// Target strings share the retail Header{refCount,length,capacity} at +0.
// Compute the payload address before selecting the empty-string fallback;
// integer arithmetic preserves the null case without dereferencing it.
static __forceinline const char* errorText(const AsciiString&s){
 const unsigned int buffer=*(const unsigned int*)&s;
 const char* text=(const char*)(buffer+8);
 if(!buffer)text="";
 return text;
}
void ThingFactory::parseObjectDefinition(INI *ini,const AsciiString &name,const AsciiString &reskinFrom,const AsciiString &childOf)
{
    ThingTemplate *tmplate = 0;
    if (TheThingFactory->rva002D06AA(name))
        tmplate = (ThingTemplate *)TheThingFactory->findTemplate(name);
    if (!tmplate) {
        tmplate = TheThingFactory->newTemplate(name);
        if (ini->loadType==2) tmplate->isOverride = true;
    } else if (ini->loadType==5) {
        tmplate = TheThingFactory->newTemplate(name);
        ((ParserUI *)TheInGameUI)->message(UnicodeString(L"The ThingTemplate, '%S' was reloaded."),name.str());
        BfmeAudioEventPrefix136 event(*(OpaqueRefElement4 *)(((ParserAudio *)TheAudio)->settings()+0xC8),0);
        ((ParserAudio *)TheAudio)->addEvent(&event);
    } else if (ini->loadType==2) {
        tmplate = TheThingFactory->newOverride(tmplate);
    }
    MultiIniFieldParse fields;
    Rva0033A8FC::buildFieldParse(fields);
    if (!childOf.isEmpty()) {
        ThingTemplate *parent = (ThingTemplate *)TheThingFactory->findTemplate(childOf);
        if (parent) {
            tmplate->copyFrom(parent);
            tmplate->setCopiedFromDefault();
            int oldType=ini->loadType;
            ini->loadType=4;
            ini->initFromINIMulti(tmplate,fields);
            ini->loadType=oldType;
        } else {
            throw INIException(3,"ChildObject must come after the original Object (%s, %s).",childOf.str(),errorText(name));
        }
    } else {
        if (!reskinFrom.isEmpty()) {
            ThingTemplate *reskin=(ThingTemplate *)TheThingFactory->findTemplate(reskinFrom);
            if (reskin) {
                tmplate->copyFrom(reskin);
                tmplate->setCopiedFromDefault();
                ((Rva0033E06A *)tmplate)->rva0033E06A((Rva0033E06AArg *)reskin);
            } else {
                throw INIException(3,"ObjectReskin must come after the original Object (%s, %s).",reskinFrom.str(),errorText(name));
            }
        }
        ini->initFromINIMulti(tmplate,fields);
    }
    tmplate->validate();
}
