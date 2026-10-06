// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Radar window override accessors, retail 0x002D35CF (7B) and 0x002D35D6 (16B).
// Split into a dedicated TU so RadarNewMap.cpp keeps its matched newMap:
// defining these in the same unit lets MSVC see the callee and changes the
// caller's register save set (docs/matching.md pattern five).

class GameWindow;

void setHideScroll();

class Rva00524A4C
{
public:
	void Rva00524A65(int arg);
private:
	char m_pad[0x24];
public:
	unsigned char m_flags;
};

class Rva005CB260
{
public:
	void rva005CB260();
};

struct TreeHintRef00217D4C;

class Rva001FF3A9
{
public:
	void rva001FF3A9(const TreeHintRef00217D4C &hint);
};

struct RadarWindowOverrideInner
{
	char m_pad[ 0x60 ];
	bool m_flag0 : 1;
	bool m_flag1 : 1;
	bool m_flag2 : 1;
	bool m_unused : 5;
	char m_pad61[ 3 ];
	GameWindow *m_window;
	char m_pad68[ 0x10 ];
	Rva00524A4C *m_78;
	bool m_7C;
	char m_pad7D[ 0x4B ];
	Rva005CB260 *m_C8;
};

class RadarWindowOverrideSource
{
public:
	bool hasOverrideWindow( void ) const;
	GameWindow *getOverrideWindow( void ) const;
	bool rva002D35E6( void ) const;
	void rva002D35F2( void );
	void rva002D370A( void );
	void rva002D3615( bool value );
	void rva002D36F5(const TreeHintRef00217D4C &hint);

private:
	char m_pad[ 0x10 ];
	RadarWindowOverrideInner *m_inner;
};

GameWindow *RadarWindowOverrideSource::getOverrideWindow( void ) const
{
	return m_inner->m_window;
}

bool RadarWindowOverrideSource::hasOverrideWindow( void ) const
{
	return ( m_inner->m_flag0 || m_inner->m_flag1 || m_inner->m_flag2 ) ? 0 : 1;
}

bool RadarWindowOverrideSource::rva002D35E6( void ) const
{
	return m_inner->m_flag2;
}

void RadarWindowOverrideSource::rva002D35F2( void )
{
	Rva00524A4C *p = m_inner->m_78;
	if (p->m_flags & 1)
		p->Rva00524A65(500);
}

void RadarWindowOverrideSource::rva002D3615( bool value )
{
	m_inner->m_7C = value;
	setHideScroll();
}

// ?rva002D36F5@RadarWindowOverrideSource@@QAEXABUTreeHintRef00217D4C@@@Z @0x002D36F5 21B. Forwards TreeHintRef to +0xC8 object slot0 via 0x001FF3A9 forwarder.
// Evidence: caller 0x00405A86 passes TreeHintRef with this=theRadarWindowOverrideSource; same +0x10/+0xC8 chase as sibling rva002D370A; pin QAEXABU TreeHintRef at 0x001FF3A9.
void RadarWindowOverrideSource::rva002D36F5(const TreeHintRef00217D4C &hint)
{
	Rva001FF3A9 *p = (Rva001FF3A9 *)m_inner->m_C8;
	if (p)
		p->rva001FF3A9(hint);
}

// ?rva002D370A@RadarWindowOverrideSource@@QAEXXZ @0x002D370A 19B, call sites
// 0x0031E10A 0x0031E36C plus a jmp at 0x00405AC3. Tail-calls the pinned
// Rva005CB260 method (0x005CB260) on the inner object's +0xC8 pointer when
// set; retail passes that pointer in ecx, so it is the call's this.
void RadarWindowOverrideSource::rva002D370A( void )
{
	Rva005CB260 *p = m_inner->m_C8;
	if (p)
		p->rva005CB260();
}
