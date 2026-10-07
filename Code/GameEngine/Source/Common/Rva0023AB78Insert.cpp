// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <vector>
#include "ascii_string.h"
// ?rva0023ABDD@Rva0023ABDD@@QAEXXZ @0x0023ABDD 89B: audio-notify clear of two vectors at +0x120/+0x12c.
// Evidence: TheAudio VA 0x009FE6E8 mangled ?TheAudio@@3PAVAudioManager@@A; loop calls virtual slot 0x6c per void* element then erases via rowed 0x0031BD55 and 0x00239EA5; contiguous after 0x0023AB78; callers 0x0023AE08 0x0023B509.
class AudioManager
{
public:
	virtual void vf0();
	virtual void vf1();
	virtual void vf2();
	virtual void vf3();
	virtual void vf4();
	virtual void vf5();
	virtual void vf6();
	virtual void vf7();
	virtual void vf8();
	virtual void vf9();
	virtual void vf10();
	virtual void vf11();
	virtual void vf12();
	virtual void vf13();
	virtual void vf14();
	virtual void vf15();
	virtual void vf16();
	virtual void vf17();
	virtual void vf18();
	virtual void vf19();
	virtual void vf20();
	virtual void vf21();
	virtual void vf22();
	virtual void vf23();
	virtual void vf24();
	virtual void vf25();
	virtual void vf26();
	virtual void vf27(void *p);
};

extern AudioManager *TheAudio;

struct OpaqueRefElement4
{
	void *m_ptr;
};

class Rva0023ABDD
{
	char m_pad[0x120];
	_STL::vector<void *> m_vec120;
	_STL::vector<OpaqueRefElement4> m_vec12c;
public:
	void rva0023ABDD();
};

void Rva0023ABDD::rva0023ABDD()
{
	if (TheAudio != 0)
	{
		for (void **it = m_vec120.begin(); it != m_vec120.end(); ++it)
			TheAudio->vf27(*it);
	}
	m_vec120.clear();
	m_vec12c.clear();
}
