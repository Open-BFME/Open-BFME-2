// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// LatchRestore<int>'s destructor at 0x002E7F71.

template <typename StoredType>
class LatchRestore
{
protected:
	StoredType savedValue;
	StoredType &latchedField;

public:
	LatchRestore(StoredType &dest, const StoredType &src);
	virtual ~LatchRestore(void);
};

template <typename StoredType>
LatchRestore<StoredType>::LatchRestore(StoredType &dest, const StoredType &src) :
	latchedField(dest)
{
	savedValue = dest;
	dest = src;
}

template <typename StoredType>
LatchRestore<StoredType>::~LatchRestore(void)
{
	latchedField = savedValue;
}

template class LatchRestore<int>;

// Native 0x002E7F80..0x002E7F86 is a complete six-byte leaf after the
// preceding destructor's RET.  It subtracts 12 from raw word zero and
// returns the receiver.  The original owner, word interpretation and full
// object bounds are unknown; adjacency does not make this LatchRestore.
// Structural guide: BFME1 9cbfb551 Rva3CxxTinyBodies.cpp /O1 /arch:SSE /G7.
struct Rva002E7F80Fields
{
    unsigned int word0;
    Rva002E7F80Fields *decrement();
};

// ?decrement@Rva002E7F80Fields@@QAEPAU1@XZ
Rva002E7F80Fields *Rva002E7F80Fields::decrement()
{
    word0 -= 12;
    return this;
}
