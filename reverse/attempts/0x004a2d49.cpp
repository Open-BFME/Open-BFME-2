// ?rva004A2D49@Rva004A2D49@@QAEX_N@Z
// partial score=0.9 date=2026-10-07
// cl: /MD
// ?rva004A2D49@Rva004A2D49@@QAEX_N@Z @0x004A2D49 30B
// Evidence: target reads one boolean argument and the Object* at this+8, then calls rowed UpdateModule::setWakeFrame; class and field ownership remain address-based.
class Object;
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 0x3FFFFFFF,
	UPDATE_SLEEP_FOREVER = 1
};
class UpdateModule
{
protected:
	char m_base[8];
	void setWakeFrame(Object *object, UpdateSleepTime wakeTime);
};
class Rva004A2D49 : public UpdateModule
{
public:
	void rva004A2D49(bool sleepForever);
private:
	Object *m_object;
};
void Rva004A2D49::rva004A2D49(bool sleepForever)
{
	UpdateSleepTime wakeTime = sleepForever ? UPDATE_SLEEP_FOREVER : UPDATE_SLEEP_NONE;
	setWakeFrame(m_object, wakeTime);
}
