// cl: /MD /Oy-
// Native Ghidra 0043B8C0..0043B920 RET8. DOTManager is established by
// the rowed neighbouring update/clear receivers, which use this same tree
// at +4. Search the int key, compare and replace an existing +14 value,
// or obtain a missing value through the 92-byte lower-bound/insert helper.
// The assignment provider proves the 88-byte value extent. Its original
// class name and the wrapper's method name remain unknown.
class Rva0043B163
{
public:
    Rva0043B163 &operator=(const Rva0043B163 &other);
    char unknown00[0x10];
    int value10;
    char unknown14[0x88 - 0x14];
};
class Rva0043B196 { char unknown00[0x88]; };
class Rva0043B2E2
{
public:
    Rva0043B196 &rva0043B864(const int &key);
    void *head;
    int flag;
};
class Rva00388F63Map { public: void *find(int *key); };
class Rva0043B8C0 { public: bool rva0043B0EA(void *current, void *incoming); };
class DOTManager
{
public:
    void rva0043B278(int key, int value);
    void rva0043B8C0(int key, const Rva0043B163 *incoming);
private:
    char unknown00[4];
    Rva0043B2E2 tree;
};

void DOTManager::rva0043B8C0(int key, const Rva0043B163 *incoming)
{
    void *node = reinterpret_cast<Rva00388F63Map *>(&tree)->find(&key);
    if (node != tree.head)
    {
        Rva0043B163 *current = reinterpret_cast<Rva0043B163 *>(
            static_cast<char *>(node) + 0x14);
        if (reinterpret_cast<Rva0043B8C0 *>(this)->rva0043B0EA(
                current, const_cast<Rva0043B163 *>(incoming)))
        {
            *current = *incoming;
            rva0043B278(key, incoming->value10);
        }
    }
    else
        reinterpret_cast<Rva0043B163 &>(tree.rva0043B864(key)) = *incoming;
}
