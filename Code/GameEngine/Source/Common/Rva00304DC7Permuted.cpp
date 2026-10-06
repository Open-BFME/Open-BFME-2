// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG
//
// ??ARva00304DC7Map@@QAEAAVRva00304DC7Record@@ABVAsciiString@@@Z, retail 0x00304dc7, 157 bytes. Banked partial (score 0.97) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
#include <map>
#include "ascii_string.h"
bool operator<(const AsciiString&,const AsciiString&);
class Rva00304DC7Record {public:Rva00304DC7Record();~Rva00304DC7Record();private:char consumed[256];};
struct Rva00304DC7Entry {AsciiString key;Rva00304DC7Record value;Rva00304DC7Entry(const AsciiString&,const Rva00304DC7Record&);~Rva00304DC7Entry();};
typedef _STL::_Rb_tree_iterator<Rva00304DC7Entry,_STL::_Nonconst_traits<Rva00304DC7Entry> > Rva00304DC7Iterator;
class Rva00304DC7Map {public:Rva00304DC7Record&operator[](const AsciiString&);
private:_STL::_Rb_tree_node<Rva00304DC7Entry>*header;
_STL::_Rb_tree_node<Rva00304DC7Entry>*lower_bound(const AsciiString&);
Rva00304DC7Iterator insert(Rva00304DC7Iterator,const Rva00304DC7Entry&);};
Rva00304DC7Record& Rva00304DC7Map::operator[](const AsciiString&key) {
 Rva00304DC7Iterator i(lower_bound(key));
 if(i._M_node==header || key<i->key)
  i=insert(i,Rva00304DC7Entry(key,Rva00304DC7Record()));
 return i->value;
}
