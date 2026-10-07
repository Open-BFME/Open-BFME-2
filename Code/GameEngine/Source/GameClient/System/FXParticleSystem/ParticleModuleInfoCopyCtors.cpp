// cl: /DNDEBUG /MD /EHs-c-
// Particle module-info copy constructors (retail 0x003AE465..0x003AF50D).
// One 59-byte base plus per-class trivial bodies: each derived calls the
// base with (this, other) and then installs its own vftables.  The extra
// bases are DEFAULT-constructed, not copied: the third-base vptr stored
// first is the base's own, overwritten by the derived stores below.
//
// Identity: every body calls the base at 0x003AF50D (19 call sites across
// 0x003AE465..0x00561D94); the stored vftables sit beside their ModuleInfo
// name strings in .rdata; the 0x003AE336 name getter returns
// "ParticleTerrainCollisionModuleInfo" for the 0x003AE465 body; the second
// base vptr 0x00C1C780 is shared with the rowed FXParticleSystem
// CategoryModuleTemplate constructors.  The member at +0x04 copies through
// the pinned 12-byte smart-pointer copy at 0x0004CC19.  All vftable dwords
// are DIR32 sites the gate takes from the target.  /O2 over /Os: the
// straight-line bodies need speed-optimizer inlining plus size-optimizer
// argument passing; the head copy is forceinline so the size optimizer
// still absorbs it (a plain implicit copy outlines to a HeadBase::copy
// call under /Os, and picks ecx for the int scratch under /O2 where
// retail uses eax).

class RvaSmartPtr12
{
public:
	RvaSmartPtr12(const RvaSmartPtr12 &that);
	~RvaSmartPtr12();

private:
	void *m_ptr; // +0x0
	int m_pad04; // +0x4
	int m_pad08; // +0x8
};

// Shared second base at +0x14: vptr 0x00C1C780.
class ModuleInfoSecondBase
{
public:
	virtual ~ModuleInfoSecondBase();
};

// Head base: vptr 0x00C1B590, smart member at +0x04, int at +0x10.
// Explicit forceinline copy (see header note).
class ModuleInfoHeadBase
{
public:
	__forceinline ModuleInfoHeadBase(const ModuleInfoHeadBase &other)
		: m_smart(other.m_smart)
		, m_int10(other.m_int10)
	{
	}
	virtual ~ModuleInfoHeadBase();

	RvaSmartPtr12 m_smart; // +0x04
	int m_int10; // +0x10
};

#define MODULE_INFO_THIRD_BASE(NAME) \
	class NAME \
	{ \
	public: \
		virtual ~NAME(); \
	};

MODULE_INFO_THIRD_BASE(ModuleInfoThirdBAC0)
MODULE_INFO_THIRD_BASE(ModuleInfoThirdBD10)
MODULE_INFO_THIRD_BASE(ModuleInfoThirdBD30)
MODULE_INFO_THIRD_BASE(ModuleInfoThirdBD50)

// Retail 0x003AF50D, 59 bytes: the shared base copy constructor.
// noinline: the derived bodies below call it; inlining would absorb the
// straight-line body into each caller (the BFME1 donor marks its shared
// node copy the same way).
class Rva003AF50D : public ModuleInfoHeadBase, public ModuleInfoSecondBase
{
public:
	__declspec(noinline) Rva003AF50D(const Rva003AF50D &other);
	virtual ~Rva003AF50D();
};

Rva003AF50D::Rva003AF50D(const Rva003AF50D &other)
	: ModuleInfoHeadBase(other)
{
}

// ??0Rva003AF5AC@@QAE@ABV0@@Z @0x003AF5AC 98B: copy ctor with LineEmissionVolumeInfo base at +0x1c.
// Evidence: calls rowed base 0x003AF50D then rowed Line copy 0x003A653B; neg/sbb/and null-guarded
// adjustment of source to +0x1c for the Line base; vptrs at +0/+0x14/+0x18/+0x1c DIR32;
// caller 0x003AF57F (45B) calls this then installs its own 4 vptrs; unlocks 0x003AF57F.
namespace FXParticleSystem
{
class Snapshot5AC
{
public:
	virtual ~Snapshot5AC();
};
class EmissionVolumeInfo5AC : public Snapshot5AC
{
public:
	virtual ~EmissionVolumeInfo5AC();
	bool m_flag;
};
class LineEmissionVolumeInfo : public EmissionVolumeInfo5AC
{
public:
  LineEmissionVolumeInfo(const LineEmissionVolumeInfo &that) throw();
  virtual ~LineEmissionVolumeInfo();
private:
  float m_unk[6];
};
}

