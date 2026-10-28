// cl: /MD /O1 /GX /DNDEBUG
// The legacy row name comes from a masked Zero Hour inline placement; it
// does not establish the retail class or method name. Retail 0x0049001F
// reads bytes +9 and +8 from an interface subobject and returns their AND.
// The approved home is LargeGroupBonusUpdate.cpp (reverse/tu_map.csv).
// Keep the existing row spelling until its identity is reconciled there.
//
// This bounded view retains the imported interface offset and field order.
// An ordinary out-of-line override emits the body without instantiating the
// unrelated Zero Hour module, parser, update loop or drawable callbacks.

class UpdateModule
{
public:
    virtual ~UpdateModule();
private:
    unsigned char m_storage[0x20 - sizeof(void *)];
};

class HordeUpdateInterface
{
public:
    virtual bool isInHorde() const = 0;
    virtual bool hasFlag() const = 0;
    virtual bool isTrueHordeMember() const = 0;
    virtual bool isAllowedNationalism() const = 0;
};

class HordeUpdate : public UpdateModule, public HordeUpdateInterface
{
public:
    virtual bool isTrueHordeMember() const;
private:
    unsigned int m_lastHordeRefreshFrame;
    bool m_inHorde;
    bool m_trueHordeMember;
    bool m_hasFlag;
};

bool HordeUpdate::isTrueHordeMember() const
{
    return m_trueHordeMember && m_inHorde;
}
