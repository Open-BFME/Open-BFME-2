// cl: /MD
//
// profile_cmd.cpp ProfileCmdInterface::RunResultFunctions, the exit-time
// driver that flushes every registered profile result writer.
//
// The Generals reference carries this body unchanged:
//
//   if (!numResFunc)
//     Debug::Command("profile.result file_csv");
//   for (unsigned k = 0; k < numResFunc; k++) {
//     resFunc[k]->WriteResults();
//     resFunc[k]->Delete();
//   }
//
// and the two indirect calls in the loop are slots 0 and 4 of the element's
// vtable, which is WriteResults then Delete in ProfileResultInterface's
// declaration order. numResFunc sits at +4 and resFunc at +8, past the vtable
// pointer the interface's own virtuals put at +0.
//
// Debug::Command is not a static here. Retail loads a Debug * from the global
// at 0x00DE0880 and calls slot 0x8C on it, so the reference's static spelling
// is a forwarder that inlines away, and the model gives Debug the 35 slots
// that puts Command at that offset.

class ProfileResultInterface
{
public:
	virtual void WriteResults() = 0;
	virtual void Delete() = 0;
};

class Debug
{
public:
	virtual void _M_slot_00();
	virtual void _M_slot_04();
	virtual void _M_slot_08();
	virtual void _M_slot_0c();
	virtual void _M_slot_10();
	virtual void _M_slot_14();
	virtual void _M_slot_18();
	virtual void _M_slot_1c();
	virtual void _M_slot_20();
	virtual void _M_slot_24();
	virtual void _M_slot_28();
	virtual void _M_slot_2c();
	virtual void _M_slot_30();
	virtual void _M_slot_34();
	virtual void _M_slot_38();
	virtual void _M_slot_3c();
	virtual void _M_slot_40();
	virtual void _M_slot_44();
	virtual void _M_slot_48();
	virtual void _M_slot_4c();
	virtual void _M_slot_50();
	virtual void _M_slot_54();
	virtual void _M_slot_58();
	virtual void _M_slot_5c();
	virtual void _M_slot_60();
	virtual void _M_slot_64();
	virtual void _M_slot_68();
	virtual void _M_slot_6c();
	virtual void _M_slot_70();
	virtual void _M_slot_74();
	virtual void _M_slot_78();
	virtual void _M_slot_7c();
	virtual void _M_slot_80();
	virtual void _M_slot_84();
	virtual void _M_slot_88();
	virtual void Command(const char *cmd);
};

Debug *theDebug;

class ProfileCmdInterface
{
public:
	virtual void _M_slot_00();

	void RunResultFunctions();

private:
	unsigned numResFunc;
	ProfileResultInterface **resFunc;
};

void ProfileCmdInterface::RunResultFunctions()
{
	if (!numResFunc)
		theDebug->Command("profile.result file_csv");

	for (unsigned k = 0; k < numResFunc; k++) {
		resFunc[k]->WriteResults();
		resFunc[k]->Delete();
	}
}
