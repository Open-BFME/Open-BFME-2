// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// ?Rva00309358Tokenize@@YAXABV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@AAV?$vector@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@V?$allocator@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@2@@2@0@Z
// Retail 0x00309358 158 bytes cdecl with an EH frame for the substr temporary.
// The classic string tokenizer: clear the output then find_first_not_of
// (rowed 0x0002A3A0 through the (data size) overload) and find_first_of
// (rowed 0x00028C10) the delimiters; while either position is live push the
// substr (rowed 0x0002AD50) temporary straight into push_back (rowed
// 0x0007A773) then advance with find_first_not_of (rowed 0x0002AC90) and
// find_first_of again. MSVC tail-merges the two find_first_of calls into the
// loop head which is why retail reloads the end position from its slot.
// Original helper name unknown; semantics established by native STL range
// calls and independently by StandingWaterArea::LoadPCAFile (WB BDE250).
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <string>
#include <vector>
struct BfmeRangePF { char *begin,*end; };
struct BfmeRangePI { char *begin,*end; };
class BfmeS1155 { public: unsigned bfmeFind1155(const char *,unsigned,unsigned); };
class BfmeThingPF { public: int rva00028C10(const BfmeRangePF *,unsigned); };
class BfmeThingPI { public: unsigned bfmeGoPI(const BfmeRangePI *,unsigned); };
void Rva00309358Tokenize(const std::string &text,std::vector<std::string> &words,const std::string &delimiters)
{
 words.erase(words.begin(),words.end());
 unsigned begin=reinterpret_cast<BfmeS1155 *>(const_cast<std::string *>(&text))->bfmeFind1155(delimiters.data(),0,delimiters.size());
 unsigned end=reinterpret_cast<BfmeThingPF *>(const_cast<std::string *>(&text))->rva00028C10(reinterpret_cast<const BfmeRangePF *>(&delimiters),begin);
 while(end!=std::string::npos || begin!=std::string::npos)
 {
  words.push_back(text.substr(begin,end-begin));
  begin=reinterpret_cast<BfmeThingPI *>(const_cast<std::string *>(&text))->bfmeGoPI(reinterpret_cast<const BfmeRangePI *>(&delimiters),end);
  end=reinterpret_cast<BfmeThingPF *>(const_cast<std::string *>(&text))->rva00028C10(reinterpret_cast<const BfmeRangePF *>(&delimiters),begin);
 }
}
