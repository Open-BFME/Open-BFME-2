// cl: /MD
// ?rva001EB74B@Rva001EB74B@@QAE_NPAURva001EB6A5Out@@@Z, retail 0x001EB74B, 17 bytes.
// Chain from 0x001EB6A5: null-check wrapper over rowed 0x001EB6A5, if ptr at +0x10
// is null return false else tail-jmp to LinearCampaign::fillCampaignMenuContent forwarding out.
// Evidence: tail call to just-landed row, caller 0x00521560, prev Rva001EB73CCheck
// same null-wrapper shape.
struct Rva001EB6A5Out;
class LinearCampaign
{
public:
	bool fillCampaignMenuContent(Rva001EB6A5Out *out);
};

class Rva001EB74B
{
public:
	bool rva001EB74B(Rva001EB6A5Out *out);
private:
	char m_pad[0x10];
	LinearCampaign *m_ptr;
};

bool Rva001EB74B::rva001EB74B(Rva001EB6A5Out *out)
{
	if (m_ptr)
		return m_ptr->fillCampaignMenuContent(out);
	return false;
}
