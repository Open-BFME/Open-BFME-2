// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs
//
// Thiscall forwarder: copies the 8-byte payload behind the second argument
// into a 12-byte stack object (vtable 0x00C74DFC, empty inline virtual dtor
// whose shared body is 0x002BEDA4) and forwards (arg, &obj) to the callee
// 0x002BFDE6 with the incoming this unchanged. The callee's identity and the
// class names are address-derived; layout is read from the retail stores.
class Rva005CBB0AObj
{
public:
	virtual ~Rva005CBB0AObj() {}
	int m_a;
	int m_b;
	Rva005CBB0AObj(const int *src) : m_a(src[0]), m_b(src[1]) {}
};
class Rva005CBB0A
{
public:
	void rva002BFDE6(int arg, Rva005CBB0AObj *obj);
	void rva005CBB0A(int arg, const int *src);
};
void Rva005CBB0A::rva005CBB0A(int arg, const int *src)
{
	Rva005CBB0AObj obj(src);
	rva002BFDE6(arg, &obj);
}
