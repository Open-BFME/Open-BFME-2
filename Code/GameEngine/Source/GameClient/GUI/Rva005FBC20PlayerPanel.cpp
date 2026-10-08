// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /arch:SSE
#include "ascii_string.h"



// The narrow concatenation nodes, as rowed in RegistryAsciiPath.cpp.
class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}
	Rva000B3F84Pair *init(const char *);

	const char *m_ptr;
	int m_len;
};

struct AsciiStringRef
{
	const AsciiString *m_string;
};

// "string + string"
struct AsciiStringPlusString : AsciiStringRef
{
	AsciiStringRef m_second;
};

// "string + string + text"; its conversion is rowed at 0x0050F74B.
struct AsciiStringPlusStringText : AsciiStringPlusString
{
	operator AsciiString();

	Rva000B3F84Pair m_text;
};

inline AsciiStringPlusString operator+(const AsciiString &left, const AsciiString &right)
{
	AsciiStringPlusString result;
	result.m_string = &left;
	result.m_second.m_string = &right;
	return result;
}

// "8-byte node + text" is one identical-code fold at 0x00109CFD for every
// 8-byte left node; the ledger owns it as the AsciiStringRefWithChar overload.
// This unit's string-plus-string overload reaches it under the address name.
// ?operator+(AsciiStringPlusString, text) present-unmatched
// Existing folded callee at109CFD: complete61B and rel32 init B3F84 independently verified.
// The body is visible, so MSVC can reuse the dead left-node stack slot for the by-value delegate.
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left, const char *right)
{
 Rva000B3F84Pair text; text.init(right);
 AsciiStringPlusStringText result;
 static_cast<AsciiStringPlusString &>(result) = left;
 result.m_text = text;
 return result;
}

// The bound callbacks are handed over as a by-value delegate the callee
// destroys, built in place from an {object, method} pair by the rowed
// constructor 0x00579E47, as in StrategicHUD.cpp.
struct DelegateDesc;

class Rva00579E47
{
public:
	Rva00579E47(const DelegateDesc &desc);
	Rva00579E47(const Rva00579E47 &other);
	~Rva00579E47();

private:
	void *m_ptr;
};

class Rva00579E47Delegate;

// The +0x08 member: the 12-byte vector of bound names (constructor 0x001F81BF,
// rowed destructor 0x0052413E); 0x0052458E binds a delegate under a name.
class Rva0052413E
{
public:
	Rva0052413E();
	~Rva0052413E();
	void rva0052458E(const AsciiString &name, Rva00579E47Delegate delegate);

private:
	unsigned char m_pad[0xC];
};


#include "unicode_string.h"
// Existing names supply the independently proven ABI of the two setters.
namespace StrategicHUD { class DynamicAutoResolvePlayerPanelMovieClip { public: class Impl; }; }
class StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl {
public: void SetPlayerNameString(const UnicodeString&); void SetPlayerUnitCountString(const UnicodeString&);
};
class Rva005FBBEE {
public: virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
};
// Borrowed existing zero-eight-byte ctor owner; this array's semantic element
// identity is not established. Native iterator names callback 318329.
class IPEnumeration { public: IPEnumeration(); private: void *head; bool initialized; };
class AptTimerAdder { public: AptTimerAdder(); ~AptTimerAdder(); private: char storage[12]; };
class Rva005FBC20 {
public:
 Rva005FBC20(Rva005FBBEE*, unsigned, const AsciiString&);
 void rva005FB5AE(const char*); void rva005FB5BE(const char*); void rva005FB5D2(const char*);
private:
 Rva005FBBEE *owner; unsigned level; AsciiString name;
 Rva0052413E bindings; AptTimerAdder timers; // +c,+18
 void *field24; UnicodeString cachedName; int field2c; void *field30;
 float health; int cachedCount; IPEnumeration fields3c[2]; bool hitActive,reinforceActive;
};
struct DelegateDesc {
 DelegateDesc(Rva005FBC20 *p,void(Rva005FBC20::*f)(const char*)):m_object(p),m_method(f){}
 Rva005FBC20 *m_object; void(Rva005FBC20::*m_method)(const char*);
};
class Rva00579E47Delegate : public Rva00579E47 {
public: Rva00579E47Delegate(DelegateDesc d):Rva00579E47(d){}
};
void Rva005FBC20::rva005FB5AE(const char*) { if(hitActive) owner->slot1(); }
void Rva005FBC20::rva005FB5BE(const char*) { if(hitActive) {hitActive=false; owner->slot2();} }
void Rva005FBC20::rva005FB5D2(const char*) { if(reinforceActive) {reinforceActive=false; owner->slot3();} }
Rva005FBC20::Rva005FBC20(Rva005FBBEE *p,unsigned l,const AsciiString &n)
 :owner(p),level(l),name(n),field24(0),field2c(-1),field30(0),health(100.0f),cachedCount(-1),hitActive(false),reinforceActive(false)
{
 StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl *view=reinterpret_cast<StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl*>(this);
 view->SetPlayerNameString(UnicodeString::TheEmptyString);
 view->SetPlayerUnitCountString(UnicodeString::TheEmptyString);
 AsciiString prefix;prefix.format("_level%u.",level);
 bindings.rva0052458E(prefix+name+"_OnChainHitAnim",Rva00579E47Delegate(DelegateDesc(this,&Rva005FBC20::rva005FB5AE)));
 bindings.rva0052458E(prefix+name+"_OnHitAnimDone",Rva00579E47Delegate(DelegateDesc(this,&Rva005FBC20::rva005FB5BE)));
 bindings.rva0052458E(prefix+name+"_OnReinforceAnimDone",Rva00579E47Delegate(DelegateDesc(this,&Rva005FBC20::rva005FB5D2)));
}
