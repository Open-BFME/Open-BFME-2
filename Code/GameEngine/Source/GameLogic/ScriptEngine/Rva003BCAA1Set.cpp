// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BCAA1Set@@YGXM@Z @0x003BCAA1 57B: script float sets TheGameLogic+0xa0 scaled or -1.
// Evidence: xorps xmm0 comiss xmm0,[esp+4] jbe else mov eax,[0xDFE78C]=TheGameLogic or [eax+0xa0],-1 jmp ret; else cvtsi2ss xmm0,[0xDBA4E4]=g_Va00DBA4E4 mulss xmm0,[esp+4] mov ecx,[TheGameLogic] cvttss2si eax,xmm0 mov [ecx+0xa0],eax ret 4; caller 0x003CD7FB; sibling Rva003BBF51Set same comiss movss stdcall float shape.
class GameLogic
{
public:
	char m_pad[0xA0];
	int m_A0;
};
extern GameLogic *TheGameLogic;
extern int g_Va00DBA4E4;

void __stdcall Rva003BCAA1Set(float f)
{
	if (0.0f > f)
		TheGameLogic->m_A0 |= -1;
	else
		TheGameLogic->m_A0 = (int)((float)g_Va00DBA4E4 * f);
}
