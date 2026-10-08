// cl: /O2 /G6 /arch:SSE /DNDEBUG /MD /EHsc
// AptCharacter.cpp: the two flag-setting forwarders to the three-argument Apt
// helper (aptHelper008AE3A0, now defined below), which retail links from this TU (tu_map approved, by
// address contiguity inside the AptCharacter span), folded from two split
// units with these exact flags.
class AptValue;
AptValue *aptHelper008AE3A0(void *entry, int count, int flag);

// Retail 0x006ED450 (21B, named 008AE450 by its split unit): invoke the helper with its flag clear.
AptValue *aptHelperClearFlag008AE450(void *entry, int count)
{
    return aptHelper008AE3A0(entry, count, 0);
}

// Retail 0x006ED470 (21B, named 008AE470 by its split unit): invoke the helper with its flag set.
AptValue *aptHelperSetFlag008AE470(void *entry, int count)
{
    return aptHelper008AE3A0(entry, count, 1);
}

class BfmeAptValue006DCD20 {
public:
 BfmeAptValue006DCD20 *rva006DCF60(bool undefOK);
 int rva006E03A0() const;
 int isString() const;
 BfmeAptValue006DCD20 *checkedString();
 int toInteger() const;
};
class AptBasePtrStack { public: BfmeAptValue006DCD20 *At(int); private: char bytes[12]; };
struct AptActionInterpreter { AptBasePtrStack stack; };
extern AptActionInterpreter g_aptDateInterpreter;
extern BfmeAptValue006DCD20 *g_aptUndefinedAtE18078;
class AptCIH { public: void *rva006CFF40() const; void jumpToFrame(int); };
class BfmeF1034 { public: int bfmeGo1034F(int stringAddress); private: char prefix[8]; void *table; };
struct FrameCharacter { char pad0[8]; BfmeF1034 labels; };
struct FrameFlags { unsigned otherLow:25; unsigned play:1; unsigned otherHigh:6; };
struct FrameSprite {
 char pad0[0xC]; FrameCharacter *character; char pad10[0x1C-0x10];
 FrameFlags flags;
};
// ?aptHelper008AE3A0@@YAPAVAptValue@@PAXHH@Z native006ED390..006ED44A186B.
// Adjacent clear/set forwards
// prove its three words. Low-byte predicate use, CIH sprite+1C bit25, and
// character+C labels+8 come from this target and existing getter bodies.
AptValue *aptHelper008AE3A0(void *entry, int count, int flag)
{
 if (count < 1) return (AptValue *)g_aptUndefinedAtE18078;
 BfmeAptValue006DCD20 *frame = g_aptDateInterpreter.stack.At(0);
 BfmeAptValue006DCD20 *value = (BfmeAptValue006DCD20 *)entry;
 if ((unsigned char)value->rva006DCF60(false)->rva006E03A0()) return (AptValue *)g_aptUndefinedAtE18078;
 int frameIndex;
 if ((unsigned char)frame->isString()) {
  frameIndex = ((FrameSprite *)((AptCIH *)value->rva006DCF60(false))->rva006CFF40())->character->labels.bfmeGo1034F((int)((char *)frame->checkedString() + 8)) + 1;
 } else {
  frameIndex = frame->toInteger();
 }
 --frameIndex;
 if (frameIndex < 0) return (AptValue *)g_aptUndefinedAtE18078;
 ((AptCIH *)value->rva006DCF60(false))->jumpToFrame(frameIndex);
 FrameSprite *sprite = (FrameSprite *)((AptCIH *)value->rva006DCF60(false))->rva006CFF40();
 FrameFlags *flags = &sprite->flags;
 flags->play = (flag != 0);
 return (AptValue *)g_aptUndefinedAtE18078;
}

// Evidence: existing BFME2 getters prove CIH and string views, labels lookup
// at70F010 treats its established int as EAStringC* and reads table+8.
// The two21B wrappers prove entry/count/flag ABI. Slot string is passed
// before sprite getter evaluation; early returns share the native footer.
// Explicit flags-word subobject view gives target XOR-mask bit25 write.
// Playing is a frame-control inference; concrete callback name is unproven.
// No new global definition or alias pin; DateSetters defines the interpreter
// as struct AptActionInterpreter and only its first12B stack is viewed here.
