// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Existing ctor pin; Drawable 27675F calls it twice for its 8B value return
// and local. Target writes all-one first word and null shared-member pointer.
#include "../../Include/Common/Rva002390CB.h"
Rva002390CB::Rva002390CB() : m_00(-1) {}
