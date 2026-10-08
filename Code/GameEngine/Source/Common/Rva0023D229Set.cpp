// cl: /MD
// ?Set@Rva0023D229@@QAEXH@Z, retail 0x0023D229, 35 bytes.
// mov eax,[esp+4] test jl cmp 8 jge mov edx,[global] imul 0x1c mov edx,[edx+0x40] mov [eax+ecx+0x1cc],edx ret 4.
// Evidence: unlock lane; thiscall ret 4 with 0-7 guard; global 0x009FE78C same as 0x0023D339.
struct Rva0023D229Global
{
	char m_00[64];
	void *m_40;
};
extern class GameLogic *TheGameLogic;
class Rva0023D229
{
public:
	void Set(int index);
	void rva0023D24C(int index);
	char m_00[460];
	void *m_arr[8][7];
};
void Rva0023D229::Set(int index)
{
	if (index < 0)
		return;
	if (index >= 8)
		return;
	Rva0023D229Global *g = (*(Rva0023D229Global **)&TheGameLogic);
	int off = index * 28;
	void *p = g->m_40;
	*(void **)((char *)this + 460 + off) = p;
}
void Rva0023D229::rva0023D24C(int index)
{
	if (index < 0)
		return;
	if (index >= 8)
		return;
	Rva0023D229Global *g = (*(Rva0023D229Global **)&TheGameLogic);
	int off = index * 28;
	void *p = g->m_40;
	*(void **)((char *)this + 464 + off) = p;
}
