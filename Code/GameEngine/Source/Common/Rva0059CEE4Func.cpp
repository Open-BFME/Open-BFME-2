// cl: -GR- -EHsc-
// ?rva0059CEE4@Rva0059CEE4@@QAEMHPAXPAPAX@Z @0x0059CEE4 75B evidence: this+0xc int to float; callee 0x004FFB00 pin; float globals 007C26F0 00BC7508 00BC8980; callers 0x0059D453 0x0059D58E
extern float g_Va007C26F0;
extern float g_00BC7508;
extern float g_00BC8980;
struct Rva004FFB00Hero;
class Rva0059CFAACallee
{
public:
	Rva004FFB00Hero *rva004FFB00(int playerId, int *territory, int *distance);
};
class Rva0059CEE4
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
public:
	float rva0059CEE4(int a1, void *a2, void **a3);
};
float Rva0059CEE4::rva0059CEE4(int a1, void *a2, void **a3)
{
	int out = 0;
	float y = (float)m_0c;
	int *info = (int *)((char *)*a3 + 0x14);
	((Rva0059CFAACallee *)a2)->rva004FFB00(a1, info, &out);
	float x = (float)out * g_Va007C26F0;
	return (g_00BC7508 - x * x) * (*(const volatile float *)&y * g_00BC8980);
}
