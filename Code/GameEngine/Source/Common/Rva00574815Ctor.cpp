// cl: /DNDEBUG /MD
// ??0Rva00574815@@QAE@H@Z retail 0x00574815 49B
// Derived ctor of rowed base Rva005CBA04 (0x005CBA04): builds a 4B
// FixedStorage temp from global 0x00E0661C via rowed copy 0x002CF0F0,
// passes it by value to the base, stores the outer int arg at +8 and
// overwrites vtable with 0x0086E3E8. Evidence: call sequence matches base
// comment listing this as derived ctor with global 0x00E0661C; sole caller
// at 0x00574971; same 49B shape as sibling Rva005756B6; neighbours share /O1.
// Honest Rva address name.
class BfmeFixedStorage002CF0F0
{
	char m_bytes[4];
public:
	__declspec(nothrow) BfmeFixedStorage002CF0F0(const BfmeFixedStorage002CF0F0 &);
};
class Rva005CBA04
{
public:
	virtual ~Rva005CBA04();
	Rva005CBA04(BfmeFixedStorage002CF0F0 storage);
private:
	BfmeFixedStorage002CF0F0 m_storage;
};
class Rva00574815 : public Rva005CBA04
{
public:
	Rva00574815(int arg);
	virtual ~Rva00574815();
private:
	int m_08;
};
Rva00574815::Rva00574815(int arg)
	: Rva005CBA04(*reinterpret_cast<const BfmeFixedStorage002CF0F0 *>(0x00E0661C))
	, m_08(arg)
{
}
