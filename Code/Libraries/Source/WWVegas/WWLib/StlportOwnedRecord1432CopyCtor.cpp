// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0BfmeOpaqueOwnedRecord1432@@QAE@ABU0@@Z @0x00556375 219B
// Copy ctor for the 1432-byte (0x598) opaque deque record. Layout from retail:
// +0/+4 head dwords, +8 subobject (0x548 bytes, copy via pinned
// ??0Rva005564EBSub@@QAE@ABU0@@Z @0x0038630B), five _STL::basic_string<char>
// members at +0x550/+0x55C/+0x568/+0x574/+0x58C (rowed copy @0x00009170),
// bytes at +0x580/+0x581 and dwords at +0x584/+0x588. Total 0x598=1432.
// Evidence: LINK BONUS caller names it ??0BfmeOpaqueOwnedRecord1432@@QAE@ABU0@@Z;
// callers 0x00557C52 (_Construct dup) and 0x00558DA0 (deque push_back_aux_v).
#include <string>

struct Rva005564EBSub
{
	char m_body[0x548];
	Rva005564EBSub(const Rva005564EBSub &o);
	~Rva005564EBSub();
};

struct BfmeOpaqueOwnedRecord1432
{
	unsigned int m_00;
	unsigned int m_04;
	Rva005564EBSub m_08;
	_STL::string m_550;
	_STL::string m_55c;
	_STL::string m_568;
	_STL::string m_574;
	unsigned char m_580;
	unsigned char m_581;
	unsigned int m_584;
	unsigned int m_588;
	_STL::string m_58c;
	BfmeOpaqueOwnedRecord1432(const BfmeOpaqueOwnedRecord1432 &o);
};

BfmeOpaqueOwnedRecord1432::BfmeOpaqueOwnedRecord1432(const BfmeOpaqueOwnedRecord1432 &o)
	: m_00(o.m_00)
	, m_04(o.m_04)
	, m_08(o.m_08)
	, m_550(o.m_550)
	, m_55c(o.m_55c)
	, m_568(o.m_568)
	, m_574(o.m_574)
	, m_580(o.m_580)
	, m_581(o.m_581)
	, m_584(o.m_584)
	, m_588(o.m_588)
	, m_58c(o.m_58c)
{
}
