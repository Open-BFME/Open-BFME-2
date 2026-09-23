// cl: /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Donor: BFME 1 WW3D2/PendingSurfaceStructResizeThunk.cpp.
// Target vector ctor 0x157280 installs table 0xBD3C48; slot 2 identifies
// Resize. Its full 392 bytes end at 0x157908; Ghidra truncates the ret 8.
// Element ctor 0x156A10 and assignment 0x1568E0 establish the surface at +0
// and 24-byte renderer vector at +4. ActiveCount/GrowthStep are at record
// offsets 0x14/0x18 (vector 0x10/0x14). Resize confirms the 0x1C stride.
// Array callbacks are ctor 0x156A10 and dtor 0x290D. The latter clears the
// vector via 0xF0CD4 then tail-calls the surface destructor at 0x176CB0;
// its composition is established even though that dtor has no ledger row.
// Member assignment calls the existing vector-base assignment at 0x154C50.

#include <new.h>

extern void *__cdecl operator new[](size_t size);
extern void __cdecl operator delete[](void *pointer);

// Surface COM-style AddRef/Release calls use the surface object's vtable.
class SurfaceResource
{
public:
	virtual void unused00();
	virtual unsigned long __stdcall addRef();
	virtual unsigned long __stdcall release();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.h
class W3DRadarResetSurface
{
public:
	W3DRadarResetSurface(void) : m_surface(0) {}
	~W3DRadarResetSurface();

	W3DRadarResetSurface &operator=(const W3DRadarResetSurface &that);

protected:
	SurfaceResource *m_surface;
};

// ?W3DRadarResetSurface::operator= present-unmatched
W3DRadarResetSurface &W3DRadarResetSurface::operator=(const W3DRadarResetSurface &that)
{
	if (that.m_surface)
		that.m_surface->addRef();
	if (m_surface)
		m_surface->release();
	m_surface = that.m_surface;
	return *this;
}

class BfmeRendererVectorBase
{
public:
	BfmeRendererVectorBase(int size = 0, void *const *array = 0);
	virtual ~BfmeRendererVectorBase(void);
	virtual bool operator==(BfmeRendererVectorBase const &) const;
	virtual bool Resize(int newsize, void *const *array = 0);
	virtual void Clear(void);
	virtual int ID(void *const *ptr);
	virtual int ID(void *const &ptr);

	BfmeRendererVectorBase &operator=(const BfmeRendererVectorBase &that);

	void **Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

// ?BfmeRendererVectorBase::BfmeRendererVectorBase present-unmatched
inline BfmeRendererVectorBase::BfmeRendererVectorBase(int size, void *const *array) :
	Vector(0), VectorMax(size), IsValid(true), IsAllocated(false)
{
	(void)array;
	if (size)
	{
		if (array)
			Vector = (void **)array;
		else
		{
			Vector = new void *[size];
			IsAllocated = true;
		}
	}
}

class DynamicVectorDummy : public BfmeRendererVectorBase
{
public:
	DynamicVectorDummy(int size = 0, void *const *array = 0);

	int ActiveCount;
	int GrowthStep;
};

// ?DynamicVectorDummy::DynamicVectorDummy present-unmatched
inline DynamicVectorDummy::DynamicVectorDummy(int size, void *const *array)
	: BfmeRendererVectorBase(size, array)
{
	GrowthStep = 10;
	ActiveCount = 0;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.h
class Render2DSentenceClass
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.h
	struct PendingSurfaceStruct : public W3DRadarResetSurface
	{
		PendingSurfaceStruct(void); // matched target ctor at 0x00156A10
		~PendingSurfaceStruct(void); // array callback thunk at retail VA 0x0040290D

		DynamicVectorDummy Renderers;
	};
};

typedef Render2DSentenceClass::PendingSurfaceStruct PendingSurfaceStruct;

template <class T> class VectorClass
{
public:
	VectorClass(int size = 0, T const *array = 0);
	virtual ~VectorClass(void);								///< vtable +0x00
	virtual bool operator==(const VectorClass<T> &) const;	///< vtable +0x04
	virtual bool Resize(int newsize, T const *array = 0);		///< vtable +0x08
	virtual void Clear(void);									///< vtable +0x0C
	virtual int ID(T const *ptr);								///< vtable +0x10
	virtual int ID(T const &ptr);								///< vtable +0x14

protected:
	T &operator[](int index) { return Vector[index]; }
	int Length(void) const { return VectorMax; }

	T *Vector;						///< retail this+0x04
	int VectorMax;					///< retail this+0x08
	bool IsValid;					///< retail this+0x0C
	bool IsAllocated;				///< retail this+0x0D
	bool VectorClassPad[2];
};

template <class T>
VectorClass<T>::VectorClass(int size, T const *array) :
	Vector(0), VectorMax(size), IsValid(true), IsAllocated(false)
{
	if (size)
	{
		if (array)
			Vector = new ((void *)array) T[size];
		else
		{
			Vector = new T[size];
			IsAllocated = true;
		}
	}
}

// ?Resize@?$VectorClass@UPendingSurfaceStruct@Render2DSentenceClass@@@@UAE_NHPBUPendingSurfaceStruct@Render2DSentenceClass@@@Z
template <class T>
bool VectorClass<T>::Resize(int newsize, T const *array)
{
	if (newsize)
	{
		T *newptr;

		IsValid = false;
		if (!array)
			newptr = new T[newsize];
		else
			newptr = new ((void *)array) T[newsize];
		IsValid = true;
		if (!newptr)
			return (false);

		if (Vector != 0)
		{
			int copycount = (newsize < VectorMax) ? newsize : VectorMax;
			for (int index = 0; index < copycount; index++)
				newptr[index] = Vector[index];

			if (IsAllocated)
			{
				delete[] Vector;
				Vector = 0;
			}
		}

		Vector = newptr;
		VectorMax = newsize;
		IsAllocated = (Vector && !array);
	}
	else
	{
		Clear();
	}
	return (true);
}

// Force emission of the Resize instantiation even though nothing else in
// this isolated TU calls it.
template VectorClass<PendingSurfaceStruct>::VectorClass(int, PendingSurfaceStruct const *);
template bool VectorClass<PendingSurfaceStruct>::Resize(int, PendingSurfaceStruct const *);

template <class T>
class DynamicVectorClass : public VectorClass<T>
{
public:
	bool Add(T const &object)
	{
		if (ActiveCount >= this->Length()) {
			if ((this->IsAllocated || !this->VectorMax) && GrowthStep > 0) {
				if (!this->Resize(this->Length() + GrowthStep))
					return false;
			} else {
				return false;
			}
		}

		(*this)[ActiveCount++] = object;
		return true;
	}

protected:
	int ActiveCount;
	int GrowthStep;
};

template bool DynamicVectorClass<PendingSurfaceStruct>::Add(
	PendingSurfaceStruct const &);
