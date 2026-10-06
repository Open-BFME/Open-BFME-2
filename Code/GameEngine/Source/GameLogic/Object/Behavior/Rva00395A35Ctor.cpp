// cl: /DNDEBUG /MD /EHsc
//
// ??0Rva00395A35@@QAE@ABVBfmeFixedStorage0004543D@@0@Z, retail 0x00395A35, 43 bytes.
// Two-arg ctor over BfmeFixedStorage0004543D (28B, rowed copy at 0x0004543D):
// vtable g_00C1A268 at +0, int at +4 cleared, members at +8/+0x24 copied from
// the two args, returns this. Prev CastleMemberBehaviorPoolKey and next
// Rva00395A60 share the 00395xxx page; flags match FixedStorageCopyBFME2.
extern const void *const g_00C1A268[];
class BfmeFixedStorage0004543D
{
	char m_bytes[28];
public:
	__declspec(nothrow) BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);
};
class Rva00395A35
{
public:
	virtual void anchor();
	Rva00395A35(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b);
private:
	int m_04;
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};
Rva00395A35::Rva00395A35(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b)
	: m_04(0)
	, m_08(a)
	, m_24(b)
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?anchor@Rva00395A35@@UAEXXZ=?rva00395A19@Rva00395A19@@QAEPAXI@Z")
