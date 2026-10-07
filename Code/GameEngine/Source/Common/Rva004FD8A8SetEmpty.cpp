// cl: /O1 /arch:SSE /G7 /MD
// ?rva004FCA90@Rva004FD8A8Set@@QAE_NXZ @0x004FCA90 12B empty check begin==end.
// Evidence: caller 0x0057DD3C in AptMapPreview::rva0057DB97 tests result before 0x004FD8A8; offsets +0x38/+0x3c match Rva004FD6F9 begin/end.
class Rva004FD8A8Set
{
	unsigned char m_pad00[0x38];
	unsigned int m_38;
	unsigned int m_3c;
public:
	bool rva004FCA90();
};

bool Rva004FD8A8Set::rva004FCA90()
{
	return m_38 == m_3c;
}
