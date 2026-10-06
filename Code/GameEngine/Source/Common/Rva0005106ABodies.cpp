// cl: /O1 /DNDEBUG /MD
class Rva0005F279Elem
{
public:
	bool rva00051038();
	bool rva0005106A();
	unsigned char m_byte0;
	unsigned char m_pad0[0xF];
	unsigned char m_byte10;
};

bool Rva0005F279Elem::rva0005106A()
{
	if (m_byte0 != 0)
		return false;
	if (m_byte10 == 0)
		return false;
	return rva00051038();
}
