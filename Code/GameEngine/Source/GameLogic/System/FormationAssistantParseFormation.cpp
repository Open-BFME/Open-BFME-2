// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /arch:SSE /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// FormationAssistant row-data parser, original retail routine name unknown.
// Target 0x004251C4..0x00425369 is 421B; emitted INT3 at 0x00425369 extends the row to422B.
// The next independently owned function begins at 0x0042536A.
// Adjacent init loads FormationAssistant.ini. Native literal says row cell counts must agree.
// Target starts a row in the triple deque at table+8, splits each INI token on '|', converts
// each cell entry with TheNameKeyGenerator, and checks row width against table+4.
// STLport4.5.3 and existing nested-deque providers are the reference implementation.
// Inner values are unowned-name four-byte keys; outer elements are 40-byte deques.
// The ledger's neutral back/push/subtract views are used at their proven native call sites;
// this preserves original type uncertainty and avoids giving folded templates another name.
// Native compiler lifetimes require the filename temporary in the throw expression.

#include "ascii_string.h"
// Keep deque growth's unsigned comparison local. Its standalone template
// copy differs from retail; all uses in this unit are already inlined.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
 return a < b ? b : a;
}
}
#include <deque>
// Declaration-only: retail keeps one _STL::max<unsigned int> (17-byte jae
// shape); this TU's flags would emit a private copy.
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}
struct BfmeWordValue4 {unsigned int bits;BfmeWordValue4(){}~BfmeWordValue4(){}};
typedef _STL::deque<BfmeWordValue4> InnerDeque;
typedef _STL::deque<InnerDeque> OuterDeque;
typedef _STL::deque<OuterDeque> TripleDeque;
namespace _STL {template<> OuterDeque::~deque();}
// The verified /EHs provider owns retail's 123-byte growth helper. This
// parser's /EHsc copy omits its final EH state store and must not compete.
namespace _STL {template<> void OuterDeque::_M_push_back_aux_v(const InnerDeque &);}
// Native helper ledger views preserve the independently proven 40-byte deque elements
// and four-byte keys; casts select those existing specializations without new pins.
struct BfmePod40 {char data[40];};
struct Rva00423BD8Element {int word0;bool operator<(const Rva00423BD8Element &)const;bool operator==(const Rva00423BD8Element &)const;};
struct BfmeOpaque40 {char bytes[40];};
namespace _STL {
template<> BfmePod40 &deque<BfmePod40>::back();
template<> void deque<Rva00423BD8Element>::push_back(const Rva00423BD8Element &);
}
struct Rva004251C4Table {unsigned unknown;unsigned columns;TripleDeque rows;};
#include "../../../Include/Common/INI/INI.h"
enum NameKeyType {NAMEKEY_INVALID=0};
#include "../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
#include "../../../Include/Common/INI/FieldParse.h"
void Rva004251C4Parse(INI *ini,Rva004251C4Table *table)
{
 table->rows.push_back(OuterDeque());
 OuterDeque &row=*(OuterDeque *)&((_STL::deque<BfmePod40> *)&table->rows)->back();
 AsciiString text=ini->getNextAsciiString();
 AsciiString token;
 while(!text.isEmpty()) {
  row.push_back(InnerDeque());
  InnerDeque &cell=*(InnerDeque *)&((_STL::deque<BfmePod40> *)&row)->back();
  while(text.nextToken(&token,"|")) {
   Rva00423BD8Element key;key.word0=TheNameKeyGenerator->nameToKey(token);((_STL::deque<Rva00423BD8Element> *)&cell)->push_back(key);
  }
  text=ini->getNextAsciiString();
 }
 const _STL::_Deque_iterator_base<BfmeOpaque40> *rows=(const _STL::_Deque_iterator_base<BfmeOpaque40> *)&table->rows;
 const _STL::_Deque_iterator_base<BfmeOpaque40> *rowIter=(const _STL::_Deque_iterator_base<BfmeOpaque40> *)&row;
 if(rows[1]._M_subtract(rows[0])==1)table->columns=rowIter[1]._M_subtract(rowIter[0]);
 else if(rowIter[1]._M_subtract(rowIter[0])!=table->columns) {
  throw INIException(3,"Row data has different number of cells than previous row at %s:%d",ini->getFilename().str(),ini->getLineNum());
 }
}
