// cl: /DNDEBUG /MD
//
// ?loadPostProcess@UpdateModule@@MAEXXZ, retail 0x0058B03E, 5 bytes.
// Zero Hour UpdateModule.cpp: `void UpdateModule::loadPostProcess( void )
// { BehaviorModule::loadPostProcess(); }`. The base call is not inlined (the
// base lives in another unit), so it compiles to a tail jump; retail's jumps to
// 0x000B3FD0, the image's shared empty `ret` that BehaviorModule's own
// loadPostProcess (itself only forwarding to empty bases) folded into.
// Evidence: symbols.csv pin at 0x0058B03E read from the REL32 displacement of
// a placed body; 42 module units call it by this name.

class BehaviorModule
{
protected:
	virtual void loadPostProcess(void);
};

class UpdateModule : public BehaviorModule
{
protected:
	virtual void loadPostProcess(void);
};

void UpdateModule::loadPostProcess(void)
{
	BehaviorModule::loadPostProcess();
}
