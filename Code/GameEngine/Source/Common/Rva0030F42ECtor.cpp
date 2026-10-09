// cl: /O1 /arch:SSE /MD /DNDEBUG
//
// ??0Rva0030F42E@@QAE@H@Z retail 0x0030F404 (42B, RET 4). Constructor of Rva0030F42E, the class
// whose destructor is 0x0030F42E (frees +0x04) and whose vtable 0x00C09834 holds that destructor,
// the setter 0x0030F3BF and a third virtual 0x0030F2CB. The rowed 16-byte member constructor
// 0x00330757 builds the 0x10-byte object at +0x04 (modelled as a non-polymorphic base: the
// retail order is call, then the int argument at +0x14, float 0 at +0x18, byte 0 at +0x1C, the
// vtable store sitting between the first two). The argument is an opaque 32-bit value.
// Other units view this class for the destructor and setter; this one only needs the
// constructor, so it declares the two virtuals it must emit a table for.
class Rva00330757Member
{
	char m_pad[0x10];
public:
	Rva00330757Member();
};

class Rva0030F42E:public Rva00330757Member
{
public:
 virtual ~Rva0030F42E();
 virtual void rva0030F3BF(float);
 int m_14;float m_18;bool m_1C;
 Rva0030F42E(int arg);
};
Rva0030F42E::Rva0030F42E(int arg):Rva00330757Member(),m_14(arg),m_18(0),m_1C(false){}
