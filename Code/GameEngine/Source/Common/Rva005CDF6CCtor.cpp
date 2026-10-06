// cl: /MD
// ??0Rva005CDF6C@@QAE@PBUPayload@0@@Z @0x005CDF6C 31B copy 20B plus refcount 0.
// Twin of 0x005CDB8F in Rva005CDB8FCtor.cpp: vtable 0x00875108 at +0; +4
// zeroed; 5-dword rep movsd from src arg to +8; ret 4. Caller 0x005CE00E
// news 0x1C and stores with refcount inc.
class Rva005CDF6C
{
public:
	struct Payload { int v[5]; };
	Rva005CDF6C(const Payload *src);
	virtual ~Rva005CDF6C();
private:
	int m_ref;
	Payload m_data;
};
Rva005CDF6C::Rva005CDF6C(const Payload *src)
	: m_ref(0)
	, m_data(*src)
{
}