MODULE_INFO_THIRD_BASE(ModuleInfoThirdC6FC)

// Shared intermediate with primary 0x00C1C6FC (also used by 0x003AF672 Box version):
// Rva base at +0 plus third at +0x18; trivial inline copy (Rva call plus own vptrs)
// so it folds into each derived 98B body as the 4 pre-Line stores.
class Intermediate3AFC6FC : public Rva003AF50D, public ModuleInfoThirdC6FC
{
public:
	__forceinline Intermediate3AFC6FC(const Intermediate3AFC6FC &other)
		: Rva003AF50D(other)
	{
	}
	virtual ~Intermediate3AFC6FC();
};

class Rva003AF5AC : public Intermediate3AFC6FC, public FXParticleSystem::LineEmissionVolumeInfo
{
public:
	Rva003AF5AC(const Rva003AF5AC &other);
	virtual ~Rva003AF5AC();
};

Rva003AF5AC::Rva003AF5AC(const Rva003AF5AC &other)
	: Intermediate3AFC6FC(other)
	, FXParticleSystem::LineEmissionVolumeInfo((const FXParticleSystem::LineEmissionVolumeInfo &)other)
{
}

// ??0Rva003AF57F@@QAE@ABV0@@Z @0x003AF57F 45B: derived copy calling rowed 0x003AF5AC then own 4 vptrs.
// Evidence: calls 0x003AF5AC (landed this session) then stores at +0/+0x14/+0x18/+0x1c DIR32;
// third 0x00C1D788 shared with base; caller 0x003AF548 calls this; unlocks 0x003AF548.
class Rva003AF57F : public Rva003AF5AC
{
public:
	Rva003AF57F(const Rva003AF57F &other);
	virtual ~Rva003AF57F();
};

Rva003AF57F::Rva003AF57F(const Rva003AF57F &other)
	: Rva003AF5AC(other)
{
}

// ??0Rva003AF738@@QAE@ABV0@@Z @0x003AF738 98B: copy ctor with SphereEmissionVolumeInfo base at +0x1c.
// Evidence: calls rowed base 0x003AF50D then rowed Sphere copy 0x003A67FD; neg/sbb/and null-guarded
// adjustment of source to +0x1c for the Sphere base; vptrs at +0/+0x14/+0x18/+0x1c DIR32;
// same Intermediate3AFC6FC pre-Sphere stores as rowed 0x003AF5AC Line version; unlocks 0x003AF70B.
namespace FXParticleSystem
{
class Snapshot738
{
public:
	virtual ~Snapshot738();
};
class EmissionVolumeInfo738 : public Snapshot738
{
public:
	virtual ~EmissionVolumeInfo738();
	bool m_flag;
};
class SphereEmissionVolumeInfo : public EmissionVolumeInfo738
{
public:
  SphereEmissionVolumeInfo(const SphereEmissionVolumeInfo &that) throw();
  virtual ~SphereEmissionVolumeInfo();
private:
  float m_radius;
};
}

class Rva003AF738 : public Intermediate3AFC6FC, public FXParticleSystem::SphereEmissionVolumeInfo
{
public:
	Rva003AF738(const Rva003AF738 &other);
	virtual ~Rva003AF738();
};

Rva003AF738::Rva003AF738(const Rva003AF738 &other)
	: Intermediate3AFC6FC(other)
	, FXParticleSystem::SphereEmissionVolumeInfo((const FXParticleSystem::SphereEmissionVolumeInfo &)other)
{
}

// ??0Rva003AF70B@@QAE@ABV0@@Z @0x003AF70B 45B: derived copy calling rowed 0x003AF738 then own 4 vptrs.
// Evidence: calls 0x003AF738 (landed this session) then stores at +0/+0x14/+0x18/+0x1c DIR32;
// same 45B shape as rowed 0x003AF57F; caller 0x003AF6D4 calls this; unlocks 0x003AF6D4.
class Rva003AF70B : public Rva003AF738
{
public:
	Rva003AF70B(const Rva003AF70B &other);
	virtual ~Rva003AF70B();
};

