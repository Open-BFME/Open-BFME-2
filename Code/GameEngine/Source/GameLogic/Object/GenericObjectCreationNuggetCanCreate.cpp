// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /arch:SSE /G7 /Op /D_CRTIMP=
// Native1F1010..1F12DF,719B RET8. WB B04A00 names canCreate in
// ObjectCreationList.cpp:1083; native OCL walker1F0434 dispatches slot5.
// ZH ObjectCreationList.cpp guides the creation rules; retail establishes
// the BFME2 offsets, helper calls and ABI. Const qualifications and private
// scalar labels are structural inferences, not independently exported names.
// A direct ModuleInfo string temporary gives the native key/result homes.
// Load primary angle before spin to retain the target's rounded SSE ordering.
// The comparison below reads strings and calls only C strlen/_memicmp;
// its native91B implementation has no throwing C++ path. Preserve its
// no-throw contract locally without changing the shared string header.
// The equal-arm expressions preserve target scheduling/register allocation.
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
class Player;
class Object { public: Player *getControllingPlayer() const; char pad00[0x44]; float angle44; };

class ModuleData;
#include "../../../Include/GameClient/Rva00396A5C.h"
class ObjectCreationNugget;
#include "../../../Include/GameLogic/ObjectCreationListClass.h"
struct OCLArray { ObjectCreationList **begin,**end,**cap; };
class SlowDeathData { public: char pad00[0x88]; OCLArray ocls[4]; };
struct ModuleNugget { char name[4],tag[4]; const ModuleData *data; int mask,tail; };
class ModuleInfo {
public:
    AsciiString getNthName(int) const;
    int count() const { return ((const char*)end-(const char*)begin)/20; }
    __forceinline const ModuleData *nthData(int i) const { if(i<0 || (unsigned)i >= (unsigned)count()) return 0; return begin[i].data; }
    ModuleNugget *begin,*end,*cap;
};
class ThingTemplate {
public:
    const ModuleData *rva0033B3D7() const;
    char pad00[0x108]; unsigned int kind108[8]; char pad128[0x2e4-0x128]; ModuleInfo info;
};
#include "../../../Include/Common/ThingFactory.h"
extern ThingFactory *TheThingFactory;
class BuildListInfo {
    friend class GenericObjectCreationNugget;
public:
    BuildListInfo();
    AsciiString getTemplateName() const;
protected: virtual ~BuildListInfo();
private: char data[0x80-4];
};
#include "../../../Include/Common/SidesList.h"
extern SidesList *TheSidesList;
enum LegalBuildCode { LBC_OK=0 };
#include "../../../Include/Common/BuildAssistantClass.h"
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
template<> __declspec(nothrow) int StringBase<char>::compareNoCase(const char *str)const;
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
            const ThingTemplate *part=TheThingFactory->findTemplate(entry.getTemplateName());
            if(part==0) continue;
            if(disposition40 & 0x2000) angle=spin48;
            if(disposition40 & 0x8000) { angle=primary->angle44; angle+=spin48; angle=normalizeAngle(angle); }
            if((what ? (TheBuildAssistant->isLocationLegalToBuild(pos,part,angle,0x19d,primary,0)) : (TheBuildAssistant->isLocationLegalToBuild(pos,part,angle,0x19d,primary,0))) != LBC_OK) return false;
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
            { slow=info->getNthName(i).compareNoCase("SlowDeathBehavior")==0; }
            if(slow) {
                const SlowDeathData *data=(const SlowDeathData*)info->nthData(i);
                for(int j=0;j<4;++j) {
                    for(ObjectCreationList **list=data->ocls[j].begin;list!=data->ocls[j].end;++list) {
                        if(!((what ? *list : *list))->rva001F0434(primary,(void*)pos)) return false;
                    }
                }
            }
        }
    }
    return true;
}
