// cl: /O1 /G7 /EHsc /MD /Ireference/shims/bfme2_ascii
// Complete native 5BA593..5BA621 and WB 15875B0 establish the QuickMatch
// singleton cleanup, non-owning window reference+80, preferences+64 and base.
// The constructor at5BAB7E installs this same C73E24 vptr and binds the
// named AptOnline::OnlineQuickMatch callbacks; reconcile its real owner here.
#include "ascii_string.h"
class Rva005248D0 {
public:
    virtual ~Rva005248D0();
private:
    unsigned char unknown04[0x58-4];
};
class AptOnline;
class Rva0056DC4C:public Rva005248D0 {
public:
    Rva0056DC4C(void*);
    virtual ~Rva0056DC4C();
protected:
    AptOnline *m_owner; // +0x58
    int unknown5c;
};
class UserPreferences
{
public:
	virtual ~UserPreferences();
	virtual bool write();

private:
	unsigned char m_unmodelled[0x10];
};

class QuickMatchPreferences : public UserPreferences
{
public:
	QuickMatchPreferences();
public:
	virtual ~QuickMatchPreferences();
public:
	void setLastLadder(const AsciiString &address, unsigned short port);
public:
	void setNumPlayers(int value);
public:
	void setMaxPing(int value);
public:
	void setSide(int value);
public:
	void setColor(int value);
public:
	int getNumPlayers();
	int getMaxPing();
	int getSide();
};
class GameWindow;
class OnlineQuickMatchWindowRef {
public:
    ~OnlineQuickMatchWindowRef();
private:
    GameWindow *m_window;
};
extern int g_Va00E06550;
void _bfme_closeAptScreen(const AsciiString&);
class Image;
class AptOnline
{
public:
    void rva00516F08();

    class OnlineQuickMatch : public Rva0056DC4C
    {
    public:
        OnlineQuickMatch(AptOnline *shell);
        virtual ~OnlineQuickMatch();
        void StartSimple(const char *unused);
        void PlayGame(const char *unused);
        void OnFoundMovieDone(const char *unused);
        void WidenSearch(const char *unused);
        void Cancel(const char *unused);
        void InitGadgets(const char *name, void *argument, GameWindow *window);
        int rva005BAECA(int window, int msg, unsigned char key, int flags);

    private:
        int m_state; // +0x60
        QuickMatchPreferences m_prefs; // +0x64
        bool m_78, m_simple, m_foundMovie;
        unsigned int m_gadgets; // +0x7C
        OnlineQuickMatchWindowRef m_color; // +0x80
        GameWindow *m_numPlayers, *m_side, *m_connectionSpeed, *m_ladder;
        const Image *m_selectedImage, *m_unselectedImage;
        int m_9C;
    };
};
class Image;

inline Rva0056DC4C::~Rva0056DC4C() {}
AptOnline::OnlineQuickMatch::~OnlineQuickMatch()
{
    if((int)this==g_Va00E06550) {
        _bfme_closeAptScreen("AptOnlineQuickMatch::InitGadgets");
        g_Va00E06550=0;
    }
}
