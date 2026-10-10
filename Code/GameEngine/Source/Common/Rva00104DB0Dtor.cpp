// cl: /MD /EHsc
// ??1Rva00104DB0@@UAE@XZ, retail 0x00104DB0, 54 bytes.
// Evidence: leaf lane pin dtor, callers in Rva00104E03Dtor and deleting dtor, callee Render2DSentenceClass dtor pin 0x00157C70.
class Render2DSentenceClass
{
public:
	~Render2DSentenceClass();
};

class Rva00104DB0Base
{
public:
	Rva00104DB0Base();
	virtual ~Rva00104DB0Base() {}
};
// ??0Rva00104DB0Base@@QAE@XZ @0x00104DA7 9B: the default constructor, storing the
// class's own vtable (VA 0x00BCF7E8) and returning this.
Rva00104DB0Base::Rva00104DB0Base()
{
}

class Rva00104DB0 : public Rva00104DB0Base
{
public:
	virtual ~Rva00104DB0();
private:
	Render2DSentenceClass m_sentence;
};

Rva00104DB0::~Rva00104DB0()
{
}