Rva003AF70B::Rva003AF70B(const Rva003AF70B &other)
	: Rva003AF738(other)
{
}

// ??0Rva003AF7FE@@QAE@ABV0@@Z @0x003AF7FE 98B: copy ctor with LineEmissionVolumeInfo base at +0x1c.
// Evidence: calls rowed base 0x003AF50D then rowed Line copy 0x003A653B; neg/sbb/and null-guarded
// adjustment of source to +0x1c for the Line base; vptrs at +0/+0x14/+0x18/+0x1c DIR32;
// same Intermediate3AFC6FC pre-Line stores as rowed 0x003AF5AC and 0x003AF738 Sphere version;
// unlocks 0x003AF7D1.
class Rva003AF7FE : public Intermediate3AFC6FC, public FXParticleSystem::LineEmissionVolumeInfo
{
public:
	Rva003AF7FE(const Rva003AF7FE &other);
	virtual ~Rva003AF7FE();
};

Rva003AF7FE::Rva003AF7FE(const Rva003AF7FE &other)
	: Intermediate3AFC6FC(other)
	, FXParticleSystem::LineEmissionVolumeInfo((const FXParticleSystem::LineEmissionVolumeInfo &)other)
{
}

// ??0Rva003AF7D1@@QAE@ABV0@@Z @0x003AF7D1 45B: derived copy calling rowed 0x003AF7FE then own 4 vptrs.
// Evidence: calls 0x003AF7FE (landed this session) then stores at +0/+0x14/+0x18/+0x1c DIR32;
// same 45B shape as rowed 0x003AF70B and 0x003AF57F; caller 0x003AF79A calls this; unlocks 0x003AF79A.
class Rva003AF7D1 : public Rva003AF7FE
{
public:
	Rva003AF7D1(const Rva003AF7D1 &other);
	virtual ~Rva003AF7D1();
};

Rva003AF7D1::Rva003AF7D1(const Rva003AF7D1 &other)
	: Rva003AF7FE(other)
{
}

// ??0Rva003AF9A9@@QAE@ABV0@@Z @0x003AF9A9 98B: copy ctor with TerrainFireEmissionInfo base at +0x1c.
// Evidence: calls rowed base 0x003AF50D then rowed TerrainFire copy 0x003A6E0E; neg/sbb/and null-guarded
// adjustment of source to +0x1c for the TerrainFire base; vptrs at +0/+0x14/+0x18/+0x1c DIR32;
// same Intermediate3AFC6FC pre-stores as rowed Line/Sphere versions; unlocks 0x003AF97C.
namespace FXParticleSystem
{
class Snapshot9A9
{
public:
	virtual ~Snapshot9A9();
};
class EmissionVolumeInfo9A9 : public Snapshot9A9
{
public:
	virtual ~EmissionVolumeInfo9A9();
	bool m_flag;
};
class TerrainFireEmissionInfo : public EmissionVolumeInfo9A9
{
public:
  TerrainFireEmissionInfo(const TerrainFireEmissionInfo &that) throw();
  virtual ~TerrainFireEmissionInfo();
private:
  float m_unk[4];
};
}

class Rva003AF9A9 : public Intermediate3AFC6FC, public FXParticleSystem::TerrainFireEmissionInfo
{
public:
	Rva003AF9A9(const Rva003AF9A9 &other);
	virtual ~Rva003AF9A9();
};

Rva003AF9A9::Rva003AF9A9(const Rva003AF9A9 &other)
	: Intermediate3AFC6FC(other)
	, FXParticleSystem::TerrainFireEmissionInfo((const FXParticleSystem::TerrainFireEmissionInfo &)other)
{
}

// ??0Rva003AF97C@@QAE@ABV0@@Z @0x003AF97C 45B: derived copy calling rowed 0x003AF9A9 then own 4 vptrs.
// Evidence: calls 0x003AF9A9 (landed this session) then stores at +0/+0x14/+0x18/+0x1c DIR32;
// same 45B shape as rowed 0x003AF7D1; caller 0x003AF945 calls this; unlocks 0x003AF945.
class Rva003AF97C : public Rva003AF9A9
{
public:
	Rva003AF97C(const Rva003AF97C &other);
	virtual ~Rva003AF97C();
};

