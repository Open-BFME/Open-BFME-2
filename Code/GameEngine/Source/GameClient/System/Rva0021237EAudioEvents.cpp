// cl: /O1 /DNDEBUG /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva0021237E@Rva0021237E@@QAEXXZ @0x0021237E 64B
// The target walks the four-byte range at this+0x2CC, passes each word to
// TheAudio's slot 0x6C, then erases the whole range through rowed vector erase
// 0x0031BD55. TheAudio is pinned at VA 0x00DFE6E8. The neighboring 0x0021246D
// caller invokes this body at +0x48B. The handle interpretation follows the
// target call and AudioManager's established removeAudioEvent slot; the owning
// class identity remains address-derived.
#include <vector>

typedef unsigned int AudioHandle;

class AudioManager
{
public:
	virtual void _pad00() = 0;
	virtual void _pad01() = 0;
	virtual void _pad02() = 0;
	virtual void _pad03() = 0;
	virtual void _pad04() = 0;
	virtual void _pad05() = 0;
	virtual void _pad06() = 0;
	virtual void _pad07() = 0;
	virtual void _pad08() = 0;
	virtual void _pad09() = 0;
	virtual void _pad10() = 0;
	virtual void _pad11() = 0;
	virtual void _pad12() = 0;
	virtual void _pad13() = 0;
	virtual void _pad14() = 0;
	virtual void _pad15() = 0;
	virtual void _pad16() = 0;
	virtual void _pad17() = 0;
	virtual void _pad18() = 0;
	virtual void _pad19() = 0;
	virtual void _pad20() = 0;
	virtual void _pad21() = 0;
	virtual void _pad22() = 0;
	virtual void _pad23() = 0;
	virtual void _pad24() = 0;
	virtual void _pad25() = 0;
	virtual void _pad26() = 0;
	virtual void removeAudioEvent(AudioHandle handle) = 0;
};

extern AudioManager *TheAudio;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva0021237E
{
	char m_pad[0x2CC];

public:
	void rva0021237E();
};

void Rva0021237E::rva0021237E()
{
	_STL::vector<void *> *eventHandles = (_STL::vector<void *> *)((char *)this + 0x2CC);
	unsigned int i;
	for (i = 0; i < (unsigned int)(eventHandles->end() - eventHandles->begin()); ++i)
	{
		_ReadWriteBarrier();
		TheAudio->removeAudioEvent((AudioHandle)(unsigned int)eventHandles->begin()[i]);
	}
	eventHandles->erase(eventHandles->begin(), eventHandles->end());
}
