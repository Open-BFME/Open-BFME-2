// cl: /O1 /MD
// ?rva0040F7E5@BfmeY1038@@QAEXXZ @0x0040F7E5 24B: member state advance 3 to 4
// through the 3-zero helper 0x0040F497. Evidence: same +0x2c state word as
// rowed Rva0040D380Get 0x0040D380; helper read from REL32.
class BfmeY1038
{
public:
	void rva0040F7E5();

private:
	char m_pad[0x2C];
	int m_2C;
};

void __stdcall rva0040F497(int a, int b, int c); // pinned retail 0x0040F497
BfmeY1038 *__stdcall bfmeFind1038(int key);

void BfmeY1038::rva0040F7E5()
{
	if (m_2C == 3) {
		m_2C = 4;
		rva0040F497(0, 0, 0);
	}
}

void __stdcall Rva0040FAFEAdvance(int key)
{
	BfmeY1038 *p = bfmeFind1038(key);
	if (!p)
		return;
	p->rva0040F7E5();
}
