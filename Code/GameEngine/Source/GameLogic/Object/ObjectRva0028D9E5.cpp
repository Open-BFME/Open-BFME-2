// cl: /DNDEBUG /MD
// ?rva0028D9E5@Object@@QBE_NH@Z retail 0x0028D9E5 67B.
// Object bit query with provider override: calls rowed
// ?rva0028C197@Object (0x0028C197) for the +0x250 interface object then its
// virtual slot 44 (0xb0) with the bit index; on null or false falls back to
// the local flag words at +0x284 via unsigned-shr bit test. Owner proven by
// same-this call to the Object row plus Object-consistent +0x284. Callers
// include 0x00290D3A 0x00294103 0x0046B988 0x004CB3C3. Flags from the next
// rowed neighbour BitFlagsCountIntersection.cpp.
class BitTestProvider
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
    virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
    virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
    virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
    virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
    virtual bool slot44(int bit);
};

class Object
{
public:
    void *rva0028C197() const;
    bool rva0028D9E5(int bit) const;
private:
    char m_pad00[0x284];
    unsigned int m_bits[4];
};

bool Object::rva0028D9E5(int bit) const
{
    void *prov = rva0028C197();
    if (prov != 0)
    {
        if (((BitTestProvider*)prov)->slot44(bit))
            return true;
    }
    return (m_bits[(unsigned int)bit >> 5] & (1u << (bit & 31))) != 0;
}
