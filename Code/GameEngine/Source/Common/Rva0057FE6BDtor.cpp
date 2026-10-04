// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva0057FE6B@@UAE@XZ @0x0057FE6B 99B
// Evidence: unlock lane, vtable store 0x0086F64C, +0x64 virtual slot2 f2(0) with delete like neighbour 0x0057FECE, +0x58 ReleaseTreeHintRef00217D4C row 0x0007DEEF, base dtor pin 0x005248D0, callers 0x00442251 0x0057FFA0.
struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
void operator delete(void *p);
class Rva005248D0
{
public:
	virtual ~Rva005248D0();
};
class Rva0057FE6B_P64
{
public:
	virtual ~Rva0057FE6B_P64();
	virtual void f0();
	virtual void *f2(int x);
};
struct Rva0057FE6B_Holder58
{
	TargetRef00217D4C *m_ptr;
	__forceinline ~Rva0057FE6B_Holder58() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
struct Rva0057FE6B_Holder64
{
	Rva0057FE6B_P64 *m_ptr;
	__forceinline ~Rva0057FE6B_Holder64()
	{
		void *p;
		if (m_ptr != 0) {
			p = m_ptr->f2(0);
		} else {
			p = 0;
		}
		::operator delete(p);
		m_ptr = 0;
	}
};
class Rva0057FE6B : public Rva005248D0
{
public:
	virtual ~Rva0057FE6B();
private:
	char m_pad0[84];
	Rva0057FE6B_Holder58 m_58;
	char m_pad1[8];
	Rva0057FE6B_Holder64 m_64;
};
Rva0057FE6B::~Rva0057FE6B()
{
}
