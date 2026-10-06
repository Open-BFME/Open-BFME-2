// cl: /MD
// ?rva000EFD77@Rva000EFD77@@QAE_NH@Z @0x000EFD77 41B: Alloc array count times 22 via new[] into plus24 plus count into plus28 with bool success. Evidence: unlock lane sibling Rva000EFDA0Free plus24 plus28 plus caller 0x000F299D plus new[] null-check pop-ecx shape.
void *__cdecl operator new[](unsigned int size);
class Rva000EFD77 {
public:
	bool rva000EFD77(int n);
private:
	char _pad0[0x24];
	char *m_24;
	int m_28;
};
bool Rva000EFD77::rva000EFD77(int n)
{
	m_24 = (char *)::operator new[](n * 22);
	if (m_24 == 0)
		return false;
	m_28 = n;
	return true;
}
