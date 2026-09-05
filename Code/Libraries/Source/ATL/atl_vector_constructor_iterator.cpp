// cl: /O1
// Microsoft Visual C++ .NET 2003's plain vector constructor iterator is
// emitted by a translation unit that allocates an array of a class with a
// user supplied constructor and no destructor.  ATL's headers use this same
// compiler helper for the non-throwing array paths.

typedef unsigned int size_t;

extern void *__cdecl operator new[](size_t size);

class CAtlVectorConstructorElement
{
public:
    CAtlVectorConstructorElement() : m_value(0)
    {
    }

private:
    int m_value;
};

void AtlVectorConstructorIteratorAnchor(int count)
{
    CAtlVectorConstructorElement *elements =
        new CAtlVectorConstructorElement[count];
    (void)elements;
}
