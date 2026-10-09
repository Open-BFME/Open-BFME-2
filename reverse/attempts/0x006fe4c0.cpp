// ??0Rva006ECFC0Owner@@QAE@PAVAptValue@@MHHHHHH0HHHH@Z
// partial score=0.9397323665 date=2026-10-09
// cl: /O2 /DNDEBUG /MD /EHsc
// Native 006FE4C0 constructor. Layout from native, base declarations from
// the byte-verified Rva006D6360/Rva006D6470Owner family. WB1760610 guide.
class BfmeAptValue006DCD20 {virtual void vtableSlot0();unsigned int flags;public:BfmeAptValue006DCD20(int);virtual ~BfmeAptValue006DCD20();};
class AptValue;
class AptNativeHash {int count;void *items;AptValue *proto,*prototype;unsigned int events;public:AptNativeHash(int);~AptNativeHash();};
class Rva006D6360:public BfmeAptValue006DCD20 {AptNativeHash hash;public:Rva006D6360(int type,int size):BfmeAptValue006DCD20(type),hash(size){}virtual ~Rva006D6360();};
class Rva006D6470Owner:public Rva006D6360 {unsigned int bits;public:Rva006D6470Owner(int type,int size):Rva006D6360(type,size){*(unsigned char*)&bits=0;unsigned int t=bits;bits=t&0xFFFFFCFF;}virtual ~Rva006D6470Owner();};
class EAStringC {void *data;public:EAStringC(){clear();}EAStringC&clear();~EAStringC();};
class Rva006EB4B0 {EAStringC font;float size;int color,align;unsigned flags;int indent,left,right;public:Rva006EB4B0(AptValue*,float,int,int,int,int,int,int,AptValue*,int,int,int,int);};
class Rva006ECFC0Owner:public Rva006D6470Owner {Rva006EB4B0 format;public:Rva006ECFC0Owner(AptValue*,float,int,int,int,int,int,int,AptValue*,int,int,int,int);virtual ~Rva006ECFC0Owner();};
Rva006ECFC0Owner::Rva006ECFC0Owner(AptValue *font,float size,int color,int bold,int italic,int underline,int unused6,int unused7,AptValue *align,int left,int right,int indent,int unused12)
:Rva006D6470Owner(0x24,8),format(font,size,color,bold,italic,underline,unused6,unused7,align,left,right,indent,unused12){}
