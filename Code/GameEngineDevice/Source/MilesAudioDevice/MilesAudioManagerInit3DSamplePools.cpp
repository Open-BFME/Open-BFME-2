// cl: /Oy- /Oi- /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Donor: reference/open-bfme-1/Code/GameEngineDevice/Source/MilesAudioDevice/
// MilesAudioManager.cpp. init3DSamplePools is the donor's semantic name.
// Target: Ghidra boundary 0x000566B6, 144 bytes. AIL_allocate_3D_sample_handle
// and AIL_set_3D_user_data corroborate purpose. Retail accesses settings +0x10,
// requested count +0x68, available list +0xA3C and actual count +0x680.
// Provider array +0x6CC (stride 12, handle +4), count +0x9CC and selected index
// +0x9D0 agree with the existing createListener recovery. isOn uses slot +0xE0.
// Opaque gaps deliberately make no claim about unaccessed fields.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

// Retail calls the separately rowed four-byte-element append at 0x5548F.
// The list<void*> instance owned by the 3D pool TU is 0x526103 and calls
// a different insertion provider. Preserve it, but select the retail call.
// The int-element view selects that verified four-byte ABI instance.
// The target sample/record remains a pointer; no int-container identity is claimed.


typedef unsigned char Bool;
typedef void *H3DSAMPLE;
typedef void *HPROVIDER;

extern "C" __declspec(dllimport) H3DSAMPLE __stdcall
AIL_allocate_3D_sample_handle(HPROVIDER provider);
extern "C" __declspec(dllimport) void __stdcall
AIL_set_3D_user_data(H3DSAMPLE sample, int index, unsigned int value);

struct AudioSettings
{
	unsigned char m_pad[0x68];
	int m_sampleCount3D;
};

struct MilesProvider
{
	void *m_unused;
	HPROVIDER m_id;
	void *m_unused2;
};

class MilesAudioManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45();
	virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual Bool isOn(int which) const;

	void init3DSamplePools();

private:
	unsigned char m_objectPrefix[0xc];
	AudioSettings *m_audioSettings;
	unsigned char m_prefix[0x67c - 0x14];
	unsigned int m_num2DSamples;
	unsigned int m_num3DSamples;
	unsigned int m_numStreams;
	unsigned char m_gap688[0x6cc - 0x688];
	MilesProvider m_provider3D[64];
	unsigned int m_providerCount;
	unsigned int m_selectedProvider;
	unsigned char m_gap95c[0x64];
	unsigned char m_availableSamples[4];
	_STL::list<H3DSAMPLE> m_available3DSamples;
};

void MilesAudioManager::init3DSamplePools()
{
	if (!(isOn(4) && m_selectedProvider < m_providerCount))
		return;

	while (m_available3DSamples.size() <
		(unsigned int)m_audioSettings->m_sampleCount3D)
	{
		register H3DSAMPLE sample = AIL_allocate_3D_sample_handle(
			m_provider3D[m_selectedProvider].m_id);
		if (!sample)
			break;
		AIL_set_3D_user_data(sample, 0,
			(unsigned int)m_available3DSamples.size() + 1);
		reinterpret_cast<_STL::list<int> *>(&m_available3DSamples)->push_back(reinterpret_cast<const int &>(sample));
		++m_num3DSamples;
	}
}

// Preserve the existing row at 0x526103 in this TU.
template void _STL::list<void *>::push_back(void *const &);
