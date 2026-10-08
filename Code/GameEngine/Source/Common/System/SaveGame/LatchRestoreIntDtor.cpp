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
