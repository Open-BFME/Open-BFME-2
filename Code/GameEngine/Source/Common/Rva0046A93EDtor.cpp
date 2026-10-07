// cl: /MD /EHs
// ??1Rva0046A93E@@QAE@XZ 0x0046AB1B 56B evidence: chain from rowed clear 0x46A93E plus rowed free 0x30830 header free after clear
extern "C" void __cdecl free(void *block);
struct Rva00469C34Node;
struct Rva0046A93EHeader
{
	int m_unk0;
	Rva00469C34Node *m_head;
	Rva0046A93EHeader *m_next;
	Rva0046A93EHeader *m_prev;
};
struct Rva0046A93EHolder
{
	Rva0046A93EHeader *m_ptr;
	~Rva0046A93EHolder()
	{
		if (m_ptr != 0)
			free(m_ptr);
	}
};
class Rva0046A93E
{
public:
	Rva0046A93EHolder m_header;
	int m_flag;
	void rva0046A93E();
	~Rva0046A93E();
};
Rva0046A93E::~Rva0046A93E()
{
	rva0046A93E();
}

// Three more destructors of this 56-byte clear-then-free shape, byte-identical to
// ??1Rva0046A93E except for the clear they call (and the EH handler record): the
// rowed clears of their own lists, whose units lay the owner out the same way
// (header +0, count +4). Owners keep their address tokens.

// ??1Rva0046A915@@QAE@XZ @0x0046AAE3 56B -> Rva0046A915::rva0046A915
class Rva0046A915
{
public:
	Rva0046A93EHolder m_header;
	int m_flag;
	void rva0046A915();
	~Rva0046A915();
};

Rva0046A915::~Rva0046A915()
{
	rva0046A915();
}

// ??1Rva0046AB7D@@QAE@XZ @0x0046E2D3 56B -> Rva0046AB7D::rva0046AB7D
class Rva0046AB7D
{
public:
	Rva0046A93EHolder m_header;
	int m_flag;
	void rva0046AB7D();
	~Rva0046AB7D();
};

Rva0046AB7D::~Rva0046AB7D()
{
	rva0046AB7D();
}

// ??1Rva0021C459@@QAE@XZ @0x0021D5D5 56B -> Rva0021C459::rva0021CF03
class Rva0021C459
{
public:
	Rva0046A93EHolder m_header;
	int m_flag;
	void rva0021CF03();
	~Rva0021C459();
};

Rva0021C459::~Rva0021C459()
{
	rva0021CF03();
}

// Seventeen more of the same destructor: every byte matches ??1Rva0046A93E except
// the EH handler record and the call to the owner's rowed clear, which names the
// owner (address tokens, as the clears' own units have them).

// ??1Rva00226829@@QAE@XZ @0x0022C5A2 56B -> Rva00226829::rva0022994D
class Rva00226829
{
public:
	Rva0046A93EHolder m_header;
	int m_flag;
	void rva0022994D();
	~Rva00226829();
};

Rva00226829::~Rva00226829()
{
	rva0022994D();
}

// ??1Rva00226856@@QAE@XZ @0x0022C5DA 56B -> Rva00226856::rva00229976
class Rva00226856
{
public:
	Rva0046A93EHolder m_header;
	int m_flag;
	void rva00229976();
	~Rva00226856();
};

Rva00226856::~Rva00226856()
{
	rva00229976();
}

// ??1Rva002268B0@@QAE@XZ @0x0022C64A 56B -> Rva002268B0::rva002299C8
class Rva002268B0
{
public:
	Rva0046A93EHolder m_header;
	int m_flag;
	void rva002299C8();
	~Rva002268B0();
};

Rva002268B0::~Rva002268B0()
{
	rva002299C8();
}

// ??1Rva00358D62@@QAE@XZ @0x00358F44 56B -> Rva00358D62::rva00358DFD
class Rva00358D62
{
public:
	Rva0046A93EHolder m_header;
	int m_flag;
	void rva00358DFD();
	~Rva00358D62();
};

Rva00358D62::~Rva00358D62()
{
	rva00358DFD();
}

// ??1Rva00358E6A@@QAE@XZ @0x00359231 56B -> Rva00358E6A::rva00358F7C
class Rva00358E6A
{
public:
	Rva0046A93EHolder m_header;
	int m_flag;
	void rva00358F7C();
	~Rva00358E6A();
};

Rva00358E6A::~Rva00358E6A()
{
	rva00358F7C();
}

// ??1Rva00364A37@@QAE@XZ @0x0036528F 56B -> Rva00364A37::rva00364A37
class Rva00364A37
{
public:
	Rva0046A93EHolder m_header;
	int m_flag;
	void rva00364A37();
	~Rva00364A37();
};

Rva00364A37::~Rva00364A37()
{
	rva00364A37();
}

// ??1Rva00364A60@@QAE@XZ @0x003652C7 56B -> Rva00364A60::rva00364A60
class Rva00364A60
{
public:
	Rva0046A93EHolder m_header;
	int m_flag;
	void rva00364A60();
	~Rva00364A60();
};

Rva00364A60::~Rva00364A60()
{
	rva00364A60();
}

// ??1Rva0038201D@@QAE@XZ @0x0038323E 56B -> Rva0038201D::rva003828B6
class Rva0038201D
{
public:
	Rva0046A93EHolder m_header;
	int m_flag;
	void rva003828B6();
	~Rva0038201D();
};

Rva0038201D::~Rva0038201D()
{
	rva003828B6();
}

