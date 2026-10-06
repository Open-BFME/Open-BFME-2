// cl: /MD
// ??1Rva005ECFE4@@MAE@XZ @ 0x005ECFE4 (11B): derived dtor stores vtable 0x008785B4 then tail-jmps to base 0x005ECAD0.
// Evidence: mov [ecx] 0x008785B4 then jmp 0x005ECAD0 ??1Rva005ECA91@@MAE@XZ rowed; callers include 0x005ECFC8; chain from 0x005ECAD0.
extern const void *const g_00C785B4[];

class Rva005ECA91
{
protected:
	virtual ~Rva005ECA91();
};

class Rva005ECFE4 : public Rva005ECA91
{
protected:
	virtual ~Rva005ECFE4();
};

Rva005ECFE4::~Rva005ECFE4()
{
	*(const void **)this = g_00C785B4;
}
