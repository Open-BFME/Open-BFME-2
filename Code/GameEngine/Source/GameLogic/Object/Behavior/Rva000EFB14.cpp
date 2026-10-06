// cl: /MD
// ?rva000EFB14@Rva000EFB14@@QAEPAXPAXH@Z @0x000EFB14 27B: Ternary pointer-or-table select with offset 0x9000 array. Evidence: unlock lane plus 4 callers in 0x000F4017 and 0x000F4AB7 plus test-jne-field shape.
struct FieldAt10 { char _p[16]; void *p10; };
class Rva000EFB14 {
public:
	void *rva000EFB14(void *a, int b);
private:
	char _pad0[36864];
	void *m_tab[1];
};
void *Rva000EFB14::rva000EFB14(void *a, int b)
{
	return a == 0 ? m_tab[b] : ((FieldAt10 *)a)->p10;
}
