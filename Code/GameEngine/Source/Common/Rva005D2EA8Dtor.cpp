// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// Retail 5D2EA8 destructor and 5D3398 constructor of the 24-byte counter
// callback member used three times by the RegionStatsTray ctor 5D3506.
// Original member class identity remains unknown. Layout and all four
// vtable slots come from C75898 and target accesses, not donor type names.
// Reference guide: verified EndTurnButtonImpl callback registration and
// RegistryAsciiPath concat nodes; target binds _On<stat>RollOver/RollOut.
#include "ascii_string.h"

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

// Delegate payload (object, member) handed to the command-map reference
// (as in Rva0042DB21Method.cpp).
class AptCommandTarget
{
};

struct DelegateDesc
{
	template <class T> DelegateDesc(T *object, void (T::*method)(const char *path))
		: m_object(reinterpret_cast<AptCommandTarget *>(object)), m_method(reinterpret_cast<void (AptCommandTarget::*)(const char *path)>(method)) {}

	AptCommandTarget *m_object;
	void (AptCommandTarget::*m_method)(const char *path);
};

class AptCommandMap
{
public:
	void *m_vtbl;
	int m_refCount;
};

template <class T> class AptRef
{
public:
	__forceinline AptRef(const DelegateDesc &desc) { rva00579E47(&desc); }
	AptRef &rva00579E47(const DelegateDesc *desc); // 0x00579E47
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
class AptCommandMapAdder
{
public:
	AptCommandMapAdder();
	~AptCommandMapAdder();
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);

	__forceinline void AddCommandMapDelegate(const AsciiString &name, DelegateDesc desc)
	{
		AddCommandMap(name, desc);
	}

private:
	void *m_pad[3];
};

// "prefix + name + text" concat nodes (layout as in System/RegistryAsciiPath.cpp).
class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}
	Rva000B3F84Pair *init(const char *src); // 0x000B3F84

	const char *m_ptr;
	int m_len;
};

struct AsciiStringRef
{
	const AsciiString *m_string;
};

struct AsciiStringPlusString : AsciiStringRef
{
	AsciiStringRef m_second;
};

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
class Rva005D2EA8Listener {
public: virtual void notify(void *)=0;
 virtual void slot1()=0; virtual void slot2()=0;
 virtual void rollOut(void *)=0; virtual void rollOver(void *)=0;
};
class Rva005D2EA8Base {
public: virtual Rva005D2EA8Listener *getListener() const=0;
 virtual void setListener(Rva005D2EA8Listener *)=0;
 virtual bool getRollOver() const=0;
 // ?Rva005D2EA8BaseDestructor present-unmatched
 virtual ~Rva005D2EA8Base() {}
};
class Rva005D2EA8:public Rva005D2EA8Base {
public:
 Rva005D2EA8(int level,const AsciiString &name,const char *stat);
 virtual ~Rva005D2EA8();
 virtual Rva005D2EA8Listener *getListener() const {return m_listener;}
 virtual void setListener(Rva005D2EA8Listener *listener) {m_listener=listener;}
 virtual bool getRollOver() const {return m_rollOver;}
 void rva005D2EF1(const char *);
 void rva005D2F07(const char *);
private: Rva005D2EA8Listener *m_listener; bool m_rollOver; AptCommandMapAdder m_0C;
};
Rva005D2EA8::Rva005D2EA8(int level,const AsciiString &name,const char *stat):m_listener(0),m_rollOver(false)
{
 AsciiString prefix; prefix.format("_level%u.",level);
 m_0C.AddCommandMapDelegate(prefix+name+"_On"+stat+"RollOver",DelegateDesc(this,&Rva005D2EA8::rva005D2F07));
 m_0C.AddCommandMapDelegate(prefix+name+"_On"+stat+"RollOut",DelegateDesc(this,&Rva005D2EA8::rva005D2EF1));
}
Rva005D2EA8::~Rva005D2EA8() {if(m_listener) m_listener->notify(this);}
void Rva005D2EA8::rva005D2EF1(const char *) {m_rollOver=false;if(m_listener) m_listener->rollOut(this);}
void Rva005D2EA8::rva005D2F07(const char *) {m_rollOver=true;if(m_listener) m_listener->rollOver(this);}
