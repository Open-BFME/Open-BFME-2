// ?Rva005F32B5@@YA?AURva005F32B5Dimensions@@ABVAsciiString@@I@Z
// partial score=0.99498 date=2026-10-09
// ?Rva005F32B5@@YA?AURva005F32B5Dimensions@@ABVAsciiString@@I@Z
// partial score=0.99498 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /arch:SSE
#include "ascii_string.h"
#include <stdlib.h>
struct TargetRef00217D4C; void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
class Rva00222A8BTarget; extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget*,void*,const char*,const char*);
struct Rva0057ACEBData { bool*flag; AsciiString*value; };
class Rva005D4E22 :public Rva0057ACEBData { public:Rva005D4E22(bool*,AsciiString*); };
class Rva0057ACEB {public:Rva0057ACEB(const Rva0057ACEBData*); Rva0057ACEB(const Rva0057ACEB&d):ptr(d.ptr){if(ptr)((int*)ptr)[1]++;}~Rva0057ACEB(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)ptr);} private:void*ptr;};
class AptExternHandler;
template<class T>class AptRef:public Rva0057ACEB { public:AptRef(Rva0057ACEBData d):Rva0057ACEB(&d){} };
class AptSingleExternHandlerAdder {public:AptSingleExternHandlerAdder(const AsciiString&,int,AptRef<AptExternHandler>);~AptSingleExternHandlerAdder();private:AsciiString name;};
struct Rva005F32B5Dimensions { Rva005F32B5Dimensions(float a,float b):x(a),y(b){} float x,y; };
static Rva005F32B5Dimensions Rva005F32B5(const AsciiString&name,unsigned level)
{
 AsciiString width,height;
 {AsciiString key;
 bool gotWidth,gotHeight;
 key.format("_level%u.%s_UnitIconStageWidth",level,name.str());
 AptSingleExternHandlerAdder widthBinding(key,0,AptRef<AptExternHandler>(Rva005D4E22(&gotWidth,&width)));
 key.format("_level%u.%s_UnitIconStageHeight",level,name.str());
 AptSingleExternHandlerAdder heightBinding(key,0,AptRef<AptExternHandler>(Rva005D4E22(&gotHeight,&height)));
 Rva00524EF4AptCall((Rva00222A8BTarget*)g_bfmeAptWindowManager,(void*)level,name.str(),"GetUnitIconStageDimensions");
 }
 float w=(float)atof(width.str()); return Rva005F32B5Dimensions(w,(float)atof(height.str()));
}
// Synthetic caller witnesses the native local-helper convention; no retail claim.
Rva005F32B5Dimensions s3Use(const AsciiString&n,unsigned l) {return Rva005F32B5(n,l);}
