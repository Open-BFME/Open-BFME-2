// cl: /O1 /MD
// ??0Rva003ABAC3@@QAE@PAX0@Z @0x003ABAC3 42B
// ??0Rva003ABAF3@@QAE@PAX0@Z @0x003ABAF3 42B
// ??0Rva003ABB23@@QAE@PAX0@Z @0x003ABB23 42B
// ??0Rva003ABCB5@@QAE@PAX0@Z @0x003ABCB5 49B
// ??0Rva003ABDC8@@QAE@PAX0@Z @0x003ABDC8 49B
// ??0Rva003ABECC@@QAE@PAX0@Z @0x003ABECC 49B
// ??0Rva003ACDA0Module@@QAE@PAXPAVRva003AD71BTemplate@@@Z @0x003ACDA0 42B
// ??0Rva003ACDCFModule@@QAE@PAXPAVRva003AD757Template@@@Z @0x003ACDCF 42B
// ??0Rva003ACDFEModule@@QAE@PAXPAVRva003AD793Template@@@Z @0x003ACDFE 42B
// ??0Rva003ACF32Module@@QAE@PAXPAVRva003AD8C5Template@@@Z @0x003ACF32 49B
// ??0Rva003ACFCFModule@@QAE@PAXPAVRva003AD904Template@@@Z @0x003ACFCF 49B
// ??0Rva003AD005Module@@QAE@PAXPAVRva003AD940Template@@@Z @0x003AD005 49B
// ??0Rva003AD094Module@@QAE@PAXPAVRva003AD97FTemplate@@@Z @0x003AD094 49B
// ??0Rva003AD278Module@@QAE@PAXPAVRva003ADB21Template@@@Z @0x003AD278 49B
// ??0Rva003AD2B3Module@@QAE@PAXPAVRva003ADB44Template@@@Z @0x003AD2B3 49B
// ??0Rva003AD38BModule@@QAE@PAXPAVRva003ADBD0Template@@@Z @0x003AD38B 49B
//
// Particle-module constructor chains, two links each. Every body forwards its
// two stack arguments to one base constructor, then stamps the vtables of its
// three or four subobjects at +0, +0x14, +0x18 and +0x1C (Rva003ACD71Ctor.cpp
// and Rva003AD355ModuleCtor.cpp are landed members of the same family, written
// the same way). The module constructors are the ones the slot-2 template
// factories in ModuleTemplateFactorySlots.cpp call (pinned there); each calls
// one of the six intermediate constructors below, or an already-rowed one, and
// each intermediate calls a rowed module constructor. Call targets, store
// offsets and vtable addresses are read from retail; every class is
// address-named and no identity is inferred beyond the rowed callees.

extern const void *const g_00C1BF80[];
extern const void *const g_00C1BFB4[];
extern const void *const g_00C1C09C[];
extern const void *const g_00C1C0C0[];
extern const void *const g_00C1C150[];
extern const void *const g_00C1C378[];
extern const void *const g_00C1C388[];
extern const void *const g_00C1C3C8[];
extern const void *const g_00C1C404[];
extern const void *const g_00C1C538[];
extern const void *const g_00C1C53C[];
extern const void *const g_00C1C574[];
extern const void *const g_00C1C5B8[];
extern const void *const g_00C1C608[];
extern const void *const g_00C1C60C[];
extern const void *const g_00C1C6CC[];
extern const void *const g_00C1C6DC[];
extern const void *const g_00C1C72C[];
extern const void *const g_00C1C780[];
extern const void *const g_00C1C950[];
extern const void *const g_00C1CB24[];
extern const void *const g_00C1CB54[];
extern const void *const g_00C1CC54[];
extern const void *const g_00C1CC58[];
extern const void *const g_00C1CC84[];
extern const void *const g_00C1CC94[];
extern const void *const g_00C1CC98[];
extern const void *const g_00C1CCC4[];
extern const void *const g_00C1CCD4[];
extern const void *const g_00C1CCD8[];
extern const void *const g_00C1CDE0[];
extern const void *const g_00C1CDF0[];
extern const void *const g_00C1CE1C[];
extern const void *const g_00C1CE54[];
extern const void *const g_00C1CE64[];
extern const void *const g_00C1CE88[];
extern const void *const g_00C1CE98[];
extern const void *const g_00C1CEE8[];
extern const void *const g_00C1CEF8[];
extern const void *const g_00C1D00C[];
extern const void *const g_00C1D02C[];
extern const void *const g_00C1D0BC[];
extern const void *const g_00C1D788[];

struct Rva0055BF4BSrc;
class RvaSmartPtr12;

namespace FXParticleSystem
{
class ParticleSystem;
template <class T> class TrackingPtr;
class DefaultModuleTemplate7;
class LightningEmissionModuleTemplate;
class PointEmissionVolumeModuleTemplate;

class Rva005FEAD0DefaultModule7
{
public:
	Rva005FEAD0DefaultModule7(TrackingPtr<ParticleSystem> &system, const DefaultModuleTemplate7 *moduleTemplate);
};

class LightningEmissionModule
{
public:
	LightningEmissionModule(TrackingPtr<ParticleSystem> &system, const LightningEmissionModuleTemplate *moduleTemplate);
};
}

