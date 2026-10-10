// cl: /DNDEBUG /MD /EHsc
//
// ??0Made002CCAA1@@QAE@XZ retail 0x0050B374 29B
// Evidence: pin ??0Made002CCAA1; callee base Rva00507823 0x0050775B;
// caller parseOpenGateNugget 0x002CCAC6; prev Made002CCAA1Parse same
// /O1 DNDEBUG MD plus arch:SSE for xorps float zero; vtable 0x00864C94
// plus float at +0x128 zero.
class Module {public: virtual void s00();};
enum NameKeyType {};
class Made002CCAA1;
class Object {friend class Made002CCAA1;protected:Module *findModule(NameKeyType) const;};
class NameKeyGenerator {public:NameKeyType nameToKey(const char*);};
extern NameKeyGenerator *TheNameKeyGenerator;
class OpenGateCallView {public:
virtual void s00()=0;virtual void s04()=0;virtual void s08()=0;virtual void s0C()=0;virtual void s10()=0;virtual void s14()=0;
virtual bool isOpen()=0;virtual void open()=0;virtual void s20()=0;virtual void s24()=0;virtual bool mayOpen()=0;
};
class Rva00507823
{
public:
	Rva00507823();
	virtual void __pad();
virtual bool accepts(void *,Object *)=0;
virtual void s08()=0;virtual void s0C()=0;virtual void s10()=0;
virtual void rva0050B32D(void *,Object *)=0;
virtual void rva0050B391(void *,const struct Coord3D *)=0;
private:
	char m_pad[0x128 - 4];
};

class Made002CCAA1 : public Rva00507823
{
public:
	Made002CCAA1();
 void rva0050B288(void *,Object *);
 virtual void rva0050B32D(void *,Object *);
 virtual void rva0050B391(void *,const struct Coord3D *);
private:
	float m_128;
};

Made002CCAA1::Made002CCAA1()
{
	m_128 = 0.0f;
}

void Made002CCAA1::rva0050B288(void *,Object *target)
{
static NameKeyType gateKey=TheNameKeyGenerator->nameToKey("GateOpenAndCloseBehavior");
Module *module=target->findModule(gateKey);
OpenGateCallView *gate=module ? (OpenGateCallView *)((char *)module-4) : 0;
if(!gate){module=target->findModule(TheNameKeyGenerator->nameToKey("GateProxyBehavior"));gate=module ? (OpenGateCallView *)((char *)module-4):0;}
if(gate && gate->mayOpen() && !gate->isOpen()) gate->open();
}

void Made002CCAA1::rva0050B32D(void *source,Object *target)
{
if(accepts(source,target))rva0050B288(source,target);
if(m_128>0.0f)rva0050B391(source,(const Coord3D *)((char *)target+0x38));
}
#include "../../Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;
void Made002CCAA1::rva0050B391(void *source,const Coord3D *position)
{
float radius=m_128 > 1.0f ? m_128:1.0f;
BfmeWideResult result=ThePartitionManager->rva006255D0(position,radius,3,0);
Object *target;
while((target=result.next())!=0){if(accepts(source,target))rva0050B288(source,target);}
}
