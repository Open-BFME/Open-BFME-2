// cl: /O1 /DNDEBUG /MD
//
// Scalar deleting destructors of classes whose destructor is empty and
// inline, batch C01: the 29-byte wrapper stores the class's own vtable,
// then frees through operator delete (0x0002FD60) when bit 0 of the flags is
// set and returns this (ret 4). Each class is named after the ledger name its
// vtable already carries, else after the wrapper's address; the dummy tag
// constructors (no retail counterpart) only make this TU emit each vtable and
// with it the deleting destructor. No layout or identity beyond that is
// modelled.
//
//   wrapper     vtable
//   0x00051E4D  0x00BC5128  Rva00051E4D
//   0x000723C7  0x00BC64B0  Rva000723C7
//   0x00072899  0x00BC650C  Rva00072899
//   0x00074626  0x00BC65A8  Rva00074626
//   0x0007827B  0x00BC6778  FileFactoryClass
//   0x0007DFF2  0x00BC6F24  Rva0007DFF2
//   0x000906DE  0x00BC7E94  Rva000906DE
//   0x000A8E9C  0x00BC93BC  Rva000A8E9C
//   0x000A8EF6  0x00BC93DC  Rva000A8EF6
//   0x000EF9D6  0x00BCEF94  HashableClass
//   0x000EFA0E  0x00BCEF9C  Rva000EFA0E
//   0x001164B6  0x00BCFB24  Rva001164B6
//   0x001A4697  0x00BD6CB4  BFME2MotionChannel
//   0x001DB080  0x00BDBA74  Rva001DB080
//   0x00203E76  0x00BE3990  Rva00203E76
//   0x0020E20C  0x00BE4318  Rva0020E20C
//   0x00215E42  0x00BE5838  Rva00215E42
//   0x00285635  0x00BFB698  Rva00285635
//   0x002BED74  0x00BFE4EC  Rva002BED74
//   0x002C1283  0x00BFE5B4  Rva002C1283
//   0x002D252B  0x00C02A5C  Rva002D252B
//   0x002D3556  0x00C02A84  Rva002D3556
//   0x00306DE9  0x00C07E84  InputChunk
//   0x0037F57E  0x00C18DFC  Rva0037F57E
//   0x00381D78  0x00C19230  Rva00381D78
//   0x003919D9  0x00C1A074  Rva003919D9
//   0x0039AE75  0x00C1AD60  Rva0039AE75
//   0x003EE711  0x00C363B8  Rva003EE711
//   0x003F7BCC  0x00C37298  Rva003F7BCC

struct EmitVtableTag;

class Rva00051E4D
{
public:
	Rva00051E4D(EmitVtableTag *);
	virtual ~Rva00051E4D() {}
};

// ?<Rva00051E4D::Rva00051E4D> absent-from-retail
Rva00051E4D::Rva00051E4D(EmitVtableTag *)
{
}

class Rva000723C7
{
public:
	Rva000723C7(EmitVtableTag *);
	virtual ~Rva000723C7() {}
};

// ?<Rva000723C7::Rva000723C7> absent-from-retail
Rva000723C7::Rva000723C7(EmitVtableTag *)
{
}

class Rva00072899
{
public:
	Rva00072899(EmitVtableTag *);
	virtual ~Rva00072899() {}
};

// ?<Rva00072899::Rva00072899> absent-from-retail
Rva00072899::Rva00072899(EmitVtableTag *)
{
}

class Rva00074626
{
public:
	Rva00074626(EmitVtableTag *);
	virtual ~Rva00074626() {}
};

// ?<Rva00074626::Rva00074626> absent-from-retail
Rva00074626::Rva00074626(EmitVtableTag *)
{
}

class FileFactoryClass
{
public:
	FileFactoryClass(EmitVtableTag *);
	virtual ~FileFactoryClass() {}
};

// ?<FileFactoryClass::FileFactoryClass> absent-from-retail
FileFactoryClass::FileFactoryClass(EmitVtableTag *)
{
}

class Rva0007DFF2
{
public:
	Rva0007DFF2(EmitVtableTag *);
	virtual ~Rva0007DFF2() {}
};

// ?<Rva0007DFF2::Rva0007DFF2> absent-from-retail
Rva0007DFF2::Rva0007DFF2(EmitVtableTag *)
{
}

class Rva000906DE
{
public:
	Rva000906DE(EmitVtableTag *);
	virtual ~Rva000906DE() {}
};

// ?<Rva000906DE::Rva000906DE> absent-from-retail
Rva000906DE::Rva000906DE(EmitVtableTag *)
{
}

class Rva000A8E9C
{
public:
	Rva000A8E9C(EmitVtableTag *);
	virtual ~Rva000A8E9C() {}
};

// ?<Rva000A8E9C::Rva000A8E9C> absent-from-retail
Rva000A8E9C::Rva000A8E9C(EmitVtableTag *)
{
}

class Rva000A8EF6
{
public:
	Rva000A8EF6(EmitVtableTag *);
	virtual ~Rva000A8EF6() {}
};

// ?<Rva000A8EF6::Rva000A8EF6> absent-from-retail
Rva000A8EF6::Rva000A8EF6(EmitVtableTag *)
{
}

class HashableClass
{
public:
	HashableClass(EmitVtableTag *);
	virtual ~HashableClass() {}
};

// ?<HashableClass::HashableClass> absent-from-retail
HashableClass::HashableClass(EmitVtableTag *)
{
}

