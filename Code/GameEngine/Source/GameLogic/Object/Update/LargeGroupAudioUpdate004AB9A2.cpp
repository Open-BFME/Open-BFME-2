// cl: /DNDEBUG /MD
// ?rva004AB9A2@LargeGroupAudioUpdate@@QAEXXZ @0x004AB9A2 51B
// When +0x8D set: unregister +0x24 via rowed-pin 0x0020D959 on global 0x00DFE1A8 then sleep forever via rowed UpdateModule::setWakeFrame and clear flag.
// Evidence: linkbody LINK BONUS 48B; callers jmp at 0x004ABA74 0x004ABB46; callees pin 0x0020D959 row 0x0044DF71; layout +8 Object +0x24 host +0x8D flag from slots and Rva0028572A precedents.
class Object;
enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
class Rva0028572AHost
{
public:
	void rva0028572A();
private:
	unsigned char m_pad[0x10];
	int m_10;
};
class Rva0020D959Host;
// The ledger row at 0x0020D959 is Rva0020DXXX::rva0020D959(int).
class Rva0020DXXX
{
public:
	void rva0020D959(int v);
};

extern Rva0020D959Host *g_00DFE1A8;
class UpdateModule
{
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
	char m_pad00[0x8]; // +0 to keep m_object at +8 without emitting a vtable
	Object *m_object; // +8
private:
	char m_pad0C[0x24 - 0x0C];
};
class LargeGroupAudioUpdate : public UpdateModule
{
public:
	void rva004AB9A2();
private:
	Rva0028572AHost m_24; // +0x24
	char m_pad38[0x8D - 0x24 - 0x14];
	bool m_8D; // +0x8D
};
void LargeGroupAudioUpdate::rva004AB9A2()
{
	if (m_8D)
	{
		((Rva0020DXXX *)g_00DFE1A8)->rva0020D959((int)&m_24);
		setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
		m_8D = false;
	}
}
