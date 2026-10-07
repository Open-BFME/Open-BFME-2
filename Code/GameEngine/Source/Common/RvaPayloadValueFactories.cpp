// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// These 50-byte Ghidra factory boundaries share a nontrivial one-pointer
// value result: allocate, call the already matched payload constructor,
// write the hidden result and increment the object's count at +4.
// The native cdecl return and otherwise unused zeroed stack flag agree
// with the value-return ABI established by RvaPayloadValueReturns.cpp.
// Each constructor's verified body only installs a vptr, zeroes the count,
// and copies scalar words at +8; throw() records that nonthrowing contract.
// Only declarations of the result destructor and owner destructors are
// needed by these factories. No new vtable or deleting destructor is emitted.

template <class T> class RvaCloneResult
{
public:
 RvaCloneResult(T *p) : pointer(p)
 {
  if (p) ++p->m_ref;
 }
 ~RvaCloneResult();
private:
 T *pointer;
};

struct RvaPayloadInput16 {int words[4];};

// Native factory 0x00574BA5 calls constructor 0x00574ABB;
// its allocation is 16 bytes, with a 8-byte payload at +8.
class Rva00574ABB
{
public:
 struct Payload { int v[2]; };
 Rva00574ABB(const Payload *src) throw();
 virtual ~Rva00574ABB();
 int m_ref; // +4
 Payload m_data; // +8
};

RvaCloneResult<Rva00574ABB> Rva00574BA5Create(const Rva00574ABB::Payload *src)
{
 return RvaCloneResult<Rva00574ABB>(new Rva00574ABB(src));
}

// Native factory 0x005CDC18 calls constructor 0x005CDB8F;
// its allocation is 28 bytes, with a 20-byte payload at +8.
class Rva005CDB8F
{
public:
 struct Payload {RvaPayloadInput16 first;int value;};
 Rva005CDB8F(const Payload *src) throw();
 virtual ~Rva005CDB8F();
 int m_ref; // +4
 Payload m_data; // +8
};

RvaCloneResult<Rva005CDB8F> Rva005CDC18Create(const Rva005CDB8F::Payload *src)
{
 return RvaCloneResult<Rva005CDB8F>(new Rva005CDB8F(src));
}

// Native factory 0x005CDFF5 calls constructor 0x005CDF6C;
// its allocation is 28 bytes, with a 20-byte payload at +8.
class Rva005CDF6C
{
public:
 struct Payload {RvaPayloadInput16 first;int value;};
 Rva005CDF6C(const Payload *src) throw();
 virtual ~Rva005CDF6C();
 int m_ref; // +4
 Payload m_data; // +8
};

RvaCloneResult<Rva005CDF6C> Rva005CDFF5Create(const Rva005CDF6C::Payload *src)
{
 return RvaCloneResult<Rva005CDF6C>(new Rva005CDF6C(src));
}

// Native factory 0x005CEC5D calls constructor 0x005CEA74;
// its allocation is 16 bytes, with a 8-byte payload at +8.
class Rva005CEA74
{
public:
 struct Payload { int v[2]; };
 Rva005CEA74(const Payload *src) throw();
 virtual ~Rva005CEA74();
 int m_ref; // +4
 Payload m_data; // +8
};

RvaCloneResult<Rva005CEA74> Rva005CEC5DCreate(const Rva005CEA74::Payload *src)
{
 return RvaCloneResult<Rva005CEA74>(new Rva005CEA74(src));
}

// Native factory 0x005CECC1 calls constructor 0x005CEB57;
// its allocation is 32 bytes, with a 24-byte payload at +8.
class Rva005CEB57
{
public:
 struct Payload { int v[6]; };
 Rva005CEB57(const Payload *src) throw();
 virtual ~Rva005CEB57();
 int m_ref; // +4
 Payload m_data; // +8
};

RvaCloneResult<Rva005CEB57> Rva005CECC1Create(const Rva005CEB57::Payload *src)
{
 return RvaCloneResult<Rva005CEB57>(new Rva005CEB57(src));
}

// Native factory 0x005E5C63 calls constructor 0x005E59A5;
// its allocation is 20 bytes, with a 12-byte payload at +8.
class Rva005E59A5
{
public:
 struct Payload { int v[3]; };
 Rva005E59A5(const Payload *src) throw();
 virtual ~Rva005E59A5();
 int m_ref; // +4
 Payload m_data; // +8
};

