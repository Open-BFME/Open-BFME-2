// cl: /O1 /G7 /arch:SSE /MD
// Native2BB5DD..2BB686 RET4: version1/3 and shared world state2BB2B7,
// non-CRC24B record-pointer vectorBC, polymorphic vectorsCC/D8, then
// version>=2 counted-list transfer. Names remain address-derived; offsets,
// stream slots and all call ABIs are target evidence. The two opaque helper
// bindings are full in-image boundaries2BB49C321 RET8 and2B8BFE264 RET4.
struct Version {unsigned char minimum,current;Version(unsigned char a,unsigned char b):minimum(a),current(b){}};
class Xfer {public:
virtual void s0();
virtual bool IsLoading() const;
virtual void s2();
virtual bool IsCRC() const;
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void xferVersion(Version*);
virtual void s11();
virtual void xferSnapshot(void*);
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s30();
virtual void xferInt(int*);
virtual void s32();
virtual void s33();
virtual void s34();
virtual void s35();
virtual void xferBool(bool*);
virtual void s37();
};
class LivingWorldLogic{public:void rva002BB2B7(Xfer*);};
class Rva002B22AFArg;
class Rva002B22AF{public:void rva002B22AF(Rva002B22AFArg*);};
struct RecVec{Rva002B22AF**begin,**end,**cap;};
class Rva002BB49C{public:void rva002BB49C(Xfer*,RecVec*);};
class Rva002B8BFE{public:void rva002B8BFE(Xfer*);};
class Rva002BB5DD {public:void rva002BB5DD(Xfer*);char pad[0xBC];RecVec records;char gap[4];RecVec first,second;};
void Rva002BB5DD::rva002BB5DD(Xfer*xfer){
 Version v(1,3);xfer->xferVersion(&v);
 ((LivingWorldLogic*)this)->rva002BB2B7(xfer);
 if(!xfer->IsCRC()){
  int count=records.end-records.begin;xfer->xferInt(&count);
  for(int i=0;i<count;++i)records.begin[i]->rva002B22AF((Rva002B22AFArg*)xfer);
 }
 ((Rva002BB49C*)this)->rva002BB49C(xfer,&first);
 ((Rva002BB49C*)this)->rva002BB49C(xfer,&second);
 if(!xfer->IsCRC() && v.current>=2)((Rva002B8BFE*)this)->rva002B8BFE(xfer);
}
