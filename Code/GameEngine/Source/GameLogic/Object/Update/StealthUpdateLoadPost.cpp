// cl: /MD
// ?rva00374AE8@StealthUpdate@@QAEXXZ 0x00374AE8 26B evidence: slot 1 of vtable 0x00817F20; base UpdateModule loadPostProcess pin plus flag at +0x47 when +0x3c set then tail to rowed rva003748BD; donor Rva0024A797Derived flags
class UpdateModule {
protected:
    virtual void loadPostProcess();
};
class StealthUpdate : public UpdateModule {
    const void *m_data;
    char m_pad08[0x34];
    int m_3c;
    char m_pad40[0x7];
    bool m_47;
public:
    void rva00374AE8();
    void rva003748BD();
};
void StealthUpdate::rva00374AE8()
{
    UpdateModule::loadPostProcess();
    if (m_3c)
        m_47 = true;
    return rva003748BD();
}
