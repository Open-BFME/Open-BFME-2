// cl: -GF -Gy -MD -EHsc -GR -DNDEBUG -DWIN32 -D_WINDOWS /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI

class Rva00791F70CallbackHost;

typedef void (__cdecl *Rva00791F70Callback)(
	Rva00791F70CallbackHost *, int, int, int );

void j_0003c281();

class Rva00791F70CallbackHost
{
public:
	void dispatch( int first, int second, int third );

private:
	char m_unreconstructed[ 0x1E0 ];
	Rva00791F70Callback m_callback;
};

void Rva00791F70CallbackHost::dispatch(
	int first, int second, int third )
{
	if( m_callback )
		m_callback( this, first, second, third );
	else
		((Rva00791F70Callback)&j_0003c281)( this, first, second, third );
}
