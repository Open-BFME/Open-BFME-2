// cl: /MD
class Rva005248D0
{
public:
	unsigned char rva002D2C12() const;
	unsigned char rva002D2C18() const;
private:
	char m_pad[0x24];
	union {
		unsigned char m_flags;
		struct {
			unsigned char m_b0 : 1;
			unsigned char m_b1 : 1;
			unsigned char m_b2 : 1;
			unsigned char m_rest : 5;
		};
	};
};

unsigned char Rva005248D0::rva002D2C12() const
{
	return m_b0;
}

unsigned char Rva005248D0::rva002D2C18() const
{
	return m_b2;
}
