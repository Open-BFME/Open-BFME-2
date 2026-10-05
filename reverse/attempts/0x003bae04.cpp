// ?Rva003BAE04@@YAXXZ
// partial score=0.85 date=2026-10-05
// cl: /O1 /arch:SSE
// ?Rva003BAE04@@YAXXZ @0x003BAE04 198B: free averaging BFMERopeDrawable positions with flag 0x43c via list 0x104 to TacticalView slot 0x9c.
// Evidence: ret 0 no args; xorps zero [ebp-0xc]; mov ecx [TheGameClient] call [eax+0x44]; cmp byte [esi+0x43c] je; getPosition row; addss movss sum; mov esi [esi+0x104]; divss g_Va00BBB8D8 count; mulss avg; lea edx [ebp-0xc] push call [eax+0x9c]; caller 0x003CAFFF.
struct Coord3D
{
	float x;
	float y;
	float z;
};
class BFMERopeDrawable
{
public:
	const Coord3D *getPosition() const;
	char m_pad104[0x104];
	BFMERopeDrawable *m_next;
	char m_pad108[0x43C - 0x108];
	bool m_flag;
};
class ClientFrameSubsystem
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual BFMERopeDrawable *s17();
};
extern ClientFrameSubsystem *TheGameClient;
extern float g_Va00BBB8D8;

class TacticalView
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual void s38();
	virtual void s39(const Coord3D *p);
};
extern TacticalView *TheTacticalView;

// ?Rva003BAE04@@YAXXZ present-unmatched
void Rva003BAE04()
{
	float sum[3];
	sum[2] = 0.0f;
	sum[1] = 0.0f;
	sum[0] = 0.0f;
	BFMERopeDrawable *cur = TheGameClient->s17();
	int count = 0;
	while (cur)
	{
		if (cur->m_flag)
		{
			const Coord3D *pos = cur->getPosition();
			sum[0] = pos->x + sum[0];
			sum[1] = pos->y + sum[1];
			sum[2] = pos->z + sum[2];
			++count;
		}
		cur = cur->m_next;
	}
	if (count == 0)
		return;
	float avg = g_Va00BBB8D8 / (float)count;
	sum[0] = avg * sum[0];
	sum[1] = avg * sum[1];
	sum[2] = avg * sum[2];
	TheTacticalView->s39((const Coord3D *)sum);
}
