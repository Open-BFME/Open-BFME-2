// cl: /MD
// ??0Rva005CEB57@@QAE@PBUPayload@0@@Z, retail 0x005CEB57, 31 bytes.
// vtable 0x008751E8 at +0; +4 zeroed; 6-dword rep movsd from src arg to +8; ret 4.
// Caller 0x005CECDA news 0x20 and stores with refcount inc; twin pattern of
// Rva005CDF6C 5-dword ctor with push 6 pop ecx shape; unblocks 0x005CECC1.
class Rva005CEB57
{
public:
	struct Payload { int v[6]; };
	Rva005CEB57(const Payload *src);
	virtual ~Rva005CEB57();
private:
	int m_ref; // +4
	Payload m_data; // +8
};

Rva005CEB57::Rva005CEB57(const Payload *src)
	: m_ref(0)
	, m_data(*src)
{
}

// One more constructor of this shape, each installing its own vtable (the only
// differing operand): 0x005E9742 (VA 0xc78038). The virtual is declared inline and
// empty so the vtable the compiler emits resolves in this unit. Owners keep
// their addresses.

class Rva005E9742
{
public:
	struct Payload { int v[6]; };
	Rva005E9742(const Payload *src);
	virtual ~Rva005E9742() {}
private:
	int m_ref; // +4
	Payload m_data; // +8
};

Rva005E9742::Rva005E9742(const Payload *src)
	: m_ref(0)
	, m_data(*src)
{
}
