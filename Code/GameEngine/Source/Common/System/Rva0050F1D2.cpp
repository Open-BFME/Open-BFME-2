// cl: /EHsc
// ?rva0050F1D2@BFME2WideConcatPair@@QBEHXZ @0x0050F1D2
// (13B): returns totalLength() plus int at +0xc; pinned callee 0x002198C8.
// Identity via BFME2WideConcatPair totalLength pin plus same-page sibling
// Rva0050F0AB /O1 /EHsc; no callers, honest address name.

class BFME2WideConcatPair
{
public:
	int totalLength() const;
	int rva0050F1D2() const;
private:
	unsigned char m_pad[0xc];
	int m_0c;
};

int BFME2WideConcatPair::rva0050F1D2() const
{
	return totalLength() + m_0c;
}
