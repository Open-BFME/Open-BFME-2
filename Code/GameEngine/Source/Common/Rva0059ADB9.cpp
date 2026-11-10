// cl: /MD
// ?rva0059ADB9@Rva0059ADB9@@QAE_NXZ @0x0059ADB9 24B
// Target evidence: Ghidra boundary 0x0059ADB9..0x0059ADD1; reads a float
// at +0x0C, calls the rowed body fallback getter through the pointer at
// +0x2C, and returns the byte at +0x1C from that getter's result. The owner
// identity remains address-derived.
class Rva0033A65E
{
public:
	void *rva0033A65E();

private:
	char m_pad[0x490];
	void *m_body;
};

class Rva0059ADB9
{
public:
	bool rva0059ADB9();

private:
	char m_pad000[0x0C];
	float m_value;
	char m_pad010[0x1C];
	Rva0033A65E *m_body;
};

bool Rva0059ADB9::rva0059ADB9()
{
	if (m_value <= 0.0f)
		return false;
	return *(bool *)((char *)m_body->rva0033A65E() + 0x1C);
}

// ?rva0059ADF4@Rva0059ADF4@@QAEXH@Z @0x0059ADF4 29B
// Target evidence: the direct call at VA 0x0099AE04 resolves to executable
// code at VA 0x009DB045; the call target has a thiscall frame and ret 0x10.
// The owner pointer read at +0x24 and callee identity remain address-derived.
class Rva005DB045
{
public:
	// Rowed virtual at 0x005DB045; called directly (qualified), not through the vtable.
	virtual void rva005DB045(float value, bool first, bool second, bool third);
};

class Rva0059ADF4
{
public:
	void rva0059ADF4(int value);

private:
	char m_pad[0x24];
	Rva005DB045 *m_component;
};

void Rva0059ADF4::rva0059ADF4(int value)
{
	float converted = (float)value;
	m_component->Rva005DB045::rva005DB045(converted, true, true, false);
}

// ?rva0059AE55@Rva0059AE55@@QAEXPAXPAPAX@Z @0x0059AE55 29B
// Target evidence: copies five dwords from the first stack argument into
// this, then dereferences the second stack argument and stores it at +0x14.
// The structure identity remains address-derived.
struct Rva0059AE55Prefix
{
	unsigned int m_words[5];
};

class Rva0059AE55
{
public:
	void rva0059AE55(void *source, void **slot);

private:
	Rva0059AE55Prefix m_prefix;
	void *m_value;
};

void Rva0059AE55::rva0059AE55(void *source, void **slot)
{
	m_prefix = *(Rva0059AE55Prefix *)source;
	m_value = *slot;
}

// ?rva0059AC4D@AITeamBuilder@@QAEXPAX@Z @0x0059AC4D 33B
// Target evidence: clamps the argument object's unsigned dword at +0x2D0 to
// 2, stores it, then calls the address-named helper at 0x0059ABC9 with the
// same ECX and object argument. The original method name remains unknown.
struct Rva0059AC4DArg
{
	char m_pad[0x2D0];
	unsigned int m_value;
};

class AITeamBuilder
{
public:
	void rva0059AC4D(void *object);
	__declspec(noinline) void rva0059ABC9(void *object);
	class Team *rva00599F74(class TeamPrototype *);
	int getCurNumUnits(class Team *);
	void recruitPreDefined(class Team *, int *, class TeamPrototype *);	// row 0x0059A499
	void recruitUnDefined(class Team *, int *);	// row 0x0059A8D7
private:
	char prefix00[0x14];
	class Player *owner14;
};

void AITeamBuilder::rva0059AC4D(void *object)
{
	Rva0059AC4DArg *arg = (Rva0059AC4DArg *)object;
	unsigned int value = arg->m_value;
	if (value > 2)
		value = 2;
	arg->m_value = value;
	rva0059ABC9(object);
}

// ?rva0059AE11@Rva0059AE11@@QAEPAXPAXPAI@Z @0x0059AE11 33B
// Target evidence: copies three dwords from the first stack argument, then
// copies two dwords from the second to this+0x0C and this+0x10, and leaves
// this in EAX at return. Identity and field meaning remain address-derived.
struct Rva0059AE11Prefix
{
	unsigned int m_words[3];
};

