// cl: /DNDEBUG /MD /EHsc
// ?rva0028B842@Object@@QBEMXZ, retail 0x0028B842, 25 bytes.
// Object float wrapper over the +0x250 provider: when null returns the shared
// 1.0f at 0x00BBB8D8, else tail-forwards to the provider vtable slot 0xD4.
// Evidence: caller at 0x001E478F multiplies the x87 result; same +0x250 offset
// as ObjectRva0028C197 and Weapon_getRemainingAmmo document; slot 0xD4 is the
// retail jmp immediate; 1.0f literal proven by BuffNuggetFXNuggetCtor and
// GlobalFloatGetters. Name stays address-derived; true method name unproven.

class Rva0028B842Provider
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52();
	virtual float slot53();
};

class Object
{
	char m_pad[0x250];
	Rva0028B842Provider *m_provider250;

public:
	float rva0028B842() const;
};

float Object::rva0028B842() const
{
	Rva0028B842Provider *provider = m_provider250;
	if (provider == 0)
		return 1.0f;
	return provider->slot53();
}
