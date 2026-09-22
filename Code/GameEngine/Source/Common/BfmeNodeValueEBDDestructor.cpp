// cl: /O1 /MD
// The value destructor reached by the matched EBD tree erase and scalar
// deleting destructor. Retail adjusts this by four before tailcalling the
// mapped-value destructor at 0x0038240F.

class BfmeMappedValueEBD
{
public:
    ~BfmeMappedValueEBD();
};

class BfmeNodeValueEBD
{
public:
    ~BfmeNodeValueEBD();
private:
    unsigned m_key;
    BfmeMappedValueEBD m_value;
};

BfmeNodeValueEBD::~BfmeNodeValueEBD()
{
}
