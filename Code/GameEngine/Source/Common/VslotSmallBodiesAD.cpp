// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry, batch
// AD: each calls an unrowed (Ghidra-listed, larger) function, pinned in
// reverse/symbols.csv under an address-derived name with the arguments and
// return its call sites and ret show. As in VslotSmallBodiesA-AC, classes
// and methods are address-derived unless the ledger already names them,
// and model only what each body touches. Meanings are not recovered.

typedef int Int;
typedef float Real;

class Object;
enum ObjectStatusTypes
{
	OBJECT_STATUS_1C = 0x1C
};
class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool set);
};
struct Rva00349D02Machine
{
	char m_pad00[0x14];
	Object *m_owner14;
};

// 0x00260E44: whether the object at VA 0x00DFECC4 exists and its pinned
// 0x00288CFA accepts the argument's +0x264 word.
class Rva00288CFA
{
public:
	bool rva00288CFA(Int a);
};
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;
struct Rva00260E44Arg
{
	char m_pad00[0x264];
	Int m_264;
};
class Rva00260E44
{
public:
	bool rva00260E44(const Rva00260E44Arg *arg);
};
bool Rva00260E44::rva00260E44(const Rva00260E44Arg *arg)
{
	if (TheExperienceLevelSystem && reinterpret_cast<Rva00288CFA *>(TheExperienceLevelSystem)->rva00288CFA(arg->m_264))
		return true;
	return false;
}

// 0x0026156C: the pinned 0x0029493F of the +0x08 object with the argument
// and the +0x0C word.
class Rva0029493F
{
public:
	void rva0029493F(Int a, Int b);
};
class Rva0026156C
{
public:
	void rva0026156C(Int a);
private:
	Int m_00;
	Int m_04;
	Rva0029493F *m_08;
	Int m_0C;
};
void Rva0026156C::rva0026156C(Int a)
{
	m_08->rva0029493F(a, m_0C);
}

// 0x00349D02 (AI state tables): the pinned 0x003497E6 result, setting or
// clearing status 0x1C on the owner as it is -1.
class Rva00349D02
{
public:
	Int rva00349D02();
	Int rva003497E6();
private:
	char m_pad00[0x18];
	Rva00349D02Machine *m_18;
};
Int Rva00349D02::rva00349D02()
{
	Object *owner = m_18->m_owner14;
	Int result = rva003497E6();
	owner->setStatus(OBJECT_STATUS_1C, result == -1);
	return result;
}

// 0x00359729: the pinned 0x00359556 of the object at VA 0x00E01E28 with the
// argument, 0 without the object.
class Rva00359556
{
public:
	Int rva00359556(Int a);
};
extern Rva00359556 *g_rva00359729Target;
class Rva00359729
{
public:
	Int rva00359729(Int a);
};
Int Rva00359729::rva00359729(Int a)
{
	if (g_rva00359729Target)
		return g_rva00359729Target->rva00359556(a);
	return 0;
}

// 0x003AFE24 and 0x003AFE36: GPU resource access through the manager
// at VA 0x00DFDD04; return zero if it is absent. Providers are byte-verified
// in ParticleSystemManagerGetShaderSetup.cpp (1F4002 and 1F40AF).
struct IDirect3DVertexDeclaration9;
class DX8IndexBufferClass;
namespace FXParticleSystem {
class ParticleSystemManager {
public:
	IDirect3DVertexDeclaration9 *GetVertexDeclaration();
	DX8IndexBufferClass *rva001F40AF();
};
}
extern class ParticleSystemManager *TheParticleSystemManager;
class Rva003AFE24
{
public:
	Int rva003AFE24();
	Int rva003AFE36();
};
Int Rva003AFE24::rva003AFE24()
{
	if ((*(FXParticleSystem::ParticleSystemManager **)&TheParticleSystemManager))
		return reinterpret_cast<Int>((*(FXParticleSystem::ParticleSystemManager **)&TheParticleSystemManager)->GetVertexDeclaration());
	return 0;
}
Int Rva003AFE24::rva003AFE36()
{
	if ((*(FXParticleSystem::ParticleSystemManager **)&TheParticleSystemManager))
		return reinterpret_cast<Int>((*(FXParticleSystem::ParticleSystemManager **)&TheParticleSystemManager)->rva001F40AF());
	return 0;
}

// 0x003C35F7: the pinned 0x003C35AA with both arguments and true.
class Rva003C35F7
{
public:
	void rva003C35F7(Int a, Int b);
	void rva003C35AA(Int a, Int b, bool c);
};
void Rva003C35F7::rva003C35F7(Int a, Int b)
{
	rva003C35AA(a, b, true);
}

