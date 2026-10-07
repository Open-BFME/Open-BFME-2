// cl: /O1
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva000B9AAA@@QAE@XZ, retail 0x000B9A9E, 12 bytes.
// __thiscall default ctor delegating to rowed base-like ctor 0x000B6A67 on same this; returns this.
// Evidence: call at 0xB9AA1 to rowed ??0Rva000B6A67@@QAE@XZ, immediately followed by rowed ??1Rva000B9AAA@@QAE@XZ at 0xB9AAA (same StringBase at +0x10), prev/next // cl: /O1 with no EH.
class Rva000B6A67 {
public:
    Rva000B6A67();
private:
    char m_nativeFields[0x14];
};
class Rva000B9AAA {
public:
    Rva000B9AAA();
private:
    Rva000B6A67 m_base;
};
Rva000B9AAA::Rva000B9AAA() {}

// Retail0x000B9AB2..0x000B9AC2 extends the same 20-byte base-like
// record with a null pointer at+0x14. The paired cleanup0xB9AC2 releases this pointer at+0x28 and
// destroys the base string at+0x10.
// The original application class and identity of the tail pointer are unknown.
class Rva000B9AB2 {
public:
    Rva000B9AB2();
private:
    Rva000B6A67 m_base;
    void *m_pointer14;
};
Rva000B9AB2::Rva000B9AB2() : m_pointer14(0) {}
