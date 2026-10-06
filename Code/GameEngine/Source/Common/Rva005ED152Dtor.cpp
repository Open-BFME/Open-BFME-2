// cl: /MD
// ??1Rva005ED152@@MAE@XZ @0x005ED152 11B: derived dtor stores vtable 0x008785B8 then tail-jmps to base 0x005ECAD0. Evidence: mov [ecx] 0x008785B8 then jmp ??1Rva005ECA91@@MAE@XZ rowed; caller 0x005ED139; chain from 0x005ECAD0; sibling Rva005ECFE4Dtor same shape.
extern const void *const g_00C785B8[];

class Rva005ECA91
{
protected:
	virtual ~Rva005ECA91();
};

class Rva005ED152 : public Rva005ECA91
{
protected:
	virtual ~Rva005ED152();
};

Rva005ED152::~Rva005ED152()
{
	*(const void **)this = g_00C785B8;
}
