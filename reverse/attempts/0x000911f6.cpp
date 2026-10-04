// ?rva000911F6@Rva007E3C20Vp6Stream@@UAEHH@Z
// partial score=0.93 date=2026-10-04
// cl: /O1 /MD
//
// ?rva000911F6@Rva007E3C20Vp6Stream@@UAEHH@Z 0x000911F6 301B.
// Chain from 0x00091189: slot 6 (offset 0x18) of vtable 0x007C7F20 whose
// class is ??0Rva007E3C20Vp6Stream (ctor 0x000907C1). Calls slot 0x34 (bool),
// slot 8 (void), slot 0x14 (bool(int)), slot 0xc (void), m_at2c slot 0,
// pin 0x00090FE0 ?rva000190ABTransform@@YGHH@Z, winmm timeGetTime and
// __alldiv, then 0x00091189. Layout matches Rva007E3C20Vp6StreamCtor
// (+0x40/+0x44/+0x48/+0x4c/+0x50/+0x2c). Donor: Open-BFME-1 VP6 stream.

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

class Rva00091189
{
public:
	void rva00091189();
};

class At2cObj
{
public:
	virtual void v0();
};

class Gen_0081E480
{
public:
	virtual ~Gen_0081E480();
	int m_b04;
	int m_b08;
	int m_b0c;
	int m_b10;
};

class Rva007E3C20Vp6Stream : public Gen_0081E480
{
public:
	virtual void v0();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual bool v5( int arg );
	virtual int rva000911F6( int arg );
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual bool v13();
	int rva00090FE0( int value );

private:
	void *m_at14;
	void *m_at18;
	char m_parser[ 0x10 ];
	At2cObj *m_at2c;
	int m_at30;
	int m_at34;
	unsigned char m_at38;
	int m_at3c;
	int m_at40;
	int m_at44;
	int m_at48;
	int m_at4c;
	int m_at50;
	char *m_at54;
	int m_at58;
	int m_at5c;
	int m_at60;
};

extern char g_00DE4498;

// ?rva000911F6@Rva007E3C20Vp6Stream@@UAEHH@Z present-unmatched
int Rva007E3C20Vp6Stream::rva000911F6( int arg )
{
	bool b = v13();
	int ebx = b ? 2 : 0;
	if ( m_at48 < 0 )
		v2();
	int edi = arg & 4;
	if ( edi == 0 && ( ebx & 2 ) )
		return ebx;
	if ( !v5( arg ) )
		return ebx;
	int trans = rva00090FE0( arg );
	if ( g_00DE4498 != 0 || edi != 0 || ( arg & 0x40 ) != 0 ) {
		int m44 = m_at44;
		int m40 = m_at40;
		unsigned int now = timeGetTime();
		__int64 mult = ( (__int64)( m44 * 1000 ) * trans );
		__int64 div1 = mult / m40;
		int diff = (int)now - (int)div1;
		int q1 = m40 / m44;
		int q2 = 1000 / q1;
		if ( diff - m_at50 > q2 )
			m_at50 = diff;
	}
	while ( m_at48 < trans ) {
		if ( !v13() )
			break;
		if ( edi != 0 )
			break;
		v2();
		ebx |= 4;
	}
	if ( arg & 1 )
		return ebx;
	if ( m_at4c == m_at48 )
		return ebx;
	v3();
	m_at2c->v0();
	ebx |= 1;
	v2();
	if ( edi == 0 )
		return ebx;
	if ( !v13() )
		return ebx;
	( (Rva00091189 *)this )->rva00091189();
	return ebx;
}
