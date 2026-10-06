// cl: /EHs
// ??1Rva003C649E@@QAE@XZ @0x003C649E 105B. Non-virtual dtor over four
// inline string members at +0x4/+0x10/+0x1C/+0x2C whose bodies free
// via rowed _free at 0x00030830. Evidence: unlock lane, __thiscall,
// __EH_prolog with scopetable 0x00782F8F plus Unwind funclets at
// 0x0078312F/0x0078315C, EH states 2/1/0/-1, no vptr store and no base
// call. Layout honest-address only.
// These members are NOT AsciiString: the inlined dtor calls free directly
// with a null check, while the shared AsciiString dtor calls releaseBuffer
// (row 0x00036410). Named Rva003C649EString per LINK-COMDAT rename rule.
extern "C" void __cdecl free(void *p);
template <typename T> class Rva003C649EStringBase
{
public:
	~Rva003C649EStringBase()
	{
		if (m_data)
			free(m_data);
	}
private:
	T *m_data;
};
class Rva003C649EString : public Rva003C649EStringBase<char>
{
};
struct Rva003C649E
{
	char m_pad00[4];
	Rva003C649EString m_04;
	char m_pad08[8];
	Rva003C649EString m_10;
	char m_pad14[8];
	Rva003C649EString m_1C;
	char m_pad20[12];
	Rva003C649EString m_2C;
	~Rva003C649E();
};
Rva003C649E::~Rva003C649E()
{
}
