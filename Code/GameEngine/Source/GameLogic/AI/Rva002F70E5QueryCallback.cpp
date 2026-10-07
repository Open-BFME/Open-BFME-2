// cl: /O1 /arch:SSE /G7 /Oy- /MD
// Native 002F70E5..002F714B, framed ECX member, RET 8, AL result. Target
// evidence establishes eleven arguments to 002F57E6 (RET 44, AL result).
// The call may replace the second input word. A zero result word returns
// true; otherwise a lower signed word, or an unset minimum, saves both
// original inputs and the new minimum. Original identities and the roles
// of these fields are unknown; declarations below are measured ABI views.
struct Rva002F70E5Coord { float x, y, z; };
class Rva002F57E6Query
{
public:
    bool rva002F57E6(unsigned int a, unsigned int b, unsigned char mode,
        unsigned int first, int second, unsigned int c, unsigned int d,
        unsigned char option, Rva002F70E5Coord *position, float value,
        int *word);
};
class Rva002F70E5Context
{
public:
    bool rva002F70E5(unsigned int first, int second);
private:
    Rva002F57E6Query *query;
    unsigned int word04, word08;
    unsigned char mode0C, option0D, padding0E[2];
    unsigned int word10, word14;
    float value18;
    unsigned int saved1C;
    int saved20, minimum24;
    Rva002F70E5Coord position28;
};

// ?rva002F70E5@Rva002F70E5Context@@QAE_NIH@Z
bool Rva002F70E5Context::rva002F70E5(unsigned int first, int second)
{
    int originalSecond = second;
    if (query->rva002F57E6(word04, word08, mode0C, first, second,
            word14, word10, option0D, &position28, value18, &second))
    {
        if (!second)
            return true;
        if (second < minimum24 || !minimum24)
        {
            minimum24 = second;
            saved1C = first;
            saved20 = originalSecond;
        }
    }
    return false;
}
