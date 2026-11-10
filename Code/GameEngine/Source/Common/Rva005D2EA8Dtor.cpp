// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// Retail 5D2EA8 destructor and 5D3398 constructor of the 24-byte counter
// callback member used three times by the RegionStatsTray ctor 5D3506.
// Original member class identity remains unknown. Layout and all four
// vtable slots come from C75898 and target accesses, not donor type names.
// Reference guide: verified EndTurnButtonImpl callback registration and
// RegistryAsciiPath concat nodes; target binds _On<stat>RollOver/RollOut.
#include "ascii_string.h"

#include "../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

// Delegate payload (object, member) handed to the command-map reference
// (as in Rva0042DB21Method.cpp).
#include "../../../Libraries/Source/Apt/AptCommandTarget.h"

#include "../../Include/Common/DelegateDesc.h"

class AptCommandMap
{
public:
	void *m_vtbl;
	int m_refCount;
};

// 0x00579E47 is rowed as the delegate-wrapper constructor ??0Rva00579E47@@QAE@ABUDelegateDesc@@@Z
// (built in place as the by-value AddCommandMap argument); AptRef<T> builds through it.
class Rva00579E47
{
public:
	Rva00579E47(const DelegateDesc &desc); // 0x00579E47
protected:
	Rva00579E47() {}
};

template <class T> class AptRef : public Rva00579E47
{
public:
	__forceinline AptRef(const DelegateDesc &desc) : Rva00579E47(desc) {}
	AptRef(const AptRef &that) : m_ptr(that.m_ptr)
	{
		if (m_ptr)
			m_ptr->m_refCount++;
	}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}

private:
	T *m_ptr;
};

// The 12-byte command-map name list: ctor 0x001F81BF (ICF fold, pinned),
// AddCommandMap 0x0052458E, dtor 0x0052413E (pinned).
#include "../../../Libraries/Source/Apt/AptCommandMapAdder.h"

static __forceinline void AddCommandMapDelegate(AptCommandMapAdder &adder, const AsciiString &name, DelegateDesc desc)
{
	adder.AddCommandMap(name, desc);
}

// "prefix + name + text" concat nodes (layout as in System/RegistryAsciiPath.cpp).
#include "../../Include/Common/Rva000B3F84Pair.h"

#include "../../Include/Common/AsciiStringRef.h"

#include "../../Include/Common/AsciiStringPlusString.h"

struct AsciiStringPlusStringText : AsciiStringPlusString
{
	operator AsciiString(); // 0x0050F74B

	Rva000B3F84Pair m_right;
};

static __forceinline AsciiStringPlusString operator+(const AsciiString &left, const AsciiString &right)
{
	AsciiStringPlusString result;
	result.m_string = &left;
	result.m_second.m_string = &right;
	return result;
}

// ?operator+(AsciiStringPlusString, text) present-unmatched (inline, emitted out of line; ICF-folded at 0x00109CFD; pinned)
// ?operatorPlusTwoStringsText present-unmatched
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left, const char *right)
{
	Rva000B3F84Pair text;
	text.init(right);
	AsciiStringPlusStringText result;
	static_cast<AsciiStringPlusString &>(result) = left;
	result.m_right = text;
	return result;
}


struct Rva005D32EC:AsciiStringPlusStringText { Rva000B3F84Pair m_text2; };
struct Rva005D3311:Rva005D32EC { Rva000B3F84Pair m_text3; operator AsciiString(); };
// ?operatorPlusThirdText present-unmatched
inline Rva005D32EC operator+(const AsciiStringPlusStringText &left,const char *right)
{
 Rva000B3F84Pair text; text.init(right);
 Rva005D32EC result; static_cast<AsciiStringPlusStringText &>(result)=left;
 result.m_text2=text; return result;
}
// ?operatorPlusFourthText present-unmatched
inline Rva005D3311 operator+(const Rva005D32EC &left,const char *right)
{
 Rva000B3F84Pair text; text.init(right);
 Rva005D3311 result; static_cast<Rva005D32EC &>(result)=left;
 result.m_text3=text; return result;
}
class RollOverListener {
public: virtual void notify(void *)=0;
 virtual void slot1()=0; virtual void slot2()=0;
 virtual void rollOut(void *)=0; virtual void rollOver(void *)=0;
};
class Rva005D2EA8Base {
public: virtual RollOverListener *getListener() const=0;
 virtual void setListener(RollOverListener *)=0;
 virtual bool getRollOver() const=0;
 // ?Rva005D2EA8BaseDestructor present-unmatched
 virtual ~Rva005D2EA8Base() {}
};
class Rva005D2EA8:public Rva005D2EA8Base {
public:
 Rva005D2EA8(int level,const AsciiString &name,const char *stat);
 virtual ~Rva005D2EA8();
 virtual RollOverListener *getListener() const {return m_listener;}
 virtual void setListener(RollOverListener *listener) {m_listener=listener;}
 virtual bool getRollOver() const {return m_rollOver;}
 void onRollOut(const char *);
 void OnRollOver(const char *);
private: RollOverListener *m_listener; bool m_rollOver; AptCommandMapAdder m_0C;
};
Rva005D2EA8::Rva005D2EA8(int level,const AsciiString &name,const char *stat):m_listener(0),m_rollOver(false)
{
 AsciiString prefix; prefix.format("_level%u.",level);
 AddCommandMapDelegate(m_0C, prefix+name+"_On"+stat+"RollOver",DelegateDesc(this,&Rva005D2EA8::OnRollOver));
 AddCommandMapDelegate(m_0C, prefix+name+"_On"+stat+"RollOut",DelegateDesc(this,&Rva005D2EA8::onRollOut));
}
Rva005D2EA8::~Rva005D2EA8() {if(m_listener) m_listener->notify(this);}
void Rva005D2EA8::onRollOut(const char *) {m_rollOver=false;if(m_listener) m_listener->rollOut(this);}
void Rva005D2EA8::OnRollOver(const char *) {m_rollOver=true;if(m_listener) m_listener->rollOver(this);}
