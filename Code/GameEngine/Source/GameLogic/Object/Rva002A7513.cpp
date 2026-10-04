// cl: /O1 /DNDEBUG /MD
// ?rva002A7513@Rva002A7513@@QAEXPAX@Z 19B @0x002A7513: thiscall subtracting Rva002A74C3Get result from +0xC.
// Evidence: chain lane calls 0x002A74C3 rowed sibling of 0x002A7500 add-variant; caller 0x002A9B6C passes one arg ret4 void; prev Rva002A7500 next Rva002A752FDestroy share /O1 /DNDEBUG /MD; LINK BONUS via 0x002A9B58.
class Rva002A7513
{
public:
	void rva002A7513(void *a);
private:
	char m_pad[0xC];
	int m_val0C;
};
int __stdcall Rva002A74C3Get(void *a);
void Rva002A7513::rva002A7513(void *a)
{
	m_val0C -= Rva002A74C3Get(a);
}