Rva003AF97C::Rva003AF97C(const Rva003AF97C &other)
	: Rva003AF9A9(other)
{
}

// ??0Rva003AF4AA@@QAE@ABV0@@Z @0x003AF4AA 99B: copy ctor with inline EmissionVolumeInfo base at +0x1c.
// Evidence: calls rowed base 0x003AF50D; second base inlined as base vtable DIR32 plus byte copy
// from other+0x20 to this+0x20 (neg/sbb/and null-guarded adjustment to +0x1c then al from +4);
// vptrs at +0/+0x14/+0x18/+0x1c DIR32; same Intermediate3AFC6FC pre-stores; unlocks 0x003AF47D.
namespace FXParticleSystem
{
class EmissionVolumeInfo4AA
{
public:
	virtual ~EmissionVolumeInfo4AA();
	bool m_flag;
};
}

class Rva003AF4AA : public Intermediate3AFC6FC, public FXParticleSystem::EmissionVolumeInfo4AA
{
public:
	Rva003AF4AA(const Rva003AF4AA &other);
	virtual ~Rva003AF4AA();
};

Rva003AF4AA::Rva003AF4AA(const Rva003AF4AA &other)
	: Intermediate3AFC6FC(other)
	, FXParticleSystem::EmissionVolumeInfo4AA((const FXParticleSystem::EmissionVolumeInfo4AA &)other)
{
}

// ??0Rva003AF47D@@QAE@ABV0@@Z @0x003AF47D 45B: derived copy calling rowed 0x003AF4AA then own 4 vptrs.
// Evidence: calls 0x003AF4AA (landed this session) then stores at +0/+0x14/+0x18/+0x1c DIR32;
// same 45B shape as rowed 0x003AF97C; caller 0x003AF446 calls this; unlocks 0x003AF446.
class Rva003AF47D : public Rva003AF4AA
{
public:
	Rva003AF47D(const Rva003AF47D &other);
	virtual ~Rva003AF47D();
};

Rva003AF47D::Rva003AF47D(const Rva003AF47D &other)
	: Rva003AF4AA(other)
{
}

// ??0Rva003AE465@@QAE@ABV0@@Z @0x003AE465 45B: ParticleTerrainCollisionModuleInfo copy ctor calling rowed base 0x003AF50D then own 3 vptrs.
// Evidence: calls 0x003AF50D then stores at +0x18/+0/+0x14/+0x18 DIR32; primary 0x00C1D3F4 second 0x00C1C780 third 0x00C1BAC0 overwritten by 0x00C1D3E4; name getter 0x003AE336 returns ParticleTerrainCollisionModuleInfo; unlocks 0x003AE43F.
// ??0Rva003AE465@@QAE@ABV0@@Z @0x003AE465 present-unmatched
class Rva003AE465 : public Rva003AF50D, public ModuleInfoThirdBAC0
{
public:
	Rva003AE465(const Rva003AE465 &other);
	virtual ~Rva003AE465();
};

Rva003AE465::Rva003AE465(const Rva003AE465 &other)
	: Rva003AF50D(other)
{
}

// ??0Rva003AE43F@@QAE@ABV0@@Z @0x003AE43F 38B: derived copy calling rowed 0x003AE465 then own 3 vptrs.
// Evidence: calls 0x003AE465 then stores at +0/+0x14/+0x18 DIR32; primary 0x00C1CC28 second 0x00C1CC24 third 0x00C1C324; caller staticInitModules 0x003AE42D; unlocks none.
// ??0Rva003AE43F@@QAE@ABV0@@Z @0x003AE43F present-unmatched
class Rva003AE43F : public Rva003AE465
{
public:
	Rva003AE43F(const Rva003AE43F &other);
	virtual ~Rva003AE43F();
};

Rva003AE43F::Rva003AE43F(const Rva003AE43F &other)
	: Rva003AE465(other)
{
}

