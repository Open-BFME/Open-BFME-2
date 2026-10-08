// ?rva006ED390@@YAPAVAptValue@@PAXHH@Z
// partial score=0.8 date=2026-10-09
// cl: /O2 /Os /MD
// Native6ED390..6ED44A: three-word cdecl helper; self, argc, integer play flag.
// Checked current CIH, label-to-frame or one-based integer, jumpToFrame,
// sprite+1C bit25 playing update. Names/layouts below only use target accesses
// and existing matched call views; no claim to full class layouts.
class AptValue;
class BfmeAptValue006DCD20 {
public:BfmeAptValue006DCD20 *rva006DCF60(bool);int rva006E03A0() const;
 int isString() const;BfmeAptValue006DCD20 *checkedString();int toInteger() const;
};
class AptBasePtrStack {public:BfmeAptValue006DCD20 *At(int);};
struct AptActionInterpreter {AptBasePtrStack stack;};
extern AptActionInterpreter g_aptDateInterpreter;
extern BfmeAptValue006DCD20 *g_aptUndefinedAtE18078;
class AptCIH {public:void *rva006CFF40() const;void jumpToFrame(int);};
class BfmeF1034 {public:int bfmeGo1034F(int);};
struct SpritePlayingBits {unsigned rest:25;unsigned playing:1;unsigned tail:6;};
struct SpriteView {char prefix[0xC];void *character;char rest[0x1C-0x10];SpritePlayingBits bits;};
AptValue *rva006ED390(void *self,int argc,int play) {
 if(argc>=1) {
  BfmeAptValue006DCD20 *arg=g_aptDateInterpreter.stack.At(0);
  BfmeAptValue006DCD20 *owner=(BfmeAptValue006DCD20 *)self;
  if(!(unsigned char)owner->rva006DCF60(false)->rva006E03A0()) {
   int frame;
   if((unsigned char)arg->isString()) {
    void *label=(char *)arg->checkedString()+8;
    SpriteView *sprite=(SpriteView *)((AptCIH *)owner->rva006DCF60(false))->rva006CFF40();
    frame=((BfmeF1034 *)((char *)sprite->character+8))->bfmeGo1034F((int)label)+1;
   } else frame=arg->toInteger();
   --frame;
   if(frame>=0) {
    ((AptCIH *)owner->rva006DCF60(false))->jumpToFrame(frame);
    SpriteView *sprite=(SpriteView *)((AptCIH *)owner->rva006DCF60(false))->rva006CFF40();
    SpritePlayingBits *bits=(SpritePlayingBits *)((char *)sprite+0x1C);
    bits->playing=play!=0;
   }
  }
 }
 return (AptValue *)g_aptUndefinedAtE18078;
}
