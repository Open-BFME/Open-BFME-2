// cl: /MD
// ?Rva00516F21Invoke@@YAXPAVRva00222A8BTarget@@PAXPBD2@Z @0x00516F21 30B unlock.
// Free invoke wrapper: target->invoke(owner, name, 1, value, 0, 0, 0, 0) via
// pin 0x00222A8B. Evidence: caller 0x0042D653 pushes _fadeOut SetState owner
// target then add esp 0x10; variable pushes map to a4 a3 a2 in retail order.
class Rva00222A8BTarget
{
public:
	void invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
};

void Rva00516F21Invoke(Rva00222A8BTarget *target, void *owner, const char *name, const char *value)
{
	target->invoke(owner, name, 1, value, 0, 0, 0, 0);
}
