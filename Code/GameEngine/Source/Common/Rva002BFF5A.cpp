// cl: /O1 /arch:SSE /G7 /Oy- /MD
// Ghidra 2BFF5A..2BFF9F RET4. This is an opaque table search; the
// original class and table specialization remain unresolved. Target bytes
// establish table+AC, node payload+8, embedded OVERRIDE-like view+8 and key+10.
class Rva000411084 {
public:
    void *next();
    void *current;
    void *owner;
};
class Rva000427195 {
public:
    void *first(Rva000411084 *);
};
struct Rva002BFF5AData { char unknown[0x10]; int key; };
class Rva0035C95FView {
public:
    const Rva002BFF5AData *rva0035C95F() const;
    void *head;
};
struct Rva002BFF5AEntry { char unknown[8]; Rva0035C95FView version; };
struct Rva002BFF5ANode { void *next; void *key; Rva002BFF5AEntry *value; };
class Rva002BFF5A {
public:
    Rva002BFF5AEntry *rva002BFF5A(int key);
private:
    char unknown[0xac];
    Rva000427195 table;
};
Rva002BFF5AEntry *Rva002BFF5A::rva002BFF5A(int key)
{
    Rva000411084 it;
    table.first(&it);
    while (it.current) {
        Rva002BFF5ANode *node = static_cast<Rva002BFF5ANode *>(it.current);
        if (node->value->version.rva0035C95F()->key == key)
            return node->value;
        it.next();
    }
    return 0;
}
