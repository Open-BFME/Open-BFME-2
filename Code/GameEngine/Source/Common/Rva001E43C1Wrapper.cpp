// cl: /DNDEBUG /MD /EHsc
// Object::isUsingAirborneLocomotor (0x0028B81E) is rowed in
// ObjectIsUsingAirborneLocomotor.cpp; this unit holds only the 0x001E43C1
// flag-setter wrapper below, so it carries no second definition of it.

#include "../../Include/GameLogic/LocomotorTemplate.h"

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
