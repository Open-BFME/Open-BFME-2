// BFME 2 one-pointer texture ownership views, established by the matched
// particle texture loader, fallback getters and native release/copy providers.
#ifndef BFME2_PARTICLE_TEXTURE_HANDLES_H
#define BFME2_PARTICLE_TEXTURE_HANDLES_H
class TextureClass
{
public:
	virtual void slot00();
	unsigned short m_refCount;
	unsigned short m_pad06;
	void Release_Ref();
};

// Inline acquisition has its own overload because this /O1 caller uses INC;
// the ordinary out-of-line copy provider at 0x001494F0 uses ADD. Keep that
// provider declaration while reproducing the verified inline caller expansion.
template<class T> class RefCountPtr
{
public:
    RefCountPtr() : Ptr(0) {}
    RefCountPtr(const RefCountPtr &other);
    enum InlineCopy { COPY_INLINE };
    __forceinline RefCountPtr(const RefCountPtr &other, InlineCopy)
        : Ptr(other.Ptr)
    {
        if (Ptr)
            ++Ptr->m_refCount;
    }
    ~RefCountPtr();
    T *Ptr;
};

class BFME2ParticleTextureHandle
{
public:
	TextureClass *Ptr;
	BFME2ParticleTextureHandle() : Ptr(0) {}
	BFME2ParticleTextureHandle(TextureClass *ptr);
	enum InlineAcquire { ACQUIRE_INLINE };
	__forceinline BFME2ParticleTextureHandle(TextureClass *ptr, InlineAcquire) : Ptr(ptr)
	{
		if (Ptr)
			++Ptr->m_refCount;
	}
	~BFME2ParticleTextureHandle()
	{
		if (Ptr)
			Ptr->Release_Ref();
	}
};

#endif
