// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva00171780@MeshModelClass@@QAEXXZ 0x00171780 11B chain calls 0x0015B8C0 loads [ecx+0x94] then jmp
class MeshMatDescClass
{
public:
	void rva0015B8C0();
};

class MeshModelClass
{
public:
	void rva00171780();
	char m_pad[0x94];
	MeshMatDescClass *m_desc;
};

void MeshModelClass::rva00171780()
{
	m_desc->rva0015B8C0();
}
