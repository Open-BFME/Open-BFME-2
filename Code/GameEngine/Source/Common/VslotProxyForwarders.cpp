// cl: /O1 /DNDEBUG /MD
//
// Three proxy classes whose vtable slots 3-14 each forward to the same slot
// of an inner object, passing the caller's stack arguments through (the ret N
// on the fallback path gives their count) and answering 0 or false when there
// is no inner object:
//
//   vtable 0x00C372D4  inner object pointer at +0x14            (int results)
//   vtable 0x00C37358  inner object at +0x1C, its interface at +8 (Bool)
//   vtable 0x00C3731C  inner interface from 0x003F81B0 (this)      (Bool)
//
// Slots 1 and 2 of each proxy and slot 14 of the last two forward the same
// way (slot 14 there answers 0).
//
// The interfaces are modelled only by those slots and argument counts;
// every name is address-derived.

typedef int Int;
typedef bool Bool;

class Rva003F7C53Inner
{
public:
	virtual void slot0() = 0;
	virtual Int slot1(Int a0) = 0;
	virtual Int slot2(Int a0) = 0;
	virtual Int slot3(Int a0, Int a1) = 0;
	virtual Int slot4(Int a0, Int a1) = 0;
	virtual Int slot5(Int a0) = 0;
	virtual Int slot6(Int a0) = 0;
	virtual Int slot7(Int a0) = 0;
	virtual Int slot8(Int a0) = 0;
	virtual Int slot9(Int a0, Int a1) = 0;
	virtual Int slot10(Int a0, Int a1) = 0;
	virtual Int slot11(Int a0, Int a1) = 0;
	virtual Int slot12(Int a0) = 0;
	virtual Int slot13() = 0;
	virtual Int slot14(Int a0) = 0;
};

class Rva003F7D86Inner
{
public:
	virtual void slot0() = 0;
	virtual Bool slot1(Int a0) = 0;
	virtual Bool slot2(Int a0) = 0;
	virtual Bool slot3(Int a0, Int a1) = 0;
	virtual Bool slot4(Int a0, Int a1) = 0;
	virtual Bool slot5(Int a0) = 0;
	virtual Bool slot6(Int a0) = 0;
	virtual Bool slot7(Int a0) = 0;
	virtual Bool slot8(Int a0) = 0;
	virtual Bool slot9(Int a0, Int a1) = 0;
	virtual Bool slot10(Int a0, Int a1) = 0;
	virtual Bool slot11(Int a0, Int a1) = 0;
	virtual Bool slot12(Int a0) = 0;
	virtual Bool slot13() = 0;
	virtual Int slot14(Int a0) = 0;
};

// The object the 0x00C37358 proxy holds; the interface sits at +8.
class Rva003F7D86HolderBase
{
public:
	virtual void slot0();
private:
	char m_unmodelled_04[4];
};

class Rva003F7D86Holder : public Rva003F7D86HolderBase, public Rva003F7D86Inner
{
};

class Rva003F7C53Proxy
{
public:
	Int rva003F7C2F(Int a0);
	Int rva003F7C41(Int a0);
	Int rva003F7C53(Int a0, Int a1);
	Int rva003F7C65(Int a0, Int a1);
	Int rva003F7C77(Int a0);
	Int rva003F7C89(Int a0);
	Int rva003F7C9B(Int a0);
	Int rva003F7CAD(Int a0);
	Int rva003F7CBF(Int a0, Int a1);
	Int rva003F7CD1(Int a0, Int a1);
	Int rva003F7CE3(Int a0, Int a1);
	Int rva003F7CF5(Int a0);
	Int rva003F7D07();
	Int rva003F7D17(Int a0);
private:
	char m_lead[0x14];
	Rva003F7C53Inner *m_inner;				// +0x14
};


// 0x00C372D4#3 slot 3
Int Rva003F7C53Proxy::rva003F7C53(Int a0, Int a1)
{
	return m_inner ? m_inner->slot3(a0, a1) : 0;
}

