// cl: /DNDEBUG /MD /EHsc- /Ireference/shims/bfme2_ascii
// ?Rva003285D4Input@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z @0x003285D4 101B
// Palantir command button input wrapper around rowed GadgetPushButtonInput with click sounds.
// Evidence: pin name Rva003285D4Input same signature as rowed GadgetPushButtonInput and next
// GadgetPushButtonSystem; caller input@Rva000A6097Window in W3DGadgetWindowDrawSlots; rowed callees
// winGetStatus 0x30F45F and GadgetButtonGetData 0x327D56 and PlaySound 0x412A51 with literals
// Gui_PalantirCommandButtonClick and Gui_PalantirCommandButtonDisabledClick; msg 5 and 0xD with
// status bit 8 and button data bit 0x80 at +0x1F; flags copy next GadgetPushButtonSystem.
enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };
class GameWindow {
public:
    unsigned int winGetStatus();
};
void *GadgetButtonGetData(GameWindow *window);
void PlaySound(const char *name);
WindowMsgHandledType GadgetPushButtonInput(GameWindow *window, unsigned int msg, unsigned int mData1, unsigned int mData2);
WindowMsgHandledType Rva003285D4Input(GameWindow *window, unsigned int msg, unsigned int mData1, unsigned int mData2)
{
    if (window) {
        if (msg != 5) {
            if (msg == 0xD) {
                if (window->winGetStatus() & 8) {
                    PlaySound("Gui_PalantirCommandButtonClick");
                } else {
                    void *data = GadgetButtonGetData(window);
                    if (!data || !(((unsigned char *)data)[0x1F] & 0x80))
                        PlaySound("Gui_PalantirCommandButtonDisabledClick");
                    else
                        PlaySound("Gui_PalantirCommandButtonClick");
                }
            }
        } else {
            if (window->winGetStatus() & 8)
                PlaySound("Gui_PalantirCommandButtonClick");
            else
                PlaySound("Gui_PalantirCommandButtonDisabledClick");
        }
    }
    return GadgetPushButtonInput(window, msg, mData1, mData2);
}