// 0x0040E0C5: for the argument's +0x78 object in state 4 (+0x2C), the
// pinned 0x0040DF77 then the rowed 0x0040E02B; answers true.
class Rva0040E02B
{
public:
	void rva0040E02B();
};
class Rva0040DF77 : public Rva0040E02B
{
public:
	void rva0040DF77();
	char m_pad00[0x2C];
	Int m_2C;
};
struct Rva0040E0C5Arg
{
	char m_pad00[0x78];
	Rva0040DF77 *m_78;
};
class Rva0040E0C5
{
public:
	bool rva0040E0C5(Rva0040E0C5Arg *arg);
};
bool Rva0040E0C5::rva0040E0C5(Rva0040E0C5Arg *arg)
{
	Rva0040DF77 *x = arg->m_78;
	if (x && x->m_2C == 4)
	{
		x->rva0040DF77();
		x->rva0040E02B();
	}
	return true;
}

// 0x00414B89 and 0x00415122: the pinned 0x00414B0A resp. 0x0041505B on
// every 0x30-byte entry of the [+0x10, +0x14) range.
class Rva00414B0A
{
public:
	void rva00414B0A();
	void rva0041505B();
private:
	char m_pad00[0x30];
};
class Rva00414B89
{
public:
	void rva00414B89();
	void rva00415122();
private:
	char m_pad00[0x10];
	Rva00414B0A *m_start;
	Rva00414B0A *m_finish;
};
void Rva00414B89::rva00414B89()
{
	Rva00414B0A *end = m_finish;
	for (Rva00414B0A *it = m_start; it != end; ++it)
		it->rva00414B0A();
}
void Rva00414B89::rva00415122()
{
	Rva00414B0A *end = m_finish;
	for (Rva00414B0A *it = m_start; it != end; ++it)
		it->rva0041505B();
}

// 0x00482134 and 0x00482152 (the latter through an interface at +0x20):
// the pinned 0x0035A292 of TheGameLogic's +0x170 object with the +0x08 word
// and the +0x04 object's +0x08 Real.
class Rva0035A292
{
public:
	void rva0035A292(Int a, Real b);
};
struct Rva00482134Logic
{
	char m_pad00[0x170];
	Rva0035A292 *m_170;
};
extern Rva00482134Logic *TheGameLogic;
struct Rva00482134Data
{
	Int m_00;
	Int m_04;
	Real m_08;
};
class Rva00482134
{
public:
	void rva00482134();
private:
	Int m_00;
	Rva00482134Data *m_04;
	Int m_08;
};
void Rva00482134::rva00482134()
{
	TheGameLogic->m_170->rva0035A292(m_08, m_04->m_08);
}
class Rva00482152Primary
{
public:
	virtual void primarySlot();
protected:
	Rva00482134Data *m_04;
	Int m_08;
	char m_pad0C[0x14];
};
class Rva00482152Iface
{
public:
	virtual void rva00482152(Int unused) = 0;
};
class Rva00482152 : public Rva00482152Primary, public Rva00482152Iface
{
public:
	void rva00482152(Int unused);
};
void Rva00482152::rva00482152(Int)
{
	TheGameLogic->m_170->rva0035A292(m_08, m_04->m_08);
}

// 0x004CDF00 and 0x004CDF1D: the pinned base 0x004502CE with both
// arguments then the pinned 0x004CDDBA(1); resp. only the latter while
// +0x08 is set.
class Rva004502CE
{
public:
	void rva004502CE(Int a, Int b);
};
class Rva004CDF00 : public Rva004502CE
{
public:
	void rva004CDF00(Int a, Int b);
	void rva004CDF1D();
	void rva004CDDBA(Int a);
private:
	Int m_00;
	Int m_04;
	Int m_08;
};
void Rva004CDF00::rva004CDF00(Int a, Int b)
{
	rva004502CE(a, b);
	rva004CDDBA(1);
}
void Rva004CDF00::rva004CDF1D()
{
	if (m_08)
		rva004CDDBA(1);
}

// 0x004EF2FA (interface at +0x04): the pinned 0x004EEE38 of the complete
// object with the first argument.
class Rva004EF2FAPrimary
{
public:
	virtual void primarySlot();
	void rva004EEE38(Int a);
};
class Rva004EF2FAIface
{
public:
	virtual void rva004EF2FA(Int a, Int unused) = 0;
};
class Rva004EF2FA : public Rva004EF2FAPrimary, public Rva004EF2FAIface
{
public:
	void rva004EF2FA(Int a, Int unused);
};
void Rva004EF2FA::rva004EF2FA(Int a, Int)
{
	rva004EEE38(a);
}

// 0x00508925: whether the pinned 0x005075D6 accepts both arguments.
class Rva00508925
{
public:
	bool rva00508925(Int a, Int b);
	unsigned char rva005075D6(Int a, Int b);
};
bool Rva00508925::rva00508925(Int a, Int b)
{
	return (bool)rva005075D6(a, b);
}
