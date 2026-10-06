// cl: /MD
// ?rva000724C7@Rva000724AE@@QAEHXZ, RVA 0x000724C7, 16B. Non-null check on
// +0x08/+0x0c pointers: returns 1 if either is non-null else 0. Evidence:
// sits between 0x000724AE and 0x000724D7 of the same class Rva000724AE,
// same // cl: /O1 /MD; caller at 0x0007256B.
class Rva000724AE
{
public:
	int rva000724C7();
private:
	int m_00;
	int m_04;
	void *m_08;
	void *m_0c;
};
int Rva000724AE::rva000724C7()
{
	return m_08 != 0 || m_0c != 0;
}