class Rva000EFA0E
{
public:
	Rva000EFA0E(EmitVtableTag *);
	virtual ~Rva000EFA0E() {}
};

// ?<Rva000EFA0E::Rva000EFA0E> absent-from-retail
Rva000EFA0E::Rva000EFA0E(EmitVtableTag *)
{
}

class Rva001164B6
{
public:
	Rva001164B6(EmitVtableTag *);
	virtual ~Rva001164B6() {}
};

// ?<Rva001164B6::Rva001164B6> absent-from-retail
Rva001164B6::Rva001164B6(EmitVtableTag *)
{
}

class BFME2MotionChannel
{
public:
	BFME2MotionChannel(EmitVtableTag *);
	virtual ~BFME2MotionChannel() {}
};

// ?<BFME2MotionChannel::BFME2MotionChannel> absent-from-retail
BFME2MotionChannel::BFME2MotionChannel(EmitVtableTag *)
{
}

class Rva001DB080
{
public:
	Rva001DB080(EmitVtableTag *);
	virtual ~Rva001DB080() {}
};

// ?<Rva001DB080::Rva001DB080> absent-from-retail
Rva001DB080::Rva001DB080(EmitVtableTag *)
{
}

class Rva00203E76
{
public:
	Rva00203E76(EmitVtableTag *);
	virtual ~Rva00203E76() {}
};

// ?<Rva00203E76::Rva00203E76> absent-from-retail
Rva00203E76::Rva00203E76(EmitVtableTag *)
{
}

class Rva0020E20C
{
public:
	Rva0020E20C(EmitVtableTag *);
	virtual ~Rva0020E20C() {}
};

// ?<Rva0020E20C::Rva0020E20C> absent-from-retail
Rva0020E20C::Rva0020E20C(EmitVtableTag *)
{
}

class Rva00215E42
{
public:
	Rva00215E42(EmitVtableTag *);
	virtual ~Rva00215E42() {}
};

// ?<Rva00215E42::Rva00215E42> absent-from-retail
Rva00215E42::Rva00215E42(EmitVtableTag *)
{
}

class Rva00285635
{
public:
	Rva00285635(EmitVtableTag *);
	virtual ~Rva00285635() {}
};

// ?<Rva00285635::Rva00285635> absent-from-retail
Rva00285635::Rva00285635(EmitVtableTag *)
{
}

class Rva002BED74
{
public:
	Rva002BED74(EmitVtableTag *);
	virtual ~Rva002BED74() {}
};

// ?<Rva002BED74::Rva002BED74> absent-from-retail
Rva002BED74::Rva002BED74(EmitVtableTag *)
{
}

class Rva002C1283
{
public:
	Rva002C1283(EmitVtableTag *);
	virtual ~Rva002C1283() {}
};

// ?<Rva002C1283::Rva002C1283> absent-from-retail
Rva002C1283::Rva002C1283(EmitVtableTag *)
{
}

class Rva002D252B
{
public:
	Rva002D252B(EmitVtableTag *);
	virtual ~Rva002D252B() {}
};

// ?<Rva002D252B::Rva002D252B> absent-from-retail
Rva002D252B::Rva002D252B(EmitVtableTag *)
{
}

class Rva002D3556
{
public:
	Rva002D3556(EmitVtableTag *);
	virtual ~Rva002D3556() {}
};

// ?<Rva002D3556::Rva002D3556> absent-from-retail
Rva002D3556::Rva002D3556(EmitVtableTag *)
{
}

class InputChunk
{
public:
	InputChunk(EmitVtableTag *);
	virtual ~InputChunk() {}
};

// ?<InputChunk::InputChunk> absent-from-retail
InputChunk::InputChunk(EmitVtableTag *)
{
}

class Rva0037F57E
{
public:
	Rva0037F57E(EmitVtableTag *);
	virtual ~Rva0037F57E() {}
};

// ?<Rva0037F57E::Rva0037F57E> absent-from-retail
Rva0037F57E::Rva0037F57E(EmitVtableTag *)
{
}

class Rva00381D78
{
public:
	Rva00381D78(EmitVtableTag *);
	virtual ~Rva00381D78() {}
};

// ?<Rva00381D78::Rva00381D78> absent-from-retail
Rva00381D78::Rva00381D78(EmitVtableTag *)
{
}

class Rva003919D9
{
public:
	Rva003919D9(EmitVtableTag *);
	virtual ~Rva003919D9() {}
};

// ?<Rva003919D9::Rva003919D9> absent-from-retail
Rva003919D9::Rva003919D9(EmitVtableTag *)
{
}

class Rva0039AE75
{
public:
	Rva0039AE75(EmitVtableTag *);
	virtual ~Rva0039AE75() {}
};

// ?<Rva0039AE75::Rva0039AE75> absent-from-retail
Rva0039AE75::Rva0039AE75(EmitVtableTag *)
{
}

class Rva003EE711
{
public:
	Rva003EE711(EmitVtableTag *);
	virtual ~Rva003EE711() {}
};

// ?<Rva003EE711::Rva003EE711> absent-from-retail
Rva003EE711::Rva003EE711(EmitVtableTag *)
{
}

class Rva003F7BCC
{
public:
	Rva003F7BCC(EmitVtableTag *);
	virtual ~Rva003F7BCC() {}
};

// ?<Rva003F7BCC::Rva003F7BCC> absent-from-retail
Rva003F7BCC::Rva003F7BCC(EmitVtableTag *)
{
}
