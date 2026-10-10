// ?canCreate@GenericObjectCreationNugget@@UAE_NPAVObject@@PBUCoord3D@@@Z
// partial score=0.936760408824693 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /arch:SSE /G7 /Op /D_CRTIMP=
// Native1F1010..1F12DF,719B RET8; WB B04A00 explicitly names canCreate
// in ObjectCreationList.cpp:1083. The retail OCL walker1F0434 dispatches slot5
// with the same two pointer inputs. Object and Coord3D roles are structural
// evidence from controlling-player/angle access and the three position loads;
// their source-level const qualification is not asserted as an export fact.
// All direct helpers now resolve, including177B396A5C recovered this pass.
// BuildListInfo's128B ctor/dtor and folded template-name getter are existing
// providers; ModuleInfo's20B records and BFMERetailAsciiString four-byte return
// follow its64B name getter. BFMERetailAsciiString is deliberately opaque here;
// the existing destructor pin is the complete StringBase release worker.
// The two early guards must remain separate to recover late register saves.
// /Op reproduces the native rounded SSE local stores before normalizeAngle.
// Current trial emits731B against719B; native key/temp homes(-1C/-18) are
// swapped, the rounded addition's two loads choose different source registers,
// and the nested OCL walk interchanges EBX/EDI. This is a bank, not recovery.
// Missing methods slot00..slot04 reserve the proven slot5 position only.
// Other scalar names/flags retained from the ctor view or are neutral offsets.
#include "ascii_string.h"
struct Coord3D { float x,y,z; };
class Player;
class Object { public: Player *getControllingPlayer() const; char pad00[0x44]; float angle44; };
class BFMERetailAsciiString { public: ~BFMERetailAsciiString(); private: char m_data[4]; };
class ModuleData;
class Rva00396A5C { public: int rva00396A5C(Player *); };
class ObjectCreationList { public: bool rva001F0434(void*,void*); };
struct OCLArray { ObjectCreationList **begin,**end,**cap; };
class SlowDeathData { public: char pad00[0x88]; OCLArray ocls[4]; };
struct ModuleNugget { char name[4],tag[4]; const ModuleData *data; int mask,tail; };
class ModuleInfo {
public:
    BFMERetailAsciiString getNthName(int) const;
    int count() const { return ((const char*)end-(const char*)begin)/20; }
    __forceinline const ModuleData *nthData(int i) const { if(i<0 || (unsigned)i >= (unsigned)count()) return 0; return begin[i].data; }
    ModuleNugget *begin,*end,*cap;
};
class ThingTemplate {
public:
    const ModuleData *rva0033B3D7() const;
    char pad00[0x108]; unsigned int kind108[8]; char pad128[0x2e4-0x128]; ModuleInfo info;
};
class ThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &); };
extern ThingFactory *TheThingFactory;
class BuildListInfo {
    friend class GenericObjectCreationNugget;
public:
    BuildListInfo();
    AsciiString rva000AF1DD() const;
protected: virtual ~BuildListInfo();
private: char data[0x80-4];
};
class SidesList { public: bool rva0032BD25(int,int,BuildListInfo*); };
extern SidesList *TheSidesList;
enum LegalBuildCode { LBC_OK=0 };
class BuildAssistant {
public:
    virtual void slot00();virtual void slot01();virtual void slot02();virtual void slot03();
    virtual void slot04();virtual void slot05();virtual void slot06();virtual void slot07();
    virtual void slot08();virtual void slot09();virtual void slot10();virtual void slot11();
    virtual void slot12();virtual void slot13();virtual void slot14();virtual void slot15();
    virtual LegalBuildCode isLocationLegalToBuild(const Coord3D*,const ThingTemplate*,float,unsigned int,Object*,Player*);
};
extern BuildAssistant *TheBuildAssistant;
float __cdecl normalizeAngle(float);
struct NameArray { AsciiString *begin,*end,*cap; unsigned int size() const { return end-begin; } };
class GenericObjectCreationNugget {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04();
    virtual bool canCreate(Object *primary, const Coord3D *pos);
private:
    NameArray names;
    char pad10[0x28-0x10]; int count28;
    char pad2c[8]; Coord3D offset34;
    unsigned int disposition40; float intensity44,spin48;
    char pad4c[0xab-0x4c]; bool flagAB;
};
bool GenericObjectCreationNugget::canCreate(Object *primary, const Coord3D *pos)
{
    if(count28 != 1) return true;
    if(flagAB) return true;
    if(names.size()==0) return false;
    const ThingTemplate *what=TheThingFactory->findTemplate(names.begin[0]);
    if(what==0) return false;
    if(what->kind108[3] & (1<<8)) {
        const ModuleData *castle=what->rva0033B3D7();
        float angle;
        int index=0;
        BuildListInfo entry;
        angle=0.0f;
        int key=((Rva00396A5C*)castle)->rva00396A5C(primary->getControllingPlayer());
        while(TheSidesList->rva0032BD25(key,index++,&entry)) {
            const ThingTemplate *part=TheThingFactory->findTemplate(entry.rva000AF1DD());
            if(part==0) continue;
            if(disposition40 & 0x2000) angle=spin48;
            if(disposition40 & 0x8000) { angle=spin48; angle+=primary->angle44; angle=normalizeAngle(angle); }
            if(TheBuildAssistant->isLocationLegalToBuild(pos,part,angle,0x19d,primary,0) != LBC_OK) return false;
        }
    } else if((what->kind108[0] & 0x80) && !(what->kind108[0] & 0x400)) {
        Coord3D offset;
        offset.x=offset34.x+pos->x;
        offset.y=offset34.y+pos->y;
        offset.z=offset34.z+pos->z;
        if(TheBuildAssistant->isLocationLegalToBuild(&offset,what,0.0f,0x225,primary,primary->getControllingPlayer()) != LBC_OK) return false;
    } else {
        ModuleInfo *info=(ModuleInfo*)&what->info;
        int n=info->count();
        for(int i=0;i<n;++i) {
            bool slow;
            { BFMERetailAsciiString name=info->getNthName(i); slow=((const AsciiString*)&name)->compareNoCase("SlowDeathBehavior")==0; }
            if(slow) {
                const SlowDeathData *data=(const SlowDeathData*)info->nthData(i);
                for(int j=0;j<4;++j) {
                    for(ObjectCreationList **list=data->ocls[j].begin;list!=data->ocls[j].end;++list) {
                        if(!(*list)->rva001F0434(primary,(void*)pos)) return false;
                    }
                }
            }
        }
    }
    return true;
}
