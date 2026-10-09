// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// Retail005C329B..005C33D2: 311B thiscall RET16. WorldBuilder1558520
// names AptMovieClipFrame::CreateContentMovieClip (AptMovieClipFrame.cpp:43).
// Target accesses prove level+4, name+8 and created+C. The four arguments
// are two AsciiString references plus the level/name output pointers.
// ChecklistViewHeight (0057AE1F) provides the matched lifetime/binding guide:
// stack flag and AsciiString capture through005D4E22, AptRef0057ACEB and
// AptSingleExternHandlerAdder. The CreateContent call and output processing
// are recovered from target bytes; the helper names/ABI are existing rows.
#include "ascii_string.h"
struct Rva0057ACEBData {int m_0,m_4;};
class Rva0057ACEB {public:Rva0057ACEB(const Rva0057ACEBData*);void* impl;};
class Rva005D4E22 {public:Rva005D4E22(bool*,AsciiString*);int m_0,m_4;};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
class AptExternHandler;
template<class T> class AptRef {public:T* ptr;__forceinline AptRef(Rva005D4E22 data){reinterpret_cast<Rva0057ACEB*>(this)->Rva0057ACEB::Rva0057ACEB(reinterpret_cast<const Rva0057ACEBData*>(&data));}AptRef(const AptRef& other):ptr(other.ptr){if(ptr)++reinterpret_cast<int*>(ptr)[1];}~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C*>(ptr));}};
class AptSingleExternHandlerAdder {public:AptSingleExternHandlerAdder(const AsciiString&,int,AptRef<AptExternHandler>);~AptSingleExternHandlerAdder();AsciiString name;};

class Rva00222A8BTarget;extern Rva00222A8BTarget *TheRva00222A8BTarget;
int __cdecl Rva005C3240AptCall(Rva00222A8BTarget*,void*,const char*,const char*,const AsciiString&,const AsciiString&);
namespace AptUtils { int LevelIndexFromTarget(const char*);const char *SkipLevelN(const char*); }
class AptMovieClipFrame { public: virtual ~AptMovieClipFrame();bool CreateContentMovieClip(const AsciiString&,const AsciiString&,int*,AsciiString*);private:int level;AsciiString name;bool created;};
bool AptMovieClipFrame::CreateContentMovieClip(const AsciiString& movie,const AsciiString& args,int*outLevel,AsciiString*outName) {
 if(created)return false;
 bool ready=false;
 AsciiString value;
 {
  AsciiString handlerName;handlerName.format("_level%u.%s_ContentName",level,name.str());
  AptSingleExternHandlerAdder handler(handlerName,0,AptRef<AptExternHandler>(Rva005D4E22(&ready,&value)));
  Rva005C3240AptCall(TheRva00222A8BTarget,reinterpret_cast<void*>(level),name.str(),"CreateContent",movie,args);
 }
 if(ready){created=true;*outLevel=AptUtils::LevelIndexFromTarget(value.str());*outName=AptUtils::SkipLevelN(value.str());return true;}
 return false;
}