// ??1Rva0038204A@@QAE@XZ @0x00383276 56B -> Rva0038204A::rva003828DF
class Rva0038204A
{
public:
	Rva0046A93EHolder m_header;
	int m_flag;
	void rva003828DF();
	~Rva0038204A();
};

Rva0038204A::~Rva0038204A()
{
	rva003828DF();
}

// ??1Rva00382077@@QAE@XZ @0x003832AE 56B -> Rva00382077::rva00382908
class Rva00382077
{
public:
	Rva0046A93EHolder m_header;
	int m_flag;
	void rva00382908();
	~Rva00382077();
};

Rva00382077::~Rva00382077()
{
	rva00382908();
}

// ??1Rva003820A4@@QAE@XZ @0x003832E6 56B -> Rva003820A4::rva00382931
class Rva003820A4
{
public:
	Rva0046A93EHolder m_header;
	int m_flag;
	void rva00382931();
	~Rva003820A4();
};

Rva003820A4::~Rva003820A4()
{
	rva00382931();
}

// ??1Rva003820D1@@QAE@XZ @0x0038331E 56B -> Rva003820D1::rva00382983
class Rva003820D1
{
public:
	Rva0046A93EHolder m_header;
	int m_flag;
	void rva00382983();
	~Rva003820D1();
};

Rva003820D1::~Rva003820D1()
{
	rva00382983();
}

// ??1Rva00383A28@@QAE@XZ @0x00383EB2 56B -> Rva00383A28::rva00383A28
class Rva00383A28
{
public:
	Rva0046A93EHolder m_header;
	int m_flag;
	void rva00383A28();
	~Rva00383A28();
};

Rva00383A28::~Rva00383A28()
{
	rva00383A28();
}

// ??1Rva004D9A62@@QAE@XZ @0x004D9AE0 56B -> Rva004D9A62::rva004D9A62
class Rva004D9A62
{
public:
	Rva0046A93EHolder m_header;
	int m_flag;
	void rva004D9A62();
	~Rva004D9A62();
};

Rva004D9A62::~Rva004D9A62()
{
	rva004D9A62();
}

// ??1Rva004FF582@@QAE@XZ @0x004FFBEB 56B -> Rva004FF582::rva004FF729
class Rva004FF582
{
public:
	Rva0046A93EHolder m_header;
	int m_flag;
	void rva004FF729();
	~Rva004FF582();
};

Rva004FF582::~Rva004FF582()
{
	rva004FF729();
}

// ??1Rva002BBBE7@@QAE@XZ @0x00500D68 56B -> Rva002BBBE7::rva002BC39D
class Rva002BBBE7
{
public:
	Rva0046A93EHolder m_header;
	int m_flag;
	void rva002BC39D();
	~Rva002BBBE7();
};

Rva002BBBE7::~Rva002BBBE7()
{
	rva002BC39D();
}

// ??1Rva005532D6@@QAE@XZ @0x00553830 56B -> Rva005532D6::rva005532D6
class Rva005532D6
{
public:
	Rva0046A93EHolder m_header;
	int m_flag;
	void rva005532D6();
	~Rva005532D6();
};

Rva005532D6::~Rva005532D6()
{
	rva005532D6();
}

// ??1Rva00500D30@@QAE@XZ @0x00500D30 56B -> Rva005007CF::rva00500AA6
// Clear-then-free like siblings but clear lives in RvaTreeValueEraseFamily (rowed 0x00500AA6). Holder layout matches Rva005007CF head+flag so cross-class call is address-safe. Evidence: pin ??1Rva00500D30@@QAE@XZ; caller Rva0050292BDestructor m_tree44 size 8; rowed clear 0x00500AA6 and free 0x00030830.
class Rva005007CF
{
public:
	void rva00500AA6();
};

class Rva00500D30
{
public:
	Rva0046A93EHolder m_header;
	int m_flag;
	~Rva00500D30();
};

Rva00500D30::~Rva00500D30()
{
	((Rva005007CF *)this)->rva00500AA6();
}

class Rva0022CA31
{
public:
	void rva0022CA31();
};

void Rva0022CA31::rva0022CA31()
{
	((Rva00226829 *)this)->~Rva00226829();
}

class Rva003591EF
{
public:
	void rva003591EF();
};

void Rva003591EF::rva003591EF()
{
	((Rva00358D62 *)this)->~Rva00358D62();
}

class Rva0035928B
{
public:
	void rva0035928B();
};

void Rva0035928B::rva0035928B()
{
	((Rva00358E6A *)this)->~Rva00358E6A();
}

class Rva0038465B
{
public:
	void rva0038465B();
};

void Rva0038465B::rva0038465B()
{
	((Rva00383A28 *)this)->~Rva00383A28();
}

class Rva0046AD86
{
public:
	void rva0046AD86();
};

void Rva0046AD86::rva0046AD86()
{
	((Rva0046A915 *)this)->~Rva0046A915();
}

class Rva004D9F75
{
public:
	void rva004D9F75();
};

void Rva004D9F75::rva004D9F75()
{
	((Rva004D9A62 *)this)->~Rva004D9A62();
}

class Rva005011AA
{
public:
	void rva005011AA();
};

void Rva005011AA::rva005011AA()
{
	((Rva002BBBE7 *)this)->~Rva002BBBE7();
}

class Rva00553D5E
{
public:
	void rva00553D5E();
};

void Rva00553D5E::rva00553D5E()
{
	((Rva005532D6 *)this)->~Rva005532D6();
}