// ??0Rva003AE50B@@QAE@ABV0@@Z @0x003AE50B 45B: copy ctor calling rowed base 0x003AF50D then own 3 vptrs.
// Evidence: calls 0x003AF50D then stores at +0x18/+0/+0x14/+0x18 DIR32; primary 0x00C1D440 second 0x00C1C780 third 0x00C1BD10 overwritten by 0x00C1D430; unlocks 0x003AE4E5.
// ??0Rva003AE50B@@QAE@ABV0@@Z @0x003AE50B present-unmatched
class Rva003AE50B : public Rva003AF50D, public ModuleInfoThirdBD10
{
public:
	Rva003AE50B(const Rva003AE50B &other);
	virtual ~Rva003AE50B();
};

Rva003AE50B::Rva003AE50B(const Rva003AE50B &other)
	: Rva003AF50D(other)
{
}

// ??0Rva003AE4E5@@QAE@ABV0@@Z @0x003AE4E5 38B: derived copy calling rowed 0x003AE50B then own 3 vptrs.
// Evidence: calls 0x003AE50B then stores at +0/+0x14/+0x18 DIR32; primary 0x00C1CC58 second 0x00C1CC54 third 0x00C1C378; unlocks 0x003AE4AE.
// ??0Rva003AE4E5@@QAE@ABV0@@Z @0x003AE4E5 present-unmatched
class Rva003AE4E5 : public Rva003AE50B
{
public:
	Rva003AE4E5(const Rva003AE4E5 &other);
	virtual ~Rva003AE4E5();
};

Rva003AE4E5::Rva003AE4E5(const Rva003AE4E5 &other)
	: Rva003AE50B(other)
{
}

// ??0Rva003AE595@@QAE@ABV0@@Z @0x003AE595 45B: copy ctor calling rowed base 0x003AF50D then own 3 vptrs.
// Evidence: calls 0x003AF50D then stores at +0x18/+0/+0x14/+0x18 DIR32; primary 0x00C1D47C second 0x00C1C780 third 0x00C1BD30 overwritten by 0x00C1D46C; unlocks 0x003AE56F.
// ??0Rva003AE595@@QAE@ABV0@@Z @0x003AE595 present-unmatched
class Rva003AE595 : public Rva003AF50D, public ModuleInfoThirdBD30
{
public:
	Rva003AE595(const Rva003AE595 &other);
	virtual ~Rva003AE595();
};

Rva003AE595::Rva003AE595(const Rva003AE595 &other)
	: Rva003AF50D(other)
{
}

// ??0Rva003AE56F@@QAE@ABV0@@Z @0x003AE56F 38B: derived copy calling rowed 0x003AE595 then own 3 vptrs.
// Evidence: calls 0x003AE595 then stores at +0/+0x14/+0x18 DIR32; primary 0x00C1CC98 second 0x00C1CC94 third 0x00C1CC84; unlocks 0x003AE538.
// ??0Rva003AE56F@@QAE@ABV0@@Z @0x003AE56F present-unmatched
class Rva003AE56F : public Rva003AE595
{
public:
	Rva003AE56F(const Rva003AE56F &other);
	virtual ~Rva003AE56F();
};

Rva003AE56F::Rva003AE56F(const Rva003AE56F &other)
	: Rva003AE595(other)
{
}

// ??0Rva003AE61F@@QAE@ABV0@@Z @0x003AE61F 45B: copy ctor calling rowed base 0x003AF50D then own 3 vptrs.
// Evidence: calls 0x003AF50D then stores at +0x18/+0/+0x14/+0x18 DIR32; primary 0x00C1D4B8 second 0x00C1C780 third 0x00C1BD50 overwritten by 0x00C1D4A8; unlocks 0x003AE5F9.
// ??0Rva003AE61F@@QAE@ABV0@@Z @0x003AE61F present-unmatched
class Rva003AE61F : public Rva003AF50D, public ModuleInfoThirdBD50
{
public:
	Rva003AE61F(const Rva003AE61F &other);
	virtual ~Rva003AE61F();
};

Rva003AE61F::Rva003AE61F(const Rva003AE61F &other)
	: Rva003AF50D(other)
{
}

