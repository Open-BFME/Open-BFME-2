// cl: /O1 /MD /EHsc
// BFME1 PlayerTemplateStore::getNthPlayerTemplate, with the retail
// 0x1DC-byte vector element and its Overridable final-override lookup.
class Overridable
{
public:
    const Overridable *getFinalOverride() const;
    void *m_vtable;
    Overridable *m_nextOverride;
};

class PlayerTemplate : public Overridable
{
    char m_rest[0x1DC - sizeof(Overridable)];
};

class PlayerTemplateVector
{
public:
    unsigned size() const { return static_cast<unsigned>(m_last - m_first); }
    const PlayerTemplate &operator[](int index) const { return m_first[index]; }
private:
    PlayerTemplate *m_first;
    PlayerTemplate *m_last;
};

class PlayerTemplateStore
{
public:
    const PlayerTemplate *getNthPlayerTemplate(int index) const;
private:
    char m_pad[0x0C];
    PlayerTemplateVector m_playerTemplates;
};

const PlayerTemplate *PlayerTemplateStore::getNthPlayerTemplate(int index) const
{
    if (index >= 0 && static_cast<unsigned>(index) < m_playerTemplates.size()) {
        const PlayerTemplate *playerTemplate = &m_playerTemplates[index];
        const PlayerTemplate *result;
        if (playerTemplate->m_nextOverride)
            result = static_cast<const PlayerTemplate *>(playerTemplate->m_nextOverride->getFinalOverride());
        else
            result = playerTemplate;
        return result;
    }
    return 0;
}
