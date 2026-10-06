// cl: /DNDEBUG /MD
//
// ?rva0028AC34@Object@@QAEX_N@Z @0x0028AC34 26B
// Private-status bit setter at Object+0x438 (bit 1). The +0x438 private
// status byte is proven by Object::friend_notifyOfNewMapBoundary
// (retail 0x0028B5EE in Object_friendNotifyOfNewMapBoundary.cpp) and the
// 11 callers of this body. Identity beyond Object+0x438 is unproven so the
// name stays address-derived. Flags from Object setters
// (ObjectSetProducer.cpp /O1 /DNDEBUG /MD); /O1 selects the retail
// cmp-je plus or-byte/and-byte shape.
//
// ?rva0028BFF9@Object@@QAEXI@Z @0x0028BFF9 38B: sets that bit from
// (arg > 0) through rva0028AC34, then forwards (arg, false) to the rowed
// ObjectDefectionHelper::rva004DF725 0x004DF725 on the helper at +0x238 when
// present; caller 0x001F2620. Retail keeps this in ecx across the
// rva0028AC34 call, which cl only does when the callee was compiled earlier
// in the same TU, so it follows the setter here.

class ObjectDefectionHelper
{
public:
	void rva004DF725(unsigned int arg1, bool arg2);
};

class Object
{
public:
	void rva0028AC34(bool on);
	void rva0028BFF9(unsigned int arg);

private:
	unsigned char m_pad00[0x238];
	ObjectDefectionHelper *m_helper238; // +0x238
	unsigned char m_pad23C[0x438 - 0x23C];
	unsigned char m_privateStatus; // +0x438
};

void Object::rva0028AC34(bool on)
{
	if (on)
		m_privateStatus |= 2;
	else
		m_privateStatus &= ~2;
}

void Object::rva0028BFF9(unsigned int arg)
{
	rva0028AC34(arg > 0);
	ObjectDefectionHelper *helper = m_helper238;
	if (helper)
		helper->rva004DF725(arg, false);
}
