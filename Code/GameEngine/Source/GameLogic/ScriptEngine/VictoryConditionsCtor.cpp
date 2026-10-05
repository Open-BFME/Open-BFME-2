// cl: /O1 /DNDEBUG /MD
// ??0VictoryConditions@@QAE@XZ @0x0010BA2C 25B unlock via base ctor pin 0x000F0F2B plus reset pin 0x00108895 plus vtable g_00BCF9E0 prev 0x0010B9E5 next 0x0010BA45
class VictoryConditionsInterface
{
public:
    VictoryConditionsInterface();
    virtual void init();
};
class VictoryConditions : public VictoryConditionsInterface
{
public:
    VictoryConditions();
    virtual void reset();
};
VictoryConditions::VictoryConditions()
{
    reset();
}
