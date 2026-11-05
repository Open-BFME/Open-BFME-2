// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception /ICode/GameEngine/Include
//
// ?parseObjectDefinition@ThingFactory@@SAXPAVINI@@ABVAsciiString@@11@Z, retail
// 0x002D1C01..0x002D1E54 (595 bytes, cdecl, EH frame): ThingFactory::parseObjectDefinition,
// the INI "Object"/"ObjectReskin"/"ChildObject" block parser (name, reskinFrom, childOf).
// Name: WorldBuilder ThingFactory::parseObjectDefinition (ThingFactory.cpp:626..652, debug
// build 0x00A95EC0); layout and strings checked against the retail body.
//
// Source shape from the WorldBuilder debug body: the reskin branch is an `else if` whose
// found case calls initFromINIMulti itself, with a separate plain `else` that calls it too
// (cl cross-jumps the two tails; one shared call after an if-block puts `mov ecx,esi` after
// `push ebx` at the tail). Both throw sites pass name.str() inline - an errorText() helper
// that reads the payload through integer arithmetic keeps the string pointer live and
// loads into EAX where retail reuses EDI destructively (`mov edi,[edi]`).
#include "ascii_string.h"
#include "unicode_string.h"
#include "Common/INIException.h"
#include "Common/BfmeAudioEventPrefix136.h"
class MultiIniFieldParse { public: MultiIniFieldParse(); const void *entries[16]; unsigned int offsets[16]; int count; };
class Rva0033A8FC { public: static void buildFieldParse(MultiIniFieldParse &); };
#include "../../../Include/Common/INI/INI.h"
class ThingTemplate { public: void copyFrom(const ThingTemplate *); void setCopiedFromDefault(); void validate(); char pad[8]; bool isOverride; };
struct Rva0033E06AArg;
class Rva0033E06A { public: void rva0033E06A(Rva0033E06AArg *); };

#include "../../../Include/Common/ThingFactory.h"
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
void ThingFactory::parseObjectDefinition(INI *ini,const AsciiString &name,const AsciiString &reskinFrom,const AsciiString &childOf)
{
    ThingTemplate *thingTemplate = 0;
    if (TheThingFactory->rva002D06AA(name))
        thingTemplate = (ThingTemplate *)TheThingFactory->findTemplate(name);
    if (!thingTemplate) {
        thingTemplate = TheThingFactory->newTemplate(name);
        if (ini->m_loadType==2) thingTemplate->isOverride = true;
    } else if (ini->m_loadType==5) {
        thingTemplate = TheThingFactory->newTemplate(name);
        ((ParserUI *)TheInGameUI)->message(UnicodeString(L"The ThingTemplate, '%S' was reloaded."),name.str());
        BfmeAudioEventPrefix136 event(*(OpaqueRefElement4 *)(((ParserAudio *)TheAudio)->settings()+0xC8),0);
        ((ParserAudio *)TheAudio)->addEvent(&event);
    } else if (ini->m_loadType==2) {
        thingTemplate = TheThingFactory->newOverride(thingTemplate);
    }
    MultiIniFieldParse fields;
    Rva0033A8FC::buildFieldParse(fields);
    if (!childOf.isEmpty()) {
        ThingTemplate *parent = (ThingTemplate *)TheThingFactory->findTemplate(childOf);
        if (parent) {
            thingTemplate->copyFrom(parent);
            thingTemplate->setCopiedFromDefault();
            INILoadType oldType=ini->m_loadType;
            ini->m_loadType=static_cast<INILoadType>(4);
            ini->initFromINIMulti(thingTemplate,fields);
            ini->m_loadType=oldType;
        } else {
            throw INIException(3,"ChildObject must come after the original Object (%s, %s).",childOf.str(),name.str());
        }
    } else if (!reskinFrom.isEmpty()) {
        ThingTemplate *reskin=(ThingTemplate *)TheThingFactory->findTemplate(reskinFrom);
        if (reskin) {
            thingTemplate->copyFrom(reskin);
            thingTemplate->setCopiedFromDefault();
            ((Rva0033E06A *)thingTemplate)->rva0033E06A((Rva0033E06AArg *)reskin);
            ini->initFromINIMulti(thingTemplate,fields);
        } else {
            throw INIException(3,"ObjectReskin must come after the original Object (%s, %s).",reskinFrom.str(),name.str());
        }
    } else {
        ini->initFromINIMulti(thingTemplate,fields);
    }
    thingTemplate->validate();
}
