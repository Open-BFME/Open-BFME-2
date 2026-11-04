// cl: /DNDEBUG /MD /Ob2 /EHsc
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// BFME1 ShareBuffer pointer-copy pattern adapted to the opaque tail buffer.
// Descriptor assignment calls 0x15ACB0 for its +0x108 buffer, then installs
// the known derived vtable 0xBD3CA4 and AddRefs the copied elements.
// The original pointee name is unknown; only its RefCountClass prefix is used.

class RefCountClass;

// Retail's RefCountClass inline copies (scalar deleting dtor 0x00072899) are
// the size form: compile this class for size, as hlod.cpp does.
#pragma optimize("s", on)
#include "RefCountData.h"
inline RefCountClass::~RefCountClass() {}
#pragma optimize("", on)

template <class T>
class ShareBufferClass : public RefCountClass
{
public:
	ShareBufferClass(const ShareBufferClass &that);
	virtual ~ShareBufferClass();

protected:
	T *m_rawBuffer; // +0x08
	T *m_array; // +0x0C
	int m_count; // +0x10
	int m_alignment; // +0x14
};

#include <new>

template <class T>
ShareBufferClass<T>::ShareBufferClass(const ShareBufferClass<T> &that) :
	m_count(that.m_count)
{
	m_alignment = that.m_alignment;
	if (m_alignment == 0)
	{
		m_rawBuffer = new T[m_count];
		m_array = m_rawBuffer;
	}
	else
	{
		m_rawBuffer = (T *)new char[m_count * sizeof(T) + m_alignment];
		m_array = (T *)(((unsigned int)m_rawBuffer + m_alignment - 1) &
			~(m_alignment - 1));
	}
	for (int index = 0; index < m_count; ++index)
	{
		m_array[index] = that.m_array[index];
	}
}

template ShareBufferClass<RefCountClass *>::ShareBufferClass(
	const ShareBufferClass<RefCountClass *> &);
