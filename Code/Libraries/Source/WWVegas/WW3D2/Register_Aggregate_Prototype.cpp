// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva0014CE67_Prototype
{
public:
	Rva0014CE67_Prototype(const char *name, int first, int second);

private:
	unsigned char m_data[0x24];
};

bool Render_Obj_Exists(const char *name);
void Add_Prototype(void *prototype);

void Register_Aggregate_Prototype(const char *name, int first, int second)
{
	if (name && !Render_Obj_Exists(name)) {
		Add_Prototype(new Rva0014CE67_Prototype(name, first, second));
	}
}
