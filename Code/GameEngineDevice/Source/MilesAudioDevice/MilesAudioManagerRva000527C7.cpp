// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?deleteAudioRequest@MilesAudioManager@@QAEXPAX@Z @0x000527C7 27B. Null-checked destroy+free of
// Rva00A86CE: dtor pin ??1Rva00A86CE@@UAE@XZ at 0x00A86CE then rowed
// ??3@YAXPAX@Z operator delete. Evidence: retail call pair 0xA86CE pin-only
// plus 0x2FD60 row; callers are free-function sites with one push (stdcall).
class Rva00A86CE
{
public:
	virtual ~Rva00A86CE();
};

void operator delete(void *p);

class MilesAudioManager
{
public:
	void deleteAudioRequest(void *p);
};

void MilesAudioManager::deleteAudioRequest(void *p)
{
	if (p) {
		((Rva00A86CE *)p)->Rva00A86CE::~Rva00A86CE();
		::operator delete(p);
	}
}
