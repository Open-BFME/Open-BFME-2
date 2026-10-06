// cl: /MD
// ?rva000728E2@Rva000728E2@@QAEXXZ, RVA 0x000728E2, 14B. Small clear wrapper:
// if the BfmeResetTextureRef holder at +0x1c is non-null tail-jump to its
// clear (rowed 0x0004D75B). Evidence: 7 callers pass holder owners at
// 0x668B2/0x668CA/0x72D20/0x73134/0x73BAB/0x73C16/0x7441B; sibling 0x728F0
// addresses the same +0x1c holder with +0x20/+0x24 and flag +0x35.
struct BfmeResetTextureRef
{
	void *pointer;
	void clear();
};
class Rva000728E2
{
public:
	void rva000728E2();
private:
	char m_pad[0x1c];
	BfmeResetTextureRef m_ref;
};
void Rva000728E2::rva000728E2()
{
	if (m_ref.pointer)
		m_ref.clear();
}
