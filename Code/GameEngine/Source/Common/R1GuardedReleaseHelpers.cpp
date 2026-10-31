class Gen0089C880
{
public:
	void handle();
};

class BfmeThingVGP
{
public:
	int bfmeGoVGP();
};

class Rva008A2C60
{
public:
	void go();
	char m_lead[ 0x10 ];
	Gen0089C880 *m_target;
	bool m_done;
};
void Rva008A2C60::go()
{
	if( m_target )
		m_target->handle();
	m_done = true;
}

class Rva00958C40
{
public:
	void go();
	BfmeThingVGP *m_target;
};

// -------------------------------------------------- pointer-to-member call

class GenC9EF0
{
public:
	GenC9EF0 *step();
};

class Rva000C9EF0
{
public:
	void go();
	GenC9EF0 *m_target;
	GenC9EF0 *( GenC9EF0::*m_step )();
};
// ?go@Rva000C9EF0@@QAEXXZ, retail 0x004EF5BE (16B).
// Pointer-to-member step: the jz covers the indirect call and the
// write-back. BFME1 folds an identical twin (Rva00161140); only one row
// can own this address so the twin name stays unclaimed.
void Rva000C9EF0::go()
{
	if( m_target )
		m_target = ( m_target->*m_step )();
}
