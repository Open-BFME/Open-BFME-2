// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
// Full native BDE85..BDF17 constructor; caller C838F passes AsciiString ref and float.
// Existing149B copy and68B destructor own the same64B record. Float stores
// prove14/18/20/24/28/34/38 types; original class and field meanings remain unknown.
// String and vector headers use canonical existing ABI; EH state0 owns names.
#include "ascii_string.h"
#include <vector>
struct BfmeVectorRecord000BDF17 {
 _STL::vector<AsciiString>names;AsciiString text0,text1;
 float word14,word18;int word1C;float word20,word24,word28;
 bool flag2C,flag2D;int word30;float word34,word38;bool flag3C;
 BfmeVectorRecord000BDF17(const AsciiString&,float);
 BfmeVectorRecord000BDF17(const BfmeVectorRecord000BDF17&);
 ~BfmeVectorRecord000BDF17();
};
BfmeVectorRecord000BDF17::BfmeVectorRecord000BDF17(const AsciiString&text,float value):text0(text),word14(value),word18(-1.0f),word1C(1),word20(5.0f),word24(1.0f),word28(1.0f),flag2C(false),flag2D(false),word30(1),word34(-1.0f),word38(-1.0f),flag3C(false){}
