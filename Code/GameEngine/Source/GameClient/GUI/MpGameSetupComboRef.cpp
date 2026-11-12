// cl: /DNDEBUG /MD
// The lobby color-combo wrapper stores one non-owning GameWindow pointer.
// Its assignment folds with the one-pointer store at retail 0x0007B719.
class GameWindow;
#include "../../../Include/Common/MpGameSetupComboRef.h"

MpGameSetupComboRef &MpGameSetupComboRef::operator=(GameWindow *window)
{
    m_window = window;
    return *this;
}
