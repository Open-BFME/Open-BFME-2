// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Oy-
//
// ?rva001B2210@BFME2Encoding1MotionChannel@@QAEXPAIIIPAM1@Z, retail 0x001b2210, 250 bytes. Banked partial (score 0.992) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// BFME 2 stream motion channel encoding 1: nibble adaptive-delta decoders, called from the
// slot 3/4/5 evaluators (BFME2StreamMotionChannelEvaluate.cpp). The decoder continues from a
// cached state (first value record, frame) to `frame` and writes the values at `frame` and
// `frame + 1`; blocks are 16 frames, each component packet is a filter byte plus 16 signed
// nibbles (9 bytes). Structure is BFME 1 motchan.cpp AdaptiveDeltaMotionChannelClass::decompress
// (donor, 9cbfb551) fused for two outputs; packet size, component count and layout are read
// from retail 0x001B230A. Layout: Data at +0x28, scale at +0x14, initial values at +0x18,
// frame count at +0xC.
// Codegen: `bit` kept as an int and used for both the select and the pointer step; the vi
// loop advances packet in its increment expression.
class ChunkLoadClass;
class Vector3 { public: float X, Y, Z; };
class Quaternion { public: float X, Y, Z, W; };
class BFME2MotionChannel {
public:
    virtual bool Load(ChunkLoadClass &);
    virtual ~BFME2MotionChannel();
    virtual int UnknownSlot2();
    virtual void UnknownSlot3();
    virtual void UnknownSlot4();
    virtual void UnknownSlot5();
    virtual int UnknownSlot6();
    int Type, Pivot, Count, Components;
};
// Native stream decoders230A/2450 use the separate table at VA DB6C28.
// Legacy AdaptiveDelta decompression18F910 uses DB67D8, whose constructor
// initializes that table. Both image tables have the same16 power-of-ten seeds,
// but they are distinct storage instances; one external global conflates them.
// This descriptive namespace records the stream table's identity and scope;
// its original spelling and initializer owner remain unknown.
// The decode filter table is the data-ledger global ?filtertable@@3PAMA (0x009B6C28,
// BFME2EncodingFilterTableInit.cpp).
extern float filtertable[];
class BFME2StreamMotionChannel : public BFME2MotionChannel {
public:
    float Scale;
    float Initial[4];
    unsigned char *Data;
};
class BFME2Encoding1MotionChannel : public BFME2StreamMotionChannel {
public:
    void rva001B2210(unsigned int *state,unsigned int from,unsigned int frame,float *value0,float *value1);
    void rva001B230A(unsigned int *state, unsigned int from, unsigned int frame, Vector3 *value0, Vector3 *value1);
    void rva001B2450(unsigned int *state, unsigned int from, unsigned int frame, Quaternion *value0, Quaternion *value1);
};
struct ScalarValue {float x;};
void BFME2Encoding1MotionChannel::rva001B2210(unsigned int *state,unsigned int from,unsigned int frame,float *value0,float *value1)
{
 ScalarValue last;
 if(from>frame){ from=0; last=*(const ScalarValue*)Initial; }
 else last=*(const ScalarValue*)state;
 unsigned char *packet=Data+(from>>4)*9;
 while(from<=frame+1){
  if(from>=(unsigned)Count){if(value0)*(ScalarValue*)value0=last;*(ScalarValue*)value1=last;return;}
  unsigned fi0=from&0xF; from&=~0xFu;
  float filter=filtertable[*packet]*Scale;
  unsigned char *p=packet+1+(fi0>>1);
  for(unsigned fi=fi0;fi<16;++fi){
   unsigned f=fi + from;
   if(f==frame)*value0=last.x;
   else if(f==frame+1){*value1=last.x;break;}
   int bit=fi&1;
   int factor=bit?(signed char)*p>>4:(signed char)(*p<<4)>>4;
   p = p + (bit);
   last.x+=(float)factor*filter;
  }
  from+=16;packet+=9;
  if(from>frame)value0=0;
 }
}
