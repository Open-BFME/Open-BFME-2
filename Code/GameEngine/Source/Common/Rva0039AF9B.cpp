// cl: /DNDEBUG /MD /O1 /G7 /arch:SSE
//
// ?rva0039AF9B@Rva0039AF9B@@QAEMM@Z, retail 0x0039AF9B (45 bytes).
// Identity: float scale by +0x2C pointee +8 unless game state +0x114 is 3 or
// +0x4 pointee flag 0x80 at +0x108 is set; callers in Object and behavior
// units. Layout from retail offsets; TheGameLogic via rowed name.
class GameLogic
{
public:
	unsigned char m_pad[0x114];
	int m_i114;
};
extern GameLogic *TheGameLogic;
struct Rva0039AF9B_P04
{
	unsigned char m_pad[0x108];
	unsigned char m_b108;
};
struct Rva0039AF9B_P2C
{
	unsigned char m_pad[8];
	float m_f08;
};
class Rva0039AF9B
{
public:
	float rva0039AF9B(float v);
private:
	unsigned char m_pad00[4];
	Rva0039AF9B_P04 *m_p04; // +0x04
	unsigned char m_pad08[0x2C - 0x08];
	Rva0039AF9B_P2C *m_p2C; // +0x2C
};
float Rva0039AF9B::rva0039AF9B(float v)
{
	if (TheGameLogic->m_i114 == 3)
		return v;
	if ((m_p04->m_b108 & 0x80) == 0)
		return v * m_p2C->m_f08;
	return v;
}

// Native 0039B16F..0039B1E2 RET18; WB F9FBB0 confirms every guard/call.
// Donor semantic lead: GeneralsMD GameLogic/Object/ExperienceTracker.cpp
// addExperiencePoints. BFME2 uses float accumulation and extra flags.
// Target offsets and argument use are established independently by bytes.
// Rva0039AF9B is an ABI call view of this same receiver, not an asserted base;
// keeping its owned definition visible preserves ECX through the call.
struct ExperienceParent { unsigned char pad[0x5e7]; bool trainable; };
class ExperienceTracker {
public:
 int rva0039AC23(bool);
 void rva0039B16F(float,bool,bool,bool,bool,float);
private:
 unsigned char pad0[4]; ExperienceParent *parent;
 unsigned char pad8[8]; float experience;
 unsigned char pad14[8]; float multiplier;
 unsigned char pad20[4]; int level; int maxLevel;
};
void ExperienceTracker::rva0039B16F(float points,bool adjust,bool applyMultiplier,bool feedback,bool unused,float modifier)
{
 if(!parent->trainable) return;
 if(maxLevel>0 && level>=maxLevel) return;
 float amount=points;
 if(applyMultiplier) amount=multiplier*points*modifier;
 if(adjust) amount=reinterpret_cast<Rva0039AF9B *>(this)->rva0039AF9B(amount);
 experience+=amount;
 rva0039AC23(feedback);
}
