// ?rva001FCF11@ParticleSystemManager@@QAEXABVAsciiString@@PAVParticleSystemTemplate@FXParticleSystem@@@Z
// partial score=0.88 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?findTemplate@ParticleSystemManager@@QBEPAVParticleSystemTemplate@@ABVAsciiString@@@Z
// retail 0x001F90DA (43B). Zero Hour ParticleSys.cpp:
//   ParticleSystemTemplate *sysTemplate = NULL;
//   TemplateMap::const_iterator find(m_templateMap.find(name));
//   if (find != m_templateMap.end()) sysTemplate = (*find).second;
//   return sysTemplate;
// The template map sits at +0x88 and is the Rva00056F61 bucket table whose
// iterator find (0x0041534B) is rowed; retail tests the iterator's node
// rather than comparing with end(), as the rowed sibling lookups
// (Rva0021311FGet.cpp) do. Evidence: symbols.csv pin (INI::
// parseParticleSystemTemplate's call at 0x003395BB); 8 units call it.
#include "ascii_string.h"
#include <new>

class Rva00056F61;
struct Rva0041534BIter
{
	void *m_node;
	Rva00056F61 *m_table;
};
class Rva00056F61
{
public:
	Rva0041534BIter rva0041534B(const AsciiString *key);
};

class ParticleSystemTemplate;
class BfmeParticleSystemHandle;

class Rva001FCF11TemplatePairKey;
namespace FXParticleSystem {class ParticleSystemTemplate;}
class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
	BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate*,bool);
	void rva001FCF11(const AsciiString&,FXParticleSystem::ParticleSystemTemplate*);

private:
	char m_pad[0x88];
	Rva00056F61 m_templateMap;	// +0x88
};

ParticleSystemTemplate *ParticleSystemManager::findTemplate(const AsciiString &name) const
{
	ParticleSystemTemplate *sysTemplate = 0;
	Rva0041534BIter find = const_cast<Rva00056F61 &>(m_templateMap).rva0041534B(&name);
	if (find.m_node != 0)
		sysTemplate = *(ParticleSystemTemplate **)((char *)find.m_node + 8);
	return sysTemplate;
}

// Native 1F9105..1F933D (568B); WB B17890 names ParticleSystemManager::DoXfer.
// BF1 donor874e38488c7d Rva005C9FC0ParticleManagerXfer.cpp establishes the
// save/load algorithm. Target independently supplies Snapshot +0xC, ID +0x3C,
// list +0x40, count +0x4C and counters +0x50/+0x58, template +0x198 and flags
// +0x1A4/+0x1A6. This address view preserves the secondary-receiver ABI;
// the complete namespace/class relationship is not inferred from byte equality.
// The rowed copy constructor4CC19 cannot throw (pointer copies/attach helper).
// Its throw() contract permits the native overlapping handle stack lifetimes.
class Xfer;
struct Snapshot;
struct ManagerVersion191 { unsigned char minimum,current; __forceinline ManagerVersion191(unsigned char a,unsigned char b):minimum(a),current(b){} };
class ManagerXferView191 {
public:
 virtual void v00();virtual void v04();virtual bool IsStoring()const;virtual void v0C();virtual bool IsLightCRC()const;
 virtual void v14();virtual void v18();virtual void v1C();virtual void v20();virtual void v24();
 virtual void version(ManagerVersion191*);virtual void v2C();virtual void snapshot(Snapshot*);
 virtual void v34();virtual void v38();virtual void v3C();virtual void v40();virtual void v44();virtual void v48();virtual void v4C();virtual void v50();virtual void v54();virtual void v58();virtual void v5C();virtual void v60();virtual void v64();virtual void v68();
 virtual void text(AsciiString*);virtual void v70();virtual void v74();virtual void unsignedValue(unsigned*);virtual void intValue(int*);
};
void XferParticleSystemID(Xfer*,int*);
namespace FXParticleSystem { class ParticleSystemTemplate {public:AsciiString getName()const;ParticleSystemTemplate(const ParticleSystemTemplate&);__forceinline static void *operator new(unsigned size,void *p)throw(){return p;}__forceinline static void operator delete(void *p,void*){::operator delete(p);}char pad[0x9C];AsciiString name;char tail[0x34];}; }
class ParticleSystem {public:char pad[0x198];FXParticleSystem::ParticleSystemTemplate *sysTemplate;char pad19C[8];bool destroyed;char pad1A5;bool saveable;};
ParticleSystem *Make001FCBD7();
class RvaSmartPtr12 {public:RvaSmartPtr12(const RvaSmartPtr12&)throw();void rva0004CBC0()throw();};
class BfmeParticleSystemHandle {
public:
 __forceinline BfmeParticleSystemHandle(const BfmeParticleSystemHandle &that) {((RvaSmartPtr12*)this)->RvaSmartPtr12::RvaSmartPtr12(*(const RvaSmartPtr12*)&that);}
 __forceinline ~BfmeParticleSystemHandle() throw() {if(system)((RvaSmartPtr12*)this)->rva0004CBC0();}
 ParticleSystem *operator->()const {return system?system:Make001FCBD7();}
 ParticleSystem *system;void *prev,*next;
};
struct ManagerNode191 {ManagerNode191 *next,*previous;BfmeParticleSystemHandle handle;};
class ParticleSystemTemplate;
class XferException {public:XferException(int,const char*,...);XferException(const XferException&);~XferException();char *text;int tag;};
class Rva001F9105Snapshot {
public:void rva001F9105(Xfer*);
 char pad[0x3C];int uniqueId;ManagerNode191 *allSystems;char pad44[8];unsigned count;int value50;char pad54[4];int value58;
};
void Rva001F9105Snapshot::rva001F9105(Xfer *xfer)
{
 ManagerXferView191 *out=(ManagerXferView191*)xfer;
 if(out->IsLightCRC())return;
 ManagerVersion191 version(1,2);out->version(&version);
 XferParticleSystemID(xfer,&uniqueId);
 unsigned systemCount=count;out->unsignedValue(&systemCount);
 if(version.current>=2) {out->intValue(&value50);out->intValue(&value58);}
 if(out->IsStoring()) {
  for(ManagerNode191 *it=allSystems->next;it!=allSystems;it=it->next) {
   --systemCount;
   BfmeParticleSystemHandle system=it->handle;
   if(system->destroyed==true || system->saveable==false) {
    AsciiString empty="";out->text(&empty);continue;
   }
   FXParticleSystem::ParticleSystemTemplate *templ=system->sysTemplate;
   AsciiString name=templ->getName();
   out->text(&name);out->snapshot((Snapshot*)system.system);
  }
 } else {
  for(unsigned i=0;i<systemCount;++i) {
   AsciiString name;out->text(&name);
   if(name.isEmpty())continue;
   ParticleSystemManager *manager=(ParticleSystemManager*)((char*)this-0xC);
   ParticleSystemTemplate *sysTemplate=manager->findTemplate(name);
   if(!sysTemplate)throw XferException(5,0);
   BfmeParticleSystemHandle system=manager->createParticleSystem(sysTemplate,false);
   if(!system.system)throw XferException(5,0);
   out->snapshot((Snapshot*)system.system);
  }
 }
}

