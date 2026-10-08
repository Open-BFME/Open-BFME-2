// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /EHsc /MD
// stlport
// Native523DB7..523DD4 copies the referenced int and the one-pointer string.
// The original opaque caller spelling remains supported. Its full29B body
// and the genuine STLport pair<int,AsciiString> constructor compile identically,
// including the owned StringBase copy365F0 relocation; integer signedness
// is irrelevant here because this constructor performs no comparisons.
// BFME1 donor34f59164 game/GameEngine/Source/GameLogic/Object/MakePairIntAsciiString.cpp
// instantiates the same factory. Native23FC23 calls this constructor with
// the hidden result pointer and the two source refs, then returns that pointer.
#include "ascii_string.h"
#include <utility>
class Rva00523DB7 {
public: Rva00523DB7(const int *,const StringBase<char> &);
private: int m_00; AsciiString m_04;
};
Rva00523DB7::Rva00523DB7(const int *p,const StringBase<char> &s):m_00(*p),m_04(reinterpret_cast<const AsciiString &>(s)){}
template _STL::pair<int, AsciiString> _STL::make_pair<int, AsciiString>(const int &, const AsciiString &);
