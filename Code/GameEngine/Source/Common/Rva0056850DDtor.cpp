// cl: /O1 /arch:SSE /G7 /MD
// ??1Rva0056850D@@QAE@XZ @0x0056850D 26B: public non-virtual dtor deletes
// m_value (Rva0056820D pin 0x0056820D) via operator delete 0x0002FD60 then
// nulls it; caller 0x0056860C in Rva005685EE dtor; LINK BONUS name; real size
// 26B of served 127B (rest is separate ctor at 0x00568527).
class Rva0056820D
{
public:
	~Rva0056820D();
};

class Rva0056850D
{
public:
	~Rva0056850D();

private:
	Rva0056820D *m_value;
};

Rva0056850D::~Rva0056850D()
{
	Rva0056820D *tmp = m_value;
	m_value = 0;
	delete tmp;
}
