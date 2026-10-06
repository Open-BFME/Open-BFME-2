// cl: /Oi /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??0Rva000AAD5C@@QAE@XZ @0x000AAD5C 39B derived ctor over base 0x000AAD06
// Evidence: calls rowed ??0Rva000AAD06@@QAE@XZ then zeroes +0x14 +0x15 +0x18 then 6 dwords at +0x1C with rep stosd; stores vtable 0x007C9468 at +0 gate DIR32; caller 0x000AB648 in FUN_004AB485; base size 0x14 from Rva000AAD06Ctor vector at +8; honest Rva name owner unproven
#include <cstring>
class Rva000AAD06
{
public:
	Rva000AAD06();
protected:
	virtual void _0();
private:
	int m_04;
	char m_pad08[12];
};
class Rva000AAD5C : public Rva000AAD06
{
public:
	Rva000AAD5C();
protected:
	virtual void _0();
private:
	unsigned char m_14;
	unsigned char m_15;
	int m_18;
	int m_1c[6];
};
Rva000AAD5C::Rva000AAD5C()
	: m_14(0), m_15(0), m_18(0)
{
	memset(m_1c, 0, sizeof m_1c);
}
