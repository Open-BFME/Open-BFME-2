// cl: /DNDEBUG /MD /Ob2 /EHsc
//
// ShareBufferClass<VertexMaterialClass*>::ShareBufferClass, retail
// 0x0015AB50 (175 bytes). Direct port of the reference ShaderClass copy
// skeleton (reference/open-bfme-1/.../ShareBufferClassShaderCopyConstructor
// .cpp): RefCountClass resets NumRefs to 1 on copy, the pointer array goes
// through plain vector-new (trivial elements, no cookie), the aligned path
// realigns a byte block, and the elements copy over raw. RawBuffer/Array/
// Count/Alignment sit at +0x08/+0x0C/+0x10/+0x14 behind the vtable.

class VertexMaterialClass;

#pragma optimize("s", on)
class RefCountClass
{
public:
	RefCountClass() : m_refs(1) {}
	RefCountClass(const RefCountClass &) : m_refs(1) {}
	virtual void Delete_This();

protected:
	virtual ~RefCountClass() {}

private:
	int m_refs;
};
#pragma optimize("", on)

template <class T>
class ShareBufferClass : public RefCountClass
{
public:
	ShareBufferClass(const ShareBufferClass &that);
	~ShareBufferClass();

protected:
	T *m_rawBuffer; // +0x08
	T *m_array; // +0x0C
	int m_count; // +0x10
	int m_alignment; // +0x14
};

void *operator new[](unsigned int size);

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

template ShareBufferClass<VertexMaterialClass *>::ShareBufferClass(
	const ShareBufferClass<VertexMaterialClass *> &);
