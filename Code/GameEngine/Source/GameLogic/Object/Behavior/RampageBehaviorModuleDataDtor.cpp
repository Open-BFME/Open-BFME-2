// cl: /DNDEBUG /MD /EHsc /O1
// stlport
// ??1RampageBehaviorModuleData@@UAE@XZ, RVA 0x00458C9B, size 48.
// Virtual dtor destroying RequiredUpgrade vector at +8 then restoring
// Snapshot base vtable 0xBBB554 with trivial base inlined (no base call).
// Evidence: EH state 0 single vector teardown 0x2CC70, vtable-last
// 0xBBB554 same shape as UpgradeModuleData 0x255A42, slot-0 deleter
// 0x458C7F calls here, ctor 0x458C0F owns class and table 0xC40E78.
#include <vector>

class AsciiString
{
public:
    AsciiString();
    ~AsciiString();
private:
    void *m_data;
};

class ModuleDataBase
{
public:
    virtual ~ModuleDataBase() {}
};

class RampageBehaviorModuleData : public ModuleDataBase
{
public:
    RampageBehaviorModuleData(int);
private:
    unsigned int m_unused04;
    _STL::vector<AsciiString> m_requiredUpgrade;
};

// ?dummyCtor@RampageBehaviorModuleData@@QAE@H@Z present-unmatched
RampageBehaviorModuleData::RampageBehaviorModuleData(int)
{
}

void deleteRampageBehaviorModuleData(RampageBehaviorModuleData *p)
{
    delete p;
}
