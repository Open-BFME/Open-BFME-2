// cl: /O1 /MD
// ?rva0056B76D@Rva0056B76D@@QAE_NI@Z, 0x0056B76D, 51B: predicate over +0x50..+0x53 consuming the low byte of a full flags word. Evidence: leaf, ret 4, test 4/1/2 chain, caller 0x005C4B4D.
// Native caller5C4B41 pushes full dword flagsB8; native provider consumes only
// its low byte. Preserve both facts with full-width ABI and explicit low-byte
// local. Whole existing51B provider remains exact; no alternate-name alias.
class Rva0056B76D
{
public:
	bool rva0056B76D(unsigned int flags);
private:
	char m_pad[0x50];
	unsigned char m_50;
	unsigned char m_51;
	unsigned char m_52;
	unsigned char m_53;
};

bool Rva0056B76D::rva0056B76D(unsigned int flags)
{
	unsigned char bits=(unsigned char)flags;
	if (bits & 4)
		return false;
	if (bits & 1) {
		if (m_52 != 0)
			return false;
	} else {
		if (m_53 != 0)
			return false;
	}
	if (bits & 2) {
		if (m_50 != 0)
			return false;
	} else {
		if (m_51 != 0)
			return false;
	}
	return true;
}
