// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Oy-
//
// ?rva001B2599@BFME2Encoding2MotionChannel@@QAEXPAIIIPAM1@Z, retail 0x001b2599, 226 bytes. Banked partial (score 0.9578713968957872) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Native RET20 at1B2678 ends1B267B =226. Existing evaluator family pins
// prove state/from/frame/two-output ABI. Encoding2 stores16 bytes per block
// plus one filter byte (17B), mapping unsigned bytes to -128..127. Native
// multiplier BD7640 is double0.0625; Table DB6C28 has a verified provider in
// BFME2EncodingFilterTableInit.cpp. This is the clean adaptive-delta guide
// adapted from the banked encoding1 scalar fused two-frame decoder.
// Complete near match225B: first46bytes and most outer flow exact; residual
// byte load/index increment and x87-filter scheduling differ. Declaring fi
// outside the loop restores target EDX frame/EDI initial-value allocation.
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
extern float filtertable[256];
class BFME2StreamMotionChannel : public BFME2MotionChannel {
public:
    float Scale;
    float Initial[4];
    unsigned char *Data;
};
class BFME2Encoding2MotionChannel : public BFME2StreamMotionChannel {
public:
    void rva001B2599(unsigned int *state,unsigned int from,unsigned int frame,float *value0,float *value1);
    void rva001B230A(unsigned int *state, unsigned int from, unsigned int frame, Vector3 *value0, Vector3 *value1);
    void rva001B2450(unsigned int *state, unsigned int from, unsigned int frame, Quaternion *value0, Quaternion *value1);
};
struct ScalarValue {float x;};
void BFME2Encoding2MotionChannel::rva001B2599(unsigned int *state,unsigned int from,unsigned int frame,float *value0,float *value1)
{
 ScalarValue last;
 if(from>frame){ from=0; last=*(const ScalarValue*)Initial; }
 else last=*(const ScalarValue*)state;
 unsigned char *packet=Data+(from>>4)*17;
 while(from<=frame+1){
  if(from>=(unsigned)Count){if(value0)*(ScalarValue*)value0=last;*(ScalarValue*)value1=last;return;}
  // Codegen: same-valued PHI on the packet pointer (two reads) closes the native register roles.
  unsigned ix=*(packet?packet:packet);
  unsigned fi=from&0xF; from&=~0xFu;
  float filter=filtertable[ix]*Scale*0.0625;
  
  for(;fi<16;++fi){
   unsigned f=from+fi;
   if(f==frame)*value0=last.x;
   else if(f==frame+1){*value1=last.x;break;}
   int factor=(int)(packet?packet:packet)[fi+1]-128;
   last.x+=(float)factor*filter;
  }
  from+=16;packet+=17;
  if(from>frame)value0=0;
 }
}
