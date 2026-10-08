// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Retail Xfer vtable BBB910 slot28 is operator==(float&) at554C.
// updateFrame39D1F1 independently reads +F8/+FC as floats.
// Clean BF1 ba7ddda Common/RTS/ScoreKeeperXfer.cpp semantic guide.
// WBFA4540 names ScoreKeeper::DoXfer; native39C7B8..39CADA804 proves target fields,
// version12 compatibility branches and all helper addresses. Member purpose
// labels follow the donor only where the same transfer sequence supports them.
#include <map>
class ThingTemplate;
struct TemplateCountKey { const ThingTemplate *pointer; };
typedef _STL::map<TemplateCountKey,int> ObjectCountMap;
class Rva0039C1C3;
struct FrameStatsVector { void *start,*finish,*end; };
struct XferVersion { unsigned char minimum,current; };
class Xfer
{
public:
 virtual ~Xfer();
 virtual void slot01();
 virtual void slot02();
 virtual bool IsCRC() const;
 virtual bool IsLightCRC() const;
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual Xfer &xferVersion(XferVersion*);
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual Xfer &xferFloat(float*);
 virtual void slot29();
 virtual Xfer &xferUnsignedInt(unsigned int*);
 virtual Xfer &xferInt(int*);
 virtual Xfer &xferUnsignedShort(unsigned short*);
};
class XferException
{
public:
    XferException(int, const char *, ...);
    XferException(const XferException &);
    ~XferException();
    char *text;
    int tag;
};
void xferThingTemplateCountMap(Xfer *,ObjectCountMap*);
Xfer *Rva0039C4F7XferSnapshotVector(Xfer *,Rva0039C1C3*);
class ScoreKeeper
{
public:
 virtual ~ScoreKeeper();
 virtual void LoadPostProcess();
 virtual const char*GetSnapshotName();
 virtual void DoXfer(Xfer *);
private:
 int moneyEarned,moneySpent; //04,08
 int field0C,field10,field14,field18,field1C;
 int unitsDestroyed[20]; //20
 int unitsBuilt,unitsLost; //70,74
 int buildingsDestroyed[20]; //78
 int buildingsBuilt,buildingsLost; //C8,CC
 int heroesVetted,unitsVetted,powerPoints,fieldDC;
 int regionCommandPoints,regionResources,regionPowerPoints,currentScore;
 unsigned int frameOverride,fieldF4;
 float realF8, realFC;
 int field100,field104,field108,field10C;
 char opaque110[0xD4];
 ObjectCountMap map1E4,objectsBuilt,objectsDestroyed[20],objectsLost,objectsCaptured;
 char opaque304[0x18];
 FrameStatsVector stats;
};
void ScoreKeeper::DoXfer(Xfer *xfer)
{
 if(xfer->IsLightCRC())return;
 // The two transferred bytes occupy a four-byte native argument home.
 union VersionStorage {XferVersion version; unsigned int storage;} versionStorage;
 versionStorage.version.minimum=1;
 versionStorage.version.current=12;
 XferVersion &version=versionStorage.version;
 xfer->xferVersion(&version);
 if (version.current < 8)
 {
 xfer->xferInt(&moneyEarned);
 xfer->xferInt(&moneySpent);
 for (int i = 0; i < 20; ++i)
 {
  xfer->xferInt(&unitsDestroyed[i]);
  xfer->xferInt(&buildingsDestroyed[i]);
 }
 xfer->xferInt(&unitsBuilt);
 xfer->xferInt(&unitsLost);
 xfer->xferInt(&buildingsBuilt);
 xfer->xferInt(&buildingsLost);
 }
 else if (version.current < 9)
 {
 xfer->xferInt(&field108);
 xfer->xferInt(&field10C);
 }
 else
 {
 xfer->xferInt(&moneyEarned);
 xfer->xferInt(&moneySpent);
 for (int i = 0; i < 20; ++i)
 {
  xfer->xferInt(&unitsDestroyed[i]);
  xfer->xferInt(&buildingsDestroyed[i]);
 }
 xfer->xferInt(&unitsBuilt);
 xfer->xferInt(&unitsLost);
 xfer->xferInt(&buildingsBuilt);
 xfer->xferInt(&buildingsLost);
 xfer->xferInt(&field108);
 xfer->xferInt(&field10C);
 }
 xfer->xferInt(&fieldDC);
 xfer->xferInt(&currentScore);
 xfer->xferInt(&field100);
 if(version.current>=2){
  int legacyPowerPoints=0;
  xfer->xferInt(&heroesVetted);
 xfer->xferInt(&unitsVetted);
 xfer->xferInt(&legacyPowerPoints);
 xfer->xferInt(&powerPoints);
 }
 if(version.current>=3){xfer->xferInt(&regionCommandPoints);
 xfer->xferInt(&regionResources);
 xfer->xferInt(&regionPowerPoints);}
 if(version.current>=4)xfer->xferUnsignedInt(&frameOverride);
 if(xfer->IsCRC())return;
 xferThingTemplateCountMap(xfer,&objectsBuilt);
 unsigned short destroyedArraySize=20;
 xfer->xferUnsignedShort(&destroyedArraySize);
 if(destroyedArraySize!=20)throw XferException(5,0);
 for(unsigned short i=0;i<destroyedArraySize;++i)xferThingTemplateCountMap(xfer,&objectsDestroyed[i]);
 xferThingTemplateCountMap(xfer,&objectsLost);
 xferThingTemplateCountMap(xfer,&objectsCaptured);
 if(version.current>=5)Rva0039C4F7XferSnapshotVector(xfer,reinterpret_cast<Rva0039C1C3*>(&stats));
 if(version.current>=6)xfer->xferFloat(&realF8);
 if(version.current>=7){xfer->xferUnsignedInt(&fieldF4);
 xfer->xferInt(&field0C);
 xfer->xferInt(&field10);}
 if(version.current>=10)xferThingTemplateCountMap(xfer,&map1E4);
 if(version.current>=11){xfer->xferInt(&field104);
 xfer->xferFloat(&realFC);}
 if(version.current>=12){xfer->xferInt(&field14);
 xfer->xferInt(&field18);
 xfer->xferInt(&field1C);}
}
