// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// Setter reached through a this-adjusting thunk chain (0x00063693 subtracts
// 0x68 and jumps here): stores its argument eight bytes below the adjusted
// receiver. Class name is address-derived.
class Rva0006369E
{
public:
	void rva0006369E(int value);
};
void Rva0006369E::rva0006369E(int value)
{
	((int *)this)[-2] = value;
}
