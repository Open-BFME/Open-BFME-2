// cl: /O1 /G7 /arch:SSE /MD
// Native1E41D3..1E41FA and WB AF0DB0 establish12B result and hidden
// return-storage construction bit; this corrects the old void/out bank.
// Matrix68 row-translation floats at74/84/94 are target facts. Original
// result class/PODity and constructor form are unresolved structural views.
// Default construction followed by named-result return and copy construction
// emits the native all-SSE direct result stores. The original result name
// and constructor API remain structural inferences rather than target names.
struct Rva001E41D3Result
{
    float x, y, z;
    Rva001E41D3Result() {}
    Rva001E41D3Result(const Rva001E41D3Result &r)
    {
        x = r.x; y = r.y; z = r.z;
    }
};
struct Rva001E41D3Matrix
{
    float m[3][4];
    __forceinline Rva001E41D3Result get()
    {
        Rva001E41D3Result result;
        result.x = m[0][3];
        result.y = m[1][3];
        result.z = m[2][3];
        return result;
    }
};
class Rva001E41D3
{
    char prefix[0x68];
    Rva001E41D3Matrix matrix;
public:
    Rva001E41D3Result rva001E41D3();
};
Rva001E41D3Result Rva001E41D3::rva001E41D3()
{
    return matrix.get();
}
