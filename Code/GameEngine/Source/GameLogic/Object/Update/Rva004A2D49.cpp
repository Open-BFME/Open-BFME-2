// cl: /MD /Os
// ?rva004A2D49@Rva004A2D49@@QAEX_N@Z @0x004A2D49 30B
// Banked attempt reverse/attempts/0x004a2d49.cpp, re-verified exact against the current ledger
// (its callees have since been rowed or pinned); landed unchanged by the
// banked-attempt sweep. Identity and evidence: see reverse/re_attempts.log.
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
