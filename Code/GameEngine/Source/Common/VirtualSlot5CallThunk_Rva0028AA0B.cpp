// This body is the donor unit's Offset112IntegerSetterThunk::setValue lead,
// but the donor's class identity is not assigned to retail. The target bytes
// at 0x0028AA0B independently show one stack dword stored through ECX at
// +0x70, followed by ret 4. A ret 4 at 0x0028AA08 immediately precedes this
// ten-byte body, and the next retail function begins at 0x0028AA15.
// The class name below is address-derived; only the one-dword setter behavior
// and +0x70 displacement are asserted for the target.
struct Rva0028AA0BOpaqueOwner
{
    unsigned char unknown[0x70];
    int value;

    void setValue(int newValue);
};

void Rva0028AA0BOpaqueOwner::setValue(int newValue)
{
    value = newValue;
}
