// cl: /MD /Oy-
// Native Ghidra 00432038..004320B1 RET4. The two named sibling calls
// establish the FormationTranslator state-handler receiver. Their existing
// WorldBuilder provenance supplies the class name; this dispatch method's
// name and its message-number labels remain address-derived target facts.
#include "../../../Libraries/Include/Lib/ICoord2D.h"
union GameMessageArgumentType
{
    int integer;
    float real;
    int boolean, objectID, drawableID;
    unsigned int teamID;
    struct Loc { float x, y, z; } location;
    struct Pix { int x, y; } pixel;
    struct PixReg { int loX, loY, hiX, hiY; } pixelRegion;
    unsigned int timestamp;
    unsigned short wChar;
};
class GameMessage
{
public:
    const GameMessageArgumentType *getArgument(int index) const;
    char unknown00[0x10];
    int type;
};
class Rva00431978 { public: bool rva00431978(ICoord2D *point); };
#include "../../Include/GameClient/FormationTranslator.h"
class FormationTranslator::WaitForSecondButtonDownStateHandler
{
public:
    bool IsStartOfDrag(GameMessage *message);
    void Restart(void *message);
    int rva00431C9D(GameMessage *message);
    int rva00432038(GameMessage *message);
private:
    void *unknown00, *parent;
    int storedType;
    ICoord2D point;
    int unknown14, time;
};
int FormationTranslator::WaitForSecondButtonDownStateHandler::rva00432038(
    GameMessage *message)
{
    switch (message->type)
    {
    case 3:
        {
            const GameMessageArgumentType *gameMessageArgumentType = message->getArgument(0);
            int x = gameMessageArgumentType->pixel.x;
            int y = gameMessageArgumentType->pixel.y;
            ICoord2D pixel;
            pixel.y = y;
            pixel.x = x;
            if (!reinterpret_cast<Rva00431978 *>(this)->rva00431978(&pixel))
                Restart(message);
            break;
        }
    case 4:
    case 14:
        if (IsStartOfDrag(message))
            return rva00431C9D(message);
        Restart(message);
        break;
    case 6:
        if (storedType == 4)
            Restart(message);
        break;
    case 16:
        if (storedType == 14)
            Restart(message);
        break;
    }
    return 0;
}
