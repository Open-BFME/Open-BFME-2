// cl: /O1 /MD
// ?rva002BE7BB@Rva002BE7BB@@QAE_NXZ @0x002BE7BB 32B: returns m_110==0||6||1||5. Evidence: caller 0x002BF4CF plus prev 0x002BE7AE plus next 0x002BE7DB.
class Rva002BE7BB
{
public:
	bool rva002BE7BB();
private:
	char m_pad[0x110];
	int m_110;
};

bool Rva002BE7BB::rva002BE7BB()
{
	return m_110 == 0 || m_110 == 6 || m_110 == 1 || m_110 == 5;
}
