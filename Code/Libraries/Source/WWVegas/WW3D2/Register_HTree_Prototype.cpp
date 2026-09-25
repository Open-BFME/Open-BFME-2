// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// HTree prototype register helper (retail 0x0017FD2F, 92 bytes). Twin of
// Register_Aggregate_Prototype at 0x0014D01C: skips null names and names
// already present (Render_Obj_Exists via the 0x0061F0D0 row), otherwise
// news a 0x24-byte Rva0017FB41_Prototype (ctor row 0x0017FB41) and hands it
// to Add_Prototype (0x0061EF90 row).

class Rva0017FB41_Prototype
{
public:
	Rva0017FB41_Prototype(const char *name, int first, int second);

private:
	unsigned char m_data[0x24];
};

bool Render_Obj_Exists(const char *name);
void Add_Prototype(void *prototype);

void Rva0017FD2F_RegisterPrototype(const char *name, int first, int second)
{
	if (name && !Render_Obj_Exists(name)) {
		Add_Prototype(new Rva0017FB41_Prototype(name, first, second));
	}
}