class Rva0059AE11
{
public:
	void *rva0059AE11(void *source, unsigned int *tail);

private:
	Rva0059AE11Prefix m_prefix;
	unsigned int m_first;
	unsigned int m_second;
};

void *Rva0059AE11::rva0059AE11(void *source, unsigned int *tail)
{
	m_prefix = *(Rva0059AE11Prefix *)source;
	m_first = tail[0];
	m_second = tail[1];
	return this;
}

// ?rva0059AE32@Rva0059AE32@@QAEPAXPAXPAI@Z @0x0059AE32 35B
// Target evidence: copies five dwords from the first stack argument, then
// copies two dwords from the second to this+0x14 and this+0x18; returns this.
// Structure identity and field meaning remain address-derived.
struct Rva0059AE32Prefix
{
	unsigned int m_words[5];
};

class Rva0059AE32
{
public:
	void *rva0059AE32(void *source, unsigned int *tail);

private:
	Rva0059AE32Prefix m_prefix;
	unsigned int m_first;
	unsigned int m_second;
};

void *Rva0059AE32::rva0059AE32(void *source, unsigned int *tail)
{
	m_prefix = *(Rva0059AE32Prefix *)source;
	m_first = tail[0];
	m_second = tail[1];
	return this;
}

// ?rva0059AE94@Rva0059AE94@@QAE_NXZ @0x0059AE94 40B
// Target evidence: byte gate at +0x18 then float gate at +0x10 like sibling
// 0x0059ADB9; context from +0x08 plus 0x10 through rowed ThingTemplate
// 0x0033A9E2 with body at +0x2C; tail result through rowed bool 0x0041950A.
// Callers 0x004F97AC 0x004F9A05 in 0x004F971E 0x004F99CC; neighbours
// 0x0059AE55 0x0059AFC2. Owner identity remains address-derived.
#include "../../Include/Common/ThingTemplate.h"

#include "../../Include/Common/Rva004194D6.h"

class Rva0059AE94
{
public:
	bool rva0059AE94();

private:
	char m_pad000[0x08];
	char *m_base;
	char m_pad00C[0x04];
	float m_value;
	char m_pad014[0x04];
	unsigned char m_flag;
	char m_pad019[0x13];
	ThingTemplate *m_template;
};

bool Rva0059AE94::rva0059AE94()
{
	if (m_flag != 0)
		return false;
	if (m_value <= 0.0f)
		return false;
	const void *context = (const void *)(m_base + 0x10);
	void *target = m_template->getCurrentLivingWorldAutoResolveWeapon(context);
	return ((Rva004194D6 *)target)->rva0041950A();
}

// ?rva0059AEBC@LivingWorldAutoResolveUnit@@QAEMXZ @0x0059AEBC 22B
// Target evidence: level at base+0x0C from +0x08 pushed before rowed
// Rva0033A65E 0x0033A65E through +0x2C; result feeds rowed
// LivingWorldAutoResolveBodyTemplate 0x00418573. Callers 0x0059AEDB
// 0x0059AF37 0x0059B2CB 0x0059B697; neighbours 0x0059AE94 0x0059AFC2.
// Owner: the LivingWorldAutoResolveUnit constructor 0x0059B1EC calls it on
// its own this (+0x08 entry, +0x2C thing template).
struct Rva0059AEBCCtx
{
	char m_pad[0x0C];
	int m_level;
};

class LivingWorldAutoResolveBodyTemplate
{
public:
	float getHitpointsForLevel(int level);
	float getRegenRateForLevel(int level);
};

class LivingWorldAutoResolveUnit
{
public:
	float rva0059AEBC();

private:
	char m_pad000[0x08];
	Rva0059AEBCCtx *m_ctx;
	char m_pad00C[0x20];
	Rva0033A65E *m_holder;
};

float LivingWorldAutoResolveUnit::rva0059AEBC()
{
	return ((LivingWorldAutoResolveBodyTemplate *)m_holder->rva0033A65E())->getHitpointsForLevel(m_ctx->m_level);
}

