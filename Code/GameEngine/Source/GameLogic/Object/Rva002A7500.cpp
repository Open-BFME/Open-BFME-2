// cl: /O1 /DNDEBUG /MD
// ?rva002A7500@Rva002A7500@@QAEXPAX@Z 19B @0x002A7500: thiscall adding Rva002A74C3Get result to +0xC.
// Evidence: chain lane calls 0x002A74C3 just landed rowed; caller 0x002A9B49 passes one arg ret4 void; prev Rva002A74C3Get next Rva002A752FDestroy share /O1 /DNDEBUG /MD; LINK BONUS via 0x002A9B35.
class Rva002A7500
{
public:
	void rva002A7500(void *a);
private:
	char m_pad[0xC];
	int m_val0C;
};
int __stdcall Rva002A74C3Get(void *a);
void Rva002A7500::rva002A7500(void *a)
{
	m_val0C += Rva002A74C3Get(a);
}
