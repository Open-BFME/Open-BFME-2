// cl: /O1 /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ??0MouseThreadClass@@QAE@XZ @0x00098D8A 20B: MouseThreadClass ctor.
// Evidence: calls rowed ThreadClass 1-arg ctor 0x00610430 with null; installs vtable 0x007C86CC; next row is dtor 0x00098D9E; donor BFME1 W3DMouse.cpp.
#include "../../../../Libraries/Source/WWVegas/WWLib/ThreadClass.h"

class MouseThreadClass : public ThreadClass
{
public:
	MouseThreadClass();
	virtual ~MouseThreadClass();
	virtual void Thread_Function();
};

MouseThreadClass::MouseThreadClass() : ThreadClass(0)
{
}

