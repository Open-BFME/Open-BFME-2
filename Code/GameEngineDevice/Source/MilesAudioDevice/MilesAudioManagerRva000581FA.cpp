// cl: /DNDEBUG /DWIN32 /MD /EHsc
// ?rva000581FA@MilesAudioManager@@QAEXABURva0005BA08InfoRef@@H@Z @0x000581FA 83B.
// Called by initFilters twin 0x0005BA08 with the event's info reference and
// its +0x30 int: feeds the info's channel entries to the volume owner for
// that type (three 0x1C4-byte GlobalVolumeData blocks at +0x12C) through
// rowed GlobalVolumeData::volumeAdjustingSoundStarting, and type 2 also feeds the other two owners as type 2.

struct Rva0005BA08InfoRef;
struct Holder;

class MilesAudioManager
{
public:
	class GlobalVolumeData
	{
	public:
		void volumeAdjustingSoundStarting(Holder *o, int key);

		char m_body[0x1c4];
	};

	void rva000581FA(const Rva0005BA08InfoRef &info, int type);

private:
	char m_pad000[0x12c];
	GlobalVolumeData m_owners[3];
};

void MilesAudioManager::rva000581FA(const Rva0005BA08InfoRef &info, int type)
{
	m_owners[type].volumeAdjustingSoundStarting((Holder *)&info, type);
	if (type == 2)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (i != 2)
				m_owners[i].volumeAdjustingSoundStarting((Holder *)&info, 2);
		}
	}
}
