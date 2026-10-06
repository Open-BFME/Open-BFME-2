// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// MilesAudioManager::createListener, retail 0x00053B63 (62 bytes).
// Ported from reference/open-bfme-1/.../MilesAudioManagerCreateListener.cpp
// (Zero Hour twin). New official-path TU (BFME2 has no CreateListener TU).
//
// Retail-measured BFME2 adaptations:
// - Provider array at this+0x6CC (64 x 12B, BFME1 {name,id,isValid} layout
//   verbatim, so .id at +4 assembles to the retail push dword at +0x6D0) with
//   m_providerCount at +0x9CC and m_selectedProvider at +0x9D0 (the array end
//   0x6CC+0x300 lands exactly on count, confirming 64 entries).
// - isOn is virtual at slot 0xE0 (56): retail calls [vptr+0xE0] with arg 4.
// - m_listener at +0x9E0 (one pad dword at +0x9DC past the BFME1 tail).
// - Extra retail store: byte flag at +0x6AB set to 1 after opening the
//   listener (role inferred as listener-created; offset/value measured).

extern "C" __declspec(dllimport) void *__stdcall AIL_open_3D_listener(
	unsigned int provider);

struct ProviderInfo
{
	void *name;
	unsigned int id;
	int isValid;
};

enum { MAXPROVIDERS = 64 };

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
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual bool isOn(int which) const;

	void createListener();

private:
	char m_pad04[0x6A7];
	bool m_listenerFlag;
	char m_pad6AC[0x20];
	ProviderInfo m_provider3D[MAXPROVIDERS];
	unsigned int m_providerCount;
	unsigned int m_selectedProvider;
	unsigned int m_lastProvider;
	unsigned int m_selectedSpeakerType;
	unsigned int m_pad9DC;
	void *m_listener;
};

// ?createListener@MilesAudioManager@@QAEXXZ
void MilesAudioManager::createListener()
{
	if (!(isOn(4) && m_selectedProvider < m_providerCount))
		return;

	m_listener = AIL_open_3D_listener(m_provider3D[m_selectedProvider].id);
	m_listenerFlag = true;
}
