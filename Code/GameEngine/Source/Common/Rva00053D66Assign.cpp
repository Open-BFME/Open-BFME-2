// cl: /MD
// ?assign@Rva00053D66DeviceRef@@QAEXPAVRva000A8903AudioDevice@@@Z @0x00053D66 35B:
// DeviceRef assign with release: same-pointer early-out, null-tolerant store,
// then explicit virtual dtor plus global operator delete on old object.
// Evidence: caller MilesAudioManager::openDevice passes new AudioDevice;
// pin gives class/method names; callees are pinned dtor and rowed ??3.
class Rva000A8903AudioDevice;
class Rva00A897D
{
public:
	virtual ~Rva00A897D();
};
class Rva00053D66DeviceRef
{
public:
	void assign(Rva000A8903AudioDevice *device);
private:
	void *object;
};
void __cdecl operator delete(void *p);
void Rva00053D66DeviceRef::assign(Rva000A8903AudioDevice *device)
{
	void *old = object;
	if (device == old)
		return;
	object = device;
	if (old == 0)
		return;
	((Rva00A897D *)old)->Rva00A897D::~Rva00A897D();
	operator delete(old);
}
