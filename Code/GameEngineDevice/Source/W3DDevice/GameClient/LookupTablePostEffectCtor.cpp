// cl: /O1 /DNDEBUG /MD
//
// ??0LookupTablePostEffect@@QAE@XZ, retail 0x00111B84, 22 bytes.
// Target identity: the body calls the base ctor 0x0011646E (pinned as
// BfmeModuleDataSnapshotBase), installs vtable 0x00BCFAC8 and zeroes +0x08.
// That vtable's slot 0 (0x00111BE9) returns the AsciiString
// "LookupTablePostEffect" (literal 0x00BCFADC); its dtor 0x00111B9A installs
// the same vtable. The row previously named this body W3DPropDrawModuleData
// by masked byte search against the BFME1 donor; retail's ModuleFactory
// registration puts the W3DPropDrawModuleData ctor at 0x000CEF2B (vtable
// 0x00BCD420) instead. Class layout beyond +0x08 is unknown.

class BfmeModuleDataSnapshotBase
{
public:
	BfmeModuleDataSnapshotBase();
	virtual ~BfmeModuleDataSnapshotBase();

private:
	int m_04;
};

// +0x08: a pointer-sized member whose inline default ctor nulls it; its
// type is unknown (an opaque class keeps the null store after the vtable
// store, as retail has it; a scalar init is hoisted above it).
class LookupTablePostEffectField08
{
public:
	LookupTablePostEffectField08() : m_ptr(0) {}

private:
	void *m_ptr;
};

class LookupTablePostEffect : public BfmeModuleDataSnapshotBase
{
public:
	LookupTablePostEffect();
	virtual ~LookupTablePostEffect();

private:
	LookupTablePostEffectField08 m_08;
};

// ??0LookupTablePostEffect@@QAE@XZ
LookupTablePostEffect::LookupTablePostEffect()
{
}
