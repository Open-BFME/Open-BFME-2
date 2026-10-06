// cl: /DNDEBUG /MD /GX-
// ??0Rva00577838@@QAE@H@Z @0x00577863 46B: ctor stores vtable 0x00C6E978 then news 0x10 bytes and constructs Rva00577846 with outer this plus int arg storing result at +4. Evidence: calls rowed 0x00577846 plus rowed new 0x0002FDA0 plus caller 0x0042C9F8 plus dtor 0x00577838 plus holder dtor 0x00577010.
class Rva00577846;

class Rva00577838
{
public:
	virtual ~Rva00577838();
	Rva00577838(int b);
private:
	Rva00577846 *m_04;
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

Rva00577838::Rva00577838(int b)
{
	m_04 = new Rva00577846(this, b);
}
