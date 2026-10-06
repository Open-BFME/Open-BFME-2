// cl: /MD
// ??0Rva005CEAE6@@QAE@PBUPayload@0@@Z, retail 0x005CEAE6, 29 bytes.
// vtable 0x008751DC at +0; +4 zeroed; 3-dword movsd from src arg to +8; ret 4.
// Caller 0x005CECA8 news 0x14 and stores with refcount inc; twin pattern of
// 0x005CE327 Rva005CE327 3-dword ctor; unblocks 0x005CEC8F.
class Rva005CEAE6
{
public:
	struct Payload { int v[3]; };
	Rva005CEAE6(const Payload *src);
	virtual ~Rva005CEAE6();
private:
	int m_ref; // +4
	Payload m_data; // +8
};

Rva005CEAE6::Rva005CEAE6(const Payload *src)
	: m_ref(0)
	, m_data(*src)
{
}
