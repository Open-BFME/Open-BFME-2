// cl: /EHsc /MD
// ?rva0004C5C6@Rva004C743@@UAEPAVRva00091A80@@XZ @ 0x0004C5C6 (50B). Virtual factory slot 43 of Rva004C743 vtable 0x007C4738: new 0x24 + ctor 0x00091A80 with EH prolog. Evidence: vtable slot 43 offset 0xAC, callee ??0Rva00091A80@@QAE@XZ rowed, operator new ??2@YAPAXI@Z rowed, __EH_prolog.

class Rva00091A80
{
public:
	Rva00091A80();
private:
	unsigned char m_pad[0x24];
};

class Rva00090360
{
public:
	Rva00090360();
private:
	unsigned char m_pad[0x40];
};

class Rva009111B
{
public:
	Rva009111B(int a1, int a2, int a3);
private:
	unsigned char m_pad[0x1c];
};

class Rva004C743
{
public:
	virtual Rva00091A80 *rva0004C5C6();
	virtual Rva00090360 *rva0004C553();
	virtual Rva009111B *rva0004C585();
};

Rva00091A80 *Rva004C743::rva0004C5C6()
{
	return new Rva00091A80;
}

// ?rva0004C553@Rva004C743@@UAEPAVRva00090360@@XZ @ 0x0004C553 (50B). Virtual factory slot 41 of Rva004C743 vtable 0x007C4738: new 0x40 + ctor 0x00090360 with EH prolog.
Rva00090360 *Rva004C743::rva0004C553()
{
	return new Rva00090360;
}

// ?rva0004C585@Rva004C743@@UAEPAVRva009111B@@XZ @ 0x0004C585 (65B). Virtual factory slot 42 of Rva004C743 vtable 0x007C4738: new 0x1c + ctor 0x00090781 with EH prolog. Evidence: vtable slot 42 offset 0xA8 between slots 41 and 43, callee ??0Rva009111B@@QAE@HHH@Z rowed, operator new ??2@YAPAXI@Z rowed, __EH_prolog.
Rva009111B *Rva004C743::rva0004C585()
{
	return new Rva009111B(0x6604BA, 0x660557, 0x6604D0);
}
