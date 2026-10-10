// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ??0Rva00527FA7@@QAE@HABVAsciiString@@@Z, retail 0x00527FA7..0x005281F0
// (585 bytes, EH, ret 8). The 0x18-byte panel payload allocated by the rowed
// owner constructor 0x005281F0 (AptPalantirCallbacks.cpp): stores the level
// at +0, copies the movie prefix to +4, clears +8, constructs the command
// name list at +0xC and registers "_level%u.<prefix>_OnOpened / _OnClosed /
// _OnCancel / _OnDeleteAction / _OnExecute" through it. The five callbacks
// (0x00527D7E, 0x00527D88, 0x00527D8F, 0x00527DDD, 0x00527E05) are DIR32
// references. The class keeps its address name. Pattern follows
// Rva0057C04FDtor.cpp (level, prefix and name-list constructor).
#include "ascii_string.h"
#include "unicode_string.h"

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

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
	AptRef(const DelegateDesc *desc) : Rva00579E47(*desc) {}
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

class AptCommandMapAdder
{
public:
	AptCommandMapAdder();
	~AptCommandMapAdder();
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);

	__forceinline void AddCommandMapDelegate(const AsciiString &name, DelegateDesc desc)
	{
		AddCommandMap(name, &desc);
	}

private:
	char m_pad[12];
};


class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}
	Rva000B3F84Pair *init(const char *src);

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
	operator AsciiString();

	Rva000B3F84Pair m_right;
};
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left, const char *right)
{
	Rva000B3F84Pair text;
	text.init(right);
	AsciiStringPlusStringText result;
	static_cast<AsciiStringPlusString &>(result) = left;
	result.m_right = text;
	return result;
}

static __forceinline AsciiStringPlusString operator+(const AsciiString &left, const AsciiString &right)
{
	AsciiStringPlusString result;
	result.m_string = &left;
	result.m_second.m_string = &right;
	return result;
}

class Rva00527FA7
{
public:
	Rva00527FA7(int level, const AsciiString &name);
	void OnOpened(const char *path);
	void OnClosed(const char *path);
	void OnCancel(const char *path);
	void OnDeleteAction(const char *path);
	void OnExecute(const char *path);
private:
	int m_level00;
	AsciiString m_04;
	int m_08;
	AptCommandMapAdder m_0C;
};

Rva00527FA7::Rva00527FA7(int level, const AsciiString &name)
	: m_level00(level), m_04(name), m_08(0)
{
	AsciiString prefix;
	prefix.format("_level%u.", m_level00);
	m_0C.AddCommandMapDelegate(prefix + m_04 + "_OnOpened", DelegateDesc(this, &Rva00527FA7::OnOpened));
	m_0C.AddCommandMapDelegate(prefix + m_04 + "_OnClosed", DelegateDesc(this, &Rva00527FA7::OnClosed));
	m_0C.AddCommandMapDelegate(prefix + m_04 + "_OnCancel", DelegateDesc(this, &Rva00527FA7::OnCancel));
	m_0C.AddCommandMapDelegate(prefix + m_04 + "_OnDeleteAction", DelegateDesc(this, &Rva00527FA7::OnDeleteAction));
	m_0C.AddCommandMapDelegate(prefix + m_04 + "_OnExecute", DelegateDesc(this, &Rva00527FA7::OnExecute));
}
