// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /arch:SSE
//
// ??0Rva0050ED58@@QAE@HABVAsciiString@@@Z @0x0051066A 641B: constructor of
// the Apt row page whose dtor is rowed at 0x0050ED58 (caller StrategicHUD
// 0x0042E0xx through new). Target evidence: level at +0x00 and the name
// copied to +0x04 (rowed 0x000365F0); the two 12-byte callback vectors at
// +0x08/+0x14 (ctor 0x001F81BF); +0x20 cleared; seven 8-byte rows at +0x24
// built by the eh vector ctor with ctor 0x0007E81F and dtor 0x0050EB02;
// "_level<n>." (format 0x00038150) plus the name plus "_OnRowShown"
// "_OnRowHidden" "_Reset" "_Send" (folded operator+ 0x00109CFD and the
// rowed conversion 0x0050F74B) bound as commands through the by-value
// delegate 0x00579E47 and AddCommandMap 0x0052458E; "_NumOfPlayers" bound
// as an extern handler (0x005245F3 with 0); then the rowed 0x0050E8D6 and
// 0x0050F4D0 on this. Same delegate pattern as Rva005FBC20PlayerPanel.cpp.

#include "ascii_string.h"

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

struct AsciiStringPlusString : AsciiStringRef
{
	AsciiStringRef m_second;
};

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

// ?operator+(AsciiStringPlusString, text) present-unmatched
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left, const char *right)
{
	Rva000B3F84Pair text;
	text.init(right);
	AsciiStringPlusStringText result;
	static_cast<AsciiStringPlusString &>(result) = left;
	result.m_text = text;
	return result;
}

class __single_inheritance Rva0050ED58;

struct DelegateDesc
{
	DelegateDesc(Rva0050ED58 *p, void (Rva0050ED58::*f)(const char *)) : m_object(p), m_method(f) {}

	Rva0050ED58 *m_object;
	void (Rva0050ED58::*m_method)(const char *);
};

class Rva00579E47
{
public:
	Rva00579E47(const DelegateDesc &desc);
	Rva00579E47(const Rva00579E47 &other);
	~Rva00579E47();

private:
	void *m_ptr;
};

template <class T> class AptRef : public Rva00579E47
{
public:
	AptRef(DelegateDesc d) : Rva00579E47(d) {}
};

class AptCommandMap;
class AptExternHandler;

class AptCommandMapAdder
{
public:
	AptCommandMapAdder();
	~AptCommandMapAdder();
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);

private:
	unsigned char m_names[0xC];
};

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);
};

// The extern handler name list (dtor rowed 0x005241B0; its implicit ctor is
// the ICF-folded vector default ctor 0x001F81BF).
class Rva005241B0
{
public:
	Rva005241B0();
	~Rva005241B0();

private:
	unsigned char m_names[0xC];
};

struct Rva0050ED58Elem
{
	Rva0050ED58Elem();
	~Rva0050ED58Elem();
	char m_data[8];
};

class Rva0050F10B
{
public:
	void rva0050F10B(const char *p);
};

class Rva0050F5A6
{
public:
	void rva0050F5A6(int v);
	void rva0050F4D0();
};

class Rva0050E8D6
{
public:
	void rva0050E8D6();
};

class Rva0050ED58
{
public:
	Rva0050ED58(int level, const AsciiString &name);
	~Rva0050ED58();

	// Bound callbacks with no row yet (pinned by address).
	void rva0050FFEC(const char *params); // "_OnRowShown"
	void rva0050EB0A(const char *params); // "_Send"
	void rva0050E952(int which, char *result, bool skip); // "_NumOfPlayers"

private:
	int m_level; // +0x00
	AsciiString m_name; // +0x04
	AptCommandMapAdder m_commandMaps; // +0x08
	Rva005241B0 m_externHandlers; // +0x14
	int m_count; // +0x20
	Rva0050ED58Elem m_rows[7]; // +0x24
};

typedef void (Rva0050ED58::*CommandMethod)(const char *);

Rva0050ED58::Rva0050ED58(int level, const AsciiString &name)
	: m_level(level), m_name(name), m_count(0)
{
	AsciiString prefix;
	prefix.format("_level%u.", m_level);
	m_commandMaps.AddCommandMap(prefix + m_name + "_OnRowShown", AptRef<AptCommandMap>(DelegateDesc(this, &Rva0050ED58::rva0050FFEC)));
	m_commandMaps.AddCommandMap(prefix + m_name + "_OnRowHidden", AptRef<AptCommandMap>(DelegateDesc(this, reinterpret_cast<CommandMethod>(&Rva0050F10B::rva0050F10B))));
	m_commandMaps.AddCommandMap(prefix + m_name + "_Reset", AptRef<AptCommandMap>(DelegateDesc(this, reinterpret_cast<CommandMethod>(&Rva0050F5A6::rva0050F5A6))));
	m_commandMaps.AddCommandMap(prefix + m_name + "_Send", AptRef<AptCommandMap>(DelegateDesc(this, &Rva0050ED58::rva0050EB0A)));
	((AptExternHandlerAdder *)&m_externHandlers)->AddExternHandler(prefix + m_name + "_NumOfPlayers", 0, AptRef<AptExternHandler>(DelegateDesc(this, reinterpret_cast<CommandMethod>(&Rva0050ED58::rva0050E952))));
	((Rva0050E8D6 *)this)->rva0050E8D6();
	((Rva0050F5A6 *)this)->rva0050F4D0();
}
