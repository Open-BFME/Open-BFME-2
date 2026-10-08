// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Radar window override accessors, retail 0x002D35CF (7B) and 0x002D35D6 (16B).
// Split into a dedicated TU so RadarNewMap.cpp keeps its matched newMap:
// defining these in the same unit lets MSVC see the callee and changes the
// caller's register save set (docs/matching.md pattern five).

class GameWindow
{
public:
	int winHide(bool hide);
};

void setHideScroll();

// The target's 0x002D4240 body calls vtable offset +0x24 on this object.
// GeneralsMD names the analogous AptPalantirAnimation slot "stop"; only the
// BFME2 slot offset and this object's +0x24 flags byte are target evidence.
class Rva00524A4C
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1C();
	virtual void v20();
	virtual void stop();
	void Rva00524A65(int arg);

private:
	char m_pad04[0x20];

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

class Rva00528FD9Owner
{
public:
	void reset();
private:
	void *m_target;
};

class Rva00528545
{
public:
	void rva00528545();
private:
	void *m_target;
};

class Rva0052A765Owner
{
public:
	void rva0052A765();
private:
	void *m_target;
};

class Rva002D3894
{
public:
	void clear();
private:
	void *m_pointer;
};

class Rva002D38D1
{
public:
	void clear();
	Rva005CB260 *m_pointer;
};

class Rva002D3931
{
public:
	void clear();
private:
	void *m_pointer;
};

class Rva00222A8BTarget
{
public:
	int invoke(void *owner, const char *name, int argc, const char *a0,
		void *a1, void *a2, void *a3, void *a4);
};

class Rva002224FE
{
public:
	bool rva002224FE(int index);
};

class AptPalantir
{
public:
	void OnClosed(const char *unused);
};

class Radar
{
public:
	void newMap();
};

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern Radar *TheRadar;

struct RadarWindowOverrideInner
{
	char m_pad00[ 0x5C ];
	void *m_movie;
	union
	{
		unsigned char m_flags;
		struct
		{
			bool m_flag0 : 1;
			bool m_flag1 : 1;
			bool m_flag2 : 1;
			bool m_unused : 5;
		};
	};
	char m_pad61[ 3 ];
	GameWindow *m_window;
	char m_pad68[ 0x10 ];
	Rva00524A4C *m_78;
	bool m_7C;
	char m_pad7D[ 0x0F ];
	Rva00528FD9Owner m_8C;
	Rva00528545 m_90;
	Rva0052A765Owner m_94;
	char m_pad98[ 0x2C ];
	Rva002D3894 m_C4;
	Rva002D38D1 m_C8;
	Rva002D3931 m_CC;
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
	void rva002D4240(bool immediate);

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
	Rva001FF3A9 *p = (Rva001FF3A9 *)m_inner->m_C8.m_pointer;
	if (p)
		p->rva001FF3A9(hint);
}

// ?rva002D370A@RadarWindowOverrideSource@@QAEXXZ @0x002D370A 19B, call sites
// 0x0031E10A 0x0031E36C plus a jmp at 0x00405AC3. Tail-calls the pinned
// Rva005CB260 method (0x005CB260) on the inner object's +0xC8 pointer when
// set; retail passes that pointer in ecx, so it is the call's this.
void RadarWindowOverrideSource::rva002D370A( void )
{
	Rva005CB260 *p = m_inner->m_C8.m_pointer;
	if (p)
		p->rva005CB260();
}

// ?rva002D4240@RadarWindowOverrideSource@@QAEX_N@Z @0x002D4240 257B.
// GeneralsMD AptPalantirHide.cpp at reference revision 6583b3c1 supplies the
// hide semantics (stop animation, clear owned panels, update Radar, hide
// window); its layout and callees are not carried over. Target identity is
// supported by the HideControlBar(true)/ShowControlBar(false) callers on the
// 0x009FF028 singleton and the Palantir::Hide callgraph lead. BFME2 target
// bytes reach the payload through this source's +0x10 pointer and use its
// rowed close callback, three +0xC4/+0xC8/+0xCC clears, and Radar::newMap.
// The disassembly establishes manager at 0x009FE4CC, flags/movie/window at
// payload +0x5C/+0x60/+0x64, animation at +0x78, and wrappers at +0x8C/+0x90/
// +0x94. The 0x0052A765 callee remains address-named: its seven bytes load the
// pointer at +0 and tail-jump to 0x0052A66A.
void RadarWindowOverrideSource::rva002D4240(bool immediate)
{
	if (!g_bfmeAptWindowManager)
		return;

	if (immediate)
	{
		if ((m_inner->m_flags & 6) == 0)
		{
			((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(m_inner->m_movie, "Close", 0, 0, 0, 0, 0, 0);
			m_inner->m_flags |= 2;
		}

		Rva00524A4C *animation = m_inner->m_78;
		if (animation)
			animation->stop();

		m_inner->m_8C.reset();
		m_inner->m_90.rva00528545();
		m_inner->m_94.rva0052A765();
		m_inner->m_C4.clear();
		m_inner->m_C8.clear();
		m_inner->m_CC.clear();

		if (TheRadar)
			TheRadar->newMap();
	}
	else
	{
		if (m_inner->m_flags & 2)
			((AptPalantir *)m_inner)->OnClosed("");

		if ((m_inner->m_flags & 4) && !(m_inner->m_flags & 1))
		{
			((Rva002224FE *)g_bfmeAptWindowManager)->rva002224FE((int)m_inner->m_movie);
			m_inner->m_flags |= 1;
		}
	}

	m_inner->m_window->winHide(immediate);
}
