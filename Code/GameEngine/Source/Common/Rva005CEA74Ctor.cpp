// cl: /MD
// ??0Rva005CEA74@@QAE@PBUPayload@0@@Z, retail 0x005CEA74, 30 bytes.
// vtable 0x008751D0 at +0; +4 zeroed; 2-dword mov copy from src arg to +8; ret 4.
// Caller 0x005CEC76 news 0x10 and stores with refcount inc; twin pattern of
// Rva005CE259 2-dword ctor with 2-mov shape; unblocks 0x005CEC5D.
class Rva005CEA74
{
public:
	struct Payload { int v[2]; };
	Rva005CEA74(const Payload *src);
	virtual ~Rva005CEA74();
private:
	int m_ref; // +4
	Payload m_data; // +8
};

Rva005CEA74::Rva005CEA74(const Payload *src)
	: m_ref(0)
	, m_data(*src)
{
}