class Rva003AE50B { public: Rva003AE50B(void *a, void *b); };
class Rva00560A1B { public: Rva00560A1B(void *a, void *b); };
class Rva003AE61F { public: Rva003AE61F(void *a, void *b); };
class Rva003ACC7C { public: Rva003ACC7C(void *a, void *b); };
class Rva0055BF4B { public: Rva0055BF4B(const RvaSmartPtr12 &a, const Rva0055BF4BSrc *b); };
class Rva003ABD20 { public: Rva003ABD20(const RvaSmartPtr12 &a, int b); };
class Rva003ABD81 { public: Rva003ABD81(const RvaSmartPtr12 &a, int b); };
class Rva003ACC4B
{
public:
	Rva003ACC4B(FXParticleSystem::TrackingPtr<FXParticleSystem::ParticleSystem> &system,
		const FXParticleSystem::PointEmissionVolumeModuleTemplate *moduleTemplate);
};

#define STAMP(off, vtable) (*(const void **)((char *)this + (off)) = (const void *)(vtable))

// ---- intermediate constructors over rowed module constructors ----

class Rva003ABAC3 : public Rva003AE50B
{
public:
	Rva003ABAC3(void *a, void *b);
};

Rva003ABAC3::Rva003ABAC3(void *a, void *b)
	: Rva003AE50B(a, b)
{
	STAMP(0x00, g_00C1C388);
	STAMP(0x14, g_00C1C780);
	STAMP(0x18, g_00C1C378);
}

class Rva003ABAF3 : public Rva00560A1B
{
public:
	Rva003ABAF3(void *a, void *b);
};

Rva003ABAF3::Rva003ABAF3(void *a, void *b)
	: Rva00560A1B(a, b)
{
	STAMP(0x00, g_00C1C3C8);
	STAMP(0x14, g_00C1C780);
	STAMP(0x18, g_00C1CC84);
}

class Rva003ABB23 : public Rva003AE61F
{
public:
	Rva003ABB23(void *a, void *b);
};

Rva003ABB23::Rva003ABB23(void *a, void *b)
	: Rva003AE61F(a, b)
{
	STAMP(0x00, g_00C1C404);
	STAMP(0x14, g_00C1C780);
	STAMP(0x18, g_00C1CCC4);
}

class Rva003ABCB5 : public Rva0055BF4B
{
public:
	Rva003ABCB5(void *a, void *b);
};

Rva003ABCB5::Rva003ABCB5(void *a, void *b)
	: Rva0055BF4B(*(const RvaSmartPtr12 *)a, (const Rva0055BF4BSrc *)b)
{
	STAMP(0x00, g_00C1C53C);
	STAMP(0x14, g_00C1C538);
	STAMP(0x18, g_00C1C780);
	STAMP(0x1C, g_00C1CDE0);
}

class Rva003ABDC8 : public FXParticleSystem::Rva005FEAD0DefaultModule7
{
public:
	Rva003ABDC8(void *a, void *b);
};

Rva003ABDC8::Rva003ABDC8(void *a, void *b)
	: FXParticleSystem::Rva005FEAD0DefaultModule7(*(FXParticleSystem::TrackingPtr<FXParticleSystem::ParticleSystem> *)a,
		(const FXParticleSystem::DefaultModuleTemplate7 *)b)
{
	STAMP(0x00, g_00C1C60C);
	STAMP(0x14, g_00C1C608);
	STAMP(0x18, g_00C1C780);
	STAMP(0x1C, g_00C1CEE8);
}

class Rva003ABECC : public FXParticleSystem::LightningEmissionModule
{
public:
	Rva003ABECC(void *a, void *b);
};

Rva003ABECC::Rva003ABECC(void *a, void *b)
	: FXParticleSystem::LightningEmissionModule(*(FXParticleSystem::TrackingPtr<FXParticleSystem::ParticleSystem> *)a,
		(const FXParticleSystem::LightningEmissionModuleTemplate *)b)
{
	STAMP(0x00, g_00C1C6DC);
	STAMP(0x14, g_00C1C780);
	STAMP(0x18, g_00C1D788);
	STAMP(0x1C, g_00C1C6CC);
}

// ---- module constructors the template factories call ----

class Rva003AD71BTemplate;
class Rva003ACDA0Module : public Rva003ABAC3
{
public:
	Rva003ACDA0Module(void *a, Rva003AD71BTemplate *b);
};

Rva003ACDA0Module::Rva003ACDA0Module(void *a, Rva003AD71BTemplate *b)
	: Rva003ABAC3(a, b)
{
	STAMP(0x00, g_00C1CC58);
	STAMP(0x14, g_00C1CC54);
	STAMP(0x18, g_00C1C378);
}

