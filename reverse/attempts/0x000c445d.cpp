// ?rva000C445D@Rva000C445D@@QAEXABVAsciiString@@_N1MM@Z
// partial score=1.0 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB
// stlport
// BF1 clean SubObjectVisibility00775C70 donor rev9cbfb551.
// Target C445D..C4657 independently gives5 args RET20 and two24B record
// vectors5C/68 with dirty flags1BC/1BD. Float slots remain address-qualified.
#include "ascii_string.h"
#include <string.h>
struct BfmeStringRecord000B9534 {
 AsciiString name;
 bool hide;
 float at08;
 float at0c;
 float at10;
 float at14;
};
#include <vector>
namespace _STL {template<>void vector<BfmeStringRecord000B9534,allocator<BfmeStringRecord000B9534> >::push_back(const BfmeStringRecord000B9534&);}
class Rva000C445D {
 char at00[0x5C];
 _STL::vector<BfmeStringRecord000B9534,_STL::allocator<BfmeStringRecord000B9534> > at5c,at68;
 char at74[0x1BC-0x74];
 bool at1bc,at1bd;
public:
 void rva000C445D(const AsciiString& name,bool show,bool fade,float value08,float value10);
};
void Rva000C445D::rva000C445D(const AsciiString& name,bool show,bool fade,float value08,float value10) {
 if(!name.isEmpty()) {
  if(fade) {
   bool found=false;
   for(BfmeStringRecord000B9534* it=at68.begin();it!=at68.end();++it) {
    if(_strcmpi(it->name.str(),name.str())==0) {
     at1bd=true; it->hide=!show; it->at08=value08; it->at10=value10; it->at14=1.0f; found=true;
    }
   }
   if(!found) {
    at1bd=true;
    BfmeStringRecord000B9534 info;
    info.name=name; info.hide=!show; info.at08=value08; info.at10=value10; info.at14=1.0f; info.at0c=show?0.9999f:0.0001f;
    at68.push_back(info);
   }
  } else {
   bool found=false;
   for(BfmeStringRecord000B9534* it=at5c.begin();it!=at5c.end();++it) {
    if(_strcmpi(it->name.str(),name.str())==0) {
     bool wasShown = !it->hide;
     if(wasShown != show) { at1bc=true; it->hide=!show; }
     found=true;
    }
   }
   if(!found) {
    at1bc=true;
    BfmeStringRecord000B9534 info;
    info.name=name; info.hide=!show; info.at08=0; info.at0c=1.0f; info.at10=0; info.at14=0;
    at5c.push_back(info);
   }
  }
 }
}
