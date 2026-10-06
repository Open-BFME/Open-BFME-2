// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?getGlobalReverbMultiplier@MilesAudioManager@@QAEMXZ @0x00052F4C 84B.
// Same this as createListener via provider count/selection at +0x9CC/+0x9D0
// plus provider id at +0x6D0 and flag at +0x6A7. Returns reverb level for
// the current 3D room type with 0..25 bounds. Table base at +0x10+0xC4.

extern "C" __declspec(dllimport) int __stdcall AIL_3D_room_type(unsigned int provider);

struct ProviderInfo
{
	void *name;
	unsigned int id;
	int isValid;
};

enum { MAXPROVIDERS = 64 };

struct ReverbTable
{
	char m_pad[0xc4];
	float m_values[26];
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
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual bool isOn(int which) const;

	float getGlobalReverbMultiplier();

private:
	char m_pad04[0xc];
	ReverbTable *m_table;
	char m_pad14[0x6a7 - 0x14];
	bool m_flag6A7;
	char m_pad6A8[3];
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

float MilesAudioManager::getGlobalReverbMultiplier()
{
	unsigned int sel = m_selectedProvider;
	if (sel >= m_providerCount)
		return 0.0f;
	int room = AIL_3D_room_type(m_provider3D[sel].id);
	if (m_flag6A7 && room != -1)
	{
		if (room < 0 || (unsigned int)room >= 26)
			return 1.0f;
		return m_table->m_values[room];
	}
	return 0.0f;
}