// 0x00C372D4#4 slot 4
Int Rva003F7C53Proxy::rva003F7C65(Int a0, Int a1)
{
	return m_inner ? m_inner->slot4(a0, a1) : 0;
}

// 0x00C372D4#5 slot 5
Int Rva003F7C53Proxy::rva003F7C77(Int a0)
{
	return m_inner ? m_inner->slot5(a0) : 0;
}

// 0x00C372D4#6 slot 6
Int Rva003F7C53Proxy::rva003F7C89(Int a0)
{
	return m_inner ? m_inner->slot6(a0) : 0;
}

// 0x00C372D4#7 slot 7
Int Rva003F7C53Proxy::rva003F7C9B(Int a0)
{
	return m_inner ? m_inner->slot7(a0) : 0;
}

// 0x00C372D4#8 slot 8
Int Rva003F7C53Proxy::rva003F7CAD(Int a0)
{
	return m_inner ? m_inner->slot8(a0) : 0;
}

// 0x00C372D4#9 slot 9
Int Rva003F7C53Proxy::rva003F7CBF(Int a0, Int a1)
{
	return m_inner ? m_inner->slot9(a0, a1) : 0;
}

// 0x00C372D4#10 slot 10
Int Rva003F7C53Proxy::rva003F7CD1(Int a0, Int a1)
{
	return m_inner ? m_inner->slot10(a0, a1) : 0;
}

// 0x00C372D4#11 slot 11
Int Rva003F7C53Proxy::rva003F7CE3(Int a0, Int a1)
{
	return m_inner ? m_inner->slot11(a0, a1) : 0;
}

// 0x00C372D4#12 slot 12
Int Rva003F7C53Proxy::rva003F7CF5(Int a0)
{
	return m_inner ? m_inner->slot12(a0) : 0;
}

// 0x00C372D4#13 slot 13
Int Rva003F7C53Proxy::rva003F7D07()
{
	return m_inner ? m_inner->slot13() : 0;
}

// 0x00C372D4#14 slot 14
Int Rva003F7C53Proxy::rva003F7D17(Int a0)
{
	return m_inner ? m_inner->slot14(a0) : 0;
}

class Rva003F7D86Proxy
{
public:
	Bool rva003F7D5E(Int a0);
	Bool rva003F7D72(Int a0);
	Bool rva003F7D86(Int a0, Int a1);
	Bool rva003F7D9A(Int a0, Int a1);
	Bool rva003F7DAE(Int a0);
	Bool rva003F7DC2(Int a0);
	Bool rva003F7DD6(Int a0);
	Bool rva003F7DEA(Int a0);
	Bool rva003F7DFE(Int a0, Int a1);
	Bool rva003F7E12(Int a0, Int a1);
	Bool rva003F7E26(Int a0, Int a1);
	Bool rva003F7E3A(Int a0);
	Bool rva003F7E4E();
	Int rva003F7E60(Int a0);
private:
	char m_lead[0x1C];
	Rva003F7D86Holder *m_holder;			// +0x1C
};

// 0x00C37358#3 slot 3
Bool Rva003F7D86Proxy::rva003F7D86(Int a0, Int a1)
{
	if (m_holder)
		return static_cast<Rva003F7D86Inner *>(m_holder)->slot3(a0, a1);
	return false;
}

// 0x00C37358#4 slot 4
Bool Rva003F7D86Proxy::rva003F7D9A(Int a0, Int a1)
{
	if (m_holder)
		return static_cast<Rva003F7D86Inner *>(m_holder)->slot4(a0, a1);
	return false;
}

// 0x00C37358#5 slot 5
Bool Rva003F7D86Proxy::rva003F7DAE(Int a0)
{
	if (m_holder)
		return static_cast<Rva003F7D86Inner *>(m_holder)->slot5(a0);
	return false;
}

