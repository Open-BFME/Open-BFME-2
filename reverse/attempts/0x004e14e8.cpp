// ?Rva004E14E8ParseFlashRegionsEvent@@YAXPAVINI@@PAX1PBX@Z
// partial score=1.0 date=2026-10-04
// cl: /O1 /G7 /MD /EHsc
// BFME1 donor1281192f682ce6f29b8f06b7daea4b5e8fdfbb24:
// game/GameEngine/Source/GameLogic/LivingWorld/ParseFlashRegionsEvent.cpp.
// Target4E14E8/117 uniquely references this parser's exception text.
// Native ctor4E14CD/20 and this initializer agree on the 16-byte record:
// vptr0, delay4, summary flag8, flash time0C. Table VA C619E0 independently
// names DelayFromActStart / FlashTime / SummaryEvent with offsets4/C/8.
// The vtable's single slot is the native deleting dtor4E19E7/29;
// the existing R2Data010EC760 provider holds exactly its VA 008E19E7.
// Keep that established provider and an opaque address-derived record view.
// Original record/owner names are unknown. Native owner append56655F
// adjusts the receiver by84 and tails to the 16-byte-record vector helper.
class INI;
typedef void (__cdecl *ParseFunc)(INI *, void *, void *, const void *);
struct FieldParse { const char *token; ParseFunc parse; const void *data; int offset; };
class INI { public: void initFromINI(void *, const FieldParse *); static void dup_002F0F7(INI *, void *, void *, const void *); static void parseBool(INI *, void *, void *, const void *); };
class INIException { public: char *mFailureMessage; int m_argCount; INIException(int, const char *, ...); INIException(const INIException &); ~INIException(); };
extern int R2Data010EC760;
class __declspec(novtable) Rva004E14E8FlashRecord {
public:
 // ??0Rva004E14E8FlashRecord@@QAE@XZ present-unmatched
 Rva004E14E8FlashRecord() { *(int **)this=&R2Data010EC760; delay=0; summary=false; flashTime=0; }
 // ??1Rva004E14E8FlashRecord@@UAE@XZ present-unmatched
 virtual ~Rva004E14E8FlashRecord() { *(int **)this=&R2Data010EC760; }
private: unsigned delay; bool summary; unsigned flashTime;
};
static const FieldParse flashFields[]={{"DelayFromActStart",INI::dup_002F0F7,0,4},{"FlashTime",INI::dup_002F0F7,0,12},{"SummaryEvent",INI::parseBool,0,8},{0,0,0,0}};
class Rva004E14E8FlashOwner { public: void append(const Rva004E14E8FlashRecord &); };
void Rva004E14E8ParseFlashRegionsEvent(INI *ini, void *instance, void *, const void *)
{
 if(!ini || !instance)
  throw INIException(3,"ParseFlashRegionsEvent::Invalid data passed in.");
 Rva004E14E8FlashRecord record;
 ini->initFromINI(&record,flashFields);
 ((Rva004E14E8FlashOwner *)instance)->append(record);
}
