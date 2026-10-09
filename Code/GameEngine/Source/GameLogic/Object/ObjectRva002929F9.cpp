// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /ICode/Libraries/Include
//
// ?rva002929F9@Object@@QAEXPAV1@@Z
// retail 0x002929F9..0x00292D49 (848 bytes) EH thiscall ret 4. The unrowed
// 0x004BBA65 calls it with the object being run over. WB 0x00CC3960 has the
// same flow (no name): nothing when the other object's +0x438 bit 0 is set;
// with a drawable (+0x84) and TheAudio the drawable's keyed sound 0x37
// (rowed 0x0028F912) is played as an event tagged with this object's ID
// (rowed ctor 0x002D97D6 / 0x002D9531 / pinned dtor 0x002D9A43 and
// TheAudio slot 25); a container (+0x274) whose template has KindOf bit 109
// (+0x115 bit 5) takes the call instead; with a positive template +0x514
// the relative angle to the other object (pinned GetRelativeAngle 0x000B4542)
// capped at PI/2 times 0.3 plus this object's angle (+0x44) converted to
// degrees goes with +0x514 / +0x518 and an empty string to the pinned
// 0x00291A8C on the other object; then with an AI (+0x258) the template
// speed +0x510 is scaled by the attribute modifier pools of both objects
// (categories 9 and 0x1A through the inlined rowed 0x0028C15E: rowed
// findAttributeModifierPoolUpdate and 0x00403448) and when positive the
// entry of the rowed 0x0028AC4E has its rowed 0x001E48CF value reduced by
// that speed times the AI's rowed 0x002627E8 (split by the +0x250 module's
// slot 69 count when the KindOf bit is set and scaled by the category 0x12
// modifier against the clamped template +0x50C) floored at zero kept as
// the entry's +0x40 minimum and passed with the logic frame rate to the
// rowed 0x001E415F. Names are address-derived; the pinned 0x00291A8C
// spells its last argument int so the string's address is cast.
#include "Common/BfmeAudioEventPrefix136.h"
#include "Lib/Coord3D.h"

typedef float Real;
typedef int Int;
typedef bool Bool;

class Rva002390CB
{
public:
	Rva002390CB(const Rva002390CB &);
	__forceinline ~Rva002390CB() { if (ref.referent) ref.referent->Release_Ref(); }
	void *unknown00;
	OpaqueRefElement4 ref;
};

class Drawable
{
public:
	Rva002390CB rva0028F912(); // key 0x37
};

class Rva002D9531
{
public:
	void rva002D9531(int value);
};

#define SLOT(N) virtual void slot##N();
class AudioManager
{
public:
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24)
	virtual void addAudioEvent(const BfmeAudioEventPrefix136 *event); // slot 25
};

class Rva002929F9Module
{
public:
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
	SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
	SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55)
	SLOT(56) SLOT(57) SLOT(58) SLOT(59) SLOT(60) SLOT(61) SLOT(62) SLOT(63)
	SLOT(64) SLOT(65) SLOT(66) SLOT(67) SLOT(68)
	virtual Int rva002929F9Count(Int arg); // slot 69
};
#undef SLOT

extern AudioManager *TheAudio;
extern int g_Va00DBA4E4;

class AttributeModifierPoolUpdate
{
public:
	Bool rva00403448(Int attribute, Real *value, Int arg, Int arg2);
};

class Rva002627E8
{
public:
	float rva002627E8() const;
};

struct Rva0028AC4EEntry
{
	char m_pad00[0x40];
	Real m_40;
};

class Rva001E46E1
{
public:
	float rva001E48CF(class Object *object);
};

class Rva001E415F
{
public:
	void rva001E415F(Real value, Int frames);
};

class ThingTemplate
{
public:
	Bool isKindOf109() const { return (m_kindOf[13] & 0x20) != 0; }

	char m_pad000[0x108];
	unsigned char m_kindOf[0x50C - 0x108];
	Real m_50C;
	Real m_510;
	Real m_514;
	Real m_518;
};

