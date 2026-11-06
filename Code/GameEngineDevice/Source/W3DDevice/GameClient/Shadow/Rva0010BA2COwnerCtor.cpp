// cl: /DNDEBUG /MD
// Native RVA0x0010BA2C /25B: address-derived resource-owner constructor.
// The previous VictoryConditions identity is refuted by target evidence:
// factory0x10BB11 allocates0x118 and reuses owners through+0x114; the separate
// donor-designated VictoryConditions creator0x41DFB allocates0xC4 and calls4CDCD.
// Constructor and destructor0x1092B9 install the same tableVA0xBCF9E0:
// deleting wrapper0x10BA45; common0xB3FD0; manager forwarder0x109DA6.
// The next words are -3.2/+3.2 floats. Neither108895 nor10BA61 is a table slot.
// Forwarder109DA6 reaches the graphics resource manager; destructor releases
// retained objects at+0x68/+0x70 then restores base tableBCEFA0.
// Native direct calls prove the rowed base ctorF0F2B and ordinary no-arg
// member108895 ABI. The reset and factory establish the0x118 storage view;
// the original name and complete virtual interface remain unknown.
struct Rva00108895Triplet
{
    float first, second, third;
    void set(float value) { first = value; second = value; third = value; }
};
class Rva007AFF00Ref
{
public:
	virtual void deleteThis();
	int m_refCount;
};
class Rva000F0F2B
{
public:
    Rva000F0F2B() throw();
    virtual ~Rva000F0F2B();
protected:
    char m_body[0x64];
};

class Rva007AFF00Owner : public Rva000F0F2B
{
public:
    Rva007AFF00Owner() throw();
    virtual ~Rva007AFF00Owner();
    void rva00108895();
private:
    Rva007AFF00Ref *m_first;
    int m_padding;
    Rva007AFF00Ref *m_second;
    unsigned char flag74;
    char unknown75[3];
    float value78;
    float value7C;
    unsigned int word80;
    unsigned char flag84;
    unsigned char flag85;
    char unknown86[2];
    Rva00108895Triplet sentinel88;
    unsigned int array94[16];
    unsigned int arrayD4[16];
    Rva007AFF00Owner *next114;
};

Rva007AFF00Owner::Rva007AFF00Owner()
{
    rva00108895();
}
