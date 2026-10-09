// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /DNDEBUG
// Retail 005E1680..005E16A7 (39B): constructor for the same vtable
// C779B4 whose destructor is the verified Rva005E12D1 at005E12D1.
// The frame and AsciiString-reference ABI comes from the rowed base
// CommandButtonMovieClip constructor and independent constructor callers.
// Owner pointer +0C and counted handle +10 are confirmed by that destructor.
#include "ascii_string.h"
class AptMovieClipFrame;
class __declspec(novtable) Rva005E1627Base {
public: __forceinline Rva005E1627Base():m_04(0) {} virtual ~Rva005E1627Base();
protected: int m_04;
};
namespace StrategicHUD {
class CommandButtonMovieClip : public Rva005E1627Base {
public:
 CommandButtonMovieClip(AptMovieClipFrame*, const AsciiString&);
 virtual ~CommandButtonMovieClip();
private: void *m_impl;
};
}
struct TargetRef00217D4C;
struct Rva005E1680Tail {
 Rva005E1680Tail():m_ref(0) {}
 TargetRef00217D4C *m_ref;
};
class Rva005E12D1 : public StrategicHUD::CommandButtonMovieClip {
public:
 Rva005E12D1(void*,const AsciiString&,void*);
 virtual ~Rva005E12D1();
private: void *m_owner; Rva005E1680Tail m_held;
};
Rva005E12D1::Rva005E12D1(void* frame,const AsciiString& name,void* owner)
 : StrategicHUD::CommandButtonMovieClip((AptMovieClipFrame*)frame,name),m_owner(owner)
{
}
