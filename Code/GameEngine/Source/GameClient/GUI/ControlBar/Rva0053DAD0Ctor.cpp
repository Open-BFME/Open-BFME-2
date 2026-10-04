// cl: /O1 /MD
// ??0Rva0053DAD0@@QAE@H@Z @0x0053DAD0 22B
// __thiscall ctor storing vtable g_00C69310 plus 0 at +4 plus int arg at +8.
// Evidence: mov eax ecx plus mov ecx esp+4 plus and eax+4 0 plus mov eax vtable
// plus mov eax+8 ecx plus ret 4; caller at 0x0031B812; vtable no name yet.
extern const void *const g_00C69310[];

class Rva0053DAD0
{
public:
	Rva0053DAD0(int value);
private:
	char m_pad[12];
};

Rva0053DAD0::Rva0053DAD0(int value)
{
	*(const void **)this = g_00C69310;
	*(int *)((char *)this + 4) = 0;
	*(int *)((char *)this + 8) = value;
}
