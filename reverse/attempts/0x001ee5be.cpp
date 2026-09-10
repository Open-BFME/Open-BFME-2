// ?_bfme_setEngineVisibility@Mouse@@QAEX_N@Z
// partial score=0.7 date=2026-09-09
// cl: /O1 /DNDEBUG /MD
//
// Mouse::_bfme_setEngineVisibility, retail 0x001EE5BE, 24 bytes.
// Dedicated TU so GameEngineClientSubsystems.cpp cannot see this body.
// Syncs cached visibility then forwards the flag to vtable slot 0x70
// with this+0x4F9D as the extra arg.

class Mouse
{
public:
	void syncEngineVisibilityCache();
#define V(n) virtual void r##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27)
#undef V
	virtual void setEngineVisibilityState(bool visible, char *extra) = 0;
	void _bfme_setEngineVisibility(bool visible);
};

void Mouse::_bfme_setEngineVisibility(bool visible)
{
	syncEngineVisibilityCache();
	setEngineVisibilityState(visible, (char *)this + 0x4F9D);
}
