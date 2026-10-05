// cl: /O1 /DNDEBUG /MD
// ??0Rva00577846@@QAE@PAVRva00577838@@H@Z @0x00577846 29B: stores vtable 0x00C6E980 at [this] plus args at +4/+8 plus byte 0 at +0xc. Evidence: caller 0x00577863 passes outer this and outer arg. ret 8.
class Rva00577838
{
public:
	virtual ~Rva00577838();
};

class Rva00577846
{
public:
	virtual ~Rva00577846();
	Rva00577846(Rva00577838 *a, int b);
private:
	Rva00577838 *m_04;
	int m_08;
	bool m_0c;
};

Rva00577846::Rva00577846(Rva00577838 *a, int b) : m_04(a), m_08(b), m_0c(false)
{
}
