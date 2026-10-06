// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??1Rva005D1129Pointer@@QAE@XZ @0x005EC4AF 7B: chain from 0x005EC46F.
// Forwarder: loads +0 and tail-runs rowed ?rva005EC46F@Rva005EC46F@@QAEXXZ.
// Pin proves the dtor name; layout (one pointer at +0) follows the caller's
// lea edi,[esi+8] use in ?rva005D1129@Rva005D1129@@QAEXXZ.

class Rva005EC46F
{
public:
	void rva005EC46F();
};

class Rva005D1129Pointer
{
public:
	~Rva005D1129Pointer();
private:
	Rva005EC46F *m_ptr;
};

Rva005D1129Pointer::~Rva005D1129Pointer()
{
	m_ptr->rva005EC46F();
}
