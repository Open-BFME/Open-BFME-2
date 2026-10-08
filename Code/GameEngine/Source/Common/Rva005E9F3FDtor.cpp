// cl: /MD
// ??1Rva005E9F3F@@UAE@XZ retail 0x005E9F3F 14B
// Virtual dtor stores derived vtable then tail-jmps to member clear at +4.
// Layout from caller 0x005E948B deleting wrapper vtable 0x00C780A8#0 and rowed clear 0x005E9E27.
// Evidence: mov [ecx] C780A8 plus add ecx 4 plus jmp clear; twin 0x005E888A 8B plus vptr.

class Rva005E9F3F;
class Rva0057C394;
class LivingWorldBattle;
class Rva005E98A0
{
public:
	Rva005E98A0(Rva005E9F3F *owner, Rva0057C394 *provider, LivingWorldBattle *battle, void *input0C, void *input10, void *input14);
private:
	char m_unknown[0x20];
};

class Rva005E9E27
{
public:
	void clear();
	__forceinline void setNew(Rva005E98A0 *value) { m_ptr = value; }
private:
	Rva005E98A0 *m_ptr;
};

class Rva005E9F3F
{
public:
	virtual ~Rva005E9F3F();
	Rva005E9F3F(Rva0057C394 *provider, LivingWorldBattle *battle, void *input0C, void *input10, void *input14);
private:
	Rva005E9E27 m_04;
};

Rva005E9F3F::~Rva005E9F3F()
{
	m_04.clear();
}

// Native5E9EEC..5E9F3F allocates the20-byte implementation and forwards
// owner plus five inputs. The final three input types/roles remain opaque.
Rva005E9F3F::Rva005E9F3F(Rva0057C394 *provider, LivingWorldBattle *battle, void *input0C, void *input10, void *input14)
{
	m_04.setNew(new Rva005E98A0(this, provider, battle, input0C, input10, input14));
}
