// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva00275598@Drawable@@QAEXXZ, retail 0x00275598..0x0027566B (211 bytes):
// the Drawable's tint-status refresh (Zero Hour's updateDrawable block that
// compares m_tintStatus with m_prevTintStatus), in its BFME 2 form. When the
// status at +0x120 differs from the previous one at +0x124, the +0x8C tint
// envelope is created on demand (rowed constructor 0x00271826). Status bit 2
// -- or bit 1 when neither bit 3 nor bit 0 is set -- plays the global tint
// setting's colour (+0x30) with its attack/decay frames (+0x48/+0x4C), scaled
// by its +0x58 factor when the setting's mode test holds (rowed 0x0027000E),
// held indefinitely (rowed TintEnvelope::play); bits 3 or 0 instead put the
// envelope in state 2. The previous status then takes the current one.
// WorldBuilder's twin (0x00CA5060) is unnamed.

class Drawable;
class Thing { public:Drawable *getDrawable() const; };
class Object:public Thing { public:Object *rva002931F5(bool); };
class Rva002716Holder { public:void rva00271547(); };
extern int g_009BA4E8;
float Sin(float);
// Target reads the stored1/30-second value at VA DBA508; its original
// linkage/name is unknown. A local data owner preserves the measured read.
float opacityLogicStepSeconds=0.03333333507180214f;

struct RGBColor
{
	float red;
	float green;
	float blue;
};

class Rva00271826
{
public:
	Rva00271826() throw();
	char m_pad00[0x38];
	unsigned char m_38;
	char m_pad39[0x50 - 0x39];
};

class TintEnvelope
{
public:
	void play(const RGBColor *peak, unsigned int attackFrames, unsigned int decayFrames, unsigned int sustainAtPeak);
};

class Rva0027000E
{
public:
	bool rva0027000E();
};

struct Rva0027070CGlobal
{
	unsigned char m_pad00[0x30];
	RGBColor m_color30;						// +0x30
	unsigned char m_pad3C[0x48 - 0x3C];
	int m_attack48;							// +0x48
	int m_decay4C;							// +0x4C
	unsigned char m_pad50[0x58 - 0x50];
	float m_scale58;						// +0x58
};

extern Rva0027070CGlobal *g_00DFE1E4;

void *operator new(unsigned int s) throw();

class Drawable
{
public:
	void rva00275598();
    void rva00272DEE();
private:
	__forceinline void playTint(Rva0027070CGlobal *setting, bool scaled)
	{
		int attack = setting->m_attack48;
		int decay = setting->m_decay4C;
		RGBColor color = setting->m_color30;
		if (scaled)
		{
			float scale = setting->m_scale58;
			attack = (int)(attack * scale);
			decay = (int)(decay * scale);
		}
		((TintEnvelope *)m_envelope8C)->play(&color, attack, decay, (unsigned int)-2);
	}
	unsigned char m_pad000[0x8C];
	Rva00271826 *m_envelope8C;				// +0x8C
	unsigned char m_pad090[0xb4 - 0x90];
    float m_B4,m_B8,m_BC,m_C0,m_C4,m_C8,m_CC,m_D0;
    unsigned m_D4;
    unsigned char m_padD8[0xfc-0xd8];
    Object *m_objectFC;
    unsigned char m_pad100[0x120-0x100];
	unsigned int m_tintStatus120;			// +0x120
	unsigned int m_prevTintStatus124;
    unsigned char m_pad128[0x164-0x128];
    unsigned m_164;
    unsigned char m_pad168[0x43e-0x168];
    unsigned char m_43E;		// +0x124
};

void Drawable::rva00275598()
{
	if (m_prevTintStatus124 != m_tintStatus120)
	{
		if (m_envelope8C == 0)
			m_envelope8C = new Rva00271826;
		Rva0027070CGlobal *setting = g_00DFE1E4;
		bool scaled = reinterpret_cast<Rva0027000E *>(setting)->rva0027000E();
		unsigned int status = m_tintStatus120;
		if (status & 4)
			playTint(setting, scaled);
		else if (status & 8)
			m_envelope8C->m_38 = 2;
		else if (status & 1)
			m_envelope8C->m_38 = 2;
		else if (status & 2)
			playTint(setting, scaled);
	}
	m_prevTintStatus124 = m_tintStatus120;
}

// BFME2 native272DEE..272FB6: inherit parent's effective stealth look,
// otherwise update pulse/transition opacity. ZH imitateStealthLook and
// setEffectiveOpacity establish the subsystem purpose; new pulse/transition
// equations, offsets and comparisons below are independently target facts.
void Drawable::rva00272DEE() {
 Object *parent=m_objectFC?m_objectFC->rva002931F5(false):0;
 if(parent && m_objectFC!=parent) {
  Drawable *other=parent->getDrawable();
  if(!other)return;
  m_B4=other->m_B4;
  unsigned char old=m_43E;
  m_43E=other->m_43E;
  m_164=other->m_164;
  if(old!=m_43E)reinterpret_cast<Rva002716Holder *>(this)->rva00271547();
 }else if(m_B8!=m_BC) {
  float pulse=m_C4+m_C8*Sin(m_CC);
  float blend=(g_009BA4E8*m_C0-m_D4)/(g_009BA4E8*m_C0);
  if(m_D4>0)--m_D4;
  m_B4=pulse*blend+m_D0*(1.0f-blend);
  m_CC+=(opacityLogicStepSeconds/m_C0)*3.1415927410125732f;
 }else if((float)(m_B8==m_BC)==1.0f && m_B4<1.0f) {
  float blend=(g_009BA4E8*m_C0-m_D4)/(g_009BA4E8*m_C0);
  if(m_D4>0)--m_D4;
  m_B4=m_D0*(1.0f-blend)+blend;
 }
}
