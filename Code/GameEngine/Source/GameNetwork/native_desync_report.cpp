// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// BFME1 GameNetwork/native_desync_report.cpp donor for the per-frame client CRC
// guard's constructor: when CRC checking is enabled and the game mode passes the
// 0x42219 gate, snapshot the current CRC, otherwise start from zero. The
// zeroing arm wants /O1's and-form compaction (retail `and [esi],0`).

class GameLogic
{
public:
    bool rva0042219(void);
    unsigned int getCRC(int mode);
};

class BFMEDesyncCheck
{
public:
    BFMEDesyncCheck();

private:
    unsigned int m_crcBeforeClientUpdate;
};

extern unsigned char BfmeClientCRCCheckEnabled;
// BfmeClientCRCCheckEnabled: matched references place it at VA 0xe02d85 (zero-filled .bss).
unsigned char BfmeClientCRCCheckEnabled;
extern GameLogic *TheGameLogic;

// ??0BFMEDesyncCheck@@QAE@XZ
BFMEDesyncCheck::BFMEDesyncCheck()
{
    if (BfmeClientCRCCheckEnabled != 0)
    {
        GameLogic *logic = TheGameLogic;
        if (logic->rva0042219())
        {
            m_crcBeforeClientUpdate = logic->getCRC(0);
            return;
        }
    }
    m_crcBeforeClientUpdate = 0;
}
