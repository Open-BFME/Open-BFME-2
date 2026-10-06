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