// 0x00C37358#6 slot 6
Bool Rva003F7D86Proxy::rva003F7DC2(Int a0)
{
	if (m_holder)
		return static_cast<Rva003F7D86Inner *>(m_holder)->slot6(a0);
	return false;
}

// 0x00C37358#7 slot 7
Bool Rva003F7D86Proxy::rva003F7DD6(Int a0)
{
	if (m_holder)
		return static_cast<Rva003F7D86Inner *>(m_holder)->slot7(a0);
	return false;
}

// 0x00C37358#8 slot 8
Bool Rva003F7D86Proxy::rva003F7DEA(Int a0)
{
	if (m_holder)
		return static_cast<Rva003F7D86Inner *>(m_holder)->slot8(a0);
	return false;
}

// 0x00C37358#9 slot 9
Bool Rva003F7D86Proxy::rva003F7DFE(Int a0, Int a1)
{
	if (m_holder)
		return static_cast<Rva003F7D86Inner *>(m_holder)->slot9(a0, a1);
	return false;
}

// 0x00C37358#10 slot 10
Bool Rva003F7D86Proxy::rva003F7E12(Int a0, Int a1)
{
	if (m_holder)
		return static_cast<Rva003F7D86Inner *>(m_holder)->slot10(a0, a1);
	return false;
}

// 0x00C37358#11 slot 11
Bool Rva003F7D86Proxy::rva003F7E26(Int a0, Int a1)
{
	if (m_holder)
		return static_cast<Rva003F7D86Inner *>(m_holder)->slot11(a0, a1);
	return false;
}

// 0x00C37358#12 slot 12
Bool Rva003F7D86Proxy::rva003F7E3A(Int a0)
{
	if (m_holder)
		return static_cast<Rva003F7D86Inner *>(m_holder)->slot12(a0);
	return false;
}

// 0x00C37358#13 slot 13
Bool Rva003F7D86Proxy::rva003F7E4E()
{
	if (m_holder)
		return static_cast<Rva003F7D86Inner *>(m_holder)->slot13();
	return false;
}

class Rva003F81FDProxy
{
public:
	Bool rva003F81D3(Int a0);
	Bool rva003F81E8(Int a0);
	Bool rva003F81FD(Int a0, Int a1);
	Bool rva003F8212(Int a0, Int a1);
	Bool rva003F8227(Int a0);
	Bool rva003F823C(Int a0);
	Bool rva003F8251(Int a0);
	Bool rva003F8266(Int a0);
	Bool rva003F827B(Int a0, Int a1);
	Bool rva003F8290(Int a0, Int a1);
	Bool rva003F82A5(Int a0, Int a1);
	Bool rva003F82BA(Int a0);
	Bool rva003F82CF();
	Int rva003F834C(Int a0);
	Rva003F7D86Inner *rva003F81B0();			///< pinned 0x003F81B0
private:
	char m_lead[4];
};

// 0x00C3731C#3 slot 3
Bool Rva003F81FDProxy::rva003F81FD(Int a0, Int a1)
{
	Rva003F7D86Inner *inner = rva003F81B0();
	if (inner)
		return inner->slot3(a0, a1);
	return false;
}

// 0x00C3731C#4 slot 4
Bool Rva003F81FDProxy::rva003F8212(Int a0, Int a1)
{
	Rva003F7D86Inner *inner = rva003F81B0();
	if (inner)
		return inner->slot4(a0, a1);
	return false;
}

// 0x00C3731C#5 slot 5
Bool Rva003F81FDProxy::rva003F8227(Int a0)
{
	Rva003F7D86Inner *inner = rva003F81B0();
	if (inner)
		return inner->slot5(a0);
	return false;
}

// 0x00C3731C#6 slot 6
Bool Rva003F81FDProxy::rva003F823C(Int a0)
{
	Rva003F7D86Inner *inner = rva003F81B0();
	if (inner)
		return inner->slot6(a0);
	return false;
}

// 0x00C3731C#7 slot 7
Bool Rva003F81FDProxy::rva003F8251(Int a0)
{
	Rva003F7D86Inner *inner = rva003F81B0();
	if (inner)
		return inner->slot7(a0);
	return false;
}

