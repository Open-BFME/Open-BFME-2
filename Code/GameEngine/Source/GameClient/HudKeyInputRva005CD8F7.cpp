// cl: /O1 /arch:SSE /G7 /MD
// Native Ghidra 005CD8F7..005CD938, 65B, RET4. The rowed caller
// 005771F4 proves the GameMessage pointer and the full-int return value.
// Preserve its existing opaque pin's void-pointer spelling. Target facts:
// message type22, TheInGameUI virtual slot17C, argument0 low byte39h,
// and the 82B receiver helper005CD8A5. Original method names unknown.
union GameMessageArgumentType;
class GameMessage
{
public:
    const GameMessageArgumentType *getArgument(int index) const;
    char unknown00[0x10];
    int type;
};
class InGameUI;
extern InGameUI *TheInGameUI;

class Rva005CD8F7UI
{
public:
#define UI_SLOT(n) virtual void unknown##n();
    UI_SLOT(00) UI_SLOT(01) UI_SLOT(02) UI_SLOT(03) UI_SLOT(04)
    UI_SLOT(05) UI_SLOT(06) UI_SLOT(07) UI_SLOT(08) UI_SLOT(09)
    UI_SLOT(10) UI_SLOT(11) UI_SLOT(12) UI_SLOT(13) UI_SLOT(14)
    UI_SLOT(15) UI_SLOT(16) UI_SLOT(17) UI_SLOT(18) UI_SLOT(19)
    UI_SLOT(20) UI_SLOT(21) UI_SLOT(22) UI_SLOT(23) UI_SLOT(24)
    UI_SLOT(25) UI_SLOT(26) UI_SLOT(27) UI_SLOT(28) UI_SLOT(29)
    UI_SLOT(30) UI_SLOT(31) UI_SLOT(32) UI_SLOT(33) UI_SLOT(34)
    UI_SLOT(35) UI_SLOT(36) UI_SLOT(37) UI_SLOT(38) UI_SLOT(39)
    UI_SLOT(40) UI_SLOT(41) UI_SLOT(42) UI_SLOT(43) UI_SLOT(44)
    UI_SLOT(45) UI_SLOT(46) UI_SLOT(47) UI_SLOT(48) UI_SLOT(49)
    UI_SLOT(50) UI_SLOT(51) UI_SLOT(52) UI_SLOT(53) UI_SLOT(54)
    UI_SLOT(55) UI_SLOT(56) UI_SLOT(57) UI_SLOT(58) UI_SLOT(59)
    UI_SLOT(60) UI_SLOT(61) UI_SLOT(62) UI_SLOT(63) UI_SLOT(64)
    UI_SLOT(65) UI_SLOT(66) UI_SLOT(67) UI_SLOT(68) UI_SLOT(69)
    UI_SLOT(70) UI_SLOT(71) UI_SLOT(72) UI_SLOT(73) UI_SLOT(74)
    UI_SLOT(75) UI_SLOT(76) UI_SLOT(77) UI_SLOT(78) UI_SLOT(79)
    UI_SLOT(80) UI_SLOT(81) UI_SLOT(82) UI_SLOT(83) UI_SLOT(84)
    UI_SLOT(85) UI_SLOT(86) UI_SLOT(87) UI_SLOT(88) UI_SLOT(89)
    UI_SLOT(90) UI_SLOT(91) UI_SLOT(92) UI_SLOT(93) UI_SLOT(94)
#undef UI_SLOT
    virtual bool rva005CD8F7Slot17C();
};
class Rva005CD8F7Call
{
public:
    int rva005CD8F7(void *incoming);
    void rva005CD8A5();
};

int Rva005CD8F7Call::rva005CD8F7(void *incoming)
{
    GameMessage *message = reinterpret_cast<GameMessage *>(incoming);
    if (message->type == 22
        && !reinterpret_cast<Rva005CD8F7UI *>(TheInGameUI)->rva005CD8F7Slot17C()
        && *reinterpret_cast<const unsigned char *>(message->getArgument(0)) == 0x39)
    {
        rva005CD8A5();
        return 1;
    }
    return 0;
}
