// Native GameWindow table C0BBCC slots6/8 compare input callback+1E0.
// Class ownership follows the constructor/table and callback offsets; the
// existing slot placeholders deliberately make no original method-name claim.
// flags: region default (reverse/retail_inventory/flag_regions.csv)
enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };
class GameWindow;
WindowMsgHandledType LeftHUDInput(GameWindow *, unsigned int, unsigned int, unsigned int);
WindowMsgHandledType GadgetPushButtonInput(GameWindow *, unsigned int, unsigned int, unsigned int);
typedef WindowMsgHandledType (__cdecl *GameWinInputFunc)(GameWindow *, unsigned int, unsigned int, unsigned int);

class WinInstanceData;
class GameWindow
{
protected:
    virtual ~GameWindow();
public:
    virtual WindowMsgHandledType input(unsigned int, unsigned int, unsigned int);
    virtual WindowMsgHandledType bfmeGoEHCb(unsigned int, unsigned int, unsigned int);
    virtual int draw(void *);
    virtual int tooltip(WinInstanceData *, unsigned int);
    virtual int rva0009FD78();
    virtual bool vslot6() const;
    virtual void *fetchCreateInstance() = 0;
    virtual bool vslot8() const;
    virtual bool vslot9() const;
    virtual void vslot10() = 0;
private:
    unsigned char m_unmodelled04[0x1E0 - 4];
    GameWinInputFunc m_input;
};

bool GameWindow::vslot6() const
{
    return m_input == LeftHUDInput;
}

bool GameWindow::vslot8() const
{
    return m_input == GadgetPushButtonInput;
}
