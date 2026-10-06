// ?clear@Rva0041F9EE@@QAEPAXXZ
// partial score=0.75 date=2026-10-06
// cl: /O1 /MD
// ?clear@Rva0041F9EE@@QAEPAXXZ @0x0041F9EE 25B
class Rva0041F9EE
{
public:
	void *clear();
private:
	int m_00;
	int m_04;
};
void *Rva0041F9EE::clear()
{
	m_00 = 0;
	struct Zero
	{
		int v;
	};
	Zero z = { 0 };
	m_04 = z.v;
	return this;
}
