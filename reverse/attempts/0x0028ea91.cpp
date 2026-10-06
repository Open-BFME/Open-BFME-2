// ?rva0028EA91@Object@@QAE_NABVAsciiString@@H@Z
// partial score=0.85 date=2026-10-06
// cl: /O1 /arch:SSE /G7 /MD
//
// ?rva0028EA91@Object@@QAE_NABVAsciiString@@H@Z @0x0028EA91 177B, the name
// five matched callers pin (PassiveAreaEffectBehavior 0x00484A08 among them).
// A one-character name is refused. Otherwise the +0x250 module's slot-31
// holder takes it directly through its slot 118 (name, 0, value); failing
// that the object's attribute-modifier pool update takes it, bracketed by
// the controlling player's notify pair 0x002A9B58/0x002A9B35 when the
// template's +0x61C count is positive. Region flags.

class AsciiString
{
public:
	int getLength() const { return m_text ? *(const unsigned short *)(m_text + 4) : 0; }
private:
	const char *m_text;
};

class Rva0028EA91Holder
{
public:
	virtual void slot000();
	virtual void slot001();
	virtual void slot002();
	virtual void slot003();
	virtual void slot004();
	virtual void slot005();
	virtual void slot006();
	virtual void slot007();
	virtual void slot008();
	virtual void slot009();
	virtual void slot010();
	virtual void slot011();
	virtual void slot012();
	virtual void slot013();
	virtual void slot014();
	virtual void slot015();
	virtual void slot016();
	virtual void slot017();
	virtual void slot018();
	virtual void slot019();
	virtual void slot020();
	virtual void slot021();
	virtual void slot022();
	virtual void slot023();
	virtual void slot024();
	virtual void slot025();
	virtual void slot026();
	virtual void slot027();
	virtual void slot028();
	virtual void slot029();
	virtual void slot030();
	virtual void slot031();
	virtual void slot032();
	virtual void slot033();
	virtual void slot034();
	virtual void slot035();
	virtual void slot036();
	virtual void slot037();
	virtual void slot038();
	virtual void slot039();
	virtual void slot040();
	virtual void slot041();
	virtual void slot042();
	virtual void slot043();
	virtual void slot044();
	virtual void slot045();
	virtual void slot046();
	virtual void slot047();
	virtual void slot048();
	virtual void slot049();
	virtual void slot050();
	virtual void slot051();
	virtual void slot052();
	virtual void slot053();
	virtual void slot054();
	virtual void slot055();
	virtual void slot056();
	virtual void slot057();
	virtual void slot058();
	virtual void slot059();
	virtual void slot060();
	virtual void slot061();
	virtual void slot062();
	virtual void slot063();
	virtual void slot064();
	virtual void slot065();
	virtual void slot066();
	virtual void slot067();
	virtual void slot068();
	virtual void slot069();
	virtual void slot070();
	virtual void slot071();
	virtual void slot072();
	virtual void slot073();
	virtual void slot074();
	virtual void slot075();
	virtual void slot076();
	virtual void slot077();
	virtual void slot078();
	virtual void slot079();
	virtual void slot080();
	virtual void slot081();
	virtual void slot082();
	virtual void slot083();
	virtual void slot084();
	virtual void slot085();
	virtual void slot086();
	virtual void slot087();
	virtual void slot088();
	virtual void slot089();
	virtual void slot090();
	virtual void slot091();
	virtual void slot092();
	virtual void slot093();
	virtual void slot094();
	virtual void slot095();
	virtual void slot096();
	virtual void slot097();
	virtual void slot098();
	virtual void slot099();
	virtual void slot100();
	virtual void slot101();
	virtual void slot102();
	virtual void slot103();
	virtual void slot104();
	virtual void slot105();
	virtual void slot106();
	virtual void slot107();
	virtual void slot108();
	virtual void slot109();
	virtual void slot110();
	virtual void slot111();
	virtual void slot112();
	virtual void slot113();
	virtual void slot114();
	virtual void slot115();
	virtual void slot116();
	virtual void slot117();
	virtual void apply(const AsciiString &name, int zero, int value);	// slot 118
};

class Rva0028EA91Module
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual Rva0028EA91Holder *getHolder();	// slot 31
};

class AttributeModifierPoolUpdate
{
public:
	bool rva00403E72(const AsciiString &name, int value);	// 0x00403E72
};

struct Rva002A7588In;
class Rva002A9B58
{
public:
	void rva002A9B58(Rva002A7588In *obj);		// 0x002A9B58
	void rva002A9B35(Rva002A7588In *obj);		// 0x002A9B35
};

class Player;

struct ObjectTemplateView
{
	char m_pad00[0x61C];
	int m_61C;
};

class Object
{
public:
	bool rva0028EA91(const AsciiString &name, int value);
	Player *getControllingPlayer() const;		// 0x0028AFA9
private:
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate();	// 0x0028BDD7

	char m_pad00[4];
	ObjectTemplateView *m_template;				// +0x04
	char m_pad08[0x250 - 8];
	Rva0028EA91Module *m_250;					// +0x250
};

bool Object::rva0028EA91(const AsciiString &name, int value)
{
	if (name.getLength() == 1)
		return false;
	Rva0028EA91Holder *holder = m_250 ? m_250->getHolder() : 0;
	if (holder) {
		holder->apply(name, 0, value);
		return true;
	}
	AttributeModifierPoolUpdate *pool = findAttributeModifierPoolUpdate();
	if (pool == 0)
		return false;
	Rva002A9B58 *player = (Rva002A9B58 *)getControllingPlayer();
	bool notify = player != 0 && m_template->m_61C > 0;
	if (notify)
		player->rva002A9B58((Rva002A7588In *)this);
	if (!pool->rva00403E72(name, value))
		return false;
	if (notify)
		player->rva002A9B35((Rva002A7588In *)this);
	return true;
}
