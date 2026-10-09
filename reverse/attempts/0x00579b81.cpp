// ?OnStatRollOver@StatsDisplayImpl@StrategicHUD@@QAEXPBD@Z
// partial score=0.97 date=2026-10-09
// ?OnStatRollOver@StatsDisplayImpl@StrategicHUD@@QAEXPBD@Z
// cl: /O1 /G7 /arch:SSE /MD /EHa
// Native579B81..579C00; hovered stat+20, hint+1C, tooltip+18.
// StatsDisplay identity from callback registration579E82 and vtableC6ED64.
// Existing getter579770 yields a real counted reference; the qualified slot1
// calls the existing pointer-argument virtual-forwarder twin at1FF3A9.
// /EHa packs the parsed integer and returned temporary into dead param8.
// Full127B except six-byte MOV ECX/state-1 scheduling at+47; EH data EXACT.
struct TargetRef00217D4C {virtual void *destroy(unsigned);int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
struct TreeHintRef00217D4C {
 TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C&);
 ~TreeHintRef00217D4C(){if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);}
 TargetRef00217D4C *m_ptr;
};
class Rva00579731 {public:TreeHintRef00217D4C rva00579770(int);};
extern unsigned g_Va00E0631C;
class Rva003FE20FBase {public:virtual void slot0(void*);virtual void slot1(void*);};
bool __cdecl Rva00579676Parse(const char*,int*);
namespace StrategicHUD {class StatsDisplayImpl {
public:virtual ~StatsDisplayImpl();void OnStatRollOver(const char*);
private:char prefix[0x14];Rva003FE20FBase *tooltip;TreeHintRef00217D4C hint;int current;
};}
void StrategicHUD::StatsDisplayImpl::OnStatRollOver(const char *param){
 int stat;{int parsed;if(!Rva00579676Parse(param,&parsed))return;stat=parsed;}
 if(stat!=current){hint=((Rva00579731*)&g_Va00E0631C)->rva00579770(stat);current=stat;
  if(tooltip!=0&&hint.m_ptr!=0)tooltip->Rva003FE20FBase::slot1(&hint);
 }
}
