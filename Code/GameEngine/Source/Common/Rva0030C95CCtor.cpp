// cl: /O1 /arch:SSE /G7 /MD /EHsc
// Retail 30C95C..30C97E; shared caller-proven retained-reference ABI.
#include "../GameLogic/Map/AreaSetEntryView.h"
Rva0030C95C::Rva0030C95C(int value, AreaRefValueView target)
    : m_value(value), m_target(target) {}
