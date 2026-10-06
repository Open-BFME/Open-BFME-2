// cl: /MD
// ?Rva0029B4F9Init@@YAXXZ @0x0029B4F9 67B.
// Chain from 0x0029B2E7: local 0x20 zeroed via that row, then two virtuals on global 0xDFEA3C slots 0x170 and 0xC8.
// Caller at 0x0042BBF9. Free function void().
extern class View *TheTacticalView;

class Rva0029B2E7 {
public:
	Rva0029B2E7 *rva0029B2E7();
	unsigned char m_0;
	char m_pad[3];
	float m_4;
	float m_8;
	float m_C;
	float m_10;
	float m_14;
	float m_18;
	float m_1C;
};
class Rva0029B4F9Holder {
public:
	virtual void s000();
	virtual void s001();
	virtual void s002();
	virtual void s003();
	virtual void s004();
	virtual void s005();
	virtual void s006();
	virtual void s007();
	virtual void s008();
	virtual void s009();
	virtual void s010();
	virtual void s011();
	virtual void s012();
	virtual void s013();
	virtual void s014();
	virtual void s015();
	virtual void s016();
	virtual void s017();
	virtual void s018();
	virtual void s019();
	virtual void s020();
	virtual void s021();
	virtual void s022();
	virtual void s023();
	virtual void s024();
	virtual void s025();
	virtual void s026();
	virtual void s027();
	virtual void s028();
	virtual void s029();
	virtual void s030();
	virtual void s031();
	virtual void s032();
	virtual void s033();
	virtual void s034();
	virtual void s035();
	virtual void s036();
	virtual void s037();
	virtual void s038();
	virtual void s039();
	virtual void s040();
	virtual void s041();
	virtual void s042();
	virtual void s043();
	virtual void s044();
	virtual void s045();
	virtual void s046();
	virtual void s047();
	virtual void s048();
	virtual void s049();
	virtual void s050(float *p, int one, float a, float b);
	virtual void s051();
	virtual void s052();
	virtual void s053();
	virtual void s054();
	virtual void s055();
	virtual void s056();
	virtual void s057();
	virtual void s058();
	virtual void s059();
	virtual void s060();
	virtual void s061();
	virtual void s062();
	virtual void s063();
	virtual void s064();
	virtual void s065();
	virtual void s066();
	virtual void s067();
	virtual void s068();
	virtual void s069();
	virtual void s070();
	virtual void s071();
	virtual void s072();
	virtual void s073();
	virtual void s074();
	virtual void s075();
	virtual void s076();
	virtual void s077();
	virtual void s078();
	virtual void s079();
	virtual void s080();
	virtual void s081();
	virtual void s082();
	virtual void s083();
	virtual void s084();
	virtual void s085();
	virtual void s086();
	virtual void s087();
	virtual void s088();
	virtual void s089();
	virtual void s090();
	virtual void s091();
	virtual void s092(Rva0029B2E7 *p);
};
void Rva0029B4F9Init()
{
	Rva0029B2E7 tmp;
	tmp.rva0029B2E7();
	(*(Rva0029B4F9Holder **)&TheTacticalView)->s092(&tmp);
	(*(Rva0029B4F9Holder **)&TheTacticalView)->s050(&tmp.m_4, 1, 0.0f, 0.0f);
}
