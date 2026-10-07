// cl: /O1 /MD
//
// ?rva00405315@Rva00405315@@QAEXXZ @0x00405315 34B (tentative void).
// Flag-gated chain: if the +0x134 byte is set run the no-arg members at
// 0x00405094 and 0x00405258 then tail to 0x00404A29, else return.
class Rva00405315
{
public:
	void rva00405315();
	void rva00405094();
	void rva00405258();
	void rva00404A29();
private:
	char m_pad00[0x134];
	char m_134;
};

void Rva00405315::rva00405315()
{
	if (m_134 != 0)
	{
		rva00405094();
		rva00405258();
		rva00404A29();
	}
}
