// Trimmed port of reference/open-bfme-1/Code/GameEngine/Source/Common/
// Q3MakeDerivedFamily.cpp: the Rva007E9B40, Rva007F2E60, Rva007F3410,
// Rva007F40F0 and Rva007FBB20 helpers are carried; the three sibling helpers
// stay with the donor until rows land. See the donor for the full
// multiple-inheritance analysis.

void *Gen007F0130( unsigned int size );

class Q3MakeBaseA
{
public:
	// Pure: every factory's object overrides it, and retail never stores this
	// base's own vftable, so the only reference left is the base vftable the
	// compiler emits, which now names _purecall instead of an undefined slot.
	virtual void primary() = 0;
	static void *operator new( unsigned int size ) { return Gen007F0130( size ); }
};

class Q3MakeBaseB
{
public:
	// No family member overrides this slot: every +4 vftable (retail 0x008E0FB4)
	// holds 0x007244B0, `mov eax,[ecx+4]; ret`, the payload getter that ICF
	// folded with CullSystemClass::Get_First_Collected_Object_Internal.
	virtual void *secondary() { return m_payload; }
	void *m_payload;
	Q3MakeBaseB( void *payload ) { m_payload = payload; }
};

class Rva007E9B40Object : public Q3MakeBaseA, public Q3MakeBaseB
{
public:
	Rva007E9B40Object( void *payload ) : Q3MakeBaseB( payload ) {}
	virtual void primary();
};

Rva007E9B40Object *Rva007E9B40( void *payload )
{
	return new Rva007E9B40Object( payload );
}

class Rva007F2E60Object : public Q3MakeBaseA, public Q3MakeBaseB
{
public:
	Rva007F2E60Object( void *payload ) : Q3MakeBaseB( payload ) {}
	virtual void primary();
};

Rva007F2E60Object *Rva007F2E60( void *payload )
{
	return new Rva007F2E60Object( payload );
}

class Rva007F3410Object : public Q3MakeBaseA, public Q3MakeBaseB
{
public:
	Rva007F3410Object( void *payload ) : Q3MakeBaseB( payload ) {}
	virtual void primary();
};

Rva007F3410Object *Rva007F3410( void *payload )
{
	return new Rva007F3410Object( payload );
}

class Rva007F40F0Object : public Q3MakeBaseA, public Q3MakeBaseB
{
public:
	Rva007F40F0Object( void *payload ) : Q3MakeBaseB( payload ) {}
	virtual void primary();
};

Rva007F40F0Object *Rva007F40F0( void *payload )
{
	return new Rva007F40F0Object( payload );
}

class Rva007FBB20Object : public Q3MakeBaseA, public Q3MakeBaseB
{
public:
	Rva007FBB20Object( void *payload ) : Q3MakeBaseB( payload ) {}
	virtual void primary();
};

Rva007FBB20Object *Rva007FBB20( void *payload )
{
	return new Rva007FBB20Object( payload );
}

// Two more family members (retail 0x0065EC70 and 0x0065E7A0, primary vftables
// 0x00CE23AC / 0x00CE20E4), same shape as the five above.
class Rva0065EC70Object : public Q3MakeBaseA, public Q3MakeBaseB
{
public:
	Rva0065EC70Object( void *payload ) : Q3MakeBaseB( payload ) {}
	virtual void primary();
};

Rva0065EC70Object *Rva0065EC70( void *payload )
{
	return new Rva0065EC70Object( payload );
}

class Rva0065E7A0Object : public Q3MakeBaseA, public Q3MakeBaseB
{
public:
	Rva0065E7A0Object( void *payload ) : Q3MakeBaseB( payload ) {}
	virtual void primary();
};

Rva0065E7A0Object *Rva0065E7A0( void *payload )
{
	return new Rva0065E7A0Object( payload );
}

// Retail 0x00669480 (primary vftable 0x00CE3788), the same shape again.
class Rva007FCF80Object : public Q3MakeBaseA, public Q3MakeBaseB
{
public:
	Rva007FCF80Object( void *payload ) : Q3MakeBaseB( payload ) {}
	virtual void primary();
};

Rva007FCF80Object *Rva007FCF80( void *payload )
{
	return new Rva007FCF80Object( payload );
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?primary@Rva007F2E60Object@@UAEXXZ=??_GGen007F2E30@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?primary@Rva007F3410Object@@UAEXXZ=??_GGen007F33E0@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?primary@Rva007F40F0Object@@UAEXXZ=??_GGen007F40C0@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?primary@Rva007FBB20Object@@UAEXXZ=??_GGen007FBAF0@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?primary@Rva007E9B40Object@@UAEXXZ=??_GGen007E9B10@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?primary@Rva0065EC70Object@@UAEXXZ=??_GGen007F2120@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?primary@Rva0065E7A0Object@@UAEXXZ=??_GGen007FCF50@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?primary@Rva007FCF80Object@@UAEXXZ=??_GGen007F1BF0@@UAEPAXI@Z")
