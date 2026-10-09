// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Target evidence: WB11A8FF0 transfers the same object to TransportContain's
// onRemoving1159EA0; native47BB3B..47BB6B RET4 is the complete48-byte wrapper.
// The object uses the established condition words at10C, bit209 (byte126 bit1),
// followed by notifier28AE6D and parent467AB8. Receiver identity and original
// helper spelling remain unproven; retain the bank's address-derived owner.
// The existing parent pin is shared without an alias or another name.
// This replaces the bank's byte-only view, which cached the field address;
// the word-based flag update reproduces retail's direct memory operation.

class Object
{
public:
    void rva0028AE6D();
    char m_unrecovered000[0x10C];
    unsigned m_modelConditionFlags[19];
};

class Rva00467AB8
{
public:
    void rva00467AB8(Object *object);
};

class Rva0047BB3BOwner
{
public:
    void rva0047BB3B(Object *object);
};

void Rva0047BB3BOwner::rva0047BB3B(Object *object)
{
    if (object)
    {
        if (reinterpret_cast<const unsigned char *>(object->m_modelConditionFlags)[26] & 2)
        {
            object->m_modelConditionFlags[6] &= ~(1U << 17);
            object->rva0028AE6D();
        }
        reinterpret_cast<Rva00467AB8 *>(this)->rva00467AB8(object);
    }
}
