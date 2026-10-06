// cl: /Oy- /DNDEBUG /MD /GX
//
// Value-returning smart-pointer getter with the RVO idiom proven by
// StlportStringRvoGetters.cpp (retail 0x00389E2D etc., 30 bytes):
// retail 0x003FDA90 (30 bytes) returns the 12-byte reference-counted
// smart-pointer member at +0x15C via the hidden return pointer; the
// member copy-constructs directly into it (RVO) through the copy body
// at 0x4CC19 (opaque pin: raw-ptr store + AddRef-or-zero triple), and
// the function returns the hidden pointer. The copy constructor and
// destructor are declared only so the call resolves to the pin and the
// EH state slot emits (declare-only-dtor trigger). Class names are
// address-derived (identity unrecoverable from 30 bytes); member names
// positional.

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

class Rva003FDA90SmartField
{
public:
	RvaSmartPtr12 get() const;

private:
	char m_pad[0x15C];
	RvaSmartPtr12 m_value; // +0x15C
};

// ?get@Rva003FDA90SmartField@@QBE?AVRvaSmartPtr12@@XZ
RvaSmartPtr12 Rva003FDA90SmartField::get() const
{
	return m_value;
}
