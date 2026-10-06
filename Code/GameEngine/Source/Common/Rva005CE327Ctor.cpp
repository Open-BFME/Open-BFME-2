// cl: /MD
// ??0Rva005CE327@@QAE@PBUPayload@0@@Z, retail 0x005CE327, 29 bytes.
// vtable 0x00875130 at +0; +4 zeroed; 3-dword movsd from src arg to +8; ret 4.
// Caller 0x005CE3F9 news 0x14 and stores with refcount inc; twin pattern of
// Rva005CDF6C / Rva005CDB8F 5-dword ctors; unblocks 0x005CE3F9.
class Rva005CE327
{
public:
	struct Payload { int v[3]; };
	Rva005CE327(const Payload *src);
	virtual ~Rva005CE327();
private:
	int m_ref; // +4
	Payload m_data; // +8
};

Rva005CE327::Rva005CE327(const Payload *src)
	: m_ref(0)
	, m_data(*src)
{
}

// 5 more constructors of this shape, each installing its own vtable
// (the only differing operand). One class per copy names that vtable; its
// destructor is declared inline and empty so the vtable the compiler emits
// resolves in this unit. Owners keep their addresses.

class Rva005E59A5
{
public:
	struct Payload { int v[3]; };
	Rva005E59A5(const Payload *src);
	virtual ~Rva005E59A5() {}
private:
	int m_ref; // +4
	Payload m_data; // +8
};

Rva005E59A5::Rva005E59A5(const Payload *src)
	: m_ref(0)
	, m_data(*src)
{
}

class Rva005E59C2
{
public:
	struct Payload { int v[3]; };
	Rva005E59C2(const Payload *src);
	virtual ~Rva005E59C2() {}
private:
	int m_ref; // +4
	Payload m_data; // +8
};

Rva005E59C2::Rva005E59C2(const Payload *src)
	: m_ref(0)
	, m_data(*src)
{
}

class Rva005E59DF
{
public:
	struct Payload { int v[3]; };
	Rva005E59DF(const Payload *src);
	virtual ~Rva005E59DF() {}
private:
	int m_ref; // +4
	Payload m_data; // +8
};

Rva005E59DF::Rva005E59DF(const Payload *src)
	: m_ref(0)
	, m_data(*src)
{
}

class Rva005E97B8
{
public:
	struct Payload { int v[3]; };
	Rva005E97B8(const Payload *src);
	virtual ~Rva005E97B8() {}
private:
	int m_ref; // +4
	Payload m_data; // +8
};

Rva005E97B8::Rva005E97B8(const Payload *src)
	: m_ref(0)
	, m_data(*src)
{
}

class Rva005E982C
{
public:
	struct Payload { int v[3]; };
	Rva005E982C(const Payload *src);
	virtual ~Rva005E982C() {}
private:
	int m_ref; // +4
	Payload m_data; // +8
};

Rva005E982C::Rva005E982C(const Payload *src)
	: m_ref(0)
	, m_data(*src)
{
}
