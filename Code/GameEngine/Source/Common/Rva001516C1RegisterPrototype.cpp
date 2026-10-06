// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?Rva001516C1RegisterPrototype@@YAXPBD@Z at 0x001516C1 (86B). Register
// helper twin of Register_Aggregate_Prototype 0x0014D01C and HTree register
// 0x0017FD2F: skips null names and names already present via Render_Obj_Exists
// row 0x0061F0D0, otherwise news a 0x1c-byte Rva00151632 via ctor row
// 0x001515CA and hands it to Add_Prototype row 0x0061EF90. Called from
// 0x0012CD94 in 0x0012CB67.

class Rva00151632
{
public:
	Rva00151632(const char *name);

private:
	unsigned char m_data[0x1c];
};

bool Render_Obj_Exists(const char *name);
void Add_Prototype(void *prototype);

void Rva001516C1RegisterPrototype(const char *name)
{
	if (name && !Render_Obj_Exists(name)) {
		Add_Prototype(new Rva00151632(name));
	}
}
