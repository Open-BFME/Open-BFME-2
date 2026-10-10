// ?load@GameWindowTransitionsHandler@@QAEXXZ
// partial score=0.9911037355 date=2026-10-10
// ?load@GameWindowTransitionsHandler@@QAEXXZ
// Target: full780B 1DC7E1..1DCAED; init2CDB0 and loadFile2DC75.
// Nineteen native strings/functions, map+0C and NameKey singleton independently decoded.
// Native dispatch1DCAED uses a four-argument cdecl field parser. Existing parser
// providers with neutral names keep their ledger signatures; casts store their entrypoints.
// ZH load supplies INI/WindowTransitions.ini purpose; BF2 adds registration.
// INI87C from verified ctor2CDB0; no shortening to hide four-byte frame difference.
// Current O1 body780 differs only frame+4 and four stack-home bytes.
// cl: /Ireference/shims/bfme2_ascii /O1 /MD /GX /DNDEBUG /D_CRTIMP=
#include "ascii_string.h"
class Xfer;
enum INILoadType {INI_LOAD_INVALID, INI_LOAD_OVERWRITE};
class INI {public: INI(); ~INI(); unsigned char loadFile(AsciiString,INILoadType,Xfer*); private: char storage[0x87C];};
enum NameKeyType {NAMEKEY_INVALID=0,NAMEKEY_MAX=1<<23,FORCE_NAMEKEYTYPE_LONG=0x7fffffff};
class NameKeyGenerator {public: NameKeyType nameToKey(const char*);};
extern NameKeyGenerator* TheNameKeyGenerator;
class Object;
class ObjectLookupMap {public: Object** findSlot(int*); Object** slot(const NameKeyType& key) { return findSlot(reinterpret_cast<int*>(const_cast<NameKeyType*>(&key))); } private: char storage[0x14];};
typedef void (__cdecl *Factory)(INI*,void*,void*,const void*);
struct Gen_00489270;
void s5parse0059DE10(INI*, Gen_00489270*);
class Rva00360298Holder;
void Rva00360298Parse(INI*, Rva00360298Holder*);
class Rva003600D6Holder;
void Rva003600D6Parse(INI*, Rva003600D6Holder*);
class Rva003600D6Holder;
void Rva0035FD73Parse(INI*, Rva003600D6Holder*);
struct Gen_00489270;
void s4ParseFieldsRva005A01F0(INI*, Gen_00489270*);
class Rva003600D6Holder;
void Rva0035F6E2Parse(INI*, Rva003600D6Holder*);
class Rva0035F4E7Holder;
void Rva0035F4E7Parse(INI*, Rva0035F4E7Holder*);
struct Gen_00489270;
void s5parse0059D600(INI*, Gen_00489270*);
class Rva0035EEA7Holder;
void Rva0035EEA7Parse(INI*, Rva0035EEA7Holder*);
class Rva0035E650Holder;
void Rva0035E650Parse(INI*, Rva0035E650Holder*);
class Rva0035E327Holder;
void Rva0035E327Parse(INI*, Rva0035E327Holder*);
struct Gen_00489270;
void s4parse0059E860(INI*, Gen_00489270*);
struct Gen_00489270;
void s4parse0059E290(INI*, Gen_00489270*);
class Gen_00489270;
void rva0059EB90(INI*, Gen_00489270*);
class Rva0059B8F0Nugget {public: static void parse(INI*,void*,void*,const void*);};
class Rva0035D6F9Holder;
void Rva0035D6F9Parse(INI*, Rva0035D6F9Holder*);
struct Gen_00489270;
void s4ParseFieldsRva0059EE10(INI*, Gen_00489270*);
struct Gen_00489270;
void s5parse0059FB50(INI*, Gen_00489270*);
struct Gen_00489270;
void s4ParseFieldsRva0059D1F0(INI*, Gen_00489270*);
class GameWindowTransitionsHandler {public: void load(); private: char prefix[0xC]; ObjectLookupMap m_table;};
void GameWindowTransitionsHandler::load() {
    INI ini;
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("IMAGEFADE"))) = reinterpret_cast<Factory>(&s5parse0059DE10);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("IMAGECROSSFADE"))) = reinterpret_cast<Factory>(&Rva00360298Parse);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("SCREENFADE"))) = reinterpret_cast<Factory>(&Rva003600D6Parse);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("TYPETEXT"))) = reinterpret_cast<Factory>(&Rva0035FD73Parse);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("TEXTONFRAME"))) = reinterpret_cast<Factory>(&s4ParseFieldsRva005A01F0);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("COUNTUP"))) = reinterpret_cast<Factory>(&Rva0035F6E2Parse);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("WINFADE"))) = reinterpret_cast<Factory>(&Rva0035F4E7Parse);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("FULLFADE"))) = reinterpret_cast<Factory>(&s5parse0059D600);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("FLASH"))) = reinterpret_cast<Factory>(&Rva0035EEA7Parse);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("BUTTONFLASH"))) = reinterpret_cast<Factory>(&Rva0035E650Parse);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("WINSCALEUP"))) = reinterpret_cast<Factory>(&Rva0035E327Parse);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("MAINMENUSCALEUP"))) = reinterpret_cast<Factory>(&s4parse0059E860);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("MAINMENUMEDIUMSCALEUP"))) = reinterpret_cast<Factory>(&s4parse0059E290);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("MAINMENUSMALLSCALEDOWN"))) = reinterpret_cast<Factory>(&rva0059EB90);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("CONTROLBARARROW"))) = reinterpret_cast<Factory>(&Rva0059B8F0Nugget::parse);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("SCORESCALEUP"))) = reinterpret_cast<Factory>(&Rva0035D6F9Parse);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("REVERSESOUND"))) = reinterpret_cast<Factory>(&s4ParseFieldsRva0059EE10);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("SOUNDFADE"))) = reinterpret_cast<Factory>(&s5parse0059FB50);
    *reinterpret_cast<Factory*>(m_table.slot(TheNameKeyGenerator->nameToKey("FREEZE_POST_LOAD_SOUNDS"))) = reinterpret_cast<Factory>(&s4ParseFieldsRva0059D1F0);
    ini.loadFile(AsciiString("Data\\INI\\WindowTransitions.ini"),INI_LOAD_OVERWRITE,0);
}
