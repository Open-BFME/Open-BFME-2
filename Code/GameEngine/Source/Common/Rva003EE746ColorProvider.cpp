// ?color@Rva003EE746ColorProvider@@UAE?AURva003EE746Color@@PBURva003EE746Region@@@Z
// Retail 0x003EE746..0x003EE7C2, C363C0 colour-provider virtual slot.
// Target evidence: selector +4, region IDs +13C/+140, campaign RGB +20, player RGB +184.
// Structural names preserve the unknown original types; WB1036BD0 is a semantic lead.
// Explicit subobject address preserves the native MOV EAX / LEA ESI schedule.
// cl: /O1 /MD /EHsc /arch:SSE
struct Rva003EE746Color {Rva003EE746Color(float r,float g,float b):red(r),green(g),blue(b){} float red,green,blue;};
struct Rva003EE746Region {char pad[0x13c];int id0,id1;};
struct S3Campaign {char pad[0x20];Rva003EE746Color color;};
class Rva00DFE1C8Host {public:char pad[0x268];S3Campaign*campaign;};
class LivingWorldManager; extern LivingWorldManager *TheLivingWorldManager;
class Rva002E2903Player {public:char pad[0x184];Rva003EE746Color color;};
class Rva002BA8F1Logic {public:Rva002E2903Player*find(int,unsigned*);};
struct Rva0059E647World;
class LivingWorldLogic; extern LivingWorldLogic*TheLivingWorldLogic;
class S3ColorProviderBase {public:virtual ~S3ColorProviderBase(){};virtual Rva003EE746Color color(const Rva003EE746Region*)=0;};
class Rva003EE746ColorProvider:public S3ColorProviderBase {public:virtual Rva003EE746Color color(const Rva003EE746Region*);int*selector;};
Rva003EE746Color Rva003EE746ColorProvider::color(const Rva003EE746Region*r) {
 int id;
 switch(*selector){case 0:id=r->id0;break;case 1:id=r->id1;break;default:id=-1;break;}
 if(id==-1){S3Campaign*c=((Rva00DFE1C8Host*)TheLivingWorldManager)->campaign;return *(const Rva003EE746Color*)((char*)c+0x20);}
 Rva002E2903Player*p=((Rva002BA8F1Logic*)TheLivingWorldLogic)->find(id,0);
 if(p)return p->color;
 return Rva003EE746Color(1.0f,1.0f,1.0f);
}
