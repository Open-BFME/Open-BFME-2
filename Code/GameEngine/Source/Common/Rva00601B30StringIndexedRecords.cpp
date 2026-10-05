// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native601B30/140B ret12 interns a text in the string vector atC, then
// appends a12B record to the vector at0. Word0/word4 copy the first two
// argument bit patterns; word8 is the found or newly appended string index.
// Native record pushback601A3A and its nowrowed189B overflow60197D prove
// the record stride. Original owner and argument meanings remain unknown.
// The INI helper's two-vector member is a source lead only; its folded
// constructor00524415 does not prove the older E16 payload labels.
// Real STLport4.5.3 find remains visible so cl legally reuses the dead text
// parameter slot for the temporary AsciiString, matching native EH layout.
// The local text comparison overload keeps the complete171B __find and27B
// find wrapper identical to the existing verified providers; declaring find
// out of line changes the caller's stack allocation by4 bytes.
#include <vector>
#include <algorithm>
#include "ascii_string.h"
// ?operator== present-unmatched
inline bool operator==(const AsciiString& a,const char* b){return reinterpret_cast<const StringBase<char>*>(&a)->compare(b)==0;}
struct Rva00601A3AElement {unsigned int word0,word4;int stringIndex;};
namespace _STL {
template<> void vector<Rva00601A3AElement>::push_back(const Rva00601A3AElement&);
template<> void vector<AsciiString>::push_back(const AsciiString&);

}
class Rva00601B30 {
 _STL::vector<Rva00601A3AElement> records;
 _STL::vector<AsciiString> names;
public: void add(unsigned int word0,unsigned int word4,const char* name);
};
void Rva00601B30::add(unsigned int word0,unsigned int word4,const char* name) {
 AsciiString* found=_STL::find(names.begin(),names.end(),name);
 int index;
 if(found==names.end()) {names.push_back(name);index=names.size()-1;}
 else index=found-names.begin();
 Rva00601A3AElement item={word0,word4,index};
 records.push_back(item);
}