// ?rva0059AED2@Rva0059AED2@@QAEXXZ @0x0059AED2 23B
// Target evidence: chain lane, calls rowed 0x0059AEBC with same this;
// copies dword at +0x0C to +0x10, stores callee float result at +0x14,
// clears byte at +0x18. Caller 0x004F619A; neighbours 0x0059AEBC 0x0059AFC2.
// Owner identity remains address-derived via pin.
class Rva0059AED2
{
public:
	void rva0059AED2();

private:
	char m_pad000[0x0C];
	unsigned int m_value0C;
	unsigned int m_value10;
	float m_value14;
	unsigned char m_flag18;
};

void Rva0059AED2::rva0059AED2()
{
	m_value10 = m_value0C;
	m_value14 = ((LivingWorldAutoResolveUnit *)this)->rva0059AEBC();
	m_flag18 = 0;
}

// Native 59ABC9..59AC4D (132B), RET4. WB15294A0 names the same sequence
// AITeamBuilder::defineUnitsNormal; the address name and ABI are retained.
// Native proves owner14, Team flags110/111 and prototype subobject12C. The
// prototype lookup keeps its address name; WB corroborates the recruitment
// callees' roles and argument order.
#include "../../Include/Common/TeamBFME2.h"
class TeamPrototype;
#include "../../Include/Common/TeamFactory.h"
class Rva0039D5A9
{
public:
    int rva0039D5A9();
};
#include "../../Include/GameLogic/Rva002A8F24.h"
// ABI-only view of the existing rowed cardinality helper at 2BEDAB. Its
// target body subtracts the range words at +4/+8 and divides by four;
// no actual hash-table identity is assigned to the statistics pointee.
namespace _STL {
template <class T> struct hash;
template <class T> struct equal_to;
template <class T> class allocator;
template <class A, class B> struct pair;
template <class K, class T, class H, class E, class A> class hash_map
{
public:
    unsigned int bucket_count() const;
};
}
typedef _STL::hash_map<int, int, _STL::hash<int>, _STL::equal_to<int>,
    _STL::allocator<_STL::pair<const int, int> > > Rva002BEDABRangeView;
extern TeamFactory *TheTeamFactory;
extern Rva002A8F24 *TheSkirmishAIManager;

void AITeamBuilder::rva0059ABC9(void *object)
{
    TeamPrototype *prototype = static_cast<TeamPrototype *>(object);
    Team *team = rva00599F74(prototype);
    if (!team) {
        team = TheTeamFactory->createTeamOnPrototype(prototype, false);
        team->m_isRecruitablitySet = true;
        team->m_isRecruitable = true;
    }
    void *stats = TheSkirmishAIManager->rva002A8F24(owner14);
    Rva002BEDABRangeView *range = *static_cast<Rva002BEDABRangeView **>(stats);
    if (range->bucket_count() > 0) {
        int count = getCurNumUnits(team);
        Rva0039D5A9 *requirements = reinterpret_cast<Rva0039D5A9 *>(
            static_cast<char *>(object) + 0x12c);
        if (requirements->rva0039D5A9() > 0)
            recruitPreDefined(team, &count, prototype);
        else
            recruitUnDefined(team, &count);
    }
}

// Native 59AF30..59AFC2 is146B RET4. WB14D6190 corroborates rescaling
// current HP at0C after level-dependent maximum14 changes, optional mode1
// regeneration through the rowed body query and getRegenRateForLevel,
// clamping to the new maximum, and clearing word1C. Context08
// supplies level0C; body template query owner2C agrees with adjacent rows.
// The concrete owner and original method name remain address-derived.

class Rva0059AF30 {
public:
 void rva0059AF30(int mode);
 char prefix[8];
 Rva0059AEBCCtx *context;
 float current,previous,maximum;
 unsigned char flag;
 char gap19[3];
 unsigned cleared1C;
 char gap20[12];
 Rva0033A65E *body;
};
void Rva0059AF30::rva0059AF30(int mode) {
 float limit = reinterpret_cast<LivingWorldAutoResolveUnit *>(this)->rva0059AEBC();
 if (limit != maximum) {
  float scaled = current;
  if (maximum != 0.0f) scaled = (limit / maximum) * scaled;
  current = scaled;
 }
 if (mode == 1 && !(current <= 0.0f)) {
  current += reinterpret_cast<LivingWorldAutoResolveBodyTemplate *>(body->rva0033A65E())->getRegenRateForLevel(context->m_level);
  if (current > limit) current = limit;
 }
 cleared1C = 0;
}