RvaCloneResult<Rva005E59A5> Rva005E5C63Create(const Rva005E59A5::Payload *src)
{
 return RvaCloneResult<Rva005E59A5>(new Rva005E59A5(src));
}

// Native factory 0x005E5C95 calls constructor 0x005E59C2;
// its allocation is 20 bytes, with a 12-byte payload at +8.
class Rva005E59C2
{
public:
 struct Payload { int v[3]; };
 Rva005E59C2(const Payload *src) throw();
 virtual ~Rva005E59C2();
 int m_ref; // +4
 Payload m_data; // +8
};

RvaCloneResult<Rva005E59C2> Rva005E5C95Create(const Rva005E59C2::Payload *src)
{
 return RvaCloneResult<Rva005E59C2>(new Rva005E59C2(src));
}

// Native factory 0x005E5CC7 calls constructor 0x005E59DF;
// its allocation is 20 bytes, with a 12-byte payload at +8.
class Rva005E59DF
{
public:
 struct Payload { int v[3]; };
 Rva005E59DF(const Payload *src) throw();
 virtual ~Rva005E59DF();
 int m_ref; // +4
 Payload m_data; // +8
};

RvaCloneResult<Rva005E59DF> Rva005E5CC7Create(const Rva005E59DF::Payload *src)
{
 return RvaCloneResult<Rva005E59DF>(new Rva005E59DF(src));
}

// Native factory 0x005E98FD calls constructor 0x005E9742;
// its allocation is 32 bytes, with a 24-byte payload at +8.
class Rva005E9742
{
public:
 struct Payload { int v[6]; };
 Rva005E9742(const Payload *src) throw();
 virtual ~Rva005E9742();
 int m_ref; // +4
 Payload m_data; // +8
};

RvaCloneResult<Rva005E9742> Rva005E98FDCreate(const Rva005E9742::Payload *src)
{
 return RvaCloneResult<Rva005E9742>(new Rva005E9742(src));
}

// Native factory 0x005E992F calls constructor 0x005E97B8;
// its allocation is 20 bytes, with a 12-byte payload at +8.
class Rva005E97B8
{
public:
 struct Payload { int v[3]; };
 Rva005E97B8(const Payload *src) throw();
 virtual ~Rva005E97B8();
 int m_ref; // +4
 Payload m_data; // +8
};

RvaCloneResult<Rva005E97B8> Rva005E992FCreate(const Rva005E97B8::Payload *src)
{
 return RvaCloneResult<Rva005E97B8>(new Rva005E97B8(src));
}

// Native factory 0x005E9961 calls constructor 0x005E982C;
// its allocation is 20 bytes, with a 12-byte payload at +8.
class Rva005E982C
{
public:
 struct Payload { int v[3]; };
 Rva005E982C(const Payload *src) throw();
 virtual ~Rva005E982C();
 int m_ref; // +4
 Payload m_data; // +8
};

RvaCloneResult<Rva005E982C> Rva005E9961Create(const Rva005E982C::Payload *src)
{
 return RvaCloneResult<Rva005E982C>(new Rva005E982C(src));
}


// Native 005CDC8F..005CDCC2 and 005CE06C..005CE09F, each RET8.
// Hidden nontrivial result plus one four-word input reference. Each body
// copies the input's 16 bytes, appends the receiver word at +4, and passes
// this 20-byte payload to its independently matched value factory above.
// Constructor/factory owners are already verified; receiver ownership and
// the original operation names remain unknown. The receiver views expose
// only the consumed prefix and are not allocated.
class Rva005CDC8FReceiver {
public: char unknown00[4];int value;
 RvaCloneResult<Rva005CDB8F> create(const RvaPayloadInput16 &input);
};
class Rva005CE06CReceiver {
public: char unknown00[4];int value;
 RvaCloneResult<Rva005CDF6C> create(const RvaPayloadInput16 &input);
};
RvaCloneResult<Rva005CDB8F> Rva005CDC8FReceiver::create(const RvaPayloadInput16 &input)
{
 Rva005CDB8F::Payload payload;
 payload.first=input;
 payload.value=value;
 return Rva005CDC18Create(&payload);
}
RvaCloneResult<Rva005CDF6C> Rva005CE06CReceiver::create(const RvaPayloadInput16 &input)
{
 Rva005CDF6C::Payload payload;
 payload.first=input;
 payload.value=value;
 return Rva005CDFF5Create(&payload);
}
