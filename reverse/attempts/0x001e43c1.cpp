// ?rva001E43C1@Rva001E43C1@@QAEX_N@Z
// partial score=1.0 date=2026-10-09
// cl: /DNDEBUG /MD /EHsc
// ?isUsingAirborneLocomotor@Object@@QBE_NXZ @0x0028B81E
// (36B): Object::isUsingAirborneLocomotor, BFME1 ObjectFields.cpp verbatim
// with BFME2 offsets. m_ai at +0x258, cur locomotor at AI+0x1f0, template at
// loco+0x04, surfaces at tmpl+0x14 with AIR as (1<<3). Callers include
// 0x004671E8 0x00429903 0x00483CC0.

class LocomotorTemplate
{
public:
	unsigned char m_pad[0x14];
	int m_surfaces; // +0x14, AIR is (1<<3)
};

class Locomotor
{
public:
	// Rva0028B81EGetSurfaces: NOT the real Locomotor::getLegalSurfaces (kept
	// copy in AIUpdate.cpp tests m_template==null and calls
	// Overridable::getFinalOverride). Retail 0x0028B81E inlines only the
	// direct m_template->m_surfaces load, so this TU uses an honest
	// address-named accessor to avoid emitting a differing
	// ?getLegalSurfaces@Locomotor@@QBEHXZ COMDAT.
	int rva0028B81EGetSurfaces() const { return m_template->m_surfaces; }

private:
	// Retain the private access in the existing callee's decorated ABI.
	// Friendship is only this unit's access bridge; it establishes no
	// original relationship between the two independently named views.
	friend class Rva001E43C1;
	enum LocoFlag { RVA001E43C1_FLAG = 4 };
	void setFlag(LocoFlag flag, bool enabled);

	unsigned char m_pad[4];
	const LocomotorTemplate *m_template; // +0x04
};

class AIUpdateInterface
{
public:
	Locomotor *getCurLocomotor() const { return m_curLocomotor; }

private:
	unsigned char m_pad[0x1f0];
	Locomotor *m_curLocomotor; // +0x1f0
};

class Object
{
public:
	bool isUsingAirborneLocomotor() const;

private:
	unsigned char m_pad[0x258];
	AIUpdateInterface *m_ai; // +0x258
};

bool Object::isUsingAirborneLocomotor() const
{
	return (m_ai && m_ai->getCurLocomotor() && ((m_ai->getCurLocomotor()->rva0028B81EGetSurfaces() & (1 << 3)) != 0));
}

// Native 0x001E43C1..0x001E43CF is a complete thiscall entry between the
// preceding RET8 and the independently rowed matrix copy. It forwards its
// one consumed bool with index four to the existing setFlag body, preserving
// ECX. No callers establish this wrapper's original class or method name.
// BFME1 f98983a7 assetstatus.cpp supplied the constant-argument wrapper
// shape under O1/SSE2/G6; its Report_Missing_HAnim name and string argument
// do not apply to the target's independently verified flag-setter callee.
class Rva001E43C1
{
public:
	void rva001E43C1(bool enabled);
};

void Rva001E43C1::rva001E43C1(bool enabled)
{
	reinterpret_cast<Locomotor *>(this)->setFlag(
		Locomotor::RVA001E43C1_FLAG, enabled);
}
