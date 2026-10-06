// cl: /MD
// ?rva0056B76D@Rva0056B76D@@QAE_NE@Z, 0x0056B76D, 51B: honest predicate over +0x50..+0x53 with flags byte. Evidence: leaf, ret 4, test 4/1/2 chain, caller 0x005C4B4D.
class Rva0056B76D
{
public:
	bool rva0056B76D(unsigned char flags);
private:
	char m_pad[0x50];
	unsigned char m_50;
	unsigned char m_51;
	unsigned char m_52;
	unsigned char m_53;
};

bool Rva0056B76D::rva0056B76D(unsigned char flags)
{
	if (flags & 4)
		return false;
	if (flags & 1) {
		if (m_52 != 0)
			return false;
	} else {
		if (m_53 != 0)
			return false;
	}
	if (flags & 2) {
		if (m_50 != 0)
			return false;
	} else {
		if (m_51 != 0)
			return false;
	}
	return true;
}
