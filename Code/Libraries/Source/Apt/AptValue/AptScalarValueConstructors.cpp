// cl: /O1 /DNDEBUG /MD
// Three Apt scalar value constructors, one shape: construct the AptValue base
// through the rowed single-int constructor 0x006DCCC0 with the value's type
// code, store the payload at +8, then install the derived vtable.
//
// ??0Rva006D8860BoolValue@@QAE@_N@Z   @0x006D8860 29B  type 5, byte payload, vtable 0x00CEA600
// ??0Rva006D86A0FloatValue@@QAE@M@Z   @0x006D86A0 29B  type 6, float payload, vtable 0x00CEA560
// ??0Rva006D84C0IntValue@@QAE@H@Z     @0x006D84C0 29B  type 7, int payload, vtable 0x00CEA4C0
//
// Found by compiling the Open-BFME-1 donors Rva008995E0AptBoolValueCtor.cpp,
// Rva008A4C00AptFloatValueCtor.cpp and Rva008A1110AptIntValueCtor.cpp
// (reference/open-bfme-1 @ 6583b3c1) at /O1. Each places uniquely in
// unclaimed .text. The payload kinds come from the stores (byte, dword) and
// from the donors' parameter types. Class names are address-derived and the
// original Apt type names are not recovered.

class BfmeAptValue006DCD20
{
    virtual void vtableSlot0();
    unsigned int m_flags;
public:
    BfmeAptValue006DCD20(int type);
};

class Rva006D8860BoolValue : public BfmeAptValue006DCD20
{
public:
    Rva006D8860BoolValue(bool value);
    virtual void vtableSlot0();
private:
    bool m_value;   // +0x08
};

Rva006D8860BoolValue::Rva006D8860BoolValue(bool value) : BfmeAptValue006DCD20(5)
{
    m_value = value;
}

class Rva006D86A0FloatValue : public BfmeAptValue006DCD20
{
public:
    Rva006D86A0FloatValue(float value);
    virtual void vtableSlot0();
private:
    float m_value;  // +0x08
};

Rva006D86A0FloatValue::Rva006D86A0FloatValue(float value) : BfmeAptValue006DCD20(6)
{
    m_value = value;
}

class Rva006D84C0IntValue : public BfmeAptValue006DCD20
{
public:
    Rva006D84C0IntValue(int value);
    virtual void vtableSlot0();
private:
    int m_value;    // +0x08
};

Rva006D84C0IntValue::Rva006D84C0IntValue(int value) : BfmeAptValue006DCD20(7)
{
    m_value = value;
}
