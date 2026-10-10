// cl: /O2 /G6 /MD /EHsc
// Stage-property lookup recovered as clean C++. Native6E9800..6E9A39 includes
// the six-target table and101-entry case map. Original member spelling is unknown.
// Recovered Math/LoadVars siblings supply dispatch purpose and declarations;
// every case, assertion, callback ABI and literal below is independently retail.
class EAStringC {void *data;public:const char *rva00620090()const;unsigned int rva006D3750()const;bool rva006D3510(const char *)const;};
class AptValue;
struct BfmeW1228 {const char *name;int value;};
const BfmeW1228 *bfmeFind1228(const char *,unsigned int);
AptValue *__cdecl Rva008A4EA0MakeFloat(float);
void Rva006CC110Log(int,const char *,...);
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
extern AptValue *gpUndefinedValue;
extern void *g_aptGetStageHeightSlot;
extern void *g_aptGetStageWidthSlot;
void __debugbreak();
#pragma intrinsic(__debugbreak)
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva006E9800 {public:AptValue *call(AptValue *const,const EAStringC *const)const;};
AptValue *Rva006E9800::call(AptValue *const context,const EAStringC *const name)const
{
 const BfmeW1228 *prop=context?bfmeFind1228(name->rva00620090(),name->rva006D3750()):0;
 if(prop) {
  switch(prop->value) {
  case 1:case 4:return gpUndefinedValue;
  case 2:
   if(!g_aptGetStageHeightSlot) {
    g_bfmeAptAssertAtE17734("gAptFuncs.pfnGetStageHeight","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptMiscObjects.cpp",1397);
    if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
   }
   return Rva008A4EA0MakeFloat(reinterpret_cast<float(__cdecl *)()>(g_aptGetStageHeightSlot)());
  case 3:
   if(!g_aptGetStageWidthSlot) {
    g_bfmeAptAssertAtE17734("gAptFuncs.pfnGetStageWidth","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptMiscObjects.cpp",1402);
    if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
   }
   return Rva008A4EA0MakeFloat(reinterpret_cast<float(__cdecl *)()>(g_aptGetStageWidthSlot)());
  case 100:
   g_bfmeAptAssertAtE17734("false && \"addListener is not supported yet\"","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptMiscObjects.cpp",1411);
   if(g_bfmeAptBreakOnAssertAtDDC01C) {__debugbreak();_ReadWriteBarrier();}
   break;
  case 101:
   g_bfmeAptAssertAtE17734("false && \"removeListener is not support yet\"","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptMiscObjects.cpp",1416);
   if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
   break;
  }
 }
 if(name->rva006D3510("align")||name->rva006D3510("height")||name->rva006D3510("width")||name->rva006D3510("scaleMode")||name->rva006D3510("addListener")||name->rva006D3510("removeListener")) {
  Rva006CC110Log(3,"AptMathObj: Incorrect case for '%s'.\n",name->rva00620090());
  g_bfmeAptAssertAtE17734("0","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptMiscObjects.cpp",1433);
  if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 }
 return 0;
}
