// cl: /DNDEBUG /MD /EHsc
// Provenance: Open-BFME-1 game/Libraries/Source/WWVegas/WWSaveLoad/VectorClassEnumValueResize.cpp at 6583b3c1ff; include paths repointed at the
// reference checkout and built the BFME2 way (/arch:SSE /G7), where its body places
// exactly once in game.dat by masked byte search.
//
// The copy loop addRef/releases the record's second word. The element is
// Render2DSentenceClass's renderer record: this body hands 0x00001E13, rowed
// ??1RendererDataStruct@Render2DSentenceClass, to ??_L and ??_M, and
// ~Render2DSentenceClass (0x00157C70) installs the table whose Resize slot is
// this body (P104, tools/retail_identity.py RENDERER_VECTOR). It was rowed on
// EnumParameterClass::_ENUM_VALUE, a donor label. The element ctor ??_L
// receives (0x00155701 pushes VA 0x00554300) clears only +4, a body /OPT:ICF
// folds with the rowed ??0TimeAndLocationInfo 0x00154300.

#include <new.h>

#include <new>

#include "../WW3D2/Render2DSentenceClass.h"

template <class T>
class VectorClass
{
public:
	VectorClass(int size = 0, T const *array = 0);
	virtual ~VectorClass(void);
	virtual bool equal(const VectorClass<T> &) const;
	virtual bool Resize(int newsize, T const *array = 0);
	virtual void Clear(void);
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
VectorClass<T>::VectorClass(int size, T const *array)
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
bool VectorClass<T>::Resize(int newsize, T const *array)
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
		Clear();

	return true;
}

template bool VectorClass<Render2DSentenceClass::RendererDataStruct>::Resize(
	int, Render2DSentenceClass::RendererDataStruct const *);
