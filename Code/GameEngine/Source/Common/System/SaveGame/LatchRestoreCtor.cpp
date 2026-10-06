// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// LatchRestore<bool>'s constructor at 0x00519FC.
// Trimmed from the BFME1 GameState.cpp donor (byte-identical body, clean transfer):
// only the placed constructor is defined here; the donor's other bodies
// (including its naked populateSaveGameListbox lift) stay out.

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

template class LatchRestore<bool>;
