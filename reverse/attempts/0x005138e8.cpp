// ?rva005138E8@Rva005138E8@@QAEHXZ
// partial score=0.95 date=2026-10-09
// cl: /O1 /G6 /MD /EHsc /arch:SSE
// Native005138E8..00513988 (160B) takes no stack arguments. The adjacent
// verified513988 body uses the same AptMyHero subobject at27C and five
// virtual parts at418. Original containing-class identity is unknown.
// Four byte flags430..433 gate existing hero setters; any change rebuilds
// bling. FrameUpdate then precedes slot2 on each of the five parts, with
// the selected410 pointer compared independently for each part.
class Rva005B02B5 {public:void rva005B027F();void rva005B0249();void rva005B02B5();void rva005B02FD();};
class AptMyHero {public:void rva005B1019();void rva005B1EE2();};
class Rva005138E8Part {public:virtual void slot0();virtual void slot1();virtual void slot2(bool);};
class Rva005138E8 {public:int rva005138E8();private:char opaque[0x410];Rva005138E8Part *selected;char pad414[4];Rva005138E8Part *parts[5];char pad42C[4];bool flag430,flag431,flag432,flag433;};
// ?rva005138E8@Rva005138E8@@QAEHXZ present-unmatched
int Rva005138E8::rva005138E8(){
 bool changed=false;
 if(flag431){((Rva005B02B5 *)((char*)this+0x27C))->rva005B027F();changed=true;}
 if(flag430){((Rva005B02B5 *)((char*)this+0x27C))->rva005B0249();changed=true;}
 if(flag432){((Rva005B02B5 *)((char*)this+0x27C))->rva005B02B5();changed=true;}
 if(flag433){((Rva005B02B5 *)((char*)this+0x27C))->rva005B02FD();changed=true;}
 if(changed)((AptMyHero *)((char*)this+0x27C))->rva005B1019();
 ((AptMyHero *)((char*)this+0x27C))->rva005B1EE2();
 Rva005138E8Part **part=parts;
 for(int count=5;count>0;--count){(*part)->slot2(*part==selected);++part;}
 return 1;
}
