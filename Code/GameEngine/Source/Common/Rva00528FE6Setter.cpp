// cl: /O1 /MD
// ?rva00528FE6@Rva00528FE6@@QAEXPAUCameraMarker@@@Z retail 0x00528FE6 35B
// Evidence: cmp new vs old at [ecx]; store new; dtor old via 0x0029D7C2 plus delete 0x0002FD60; callers 0x0052991E 0x005D2920
struct CameraMarker
{
	~CameraMarker();
};

class Rva00528FE6
{
public:
	void rva00528FE6(CameraMarker *p);
	void rva00529009();
private:
	CameraMarker *m_ptr;
};

void Rva00528FE6::rva00528FE6(CameraMarker *p)
{
	if (p == m_ptr)
		return;
	CameraMarker *old = m_ptr;
	m_ptr = p;
	if (!old)
		return;
	delete old;
}

void Rva00528FE6::rva00529009()
{
	CameraMarker *p = m_ptr;
	m_ptr = 0;
	if (!p)
		return;
	delete p;
}
