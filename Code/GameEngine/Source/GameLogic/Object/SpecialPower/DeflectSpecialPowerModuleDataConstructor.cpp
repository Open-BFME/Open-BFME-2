// cl: /DNDEBUG /MD /EHsc
// Native0x004C5671/18B: constructs the0x18-byte base then installs Deflect's table.
// The existing AIUpdateModuleData owner supplies the witnessed base lifetime;
// this view does not establish the original intermediate class ancestry.
class AIUpdateModuleData
{
public:
    AIUpdateModuleData();
    virtual ~AIUpdateModuleData();
private:
    unsigned char m_opaque[0x14];
};

class DeflectSpecialPowerModuleData : public AIUpdateModuleData
{
public:
    DeflectSpecialPowerModuleData();
    virtual ~DeflectSpecialPowerModuleData();
};

DeflectSpecialPowerModuleData::DeflectSpecialPowerModuleData()
{
}
