// cl: /O1 /G7 /arch:SSE /MD
// Complete 14-byte float-store twin of the rowed Matrix3D setter at
// 00481FAF. Native 0005634C calls this slot on its borrowed lookup result;
// its original record identity is unknown. Keep the helper in a separate
// unit so its caller uses the retail external-call register convention.
class Rva00481FAFFloatSlot
{
public:
    __declspec(noinline) void store(float value);
private:
    char at00[0x2c];
    float value;
};

void Rva00481FAFFloatSlot::store(float next)
{
    value = next;
}