class Object
{
public:
	void rva002929F9(Object *other);
	Real GetRelativeAngle(const Coord3D *pos) const;
	void rva00291A8C(Real angle, Real a, Real b, Int name);
	const Rva0028AC4EEntry *rva0028AC4E() const;

	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_pos; }
	Real getOrientation() const { return m_angle; }
	Bool rva0028C15E(Int attribute, Real *value, Int arg, Int arg2)
	{
		AttributeModifierPoolUpdate *pool = findAttributeModifierPoolUpdate();
		if (!pool)
			return false;
		return pool->rva00403448(attribute, value, arg, arg2);
	}

private:
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;

	void *m_vtbl;
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x38 - 0x08];
	Coord3D m_pos;	// +0x38
	Real m_angle;	// +0x44
	char m_pad048[0x74 - 0x48];
	Int m_id;	// +0x74
	char m_pad078[0x84 - 0x78];
	Drawable *m_drawable;	// +0x84
	char m_pad088[0x250 - 0x88];
	Rva002929F9Module *m_250;	// +0x250
	char m_pad254[0x258 - 0x254];
	Rva002627E8 *m_ai;	// +0x258
	char m_pad25c[0x274 - 0x25C];
	Object *m_containedBy;	// +0x274
	char m_pad278[0x438 - 0x278];
	unsigned char m_438;	// +0x438
};

void Object::rva002929F9(Object *other)
{
	if (other->m_438 & 1)
		return;

	if (m_drawable && TheAudio) {
		BfmeAudioEventPrefix136 sound(m_drawable->rva0028F912().ref, 0);
		reinterpret_cast<Rva002D9531 *>(&sound)->rva002D9531(m_id);
		TheAudio->addAudioEvent(&sound);
	}

	if (m_containedBy && m_containedBy->getTemplate()->isKindOf109()) {
		m_containedBy->rva002929F9(other);
		return;
	}

	Real a = getTemplate()->m_514;
	Real b = getTemplate()->m_518;
	if (a > 0.0f) {
		Real angle = GetRelativeAngle(other->getPosition());
		if (angle > 1.5707964f)
			angle = 1.5707964f;
		Real dir = 0.3f * angle + m_angle;
		AsciiString empty("");
		other->rva00291A8C(dir * 180.0f / 3.1415927f, a, b, (Int)&empty);
	}

	Rva002627E8 *ai = m_ai;
	if (!ai)
		return;

	Real speed = getTemplate()->m_510;
	Real modifier = 1.0f;
	if (rva0028C15E(9, &modifier, 0, 1))
		speed = modifier * speed;
	if (other->rva0028C15E(0x1A, &modifier, 0, 1))
		speed = modifier * speed;
	if (speed <= 0.0f)
		return;

	Rva0028AC4EEntry *entry = const_cast<Rva0028AC4EEntry *>(rva0028AC4E());
	if (!entry)
		return;

	Real value = reinterpret_cast<Rva001E46E1 *>(entry)->rva001E48CF(this);
	Real aiSpeed = ai->rva002627E8();
	speed *= aiSpeed;
	if (getTemplate()->isKindOf109()) {
		Rva002929F9Module *module = m_250;
		if (module) {
			Int count = module->rva002929F9Count(0);
			if (count > 1)
				speed = speed / (Real)count;
		}
	}

	Real scale = 1.0f;
	if (rva0028C15E(0x12, &scale, 0, 1)) {
		Real t = getTemplate()->m_50C;
		if (t < 0.05f)
			t = 0.05f;
		else if (t > 0.95f)
			t = 0.95f;
		Real s = t * scale;
		if (s < 0.05f)
			s = 0.05f;
		else if (s > 0.95f)
			s = 0.95f;
		scale = s;
		speed = (1.0f - t) / (1.0f - s) * speed;
	}

	Real remaining = value - speed;
	if (remaining < 0.0f)
		remaining = 0.0f;
	if (entry->m_40 > remaining)
		entry->m_40 = remaining;
	reinterpret_cast<Rva001E415F *>(entry)->rva001E415F(remaining, g_Va00DBA4E4);
}
