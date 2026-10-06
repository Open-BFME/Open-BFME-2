// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ??1HAnimComboClass@@QAE@XZ @0x001977D0 94B
// HAnimComboClass dtor: calls Reset() then inlines the VectorClass member
// destructor (Vector at +4, VectorMax at +8, IsValid +0xC, IsAllocated +0xD).
// Retail uses the inline SEH prologue and leaves the EH state at 0 across the
// inlined member dtor; declaring the global delete operators throw() is what
// stops /O2 from emitting a state -1 store before the member-dtor body.
void operator delete[](void *block) throw();
void operator delete(void *block) throw();

class HAnimComboDataClass;

template <class T>
class VectorClass
{
public:
	virtual ~VectorClass()
	{
		if (Vector != 0 && IsAllocated)
		{
			delete[] Vector;
			Vector = 0;
		}
		IsAllocated = false;
		VectorMax = 0;
	}

	T *Vector;			// +0x04
	int VectorMax;			// +0x08
	bool IsValid;			// +0x0c
	bool IsAllocated;		// +0x0d
};

class HAnimComboClass
{
public:
	void Reset();
	~HAnimComboClass();

protected:
	VectorClass<HAnimComboDataClass *> HAnimComboData;
};

HAnimComboClass::~HAnimComboClass()
{
	Reset();
}