struct Rva0032ACCFTemplatePairValue {
 AsciiString key;FXParticleSystem::ParticleSystemTemplate *value;
 __forceinline Rva0032ACCFTemplatePairValue(const AsciiString &k,FXParticleSystem::ParticleSystemTemplate *v):key(k),value(v){}
};
__declspec(noinline) Rva0032ACCFTemplatePairValue makeTemplatePair191(const AsciiString &key,FXParticleSystem::ParticleSystemTemplate *const &value) {
 return Rva0032ACCFTemplatePairValue(key,value);
}
class Rva001FCF11TemplatePairKey {
public:
 __declspec(noinline) Rva001FCF11TemplatePairKey(const Rva0032ACCFTemplatePairValue&);
 const AsciiString key;FXParticleSystem::ParticleSystemTemplate *value;
};
Rva001FCF11TemplatePairKey::Rva001FCF11TemplatePairKey(const Rva0032ACCFTemplatePairValue &p):key(p.key),value(p.value){}
#pragma pack(push,1)
struct InsertRet001F8F2A {void *node,*owner;unsigned char found;};
#pragma pack(pop)
class Rva000427195 {public:InsertRet001F8F2A rva001F93A3(const void*);};
struct TemplateDeleteView191 {virtual void *destroy(unsigned flags);};
void ParticleSystemManager::rva001FCF11(const AsciiString &name,FXParticleSystem::ParticleSystemTemplate *system) {
 if(system->name!=name)system->name=name;
 void *node;
 { Rva0041534BIter it=m_templateMap.rva0041534B(&name);node=it.m_node;}
 if(node) {
  ((TemplateDeleteView191*)*(FXParticleSystem::ParticleSystemTemplate**)((char*)node+8))->destroy(0);
  FXParticleSystem::ParticleSystemTemplate *old=*(FXParticleSystem::ParticleSystemTemplate**)((char*)node+8);
  new(old) FXParticleSystem::ParticleSystemTemplate(*system);
  ::operator delete(system?((TemplateDeleteView191*)system)->destroy(0):0);
 } else {
  if(!((Rva000427195*)&m_templateMap)->rva001F93A3(&Rva001FCF11TemplatePairKey(makeTemplatePair191(name,system))).found) {
   ::operator delete(system?((TemplateDeleteView191*)system)->destroy(0):0);
  }
 }
}
