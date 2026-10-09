// ?Rva00309358Tokenize@@YAXABV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@AAV?$vector@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@V?$allocator@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@2@@2@0@Z
// partial score=0.9820334830543079 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// Native 309358..3093F6, cdecl three references, EH temporary string.
// Original helper name unknown; semantics established by native STL range calls
// and independently by StandingWaterArea::LoadPCAFile (WB BDE250).
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
 for(;;)
 {
  unsigned end=reinterpret_cast<BfmeThingPF *>(const_cast<std::string *>(&text))->rva00028C10(reinterpret_cast<const BfmeRangePF *>(&delimiters),begin);
  if(end==std::string::npos && begin==std::string::npos) break;
  { std::string token=text.substr(begin,end-begin); words.push_back(token); }
  begin=reinterpret_cast<BfmeThingPI *>(const_cast<std::string *>(&text))->bfmeGoPI(reinterpret_cast<const BfmeRangePI *>(&delimiters),end);
 }
}