// ??0Rva003AE5F9@@QAE@ABV0@@Z @0x003AE5F9 38B: derived copy calling rowed 0x003AE61F then own 3 vptrs.
// Evidence: calls 0x003AE61F then stores at +0/+0x14/+0x18 DIR32; primary 0x00C1CCD8 second 0x00C1CCD4 third 0x00C1CCC4; unlocks 0x003AE5C2.
// ??0Rva003AE5F9@@QAE@ABV0@@Z @0x003AE5F9 present-unmatched
class Rva003AE5F9 : public Rva003AE61F
{
public:
	Rva003AE5F9(const Rva003AE5F9 &other);
	virtual ~Rva003AE5F9();
};

Rva003AE5F9::Rva003AE5F9(const Rva003AE5F9 &other)
	: Rva003AE61F(other)
{
}

// ??0Rva003AF672@@QAE@ABV0@@Z @0x003AF672 98B: copy ctor with BoxEmissionVolumeInfo base at +0x1c.
// Evidence: calls rowed base 0x003AF50D then rowed Box copy 0x003A6669; neg/sbb/and null-guarded
// adjustment of source to +0x1c for the Box base; vptrs at +0/+0x14/+0x18/+0x1c DIR32;
// same Intermediate3AFC6FC pre-Box stores as rowed 0x003AF5AC Line version; caller 0x003AF645 45B;
// LINK BONUS: 1 matched file waiting via 0x003AF645.
namespace FXParticleSystem
{
class Snapshot672
{
public:
	virtual ~Snapshot672();
};
class EmissionVolumeInfo672 : public Snapshot672
{
public:
	virtual ~EmissionVolumeInfo672();
	bool m_flag;
};
class BoxEmissionVolumeInfo : public EmissionVolumeInfo672
{
public:
  BoxEmissionVolumeInfo(const BoxEmissionVolumeInfo &that) throw();
  virtual ~BoxEmissionVolumeInfo();
};
}

class Rva003AF672 : public Intermediate3AFC6FC, public FXParticleSystem::BoxEmissionVolumeInfo
{
public:
	Rva003AF672(const Rva003AF672 &other);
	virtual ~Rva003AF672();
};

Rva003AF672::Rva003AF672(const Rva003AF672 &other)
	: Intermediate3AFC6FC(other)
	, FXParticleSystem::BoxEmissionVolumeInfo((const FXParticleSystem::BoxEmissionVolumeInfo &)other)
{
}

// ??0Gen005EDB10@@QAE@PAVHost005EDA90@@@Z @0x003AF645 45B: derived copy calling rowed base 0x003AF672 then own 4 vptrs.
// Evidence: calls 0x003AF672 rowed Box copy then stores at +0/+0x14/+0x18/+0x1c DIR32; same 45B shape as rowed 0x003AF57F; caller 0x003AF60E create; LINK BONUS 1 file 55B.
class Host005EDA90;
class Gen005EDB10 : public Rva003AF672
{
public:
	Gen005EDB10(Host005EDA90 *owner);
	virtual ~Gen005EDB10();
};

Gen005EDB10::Gen005EDB10(Host005EDA90 *owner)
	: Rva003AF672(*(const Rva003AF672 *)owner)
{
}

struct Rva003AFA0BVector
{
	Rva003AFA0BVector() {}
	__forceinline Rva003AFA0BVector(const Rva003AFA0BVector &that)
	{
		x = that.x;
		y = that.y;
		z = that.z;
	}
	float x, y, z;
};

class Rva003AFA0B
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual Rva003AFA0BVector slot10(void *a, void *b) = 0;
	Rva003AFA0BVector rva003AFA0B(void *a, const Rva003AFA0BVector *source,
	                            float scale, void *b);
};

// Native 3AFA0B..3AFA64 returns the componentwise product of the input,
// a three-float virtual result at slot 0x10, and scale. RET 20 includes
// the hidden return pointer; owner, method and pointer-argument types unknown.
Rva003AFA0BVector Rva003AFA0B::rva003AFA0B(
	void *a, const Rva003AFA0BVector *source, float scale, void *b)
{
	Rva003AFA0BVector basis = slot10(a, b);
	Rva003AFA0BVector result;
	result.x = source->x * basis.x * scale;
	result.y = source->y * basis.y * scale;
	result.z = source->z * basis.z * scale;
	return result;
}
