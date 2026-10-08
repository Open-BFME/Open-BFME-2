// ?rva0028CE7B@Object@@QBECXZ
// partial score=0.9285714285714286 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// BFME1 Object.cpp crush-level donor9cbfb551 with native BFME2 attribute extension.
class AttributeModifierPoolUpdate { public: bool rva00403382(int,float *,int); };
enum KindOfType { KINDOF_VIEW_UNKNOWN = 0 };
struct ObjectCrushLevelsView {
 char unknown00[0x5f9];
 char crusher,crushable,alternateCrusher,alternateCrushable;
 char unknown5fd;
 bool gate5fe;
};
class Object {
 char unknown00[4]; const ObjectCrushLevelsView *m_template;
 char unknown08[0x124-8]; unsigned int mountedFlags;
public:
 char rva00294815();
 signed char rva0028CE7B() const;
 bool rva00293926(KindOfType);
private:
 __forceinline const ObjectCrushLevelsView *getTemplate() const { return m_template; }
 AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
};
signed char Object::rva0028CE7B() const {
 const ObjectCrushLevelsView *tpl=getTemplate();
 signed char bonusInt=0;
 AttributeModifierPoolUpdate *pool=findAttributeModifierPoolUpdate();
 if(pool) {
  float bonus;
  if(pool->rva00403382(0x19,&bonus,0)) bonusInt=(signed char)bonus;
 }
 signed char base=tpl->alternateCrushable;
 if(base==-1 || (((unsigned char)(mountedFlags>>22)&1)==0)) base=tpl->crushable;
 return base+bonusInt;
}
