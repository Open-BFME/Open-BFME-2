// cl: /MD
// ?bfmeAskRV@BfmeMemberRV@@QAE_NXZ @0x002AA231 (20B)
// Returns true when bytes at +0x33a and +0x734 are zero.
// Evidence 40+ callers plus BfmeThingRV picker plus two pins.
class BfmeMemberRV
{
public:
	bool bfmeAskRV();
private:
	char m_pad[0x33a];
	bool m_33a;
	char m_pad2[0x734 - 0x33a - 1];
	bool m_734;
};
bool BfmeMemberRV::bfmeAskRV()
{
	return !m_33a && !m_734;
}
