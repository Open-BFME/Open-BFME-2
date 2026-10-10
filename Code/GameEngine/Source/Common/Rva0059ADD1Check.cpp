// cl: /O2 /G7 /arch:SSE /MD
// Native 0059ADD1..0059ADF4 returns a Boolean with no stack arguments.
// Its adjacent matched 0059ADB9 predicate confirms the value at +0x0C
// and body-query owner at +0x2C. The rowed 0033A65E fallback query returns
// the record whose flag at +0x1D is tested here. Domain identity is unknown.
class Rva0033A65E
{
public:
    void *rva0033A65E();
};

class Rva0059ADD1
{
    char prefix[0x0C];
    float value;
    char gap10[0x1C];
    Rva0033A65E *body;
public:
    bool rva0059ADD1();
};

bool Rva0059ADD1::rva0059ADD1()
{
    if (!body)
        return true;
    if (0.0f >= value) {
        if (!*(bool *)((char *)body->rva0033A65E() + 0x1D))
            return true;
    }
    return false;
}