class Rva003AD757Template;
class Rva003ACDCFModule : public Rva003ABAF3
{
public:
	Rva003ACDCFModule(void *a, Rva003AD757Template *b);
};

Rva003ACDCFModule::Rva003ACDCFModule(void *a, Rva003AD757Template *b)
	: Rva003ABAF3(a, b)
{
	STAMP(0x00, g_00C1CC98);
	STAMP(0x14, g_00C1CC94);
	STAMP(0x18, g_00C1CC84);
}

class Rva003AD793Template;
class Rva003ACDFEModule : public Rva003ABB23
{
public:
	Rva003ACDFEModule(void *a, Rva003AD793Template *b);
};

Rva003ACDFEModule::Rva003ACDFEModule(void *a, Rva003AD793Template *b)
	: Rva003ABB23(a, b)
{
	STAMP(0x00, g_00C1CCD8);
	STAMP(0x14, g_00C1CCD4);
	STAMP(0x18, g_00C1CCC4);
}

class Rva003AD8C5Template;
class Rva003ACF32Module : public Rva003ABCB5
{
public:
	Rva003ACF32Module(void *a, Rva003AD8C5Template *b);
};

Rva003ACF32Module::Rva003ACF32Module(void *a, Rva003AD8C5Template *b)
	: Rva003ABCB5(a, b)
{
	STAMP(0x00, g_00C1CDF0);
	STAMP(0x14, g_00C1C538);
	STAMP(0x18, g_00C1C950);
	STAMP(0x1C, g_00C1CDE0);
}

class Rva003AD904Template;
class Rva003ACFCFModule : public Rva003ABD20
{
public:
	Rva003ACFCFModule(void *a, Rva003AD904Template *b);
};

Rva003ACFCFModule::Rva003ACFCFModule(void *a, Rva003AD904Template *b)
	: Rva003ABD20(*(const RvaSmartPtr12 *)a, (int)b)
{
	STAMP(0x00, g_00C1CE64);
	STAMP(0x14, g_00C1C574);
	STAMP(0x18, g_00C1CE1C);
	STAMP(0x1C, g_00C1CE54);
}

class Rva003AD940Template;
class Rva003AD005Module : public Rva003ABD81
{
public:
	Rva003AD005Module(void *a, Rva003AD940Template *b);
};

Rva003AD005Module::Rva003AD005Module(void *a, Rva003AD940Template *b)
	: Rva003ABD81(*(const RvaSmartPtr12 *)a, (int)b)
{
	STAMP(0x00, g_00C1CE98);
	STAMP(0x14, g_00C1C5B8);
	STAMP(0x18, g_00C1BF80);
	STAMP(0x1C, g_00C1CE88);
}

class Rva003AD97FTemplate;
class Rva003AD094Module : public Rva003ABDC8
{
public:
	Rva003AD094Module(void *a, Rva003AD97FTemplate *b);
};

Rva003AD094Module::Rva003AD094Module(void *a, Rva003AD97FTemplate *b)
	: Rva003ABDC8(a, b)
{
	STAMP(0x00, g_00C1CEF8);
	STAMP(0x14, g_00C1C608);
	STAMP(0x18, g_00C1BFB4);
	STAMP(0x1C, g_00C1CEE8);
}

class Rva003ADB21Template;
class Rva003AD278Module : public Rva003ACC4B
{
public:
	Rva003AD278Module(void *a, Rva003ADB21Template *b);
};

Rva003AD278Module::Rva003AD278Module(void *a, Rva003ADB21Template *b)
	: Rva003ACC4B(*(FXParticleSystem::TrackingPtr<FXParticleSystem::ParticleSystem> *)a,
		(const FXParticleSystem::PointEmissionVolumeModuleTemplate *)b)
{
	STAMP(0x00, g_00C1D00C);
	STAMP(0x14, g_00C1C09C);
	STAMP(0x18, g_00C1C72C);
	STAMP(0x1C, g_00C1CB24);
}

class Rva003ADB44Template;
class Rva003AD2B3Module : public Rva003ACC7C
{
public:
	Rva003AD2B3Module(void *a, Rva003ADB44Template *b);
};

Rva003AD2B3Module::Rva003AD2B3Module(void *a, Rva003ADB44Template *b)
	: Rva003ACC7C(a, b)
{
	STAMP(0x00, g_00C1D02C);
	STAMP(0x14, g_00C1C0C0);
	STAMP(0x18, g_00C1D788);
	STAMP(0x1C, g_00C1CB54);
}

class Rva003ADBD0Template;
class Rva003AD38BModule : public Rva003ABECC
{
public:
	Rva003AD38BModule(void *a, Rva003ADBD0Template *b);
};

Rva003AD38BModule::Rva003AD38BModule(void *a, Rva003ADBD0Template *b)
	: Rva003ABECC(a, b)
{
	STAMP(0x00, g_00C1D0BC);
	STAMP(0x14, g_00C1C150);
	STAMP(0x18, g_00C1D788);
	STAMP(0x1C, g_00C1C6CC);
}

