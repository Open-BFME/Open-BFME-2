// cl: /DNDEBUG /MD /EHsc
//
// The DynamicVectorClass<EnumParameterClass::ENUM_VALUE>::Resize caller at
// 0x0093E700 reaches this shared 8-byte VectorClass body. Retail's constructor
// at 0x0093D1E0 and destructor thunk at 0x000470F5 show a reference-counted
// surface in the record's second word, so this source uses the retail RVA for
// the ICF-shared body name.

#include <new.h>

extern void *__cdecl operator new[](size_t size);
extern void __cdecl operator delete[](void *pointer);

class Rva0093E4D0SurfaceResource
{
public:
	virtual void unused00();
	virtual unsigned long __stdcall addRef();
	virtual unsigned long __stdcall release();
};

class Rva0093E4D0Surface
{
public:
	Rva0093E4D0Surface() : m_surface(0) {}
	~Rva0093E4D0Surface();

	Rva0093E4D0Surface &operator=(const Rva0093E4D0Surface &that)
	{
		if (that.m_surface)
			that.m_surface->addRef();
		if (m_surface)
			m_surface->release();
		m_surface = that.m_surface;
		return *this;
	}

private:
	Rva0093E4D0SurfaceResource *m_surface;
};

class Rva0093E4D0Element
{
public:
	Rva0093E4D0Element();
	~Rva0093E4D0Element();

	Rva0093E4D0Element &operator=(const Rva0093E4D0Element &that)
	{
		m_first = that.m_first;
		m_surface = that.m_surface;
		return *this;
	}

	void *m_first;
	Rva0093E4D0Surface m_surface;
};

template <class T>
class Rva0093E4D0Vector
{
public:
	Rva0093E4D0Vector(int size = 0, T const *array = 0);
	virtual ~Rva0093E4D0Vector(void);
	virtual bool equal(const Rva0093E4D0Vector<T> &) const;
	virtual bool resize(int newsize, T const *array = 0);
	virtual void clear(void);
	virtual int id(T const *ptr);
	virtual int id(T const &ptr);

protected:
	T *m_vector;
	int m_vectorMax;
	bool m_isValid;
	bool m_isAllocated;
	bool m_padding[2];
};

template <class T>
Rva0093E4D0Vector<T>::Rva0093E4D0Vector(int size, T const *array)
	: m_vector(0), m_vectorMax(size), m_isValid(true), m_isAllocated(false)
{
	if (size)
	{
		if (array)
			m_vector = new ((void *)array) T[size];
		else
		{
			m_vector = new T[size];
			m_isAllocated = true;
		}
	}
}

template <class T>
bool Rva0093E4D0Vector<T>::resize(int newsize, T const *array)
{
	if (newsize)
	{
		T *newptr;

		m_isValid = false;
		if (!array)
			newptr = new T[newsize];
		else
			newptr = new ((void *)array) T[newsize];
		m_isValid = true;
		if (!newptr)
			return false;

		if (m_vector != 0)
		{
			int copycount = (newsize < m_vectorMax) ? newsize : m_vectorMax;
			for (int index = 0; index < copycount; ++index)
				newptr[index] = m_vector[index];

			if (m_isAllocated)
			{
				delete[] m_vector;
				m_vector = 0;
			}
		}

		m_vector = newptr;
		m_vectorMax = newsize;
		m_isAllocated = (m_vector && !array);
	}
	else
		clear();

	return true;
}

template bool Rva0093E4D0Vector<Rva0093E4D0Element>::resize(
	int, Rva0093E4D0Element const *);
