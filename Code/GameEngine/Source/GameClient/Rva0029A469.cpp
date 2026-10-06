// cl: /DNDEBUG /MD
// ?rva0029A469@Rva0029A469@@QAEXM@Z @0x0029A469 33B. Null-checked Shadow at +0 scaled float by 255 to setOpacity. Evidence: callees rowed setOpacity@Shadow 0x003308F6 callers 0x002A4769 0x002A4E1F pattern RadiusDecal_setOpacity.
typedef float Real;
typedef int Int;

extern float g_00BC2900;

class Shadow
{
public:
	void setOpacity(Int value);
};

class Rva0029A469
{
private:
	Shadow *m_shadow;
public:
	void rva0029A469(Real v);
};

void Rva0029A469::rva0029A469(Real v)
{
	if (m_shadow)
		m_shadow->setOpacity((Int)(*(const volatile float *)&v * g_00BC2900));
}
