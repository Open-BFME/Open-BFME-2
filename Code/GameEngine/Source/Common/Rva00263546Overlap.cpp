// cl: /Ob1 /DNDEBUG /MD
//
// ?rva00263546@Rva00263546@@QBE_NPBV1@@Z @0x00263546 (35B).
// Rva00263546 overlap test: returns true when any of the 19 dwords at +0
// shares a set bit with the other object. Retail computes other-this once
// then loops with test [ecx] esi over 0x13 dwords. Callers include 0x0026545E
// and 0x00265B5D which pass 76-byte mask objects and test al.

typedef bool Bool;

class Rva00263546
{
public:
	bool rva00263546(const Rva00263546 *other) const;
	bool rva00265459(const Rva00263546 *other) const;

private:
	int m_mask[19];
};

bool Rva00263546::rva00263546(const Rva00263546 *other) const
{
	for (unsigned int i = 0; i < 19; ++i) {
		if ((m_mask[i] & other->m_mask[i]) != 0)
			return true;
	}
	return false;
}

// Native 0x00265459..0x00265466, RET4: other is the receiver and this
// is its argument. The existing nineteen-word mask body supplies both views;
// the operation's original spelling remains unknown.
bool Rva00263546::rva00265459(const Rva00263546 *other) const
{
    return other->rva00263546(this);
}
