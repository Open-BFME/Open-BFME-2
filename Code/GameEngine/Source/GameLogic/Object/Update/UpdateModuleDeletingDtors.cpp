// cl: /O1 /MD
// The shared headers declare these members with the access/virtual spelling
// the referring objects use; this TU emits the paired definition spelling.
// Same function, same address: bind the header spelling here.
#pragma comment(linker, "/alternatename:??1DockUpdate@@MAE@XZ=??1DockUpdate@@UAE@XZ")

//
// Scalar deleting-destructor wrappers with audited owner attributions.
// Target facts: 28-byte flag-test wrappers, their call destinations, and the
// vtable slot-0 links below. Owner evidence is stated per body; retail module
// registrations and class-name strings are distinguished from donor-derived
// class spellings. A named slot alone does not establish the complete owner.
// See docs/reconstruction/deleting-destructor-identity-audit.md.
//
// These minimal declarations emit the wrappers, not complete class layouts.
// No bases, member layout, or destructor implementation are claimed here.
// The noinline empty destructor is an unmatched compilation scaffold; the
// verified wrapper call resolves to the retail destructor through its pin.

// ??_GAttributeModifierAuraUpdate@@UAEPAXI@Z @0x0049B884 28B: slot 0 of vtable 0x00C50D2C; calls ??1 at 0x0049B6DD.
// Owner evidence (audited 2026-09-26): retail slot 4 -> RVA 0x0049B5DC uses class-name string "AttributeModifierAuraUpdate".
class AttributeModifierAuraUpdate { public: __declspec(noinline) virtual ~AttributeModifierAuraUpdate(); };
// ??1AttributeModifierAuraUpdate@@UAE@XZ present-unmatched
AttributeModifierAuraUpdate::~AttributeModifierAuraUpdate() {}
void AttributeModifierAuraUpdate_Delete(AttributeModifierAuraUpdate *p) { delete p; }

// ??_GProductionUpdate@@UAEPAXI@Z @0x0049E34C 28B: slot 0 of vtable 0x00C515BC; calls ??1 at 0x0049E1BF.
// Owner evidence (audited 2026-09-26): retail slot 4 -> RVA 0x0049E15E uses class-name string "ProductionUpdate".
class ProductionUpdate { public: __declspec(noinline) virtual ~ProductionUpdate(); };
// ??1ProductionUpdate@@UAE@XZ present-unmatched
ProductionUpdate::~ProductionUpdate() {}
void ProductionUpdate_Delete(ProductionUpdate *p) { delete p; }

// ??_GEmotionTrackerUpdate@@UAEPAXI@Z @0x004B15CA 28B: slot 0 of vtable 0x00C5667C; calls ??1 at 0x004B1322.
// Owner evidence (audited 2026-09-26): retail slot 4 -> RVA 0x004B1393 uses class-name string "EmotionTrackerUpdate".
class EmotionTrackerUpdate { public: __declspec(noinline) virtual ~EmotionTrackerUpdate(); };
// ??1EmotionTrackerUpdate@@UAE@XZ present-unmatched
EmotionTrackerUpdate::~EmotionTrackerUpdate() {}
void EmotionTrackerUpdate_Delete(EmotionTrackerUpdate *p) { delete p; }

// ??_GDockUpdate@@UAEPAXI@Z @0x0058A177 28B: slot 0 of vtable 0x00C70378; calls ??1 at 0x0058A0F4.
// Owner evidence (audited 2026-09-26): donor ctor RVA 0x0058A290 stores this primary vptr at RVA 0x0058A2C5 and a separate interface vptr at +0x20; slot-3 xfer RVA 0x0058A410 corroborates the dock fields and member order.
// Rowed in Rva0058A0F4Dtor.cpp, the unit of the destructor it calls.

// ?rva0049B8A0@Rva0049B8A0@@QAEXPAVINI@@PAX@Z @0x0049B8A0 234B
// Bitstring-list INI driver, same shape as the KindOf driver Rva00256499
// (System/Rva00256499Parse.cpp) and the ModelCondition twin Rva000B937E.
// The worker is the rowed 0x0049B750 single-token worker; Append, Tok, INI
// and the empty string mirror the prototype TU (undefined externals).
class INI
{
public:
	const char *rva0002DFE2(const char *seps, bool *substituted);
};

class Rva0033B84ETok
{
public:
	Rva0033B84ETok(const char *s);
	~Rva0033B84ETok();
	Rva0033B84ETok() : m_data(0) {}
	const char *str() const { return m_data ? (const char *)m_data + 8 : ""; }
	bool nextToken(Rva0033B84ETok *out, const char *seps);
	void reset();

private:
	void *m_data;
};


__forceinline const char *GetStr0049B8A0(const Rva0033B84ETok &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : "";
}

class Rva0049B750
{
public:
	bool rva0049B750(const char *token, bool *foundNormal, bool *foundAddOrSub);
};

class Rva0049B8A0 : public Rva0049B750
{
public:
	void rva0049B8A0(INI *ini, void *extra);
	void rva0049B8A0Append(const char *s, Rva0033B84ETok *b);
};

void Rva0049B8A0::rva0049B8A0(INI *ini, void *extra)
{
	Rva0033B84ETok *accum = (Rva0033B84ETok *)extra;
	if (accum != 0)
		accum->reset();

	bool foundNormal = false;
	bool foundAddOrSub = false;
	bool wasQuoted = false;

	const char *token;
	while ((token = ini->rva0002DFE2(0, &wasQuoted)) != 0) {
		if (wasQuoted) {
			Rva0033B84ETok tmp(token);
			Rva0033B84ETok part;
			while (tmp.nextToken(&part, 0)) {
				const char *s = GetStr0049B8A0(part);
				rva0049B8A0Append(s, accum);
				if (!rva0049B750(s, &foundNormal, &foundAddOrSub))
					break;
			}
			wasQuoted = false;
		} else {
			rva0049B8A0Append(token, accum);
			if (!rva0049B750(token, &foundNormal, &foundAddOrSub))
				break;
		}
	}
}
