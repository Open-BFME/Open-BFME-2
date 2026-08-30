namespace FXParticleSystem
{
class EventModuleInfo
{
public:
    EventModuleInfo();
    EventModuleInfo &operator=(const EventModuleInfo &that);

protected:
    ~EventModuleInfo();

private:
    bool m_unk0;
    bool m_unk1;
};

EventModuleInfo::EventModuleInfo()
{
    m_unk0 = true;
    m_unk1 = true;
}
}
