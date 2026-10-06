// cl: /DNDEBUG /MD
//
// ?reset@Win32Mouse@@UAEXXZ, retail 0x000419F5, 17 bytes (pinned; next to
// the rowed Win32Mouse::addWin32Event 0x00041A10). The Zero Hour body
// extends Mouse::reset(); BFME2 then sets the byte at +0x4F9C. The base
// call goes to 0x001EE4DC, whose only caller is this one, so it is pinned
// as Mouse::reset from this call.
class Mouse
{
public:
	virtual void reset(void);
};

class Win32Mouse : public Mouse
{
public:
	virtual void reset(void);
private:
	char m_pad[0x4F9C - 4];
	bool m_4F9C;
};

void Win32Mouse::reset(void)
{
	// extend
	Mouse::reset();
	m_4F9C = true;
}
