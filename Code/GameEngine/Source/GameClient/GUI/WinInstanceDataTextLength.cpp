// cl: /O1 /MD
class DisplayString
{
public:
    virtual void draw();
    virtual void setText();
    virtual void setFont();
    virtual int getTextLength();
};

class WinInstanceData
{
public:
    int getTextLength();

private:
    char m_prefix[0x19c];
    DisplayString *m_text;
};

int WinInstanceData::getTextLength()
{
    DisplayString * volatile *textSlot = &m_text;
    if (*textSlot)
        return (*textSlot)->getTextLength();
    return 0;
}
