// cl: /G7 /DNDEBUG

// VectorClass<TextureStatisticsStruct>::Resize at 0x00129990, split out of
// TextureStatisticsVector.cpp because retail built it with /G7 -- add reg,1
// and add reg,-1 where the default build writes inc and dec -- while that
// unit's RefCountPtr<TextureClass>::operator= at 0x000424D0 only matches
// without it.  The models below are the ones TextureStatisticsVector.cpp
// carries, Add_Ref's body included, so the element copy inlines the same way.

#include <new.h>

extern void *__cdecl operator new[](size_t size);
extern void __cdecl operator delete[](void *pointer);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
	void Add_Ref();
	void Release_Ref();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureClass : public TextureBaseClass
{
};

void TextureBaseClass::Add_Ref()
{
	++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
}

template<class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/ref_ptr.h
class RefCountPtr
{
public:
	RefCountPtr() : Referent(0) {}
	RefCountPtr(RefCountPtr const &other) : Referent(other.Referent)
	{
		if (Referent != 0)
			Referent->Add_Ref();
	}
	// BFME's destructor does not null the pointer (see TextureStatisticsVector.cpp).
	~RefCountPtr()
	{
		if (Referent != 0)
		{
			Referent->Release_Ref();
		}
	}
	RefCountPtr const &operator=(RefCountPtr const &other)
	{
		if (other.Referent != 0)
			other.Referent->Add_Ref();
		if (Referent != 0)
			Referent->Release_Ref();
		Referent = other.Referent;
		return *this;
	}
	bool operator==(RefCountPtr const &other) const { return Referent == other.Referent; }
	bool operator!=(RefCountPtr const &other) const { return Referent != other.Referent; }

private:
	T *Referent;
};

struct TextureStatisticsStruct
{
	RefCountPtr<TextureClass> tex;
	int usage_count;
	int change_count;
};

template<class T>
class VectorClass
{
public:
	VectorClass(unsigned size, T const *array);
	VectorClass(VectorClass const &);
	virtual ~VectorClass();
	VectorClass &operator=(VectorClass const &);
	virtual bool operator==(VectorClass const &) const;
	virtual bool Resize(int size, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *ptr);
	virtual int ID(T const &object);
	int Length() const { return VectorMax; }
	T &operator[](int index) { return Vector[index]; }

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

template<class T>
bool VectorClass<T>::Resize(int newsize, T const *array)
{
	if (newsize)
	{
		T *newptr;
		IsValid = false;
		if (!array)
		{
			newptr = new T[newsize];
		}
		else
		{
			newptr = new ((void *)array) T[newsize];
		}
		IsValid = true;
		if (!newptr)
			return false;

		if (Vector != 0)
		{
			int copycount = (newsize < VectorMax) ? newsize : VectorMax;
			for (int index = 0; index < copycount; ++index)
				newptr[index] = Vector[index];

			if (IsAllocated)
			{
				delete [] Vector;
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
	return true;
}

template bool VectorClass<TextureStatisticsStruct>::Resize(
	int, TextureStatisticsStruct const *);