// 0x00C3731C#8 slot 8
Bool Rva003F81FDProxy::rva003F8266(Int a0)
{
	Rva003F7D86Inner *inner = rva003F81B0();
	if (inner)
		return inner->slot8(a0);
	return false;
}

// 0x00C3731C#9 slot 9
Bool Rva003F81FDProxy::rva003F827B(Int a0, Int a1)
{
	Rva003F7D86Inner *inner = rva003F81B0();
	if (inner)
		return inner->slot9(a0, a1);
	return false;
}

// 0x00C3731C#10 slot 10
Bool Rva003F81FDProxy::rva003F8290(Int a0, Int a1)
{
	Rva003F7D86Inner *inner = rva003F81B0();
	if (inner)
		return inner->slot10(a0, a1);
	return false;
}

// 0x00C3731C#11 slot 11
Bool Rva003F81FDProxy::rva003F82A5(Int a0, Int a1)
{
	Rva003F7D86Inner *inner = rva003F81B0();
	if (inner)
		return inner->slot11(a0, a1);
	return false;
}

// 0x00C3731C#12 slot 12
Bool Rva003F81FDProxy::rva003F82BA(Int a0)
{
	Rva003F7D86Inner *inner = rva003F81B0();
	if (inner)
		return inner->slot12(a0);
	return false;
}

// 0x00C3731C#13 slot 13
Bool Rva003F81FDProxy::rva003F82CF()
{
	Rva003F7D86Inner *inner = rva003F81B0();
	if (inner)
		return inner->slot13();
	return false;
}

// The same null-checked hop in vtable 0x00BD37EC slot 14 (0x0014CDBB): the
// object at +0x14's slot 22, no arguments.
class Rva0014CDBBInner
{
public:
	virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
	virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
	virtual void slot8(); virtual void slot9(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21();
	virtual Int slot22() = 0;
};

class Rva0014CDBBProxy
{
public:
	Int rva0014CDBB();
private:
	char m_lead[0x14];
	Rva0014CDBBInner *m_inner;					// +0x14
};

Int Rva0014CDBBProxy::rva0014CDBB()
{
	return m_inner ? m_inner->slot22() : 0;
}

// 0x00C372D4#1 and #2
Int Rva003F7C53Proxy::rva003F7C2F(Int a0)
{
	return m_inner ? m_inner->slot1(a0) : 0;
}

Int Rva003F7C53Proxy::rva003F7C41(Int a0)
{
	return m_inner ? m_inner->slot2(a0) : 0;
}

// 0x00C37358#1, #2 and #14
Bool Rva003F7D86Proxy::rva003F7D5E(Int a0)
{
	if (m_holder)
		return static_cast<Rva003F7D86Inner *>(m_holder)->slot1(a0);
	return false;
}

Bool Rva003F7D86Proxy::rva003F7D72(Int a0)
{
	if (m_holder)
		return static_cast<Rva003F7D86Inner *>(m_holder)->slot2(a0);
	return false;
}

Int Rva003F7D86Proxy::rva003F7E60(Int a0)
{
	if (m_holder)
		return static_cast<Rva003F7D86Inner *>(m_holder)->slot14(a0);
	return 0;
}

// 0x00C3731C#1, #2 and #14
Bool Rva003F81FDProxy::rva003F81D3(Int a0)
{
	Rva003F7D86Inner *inner = rva003F81B0();
	if (inner)
		return inner->slot1(a0);
	return false;
}

Bool Rva003F81FDProxy::rva003F81E8(Int a0)
{
	Rva003F7D86Inner *inner = rva003F81B0();
	if (inner)
		return inner->slot2(a0);
	return false;
}

Int Rva003F81FDProxy::rva003F834C(Int a0)
{
	Rva003F7D86Inner *inner = rva003F81B0();
	if (inner)
		return inner->slot14(a0);
	return 0;
}
