// cl: /O1 /DNDEBUG /MD
//
// Static-initializer strip for the behavior freelist pool at VA 0x00DA60E8.
// Retail repeats one 26-byte dynamic initializer 716 times between
// 0x007AB800 and 0x007B5xxx: grow(0, -1) on the pool (a no-op that returns
// false; the native body exits early on size -1), then atexit() of a
// per-copy cleanup thunk in the 0x007B68xx..0x007B9xxx atexit strip. Each
// copy is the per-translation-unit initializer the compiler emits for a
// header-level pool object; the owning TUs are not recovered, so each copy
// keeps an honest address name. Every cleanup is already rowed in
// Rva007B6880Thunks.cpp as ?rva<addr>@@YAXXZ (ecx=pool, tail-jump to the
// pool clear 0x001EAF7B), and the pool itself is the one the matched
// Rva0029FB3BMember::init pops from.

extern "C" int __cdecl atexit(void (__cdecl *)(void));

struct Rva007AB800PoolInits;

class FreelistPool
{
	friend struct Rva007AB800PoolInits;

private:
	bool grow( int arena, int size );
};

extern FreelistPool g_freelistPool;

void __cdecl rva007B6850();
void __cdecl rva007B6AAA();
void __cdecl rva007B6AB4();
void __cdecl rva007B6ABE();
void __cdecl rva007B6AF1();
void __cdecl rva007B6AFB();
void __cdecl rva007B6B0F();
void __cdecl rva007B6B2D();
void __cdecl rva007B6B4B();
void __cdecl rva007B6B55();
void __cdecl rva007B6B5F();
void __cdecl rva007B6B69();
void __cdecl rva007B6B7D();
void __cdecl rva007B6B87();
void __cdecl rva007B6B9B();
void __cdecl rva007B6BA5();
void __cdecl rva007B6BAF();
void __cdecl rva007B6BCD();
void __cdecl rva007B6BD7();
void __cdecl rva007B6BEB();
void __cdecl rva007B6BFF();
void __cdecl rva007B6C09();
void __cdecl rva007B6C16();
void __cdecl rva007B6C20();
void __cdecl rva007B6C34();
void __cdecl rva007B6C48();
void __cdecl rva007B6C52();
void __cdecl rva007B6C5C();
void __cdecl rva007B6CA5();
void __cdecl rva007B6CB9();
void __cdecl rva007B6CC3();
void __cdecl rva007B6CCD();
void __cdecl rva007B6CD7();
void __cdecl rva007B6CEB();
void __cdecl rva007B6CF5();
void __cdecl rva007B6D13();
void __cdecl rva007B6D31();
void __cdecl rva007B6D3B();
void __cdecl rva007B6D45();
void __cdecl rva007B6D4F();
void __cdecl rva007B6D59();
void __cdecl rva007B6D63();
void __cdecl rva007B6D6D();
void __cdecl rva007B6D77();
void __cdecl rva007B6D81();
void __cdecl rva007B6D8B();
void __cdecl rva007B6D95();
void __cdecl rva007B6D9F();
void __cdecl rva007B6DAA();
void __cdecl rva007B6DB4();
void __cdecl rva007B6DBE();
void __cdecl rva007B6DC8();
void __cdecl rva007B6DD2();
void __cdecl rva007B6DDC();
void __cdecl rva007B6DE6();
void __cdecl rva007B6DF0();
void __cdecl rva007B6E04();
void __cdecl rva007B6E0E();
void __cdecl rva007B6E22();
void __cdecl rva007B6E2C();
void __cdecl rva007B6E40();
void __cdecl rva007B6E4A();
void __cdecl rva007B6E68();
void __cdecl rva007B6E86();
void __cdecl rva007B6E9A();
void __cdecl rva007B6EA4();
void __cdecl rva007B6EB8();
void __cdecl rva007B6ECC();
void __cdecl rva007B6EE0();
void __cdecl rva007B6EFE();
void __cdecl rva007B6F1C();
void __cdecl rva007B6F28();
void __cdecl rva007B6F32();
void __cdecl rva007B6F3E();
void __cdecl rva007B6F48();
void __cdecl rva007B6F52();
void __cdecl rva007B6F66();
void __cdecl rva007B6F70();
void __cdecl rva007B6F7A();
void __cdecl rva007B6F84();
void __cdecl rva007B6FA2();
void __cdecl rva007B6FAC();
void __cdecl rva007B751A();
void __cdecl rva007B7524();
void __cdecl rva007B752E();
void __cdecl rva007B7538();
void __cdecl rva007B7542();
void __cdecl rva007B754C();
void __cdecl rva007B7560();
void __cdecl rva007B756A();
void __cdecl rva007B7574();
void __cdecl rva007B757E();
void __cdecl rva007B7592();
void __cdecl rva007B75B0();
void __cdecl rva007B75BA();
void __cdecl rva007B75CE();
void __cdecl rva007B75D8();
void __cdecl rva007B75EC();
void __cdecl rva007B7600();
void __cdecl rva007B7614();
void __cdecl rva007B761E();
void __cdecl rva007B7628();
void __cdecl rva007B7646();
void __cdecl rva007B76D2();
void __cdecl rva007B76F0();
void __cdecl rva007B7722();
void __cdecl rva007B772C();
void __cdecl rva007B774A();
void __cdecl rva007B7754();
void __cdecl rva007B7772();
void __cdecl rva007B7790();
void __cdecl rva007B779A();
void __cdecl rva007B77A4();
void __cdecl rva007B77AE();
void __cdecl rva007B77C3();
void __cdecl rva007B77CE();
void __cdecl rva007B77E2();
void __cdecl rva007B77FC();
void __cdecl rva007B7806();
void __cdecl rva007B7838();
void __cdecl rva007B7888();
void __cdecl rva007B78B0();
void __cdecl rva007B78CE();
void __cdecl rva007B78D8();
void __cdecl rva007B78E2();
void __cdecl rva007B78F6();
void __cdecl rva007B790A();
void __cdecl rva007B7914();
void __cdecl rva007B791E();
void __cdecl rva007B7928();
void __cdecl rva007B7932();
void __cdecl rva007B793C();
void __cdecl rva007B7946();
void __cdecl rva007B7950();
void __cdecl rva007B795A();
void __cdecl rva007B7964();
void __cdecl rva007B79C9();
void __cdecl rva007B79D3();
void __cdecl rva007B79DD();
void __cdecl rva007B79E7();
void __cdecl rva007B79F1();
void __cdecl rva007B7A0F();
void __cdecl rva007B7A23();
void __cdecl rva007B7A2D();
void __cdecl rva007B7A4B();
void __cdecl rva007B7A73();
void __cdecl rva007B7AAF();
void __cdecl rva007B7AB9();
void __cdecl rva007B7AC3();
void __cdecl rva007B7AEB();
void __cdecl rva007B7B1E();
void __cdecl rva007B7B32();
void __cdecl rva007B7B3C();
void __cdecl rva007B7B46();
void __cdecl rva007B7B78();
void __cdecl rva007B7B96();
void __cdecl rva007B7BA0();
void __cdecl rva007B7BAA();
void __cdecl rva007B7BB4();
void __cdecl rva007B7BD2();
void __cdecl rva007B7BDC();
void __cdecl rva007B7BE6();
void __cdecl rva007B7BF0();
void __cdecl rva007B7BFA();
void __cdecl rva007B7C0E();
void __cdecl rva007B7C18();
void __cdecl rva007B7C22();
void __cdecl rva007B7C2C();
void __cdecl rva007B7C36();
void __cdecl rva007B7C4A();
void __cdecl rva007B7C54();
void __cdecl rva007B7C5E();
void __cdecl rva007B7C68();
void __cdecl rva007B7C91();
void __cdecl rva007B7C9B();
void __cdecl rva007B7CA5();
void __cdecl rva007B7CB9();
void __cdecl rva007B7CCD();
void __cdecl rva007B7CE1();
void __cdecl rva007B7CEB();
void __cdecl rva007B7CFF();
void __cdecl rva007B7D09();
void __cdecl rva007B7D13();
void __cdecl rva007B7D1D();
void __cdecl rva007B7D4F();
void __cdecl rva007B7D63();
void __cdecl rva007B7D6D();
void __cdecl rva007B7D8B();
void __cdecl rva007B7D9F();
void __cdecl rva007B7DA9();
void __cdecl rva007B7DBD();
void __cdecl rva007B7DE5();
void __cdecl rva007B7DEF();
void __cdecl rva007B7DF9();
void __cdecl rva007B7E03();
void __cdecl rva007B7E17();
void __cdecl rva007B7E2B();
void __cdecl rva007B7E35();
void __cdecl rva007B7E53();
void __cdecl rva007B7E5D();
void __cdecl rva007B7E67();
void __cdecl rva007B7E71();
void __cdecl rva007B7E7B();
void __cdecl rva007B7E85();
void __cdecl rva007B806F();
void __cdecl rva007B8079();
void __cdecl rva007B8083();
void __cdecl rva007B808D();
void __cdecl rva007B8097();
void __cdecl rva007B80AB();
void __cdecl rva007B80D3();
void __cdecl rva007B80DD();
void __cdecl rva007B80E7();
void __cdecl rva007B815F();
void __cdecl rva007B816B();
void __cdecl rva007B819D();
void __cdecl rva007B81A7();
void __cdecl rva007B81B1();
void __cdecl rva007B81BB();
void __cdecl rva007B81C5();
void __cdecl rva007B81CF();
void __cdecl rva007B81D9();
void __cdecl rva007B81E3();
void __cdecl rva007B81ED();
void __cdecl rva007B820B();
void __cdecl rva007B8215();
void __cdecl rva007B8251();
void __cdecl rva007B825B();
void __cdecl rva007B826F();
void __cdecl rva007B8279();
void __cdecl rva007B828D();
void __cdecl rva007B8297();
void __cdecl rva007B82A1();
void __cdecl rva007B82AB();
void __cdecl rva007B82B5();
void __cdecl rva007B82F1();
void __cdecl rva007B82FB();
void __cdecl rva007B8305();
void __cdecl rva007B830F();
void __cdecl rva007B8319();
void __cdecl rva007B832D();
void __cdecl rva007B8337();
void __cdecl rva007B8341();
void __cdecl rva007B8355();
void __cdecl rva007B835F();
void __cdecl rva007B8373();
void __cdecl rva007B8387();
void __cdecl rva007B8391();
void __cdecl rva007B83AF();
void __cdecl rva007B83C3();
void __cdecl rva007B83CD();
void __cdecl rva007B83D7();
void __cdecl rva007B8413();
void __cdecl rva007B841D();
void __cdecl rva007B8427();
void __cdecl rva007B8431();
void __cdecl rva007B8445();
void __cdecl rva007B8459();
void __cdecl rva007B846D();
void __cdecl rva007B8477();
void __cdecl rva007B848B();
void __cdecl rva007B8495();
void __cdecl rva007B849F();
void __cdecl rva007B84A9();
void __cdecl rva007B84B3();
void __cdecl rva007B84BD();
void __cdecl rva007B84C7();
void __cdecl rva007B84D1();
void __cdecl rva007B84DB();
void __cdecl rva007B84E5();
void __cdecl rva007B84EF();
void __cdecl rva007B8503();
void __cdecl rva007B850D();
void __cdecl rva007B8517();
void __cdecl rva007B8521();
void __cdecl rva007B852B();
void __cdecl rva007B8535();
void __cdecl rva007B853F();
void __cdecl rva007B8549();
void __cdecl rva007B8553();
void __cdecl rva007B855D();
void __cdecl rva007B8567();
void __cdecl rva007B8571();
void __cdecl rva007B857B();
void __cdecl rva007B8586();
void __cdecl rva007B859A();
void __cdecl rva007B85A4();
void __cdecl rva007B85AE();
void __cdecl rva007B85C2();
void __cdecl rva007B85CC();
void __cdecl rva007B85D6();
void __cdecl rva007B85E3();
void __cdecl rva007B85ED();
void __cdecl rva007B85F7();
void __cdecl rva007B8601();
void __cdecl rva007B860B();
void __cdecl rva007B8615();
void __cdecl rva007B861F();
void __cdecl rva007B8629();
void __cdecl rva007B8633();
void __cdecl rva007B863D();
void __cdecl rva007B8647();
void __cdecl rva007B8651();
void __cdecl rva007B865B();
void __cdecl rva007B8665();
void __cdecl rva007B866F();
void __cdecl rva007B8679();
void __cdecl rva007B8683();
void __cdecl rva007B868D();
void __cdecl rva007B86A1();
void __cdecl rva007B86AB();
void __cdecl rva007B86B5();
void __cdecl rva007B86BF();
void __cdecl rva007B86C9();
void __cdecl rva007B86D3();
void __cdecl rva007B86DD();
void __cdecl rva007B86E7();
void __cdecl rva007B86F1();
void __cdecl rva007B86FB();
void __cdecl rva007B8705();
void __cdecl rva007B870F();
void __cdecl rva007B8719();
void __cdecl rva007B8723();
void __cdecl rva007B872D();
void __cdecl rva007B8737();
void __cdecl rva007B8741();
void __cdecl rva007B874B();
void __cdecl rva007B8755();
void __cdecl rva007B875F();
void __cdecl rva007B8773();
void __cdecl rva007B877D();
void __cdecl rva007B8787();
void __cdecl rva007B8791();
void __cdecl rva007B879B();
void __cdecl rva007B87A5();
void __cdecl rva007B87AF();
void __cdecl rva007B87B9();
void __cdecl rva007B87C3();
void __cdecl rva007B87CD();
void __cdecl rva007B87D7();
void __cdecl rva007B87E1();
void __cdecl rva007B87EB();
void __cdecl rva007B87F5();
void __cdecl rva007B87FF();
void __cdecl rva007B8809();
void __cdecl rva007B8813();
void __cdecl rva007B8827();
void __cdecl rva007B8831();
void __cdecl rva007B883B();
void __cdecl rva007B8845();
void __cdecl rva007B884F();
void __cdecl rva007B8859();
void __cdecl rva007B8863();
void __cdecl rva007B886D();
void __cdecl rva007B8877();
void __cdecl rva007B8881();
void __cdecl rva007B888B();
void __cdecl rva007B8895();
void __cdecl rva007B889F();
void __cdecl rva007B88A9();
void __cdecl rva007B88B3();
void __cdecl rva007B88BD();
void __cdecl rva007B88C7();
void __cdecl rva007B88DB();
void __cdecl rva007B88E5();
void __cdecl rva007B88EF();
void __cdecl rva007B88F9();
void __cdecl rva007B8903();
void __cdecl rva007B890D();
void __cdecl rva007B8917();
void __cdecl rva007B8921();
void __cdecl rva007B892B();
void __cdecl rva007B8935();
void __cdecl rva007B893F();
void __cdecl rva007B8949();
void __cdecl rva007B8953();
void __cdecl rva007B895D();
void __cdecl rva007B8967();
void __cdecl rva007B8971();
void __cdecl rva007B897B();
void __cdecl rva007B8985();
void __cdecl rva007B898F();
void __cdecl rva007B8999();
void __cdecl rva007B89A3();
void __cdecl rva007B89AD();
void __cdecl rva007B89B7();
void __cdecl rva007B89CB();
void __cdecl rva007B89D5();
void __cdecl rva007B89DF();
void __cdecl rva007B89E9();
void __cdecl rva007B89F3();
void __cdecl rva007B89FD();
void __cdecl rva007B8A07();
void __cdecl rva007B8A11();
void __cdecl rva007B8A1B();
void __cdecl rva007B8A25();
void __cdecl rva007B8A2F();
void __cdecl rva007B8A39();
void __cdecl rva007B8A43();
void __cdecl rva007B8A4D();
void __cdecl rva007B8A57();
void __cdecl rva007B8A61();
void __cdecl rva007B8A6B();
void __cdecl rva007B8A75();
void __cdecl rva007B8A7F();
void __cdecl rva007B8A89();
void __cdecl rva007B8A93();
void __cdecl rva007B8A9D();
void __cdecl rva007B8AA7();
void __cdecl rva007B8AB1();
void __cdecl rva007B8ABB();
void __cdecl rva007B8AC5();
void __cdecl rva007B8ACF();
void __cdecl rva007B8AD9();
void __cdecl rva007B8AE3();
void __cdecl rva007B8AED();
void __cdecl rva007B8AF7();
void __cdecl rva007B8B01();
void __cdecl rva007B8B0B();
void __cdecl rva007B8B15();
void __cdecl rva007B8B1F();
void __cdecl rva007B8B29();
void __cdecl rva007B8B33();
void __cdecl rva007B8B3D();
void __cdecl rva007B8B47();
void __cdecl rva007B8B51();
void __cdecl rva007B8B5B();
void __cdecl rva007B8B65();
void __cdecl rva007B8B6F();
void __cdecl rva007B8B79();
void __cdecl rva007B8B83();
void __cdecl rva007B8B8D();
void __cdecl rva007B8B97();
void __cdecl rva007B8BA1();
void __cdecl rva007B8BAB();
void __cdecl rva007B8BB5();
void __cdecl rva007B8BBF();
void __cdecl rva007B8BC9();
void __cdecl rva007B8BD3();
void __cdecl rva007B8BDD();
void __cdecl rva007B8BE7();
void __cdecl rva007B8BF1();
void __cdecl rva007B8BFB();
void __cdecl rva007B8C05();
void __cdecl rva007B8C0F();
void __cdecl rva007B8C19();
void __cdecl rva007B8C23();
void __cdecl rva007B8C2D();
void __cdecl rva007B8C37();
void __cdecl rva007B8C41();
void __cdecl rva007B8C4B();
void __cdecl rva007B8C55();
void __cdecl rva007B8C5F();
void __cdecl rva007B8C69();
void __cdecl rva007B8C73();
void __cdecl rva007B8C87();
void __cdecl rva007B8C91();
void __cdecl rva007B8C9B();
void __cdecl rva007B8CA5();
void __cdecl rva007B8CAF();
void __cdecl rva007B8CB9();
void __cdecl rva007B8CC3();
void __cdecl rva007B8CCD();
void __cdecl rva007B8CD7();
void __cdecl rva007B8CE1();
void __cdecl rva007B8CEB();
void __cdecl rva007B8CF5();
void __cdecl rva007B8CFF();
void __cdecl rva007B8D09();
void __cdecl rva007B8D13();
void __cdecl rva007B8D1D();
void __cdecl rva007B8D27();
void __cdecl rva007B8D31();
void __cdecl rva007B8D3B();
void __cdecl rva007B8D45();
void __cdecl rva007B8D4F();
void __cdecl rva007B8D59();
void __cdecl rva007B8D63();
void __cdecl rva007B8D6D();
void __cdecl rva007B8D77();
void __cdecl rva007B8D81();
void __cdecl rva007B8D8B();
void __cdecl rva007B8D95();
void __cdecl rva007B8D9F();
void __cdecl rva007B8DA9();
void __cdecl rva007B8DB3();
void __cdecl rva007B8DBD();
void __cdecl rva007B8DC7();
void __cdecl rva007B8DD1();
void __cdecl rva007B8DDB();
void __cdecl rva007B8DE5();
void __cdecl rva007B8DEF();
void __cdecl rva007B8DF9();
void __cdecl rva007B8E03();
void __cdecl rva007B8E0D();
void __cdecl rva007B8E17();
void __cdecl rva007B8E21();
void __cdecl rva007B8E2B();
void __cdecl rva007B8E35();
void __cdecl rva007B8E3F();
void __cdecl rva007B8E49();
void __cdecl rva007B8E53();
void __cdecl rva007B8E5D();
void __cdecl rva007B8E67();
void __cdecl rva007B8E71();
void __cdecl rva007B8E7B();
void __cdecl rva007B8E85();
void __cdecl rva007B8E8F();
void __cdecl rva007B8E9A();
void __cdecl rva007B8EAE();
void __cdecl rva007B8EB8();
void __cdecl rva007B8EC2();
void __cdecl rva007B8ECC();
void __cdecl rva007B8EE0();
void __cdecl rva007B8EEA();
void __cdecl rva007B8EF4();
void __cdecl rva007B8EFE();
void __cdecl rva007B8F30();
void __cdecl rva007B8F3A();
void __cdecl rva007B8F45();

struct Rva007AB800PoolInits
{
	static void rva007AB800();
	static void rva007ABC1B();
	static void rva007ABC45();
	static void rva007ABC7F();
	static void rva007ABCF7();
	static void rva007ABD21();
	static void rva007ABDA7();
	static void rva007ABDD1();
	static void rva007ABDFB();
	static void rva007ABE25();
	static void rva007ABE4F();
	static void rva007ABE79();
	static void rva007ABEAF();
	static void rva007ABED9();
	static void rva007ABF0D();
	static void rva007ABF27();
	static void rva007ABF51();
	static void rva007ABF9F();
	static void rva007ABFC9();
	static void rva007ABFF8();
	static void rva007AC038();
	static void rva007AC062();
	static void rva007AC0B6();
	static void rva007AC0E0();
	static void rva007AC122();
	static void rva007AC183();
	static void rva007AC1AD();
	static void rva007AC1D7();
	static void rva007AC268();
	static void rva007AC292();
	static void rva007AC2AC();
	static void rva007AC2C6();
	static void rva007AC2E0();
	static void rva007AC327();
	static void rva007AC351();
	static void rva007AC37B();
	static void rva007AC3A5();
	static void rva007AC3CF();
	static void rva007AC3F9();
	static void rva007AC423();
	static void rva007AC44D();
	static void rva007AC477();
	static void rva007AC4A1();
	static void rva007AC4CB();
	static void rva007AC4F5();
	static void rva007AC51F();
	static void rva007AC549();
	static void rva007AC573();
	static void rva007AC59D();
	static void rva007AC5C7();
	static void rva007AC5F1();
	static void rva007AC61B();
	static void rva007AC645();
	static void rva007AC66F();
	static void rva007AC699();
	static void rva007AC6C3();
	static void rva007AC6F3();
	static void rva007AC71D();
	static void rva007AC75D();
	static void rva007AC787();
	static void rva007AC7B1();
	static void rva007AC7CB();
	static void rva007AC84C();
	static void rva007AC866();
	static void rva007AC896();
	static void rva007AC8C6();
	static void rva007AC8F6();
	static void rva007AC926();
	static void rva007AC96C();
	static void rva007AC986();
	static void rva007AC9DC();
	static void rva007ACA18();
	static void rva007ACA32();
	static void rva007ACA4C();
	static void rva007ACA66();
	static void rva007ACA80();
	static void rva007ACAC5();
	static void rva007ACAEF();
	static void rva007ACB19();
	static void rva007ACB43();
	static void rva007ACB78();
	static void rva007ACBA2();
	static void rva007AD00A();
	static void rva007AD106();
	static void rva007AD217();
	static void rva007AD256();
	static void rva007AD304();
	static void rva007AD362();
	static void rva007AD3E0();
	static void rva007AD439();
	static void rva007AD4A2();
	static void rva007AD4E1();
	static void rva007AD536();
	static void rva007AD565();
	static void rva007AD5C3();
	static void rva007AD5F2();
	static void rva007AD796();
	static void rva007AD82B();
	static void rva007AD8E0();
	static void rva007AD90F();
	static void rva007AD963();
	static void rva007AD9A2();
	static void rva007ADA61();
	static void rva007ADAE7();
	static void rva007ADB32();
	static void rva007ADBA7();
	static void rva007ADBE5();
	static void rva007ADC2E();
	static void rva007ADC72();
	static void rva007ADCDE();
	static void rva007ADD83();
	static void rva007ADDAD();
	static void rva007ADDDF();
	static void rva007ADE09();
	static void rva007ADE5E();
	static void rva007ADEB2();
	static void rva007ADEDC();
	static void rva007ADF6E();
	static void rva007ADF98();
	static void rva007AE019();
	static void rva007AE06D();
	static void rva007AE0EC();
	static void rva007AE106();
	static void rva007AE130();
	static void rva007AE184();
	static void rva007AE1C8();
	static void rva007AE20C();
	static void rva007AE226();
	static void rva007AE250();
	static void rva007AE28A();
	static void rva007AE2A4();
	static void rva007AE2DE();
	static void rva007AE308();
	static void rva007AE322();
	static void rva007AE34C();
	static void rva007AE376();
	static void rva007AE3C7();
	static void rva007AE3F1();
	static void rva007AE41B();
	static void rva007AE445();
	static void rva007AE46F();
	static void rva007AE4C3();
	static void rva007AE503();
	static void rva007AE561();
	static void rva007AE57B();
	static void rva007AE62A();
	static void rva007AE654();
	static void rva007AE67E();
	static void rva007AE6A8();
	static void rva007AE784();
	static void rva007AE81E();
	static void rva007AE848();
	static void rva007AE87C();
	static void rva007AE896();
	static void rva007AE91D();
	static void rva007AE988();
	static void rva007AE9B2();
	static void rva007AE9CC();
	static void rva007AEA02();
	static void rva007AEA50();
	static void rva007AEA6A();
	static void rva007AEA94();
	static void rva007AEABE();
	static void rva007AEAD8();
	static void rva007AEB02();
	static void rva007AEB2C();
	static void rva007AEB56();
	static void rva007AEB80();
	static void rva007AEBE6();
	static void rva007AEC00();
	static void rva007AEC2A();
	static void rva007AEC44();
	static void rva007AEC5E();
	static void rva007AECD6();
	static void rva007AED00();
	static void rva007AED47();
	static void rva007AED87();
	static void rva007AEDB1();
	static void rva007AEE41();
	static void rva007AEE95();
	static void rva007AEEBF();
	static void rva007AEEE9();
	static void rva007AEF5D();
	static void rva007AEF87();
	static void rva007AEFCB();
	static void rva007AEFF5();
	static void rva007AF01F();
	static void rva007AF049();
	static void rva007AF0BD();
	static void rva007AF0D7();
	static void rva007AF146();
	static void rva007AF170();
	static void rva007AF19A();
	static void rva007AF1B4();
	static void rva007AF22A();
	static void rva007AF26E();
	static void rva007AF298();
	static void rva007AF30A();
	static void rva007AF34F();
	static void rva007AF379();
	static void rva007AF3A3();
	static void rva007AF3BD();
	static void rva007AF431();
	static void rva007AF45B();
	static void rva007AF75B();
	static void rva007AF775();
	static void rva007AF78F();
	static void rva007AF7A9();
	static void rva007AF7C3();
	static void rva007AF819();
	static void rva007AF86F();
	static void rva007AF899();
	static void rva007AF8B3();
	static void rva007AFC3C();
	static void rva007AFCC9();
	static void rva007AFD08();
	static void rva007AFD32();
	static void rva007AFD86();
	static void rva007AFDB0();
	static void rva007AFDDA();
	static void rva007AFE04();
	static void rva007AFE43();
	static void rva007AFE6D();
	static void rva007AFEC6();
	static void rva007AFEF0();
	static void rva007AFF88();
	static void rva007AFFA2();
	static void rva007B0025();
	static void rva007B0054();
	static void rva007B006E();
	static void rva007B0125();
	static void rva007B01B9();
	static void rva007B0212();
	static void rva007B0251();
	static void rva007B0325();
	static void rva007B0369();
	static void rva007B0398();
	static void rva007B03D7();
	static void rva007B0401();
	static void rva007B0455();
	static void rva007B046F();
	static void rva007B0499();
	static void rva007B04DD();
	static void rva007B0507();
	static void rva007B0531();
	static void rva007B0575();
	static void rva007B05B4();
	static void rva007B05FB();
	static void rva007B0651();
	static void rva007B066B();
	static void rva007B0695();
	static void rva007B06BF();
	static void rva007B06D9();
	static void rva007B0703();
	static void rva007B072D();
	static void rva007B0771();
	static void rva007B081A();
	static void rva007B085E();
	static void rva007B0888();
	static void rva007B08DC();
	static void rva007B0906();
	static void rva007B0930();
	static void rva007B095A();
	static void rva007B0974();
	static void rva007B098E();
	static void rva007B09B8();
	static void rva007B09D2();
	static void rva007B09FC();
	static void rva007B0A26();
	static void rva007B0A50();
	static void rva007B0ADE();
	static void rva007B0AF8();
	static void rva007B0B22();
	static void rva007B0B4C();
	static void rva007B0B76();
	static void rva007B0BB1();
	static void rva007B0BCB();
	static void rva007B0BE5();
	static void rva007B0C1F();
	static void rva007B0C39();
	static void rva007B0C63();
	static void rva007B0C8D();
	static void rva007B0D11();
	static void rva007B0D2B();
	static void rva007B0D72();
	static void rva007B0D9C();
	static void rva007B0DC6();
	static void rva007B0E0A();
	static void rva007B0E34();
	static void rva007B0E5E();
	static void rva007B0E88();
	static void rva007B0EB2();
	static void rva007B0EDC();
	static void rva007B0F06();
	static void rva007B0F30();
	static void rva007B0F5A();
	static void rva007B0F84();
	static void rva007B0F9E();
	static void rva007B0FC8();
	static void rva007B0FE2();
	static void rva007B100C();
	static void rva007B1036();
	static void rva007B1060();
	static void rva007B107A();
	static void rva007B10A4();
	static void rva007B10CE();
	static void rva007B10F8();
	static void rva007B1132();
	static void rva007B114C();
	static void rva007B1176();
	static void rva007B11AA();
	static void rva007B11C4();
	static void rva007B11DE();
	static void rva007B11F8();
	static void rva007B1222();
	static void rva007B124C();
	static void rva007B1276();
	static void rva007B1290();
	static void rva007B12BA();
	static void rva007B12E4();
	static void rva007B12FE();
	static void rva007B1338();
	static void rva007B1352();
	static void rva007B137C();
	static void rva007B13A6();
	static void rva007B13D0();
	static void rva007B13FA();
	static void rva007B1414();
	static void rva007B1458();
	static void rva007B1472();
	static void rva007B149C();
	static void rva007B14C6();
	static void rva007B14F0();
	static void rva007B151A();
	static void rva007B1544();
	static void rva007B156E();
	static void rva007B1588();
	static void rva007B15BD();
	static void rva007B15D7();
	static void rva007B1601();
	static void rva007B161B();
	static void rva007B1635();
	static void rva007B164F();
	static void rva007B1669();
	static void rva007B1693();
	static void rva007B16D7();
	static void rva007B16F1();
	static void rva007B171B();
	static void rva007B1745();
	static void rva007B176F();
	static void rva007B1789();
	static void rva007B17A3();
	static void rva007B17CD();
	static void rva007B17F7();
	static void rva007B1811();
	static void rva007B183B();
	static void rva007B1855();
	static void rva007B186F();
	static void rva007B1889();
	static void rva007B18B3();
	static void rva007B18DD();
	static void rva007B1907();
	static void rva007B194B();
	static void rva007B1975();
	static void rva007B198F();
	static void rva007B19B9();
	static void rva007B19D3();
	static void rva007B19FD();
	static void rva007B1A38();
	static void rva007B1A62();
	static void rva007B1A8C();
	static void rva007B1AB6();
	static void rva007B1AE0();
	static void rva007B1B0A();
	static void rva007B1B34();
	static void rva007B1B5E();
	static void rva007B1B78();
	static void rva007B1BA2();
	static void rva007B1BCC();
	static void rva007B1BF6();
	static void rva007B1C20();
	static void rva007B1C3A();
	static void rva007B1C54();
	static void rva007B1C6E();
	static void rva007B1C98();
	static void rva007B1CC2();
	static void rva007B1D02();
	static void rva007B1D2C();
	static void rva007B1D56();
	static void rva007B1D80();
	static void rva007B1D9A();
	static void rva007B1DB4();
	static void rva007B1DDE();
	static void rva007B1E08();
	static void rva007B1E32();
	static void rva007B1E5C();
	static void rva007B1E76();
	static void rva007B1EA0();
	static void rva007B1EBA();
	static void rva007B1EE4();
	static void rva007B1F0E();
	static void rva007B1F38();
	static void rva007B1F62();
	static void rva007B1F8C();
	static void rva007B1FB6();
	static void rva007B1FE0();
	static void rva007B200A();
	static void rva007B2034();
	static void rva007B205E();
	static void rva007B2088();
	static void rva007B20B2();
	static void rva007B20DC();
	static void rva007B2106();
	static void rva007B2130();
	static void rva007B215A();
	static void rva007B2184();
	static void rva007B21AE();
	static void rva007B21D8();
	static void rva007B2202();
	static void rva007B222C();
	static void rva007B2256();
	static void rva007B2280();
	static void rva007B22AA();
	static void rva007B22D4();
	static void rva007B22FE();
	static void rva007B2328();
	static void rva007B2352();
	static void rva007B237C();
	static void rva007B23A6();
	static void rva007B23D0();
	static void rva007B23FA();
	static void rva007B2424();
	static void rva007B243E();
	static void rva007B2458();
	static void rva007B2472();
	static void rva007B248C();
	static void rva007B24A6();
	static void rva007B24D0();
	static void rva007B24FA();
	static void rva007B2524();
	static void rva007B254E();
	static void rva007B2578();
	static void rva007B2592();
	static void rva007B2616();
	static void rva007B2640();
	static void rva007B266A();
	static void rva007B2684();
	static void rva007B269E();
	static void rva007B26B8();
	static void rva007B26D2();
	static void rva007B26FC();
	static void rva007B2716();
	static void rva007B2730();
	static void rva007B275A();
	static void rva007B279E();
	static void rva007B27C8();
	static void rva007B27E2();
	static void rva007B27FC();
	static void rva007B2816();
	static void rva007B2840();
	static void rva007B286A();
	static void rva007B2884();
	static void rva007B289E();
	static void rva007B28B8();
	static void rva007B28D2();
	static void rva007B28EC();
	static void rva007B2916();
	static void rva007B2930();
	static void rva007B295A();
	static void rva007B2984();
	static void rva007B29AE();
	static void rva007B29D8();
	static void rva007B2A02();
	static void rva007B2A2C();
	static void rva007B2A46();
	static void rva007B2A70();
	static void rva007B2A8A();
	static void rva007B2AB4();
	static void rva007B2ACE();
	static void rva007B2AE8();
	static void rva007B2B02();
	static void rva007B2B1C();
	static void rva007B2B46();
	static void rva007B2B70();
	static void rva007B2B9A();
	static void rva007B2BC4();
	static void rva007B2BEE();
	static void rva007B2C18();
	static void rva007B2C42();
	static void rva007B2C6C();
	static void rva007B2C96();
	static void rva007B2CC0();
	static void rva007B2CEA();
	static void rva007B2D04();
	static void rva007B2D1E();
	static void rva007B2D38();
	static void rva007B2D52();
	static void rva007B2D6C();
	static void rva007B2D86();
	static void rva007B2DA0();
	static void rva007B2DBA();
	static void rva007B2DD4();
	static void rva007B2DFE();
	static void rva007B2E28();
	static void rva007B2E52();
	static void rva007B2E6C();
	static void rva007B2E86();
	static void rva007B2EB0();
	static void rva007B2F00();
	static void rva007B2F1A();
	static void rva007B2F34();
	static void rva007B2F5E();
	static void rva007B2F92();
	static void rva007B2FAC();
	static void rva007B2FC6();
	static void rva007B2FF0();
	static void rva007B3030();
	static void rva007B304A();
	static void rva007B3074();
	static void rva007B30AA();
};

#define POOL_INIT(init, cleanup) \
	void Rva007AB800PoolInits::init() \
	{ \
		g_freelistPool.grow( 0, -1 ); \
		atexit( cleanup ); \
	}

// ?rva007AB800@Rva007AB800PoolInits@@SAXXZ @ 0x007AB800 (26B), cleanup 0x007B6850
POOL_INIT( rva007AB800, rva007B6850 )
// ?rva007ABC1B@Rva007AB800PoolInits@@SAXXZ @ 0x007ABC1B (26B), cleanup 0x007B6AAA
POOL_INIT( rva007ABC1B, rva007B6AAA )
// ?rva007ABC45@Rva007AB800PoolInits@@SAXXZ @ 0x007ABC45 (26B), cleanup 0x007B6AB4
POOL_INIT( rva007ABC45, rva007B6AB4 )
// ?rva007ABC7F@Rva007AB800PoolInits@@SAXXZ @ 0x007ABC7F (26B), cleanup 0x007B6ABE
POOL_INIT( rva007ABC7F, rva007B6ABE )
// ?rva007ABCF7@Rva007AB800PoolInits@@SAXXZ @ 0x007ABCF7 (26B), cleanup 0x007B6AF1
POOL_INIT( rva007ABCF7, rva007B6AF1 )
// ?rva007ABD21@Rva007AB800PoolInits@@SAXXZ @ 0x007ABD21 (26B), cleanup 0x007B6AFB
POOL_INIT( rva007ABD21, rva007B6AFB )
// ?rva007ABDA7@Rva007AB800PoolInits@@SAXXZ @ 0x007ABDA7 (26B), cleanup 0x007B6B0F
POOL_INIT( rva007ABDA7, rva007B6B0F )
// ?rva007ABDD1@Rva007AB800PoolInits@@SAXXZ @ 0x007ABDD1 (26B), cleanup 0x007B6B2D
POOL_INIT( rva007ABDD1, rva007B6B2D )
// ?rva007ABDFB@Rva007AB800PoolInits@@SAXXZ @ 0x007ABDFB (26B), cleanup 0x007B6B4B
POOL_INIT( rva007ABDFB, rva007B6B4B )
// ?rva007ABE25@Rva007AB800PoolInits@@SAXXZ @ 0x007ABE25 (26B), cleanup 0x007B6B55
POOL_INIT( rva007ABE25, rva007B6B55 )
// ?rva007ABE4F@Rva007AB800PoolInits@@SAXXZ @ 0x007ABE4F (26B), cleanup 0x007B6B5F
POOL_INIT( rva007ABE4F, rva007B6B5F )
// ?rva007ABE79@Rva007AB800PoolInits@@SAXXZ @ 0x007ABE79 (26B), cleanup 0x007B6B69
POOL_INIT( rva007ABE79, rva007B6B69 )
// ?rva007ABEAF@Rva007AB800PoolInits@@SAXXZ @ 0x007ABEAF (26B), cleanup 0x007B6B7D
POOL_INIT( rva007ABEAF, rva007B6B7D )
// ?rva007ABED9@Rva007AB800PoolInits@@SAXXZ @ 0x007ABED9 (26B), cleanup 0x007B6B87
POOL_INIT( rva007ABED9, rva007B6B87 )
// ?rva007ABF0D@Rva007AB800PoolInits@@SAXXZ @ 0x007ABF0D (26B), cleanup 0x007B6B9B
POOL_INIT( rva007ABF0D, rva007B6B9B )
// ?rva007ABF27@Rva007AB800PoolInits@@SAXXZ @ 0x007ABF27 (26B), cleanup 0x007B6BA5
POOL_INIT( rva007ABF27, rva007B6BA5 )
// ?rva007ABF51@Rva007AB800PoolInits@@SAXXZ @ 0x007ABF51 (26B), cleanup 0x007B6BAF
POOL_INIT( rva007ABF51, rva007B6BAF )
// ?rva007ABF9F@Rva007AB800PoolInits@@SAXXZ @ 0x007ABF9F (26B), cleanup 0x007B6BCD
POOL_INIT( rva007ABF9F, rva007B6BCD )
// ?rva007ABFC9@Rva007AB800PoolInits@@SAXXZ @ 0x007ABFC9 (26B), cleanup 0x007B6BD7
POOL_INIT( rva007ABFC9, rva007B6BD7 )
// ?rva007ABFF8@Rva007AB800PoolInits@@SAXXZ @ 0x007ABFF8 (26B), cleanup 0x007B6BEB
POOL_INIT( rva007ABFF8, rva007B6BEB )
// ?rva007AC038@Rva007AB800PoolInits@@SAXXZ @ 0x007AC038 (26B), cleanup 0x007B6BFF
POOL_INIT( rva007AC038, rva007B6BFF )
// ?rva007AC062@Rva007AB800PoolInits@@SAXXZ @ 0x007AC062 (26B), cleanup 0x007B6C09
POOL_INIT( rva007AC062, rva007B6C09 )
// ?rva007AC0B6@Rva007AB800PoolInits@@SAXXZ @ 0x007AC0B6 (26B), cleanup 0x007B6C16
POOL_INIT( rva007AC0B6, rva007B6C16 )
// ?rva007AC0E0@Rva007AB800PoolInits@@SAXXZ @ 0x007AC0E0 (26B), cleanup 0x007B6C20
POOL_INIT( rva007AC0E0, rva007B6C20 )
// ?rva007AC122@Rva007AB800PoolInits@@SAXXZ @ 0x007AC122 (26B), cleanup 0x007B6C34
POOL_INIT( rva007AC122, rva007B6C34 )
// ?rva007AC183@Rva007AB800PoolInits@@SAXXZ @ 0x007AC183 (26B), cleanup 0x007B6C48
POOL_INIT( rva007AC183, rva007B6C48 )
// ?rva007AC1AD@Rva007AB800PoolInits@@SAXXZ @ 0x007AC1AD (26B), cleanup 0x007B6C52
POOL_INIT( rva007AC1AD, rva007B6C52 )
// ?rva007AC1D7@Rva007AB800PoolInits@@SAXXZ @ 0x007AC1D7 (26B), cleanup 0x007B6C5C
POOL_INIT( rva007AC1D7, rva007B6C5C )
// ?rva007AC268@Rva007AB800PoolInits@@SAXXZ @ 0x007AC268 (26B), cleanup 0x007B6CA5
POOL_INIT( rva007AC268, rva007B6CA5 )
// ?rva007AC292@Rva007AB800PoolInits@@SAXXZ @ 0x007AC292 (26B), cleanup 0x007B6CB9
POOL_INIT( rva007AC292, rva007B6CB9 )
// ?rva007AC2AC@Rva007AB800PoolInits@@SAXXZ @ 0x007AC2AC (26B), cleanup 0x007B6CC3
POOL_INIT( rva007AC2AC, rva007B6CC3 )
// ?rva007AC2C6@Rva007AB800PoolInits@@SAXXZ @ 0x007AC2C6 (26B), cleanup 0x007B6CCD
POOL_INIT( rva007AC2C6, rva007B6CCD )
// ?rva007AC2E0@Rva007AB800PoolInits@@SAXXZ @ 0x007AC2E0 (26B), cleanup 0x007B6CD7
POOL_INIT( rva007AC2E0, rva007B6CD7 )
// ?rva007AC327@Rva007AB800PoolInits@@SAXXZ @ 0x007AC327 (26B), cleanup 0x007B6CEB
POOL_INIT( rva007AC327, rva007B6CEB )
// ?rva007AC351@Rva007AB800PoolInits@@SAXXZ @ 0x007AC351 (26B), cleanup 0x007B6CF5
POOL_INIT( rva007AC351, rva007B6CF5 )
// ?rva007AC37B@Rva007AB800PoolInits@@SAXXZ @ 0x007AC37B (26B), cleanup 0x007B6D13
POOL_INIT( rva007AC37B, rva007B6D13 )
// ?rva007AC3A5@Rva007AB800PoolInits@@SAXXZ @ 0x007AC3A5 (26B), cleanup 0x007B6D31
POOL_INIT( rva007AC3A5, rva007B6D31 )
// ?rva007AC3CF@Rva007AB800PoolInits@@SAXXZ @ 0x007AC3CF (26B), cleanup 0x007B6D3B
POOL_INIT( rva007AC3CF, rva007B6D3B )
// ?rva007AC3F9@Rva007AB800PoolInits@@SAXXZ @ 0x007AC3F9 (26B), cleanup 0x007B6D45
POOL_INIT( rva007AC3F9, rva007B6D45 )
// ?rva007AC423@Rva007AB800PoolInits@@SAXXZ @ 0x007AC423 (26B), cleanup 0x007B6D4F
POOL_INIT( rva007AC423, rva007B6D4F )
// ?rva007AC44D@Rva007AB800PoolInits@@SAXXZ @ 0x007AC44D (26B), cleanup 0x007B6D59
POOL_INIT( rva007AC44D, rva007B6D59 )
// ?rva007AC477@Rva007AB800PoolInits@@SAXXZ @ 0x007AC477 (26B), cleanup 0x007B6D63
POOL_INIT( rva007AC477, rva007B6D63 )
// ?rva007AC4A1@Rva007AB800PoolInits@@SAXXZ @ 0x007AC4A1 (26B), cleanup 0x007B6D6D
POOL_INIT( rva007AC4A1, rva007B6D6D )
// ?rva007AC4CB@Rva007AB800PoolInits@@SAXXZ @ 0x007AC4CB (26B), cleanup 0x007B6D77
POOL_INIT( rva007AC4CB, rva007B6D77 )
// ?rva007AC4F5@Rva007AB800PoolInits@@SAXXZ @ 0x007AC4F5 (26B), cleanup 0x007B6D81
POOL_INIT( rva007AC4F5, rva007B6D81 )
// ?rva007AC51F@Rva007AB800PoolInits@@SAXXZ @ 0x007AC51F (26B), cleanup 0x007B6D8B
POOL_INIT( rva007AC51F, rva007B6D8B )
// ?rva007AC549@Rva007AB800PoolInits@@SAXXZ @ 0x007AC549 (26B), cleanup 0x007B6D95
POOL_INIT( rva007AC549, rva007B6D95 )
// ?rva007AC573@Rva007AB800PoolInits@@SAXXZ @ 0x007AC573 (26B), cleanup 0x007B6D9F
POOL_INIT( rva007AC573, rva007B6D9F )
// ?rva007AC59D@Rva007AB800PoolInits@@SAXXZ @ 0x007AC59D (26B), cleanup 0x007B6DAA
POOL_INIT( rva007AC59D, rva007B6DAA )
// ?rva007AC5C7@Rva007AB800PoolInits@@SAXXZ @ 0x007AC5C7 (26B), cleanup 0x007B6DB4
POOL_INIT( rva007AC5C7, rva007B6DB4 )
// ?rva007AC5F1@Rva007AB800PoolInits@@SAXXZ @ 0x007AC5F1 (26B), cleanup 0x007B6DBE
POOL_INIT( rva007AC5F1, rva007B6DBE )
// ?rva007AC61B@Rva007AB800PoolInits@@SAXXZ @ 0x007AC61B (26B), cleanup 0x007B6DC8
POOL_INIT( rva007AC61B, rva007B6DC8 )
// ?rva007AC645@Rva007AB800PoolInits@@SAXXZ @ 0x007AC645 (26B), cleanup 0x007B6DD2
POOL_INIT( rva007AC645, rva007B6DD2 )
// ?rva007AC66F@Rva007AB800PoolInits@@SAXXZ @ 0x007AC66F (26B), cleanup 0x007B6DDC
POOL_INIT( rva007AC66F, rva007B6DDC )
// ?rva007AC699@Rva007AB800PoolInits@@SAXXZ @ 0x007AC699 (26B), cleanup 0x007B6DE6
POOL_INIT( rva007AC699, rva007B6DE6 )
// ?rva007AC6C3@Rva007AB800PoolInits@@SAXXZ @ 0x007AC6C3 (26B), cleanup 0x007B6DF0
POOL_INIT( rva007AC6C3, rva007B6DF0 )
// ?rva007AC6F3@Rva007AB800PoolInits@@SAXXZ @ 0x007AC6F3 (26B), cleanup 0x007B6E04
POOL_INIT( rva007AC6F3, rva007B6E04 )
// ?rva007AC71D@Rva007AB800PoolInits@@SAXXZ @ 0x007AC71D (26B), cleanup 0x007B6E0E
POOL_INIT( rva007AC71D, rva007B6E0E )
// ?rva007AC75D@Rva007AB800PoolInits@@SAXXZ @ 0x007AC75D (26B), cleanup 0x007B6E22
POOL_INIT( rva007AC75D, rva007B6E22 )
// ?rva007AC787@Rva007AB800PoolInits@@SAXXZ @ 0x007AC787 (26B), cleanup 0x007B6E2C
POOL_INIT( rva007AC787, rva007B6E2C )
// ?rva007AC7B1@Rva007AB800PoolInits@@SAXXZ @ 0x007AC7B1 (26B), cleanup 0x007B6E40
POOL_INIT( rva007AC7B1, rva007B6E40 )
// ?rva007AC7CB@Rva007AB800PoolInits@@SAXXZ @ 0x007AC7CB (26B), cleanup 0x007B6E4A
POOL_INIT( rva007AC7CB, rva007B6E4A )
// ?rva007AC84C@Rva007AB800PoolInits@@SAXXZ @ 0x007AC84C (26B), cleanup 0x007B6E68
POOL_INIT( rva007AC84C, rva007B6E68 )
// ?rva007AC866@Rva007AB800PoolInits@@SAXXZ @ 0x007AC866 (26B), cleanup 0x007B6E86
POOL_INIT( rva007AC866, rva007B6E86 )
// ?rva007AC896@Rva007AB800PoolInits@@SAXXZ @ 0x007AC896 (26B), cleanup 0x007B6E9A
POOL_INIT( rva007AC896, rva007B6E9A )
// ?rva007AC8C6@Rva007AB800PoolInits@@SAXXZ @ 0x007AC8C6 (26B), cleanup 0x007B6EA4
POOL_INIT( rva007AC8C6, rva007B6EA4 )
// ?rva007AC8F6@Rva007AB800PoolInits@@SAXXZ @ 0x007AC8F6 (26B), cleanup 0x007B6EB8
POOL_INIT( rva007AC8F6, rva007B6EB8 )
// ?rva007AC926@Rva007AB800PoolInits@@SAXXZ @ 0x007AC926 (26B), cleanup 0x007B6ECC
POOL_INIT( rva007AC926, rva007B6ECC )
// ?rva007AC96C@Rva007AB800PoolInits@@SAXXZ @ 0x007AC96C (26B), cleanup 0x007B6EE0
POOL_INIT( rva007AC96C, rva007B6EE0 )
// ?rva007AC986@Rva007AB800PoolInits@@SAXXZ @ 0x007AC986 (26B), cleanup 0x007B6EFE
POOL_INIT( rva007AC986, rva007B6EFE )
// ?rva007AC9DC@Rva007AB800PoolInits@@SAXXZ @ 0x007AC9DC (26B), cleanup 0x007B6F1C
POOL_INIT( rva007AC9DC, rva007B6F1C )
// ?rva007ACA18@Rva007AB800PoolInits@@SAXXZ @ 0x007ACA18 (26B), cleanup 0x007B6F28
POOL_INIT( rva007ACA18, rva007B6F28 )
// ?rva007ACA32@Rva007AB800PoolInits@@SAXXZ @ 0x007ACA32 (26B), cleanup 0x007B6F32
POOL_INIT( rva007ACA32, rva007B6F32 )
// ?rva007ACA4C@Rva007AB800PoolInits@@SAXXZ @ 0x007ACA4C (26B), cleanup 0x007B6F3E
POOL_INIT( rva007ACA4C, rva007B6F3E )
// ?rva007ACA66@Rva007AB800PoolInits@@SAXXZ @ 0x007ACA66 (26B), cleanup 0x007B6F48
POOL_INIT( rva007ACA66, rva007B6F48 )
// ?rva007ACA80@Rva007AB800PoolInits@@SAXXZ @ 0x007ACA80 (26B), cleanup 0x007B6F52
POOL_INIT( rva007ACA80, rva007B6F52 )
// ?rva007ACAC5@Rva007AB800PoolInits@@SAXXZ @ 0x007ACAC5 (26B), cleanup 0x007B6F66
POOL_INIT( rva007ACAC5, rva007B6F66 )
// ?rva007ACAEF@Rva007AB800PoolInits@@SAXXZ @ 0x007ACAEF (26B), cleanup 0x007B6F70
POOL_INIT( rva007ACAEF, rva007B6F70 )
// ?rva007ACB19@Rva007AB800PoolInits@@SAXXZ @ 0x007ACB19 (26B), cleanup 0x007B6F7A
POOL_INIT( rva007ACB19, rva007B6F7A )
// ?rva007ACB43@Rva007AB800PoolInits@@SAXXZ @ 0x007ACB43 (26B), cleanup 0x007B6F84
POOL_INIT( rva007ACB43, rva007B6F84 )
// ?rva007ACB78@Rva007AB800PoolInits@@SAXXZ @ 0x007ACB78 (26B), cleanup 0x007B6FA2
POOL_INIT( rva007ACB78, rva007B6FA2 )
// ?rva007ACBA2@Rva007AB800PoolInits@@SAXXZ @ 0x007ACBA2 (26B), cleanup 0x007B6FAC
POOL_INIT( rva007ACBA2, rva007B6FAC )
// ?rva007AD00A@Rva007AB800PoolInits@@SAXXZ @ 0x007AD00A (26B), cleanup 0x007B751A
POOL_INIT( rva007AD00A, rva007B751A )
// ?rva007AD106@Rva007AB800PoolInits@@SAXXZ @ 0x007AD106 (26B), cleanup 0x007B7524
POOL_INIT( rva007AD106, rva007B7524 )
// ?rva007AD217@Rva007AB800PoolInits@@SAXXZ @ 0x007AD217 (26B), cleanup 0x007B752E
POOL_INIT( rva007AD217, rva007B752E )
// ?rva007AD256@Rva007AB800PoolInits@@SAXXZ @ 0x007AD256 (26B), cleanup 0x007B7538
POOL_INIT( rva007AD256, rva007B7538 )
// ?rva007AD304@Rva007AB800PoolInits@@SAXXZ @ 0x007AD304 (26B), cleanup 0x007B7542
POOL_INIT( rva007AD304, rva007B7542 )
// ?rva007AD362@Rva007AB800PoolInits@@SAXXZ @ 0x007AD362 (26B), cleanup 0x007B754C
POOL_INIT( rva007AD362, rva007B754C )
// ?rva007AD3E0@Rva007AB800PoolInits@@SAXXZ @ 0x007AD3E0 (26B), cleanup 0x007B7560
POOL_INIT( rva007AD3E0, rva007B7560 )
// ?rva007AD439@Rva007AB800PoolInits@@SAXXZ @ 0x007AD439 (26B), cleanup 0x007B756A
POOL_INIT( rva007AD439, rva007B756A )
// ?rva007AD4A2@Rva007AB800PoolInits@@SAXXZ @ 0x007AD4A2 (26B), cleanup 0x007B7574
POOL_INIT( rva007AD4A2, rva007B7574 )
// ?rva007AD4E1@Rva007AB800PoolInits@@SAXXZ @ 0x007AD4E1 (26B), cleanup 0x007B757E
POOL_INIT( rva007AD4E1, rva007B757E )
// ?rva007AD536@Rva007AB800PoolInits@@SAXXZ @ 0x007AD536 (26B), cleanup 0x007B7592
POOL_INIT( rva007AD536, rva007B7592 )
// ?rva007AD565@Rva007AB800PoolInits@@SAXXZ @ 0x007AD565 (26B), cleanup 0x007B75B0
POOL_INIT( rva007AD565, rva007B75B0 )
// ?rva007AD5C3@Rva007AB800PoolInits@@SAXXZ @ 0x007AD5C3 (26B), cleanup 0x007B75BA
POOL_INIT( rva007AD5C3, rva007B75BA )
// ?rva007AD5F2@Rva007AB800PoolInits@@SAXXZ @ 0x007AD5F2 (26B), cleanup 0x007B75CE
POOL_INIT( rva007AD5F2, rva007B75CE )
// ?rva007AD796@Rva007AB800PoolInits@@SAXXZ @ 0x007AD796 (26B), cleanup 0x007B75D8
POOL_INIT( rva007AD796, rva007B75D8 )
// ?rva007AD82B@Rva007AB800PoolInits@@SAXXZ @ 0x007AD82B (26B), cleanup 0x007B75EC
POOL_INIT( rva007AD82B, rva007B75EC )
// ?rva007AD8E0@Rva007AB800PoolInits@@SAXXZ @ 0x007AD8E0 (26B), cleanup 0x007B7600
POOL_INIT( rva007AD8E0, rva007B7600 )
// ?rva007AD90F@Rva007AB800PoolInits@@SAXXZ @ 0x007AD90F (26B), cleanup 0x007B7614
POOL_INIT( rva007AD90F, rva007B7614 )
// ?rva007AD963@Rva007AB800PoolInits@@SAXXZ @ 0x007AD963 (26B), cleanup 0x007B761E
POOL_INIT( rva007AD963, rva007B761E )
// ?rva007AD9A2@Rva007AB800PoolInits@@SAXXZ @ 0x007AD9A2 (26B), cleanup 0x007B7628
POOL_INIT( rva007AD9A2, rva007B7628 )
// ?rva007ADA61@Rva007AB800PoolInits@@SAXXZ @ 0x007ADA61 (26B), cleanup 0x007B7646
POOL_INIT( rva007ADA61, rva007B7646 )
// ?rva007ADAE7@Rva007AB800PoolInits@@SAXXZ @ 0x007ADAE7 (26B), cleanup 0x007B76D2
POOL_INIT( rva007ADAE7, rva007B76D2 )
// ?rva007ADB32@Rva007AB800PoolInits@@SAXXZ @ 0x007ADB32 (26B), cleanup 0x007B76F0
POOL_INIT( rva007ADB32, rva007B76F0 )
// ?rva007ADBA7@Rva007AB800PoolInits@@SAXXZ @ 0x007ADBA7 (26B), cleanup 0x007B7722
POOL_INIT( rva007ADBA7, rva007B7722 )
// ?rva007ADBE5@Rva007AB800PoolInits@@SAXXZ @ 0x007ADBE5 (26B), cleanup 0x007B772C
POOL_INIT( rva007ADBE5, rva007B772C )
// ?rva007ADC2E@Rva007AB800PoolInits@@SAXXZ @ 0x007ADC2E (26B), cleanup 0x007B774A
POOL_INIT( rva007ADC2E, rva007B774A )
// ?rva007ADC72@Rva007AB800PoolInits@@SAXXZ @ 0x007ADC72 (26B), cleanup 0x007B7754
POOL_INIT( rva007ADC72, rva007B7754 )
// ?rva007ADCDE@Rva007AB800PoolInits@@SAXXZ @ 0x007ADCDE (26B), cleanup 0x007B7772
POOL_INIT( rva007ADCDE, rva007B7772 )
// ?rva007ADD83@Rva007AB800PoolInits@@SAXXZ @ 0x007ADD83 (26B), cleanup 0x007B7790
POOL_INIT( rva007ADD83, rva007B7790 )
// ?rva007ADDAD@Rva007AB800PoolInits@@SAXXZ @ 0x007ADDAD (26B), cleanup 0x007B779A
POOL_INIT( rva007ADDAD, rva007B779A )
// ?rva007ADDDF@Rva007AB800PoolInits@@SAXXZ @ 0x007ADDDF (26B), cleanup 0x007B77A4
POOL_INIT( rva007ADDDF, rva007B77A4 )
// ?rva007ADE09@Rva007AB800PoolInits@@SAXXZ @ 0x007ADE09 (26B), cleanup 0x007B77AE
POOL_INIT( rva007ADE09, rva007B77AE )
// ?rva007ADE5E@Rva007AB800PoolInits@@SAXXZ @ 0x007ADE5E (26B), cleanup 0x007B77C3
POOL_INIT( rva007ADE5E, rva007B77C3 )
// ?rva007ADEB2@Rva007AB800PoolInits@@SAXXZ @ 0x007ADEB2 (26B), cleanup 0x007B77CE
POOL_INIT( rva007ADEB2, rva007B77CE )
// ?rva007ADEDC@Rva007AB800PoolInits@@SAXXZ @ 0x007ADEDC (26B), cleanup 0x007B77E2
POOL_INIT( rva007ADEDC, rva007B77E2 )
// ?rva007ADF6E@Rva007AB800PoolInits@@SAXXZ @ 0x007ADF6E (26B), cleanup 0x007B77FC
POOL_INIT( rva007ADF6E, rva007B77FC )
// ?rva007ADF98@Rva007AB800PoolInits@@SAXXZ @ 0x007ADF98 (26B), cleanup 0x007B7806
POOL_INIT( rva007ADF98, rva007B7806 )
// ?rva007AE019@Rva007AB800PoolInits@@SAXXZ @ 0x007AE019 (26B), cleanup 0x007B7838
POOL_INIT( rva007AE019, rva007B7838 )
// ?rva007AE06D@Rva007AB800PoolInits@@SAXXZ @ 0x007AE06D (26B), cleanup 0x007B7888
POOL_INIT( rva007AE06D, rva007B7888 )
// ?rva007AE0EC@Rva007AB800PoolInits@@SAXXZ @ 0x007AE0EC (26B), cleanup 0x007B78B0
POOL_INIT( rva007AE0EC, rva007B78B0 )
// ?rva007AE106@Rva007AB800PoolInits@@SAXXZ @ 0x007AE106 (26B), cleanup 0x007B78CE
POOL_INIT( rva007AE106, rva007B78CE )
// ?rva007AE130@Rva007AB800PoolInits@@SAXXZ @ 0x007AE130 (26B), cleanup 0x007B78D8
POOL_INIT( rva007AE130, rva007B78D8 )
// ?rva007AE184@Rva007AB800PoolInits@@SAXXZ @ 0x007AE184 (26B), cleanup 0x007B78E2
POOL_INIT( rva007AE184, rva007B78E2 )
// ?rva007AE1C8@Rva007AB800PoolInits@@SAXXZ @ 0x007AE1C8 (26B), cleanup 0x007B78F6
POOL_INIT( rva007AE1C8, rva007B78F6 )
// ?rva007AE20C@Rva007AB800PoolInits@@SAXXZ @ 0x007AE20C (26B), cleanup 0x007B790A
POOL_INIT( rva007AE20C, rva007B790A )
// ?rva007AE226@Rva007AB800PoolInits@@SAXXZ @ 0x007AE226 (26B), cleanup 0x007B7914
POOL_INIT( rva007AE226, rva007B7914 )
// ?rva007AE250@Rva007AB800PoolInits@@SAXXZ @ 0x007AE250 (26B), cleanup 0x007B791E
POOL_INIT( rva007AE250, rva007B791E )
// ?rva007AE28A@Rva007AB800PoolInits@@SAXXZ @ 0x007AE28A (26B), cleanup 0x007B7928
POOL_INIT( rva007AE28A, rva007B7928 )
// ?rva007AE2A4@Rva007AB800PoolInits@@SAXXZ @ 0x007AE2A4 (26B), cleanup 0x007B7932
POOL_INIT( rva007AE2A4, rva007B7932 )
// ?rva007AE2DE@Rva007AB800PoolInits@@SAXXZ @ 0x007AE2DE (26B), cleanup 0x007B793C
POOL_INIT( rva007AE2DE, rva007B793C )
// ?rva007AE308@Rva007AB800PoolInits@@SAXXZ @ 0x007AE308 (26B), cleanup 0x007B7946
POOL_INIT( rva007AE308, rva007B7946 )
// ?rva007AE322@Rva007AB800PoolInits@@SAXXZ @ 0x007AE322 (26B), cleanup 0x007B7950
POOL_INIT( rva007AE322, rva007B7950 )
// ?rva007AE34C@Rva007AB800PoolInits@@SAXXZ @ 0x007AE34C (26B), cleanup 0x007B795A
POOL_INIT( rva007AE34C, rva007B795A )
// ?rva007AE376@Rva007AB800PoolInits@@SAXXZ @ 0x007AE376 (26B), cleanup 0x007B7964
POOL_INIT( rva007AE376, rva007B7964 )
// ?rva007AE3C7@Rva007AB800PoolInits@@SAXXZ @ 0x007AE3C7 (26B), cleanup 0x007B79C9
POOL_INIT( rva007AE3C7, rva007B79C9 )
// ?rva007AE3F1@Rva007AB800PoolInits@@SAXXZ @ 0x007AE3F1 (26B), cleanup 0x007B79D3
POOL_INIT( rva007AE3F1, rva007B79D3 )
// ?rva007AE41B@Rva007AB800PoolInits@@SAXXZ @ 0x007AE41B (26B), cleanup 0x007B79DD
POOL_INIT( rva007AE41B, rva007B79DD )
// ?rva007AE445@Rva007AB800PoolInits@@SAXXZ @ 0x007AE445 (26B), cleanup 0x007B79E7
POOL_INIT( rva007AE445, rva007B79E7 )
// ?rva007AE46F@Rva007AB800PoolInits@@SAXXZ @ 0x007AE46F (26B), cleanup 0x007B79F1
POOL_INIT( rva007AE46F, rva007B79F1 )
// ?rva007AE4C3@Rva007AB800PoolInits@@SAXXZ @ 0x007AE4C3 (26B), cleanup 0x007B7A0F
POOL_INIT( rva007AE4C3, rva007B7A0F )
// ?rva007AE503@Rva007AB800PoolInits@@SAXXZ @ 0x007AE503 (26B), cleanup 0x007B7A23
POOL_INIT( rva007AE503, rva007B7A23 )
// ?rva007AE561@Rva007AB800PoolInits@@SAXXZ @ 0x007AE561 (26B), cleanup 0x007B7A2D
POOL_INIT( rva007AE561, rva007B7A2D )
// ?rva007AE57B@Rva007AB800PoolInits@@SAXXZ @ 0x007AE57B (26B), cleanup 0x007B7A4B
POOL_INIT( rva007AE57B, rva007B7A4B )
// ?rva007AE62A@Rva007AB800PoolInits@@SAXXZ @ 0x007AE62A (26B), cleanup 0x007B7A73
POOL_INIT( rva007AE62A, rva007B7A73 )
// ?rva007AE654@Rva007AB800PoolInits@@SAXXZ @ 0x007AE654 (26B), cleanup 0x007B7AAF
POOL_INIT( rva007AE654, rva007B7AAF )
// ?rva007AE67E@Rva007AB800PoolInits@@SAXXZ @ 0x007AE67E (26B), cleanup 0x007B7AB9
POOL_INIT( rva007AE67E, rva007B7AB9 )
// ?rva007AE6A8@Rva007AB800PoolInits@@SAXXZ @ 0x007AE6A8 (26B), cleanup 0x007B7AC3
POOL_INIT( rva007AE6A8, rva007B7AC3 )
// ?rva007AE784@Rva007AB800PoolInits@@SAXXZ @ 0x007AE784 (26B), cleanup 0x007B7AEB
POOL_INIT( rva007AE784, rva007B7AEB )
// ?rva007AE81E@Rva007AB800PoolInits@@SAXXZ @ 0x007AE81E (26B), cleanup 0x007B7B1E
POOL_INIT( rva007AE81E, rva007B7B1E )
// ?rva007AE848@Rva007AB800PoolInits@@SAXXZ @ 0x007AE848 (26B), cleanup 0x007B7B32
POOL_INIT( rva007AE848, rva007B7B32 )
// ?rva007AE87C@Rva007AB800PoolInits@@SAXXZ @ 0x007AE87C (26B), cleanup 0x007B7B3C
POOL_INIT( rva007AE87C, rva007B7B3C )
// ?rva007AE896@Rva007AB800PoolInits@@SAXXZ @ 0x007AE896 (26B), cleanup 0x007B7B46
POOL_INIT( rva007AE896, rva007B7B46 )
// ?rva007AE91D@Rva007AB800PoolInits@@SAXXZ @ 0x007AE91D (26B), cleanup 0x007B7B78
POOL_INIT( rva007AE91D, rva007B7B78 )
// ?rva007AE988@Rva007AB800PoolInits@@SAXXZ @ 0x007AE988 (26B), cleanup 0x007B7B96
POOL_INIT( rva007AE988, rva007B7B96 )
// ?rva007AE9B2@Rva007AB800PoolInits@@SAXXZ @ 0x007AE9B2 (26B), cleanup 0x007B7BA0
POOL_INIT( rva007AE9B2, rva007B7BA0 )
// ?rva007AE9CC@Rva007AB800PoolInits@@SAXXZ @ 0x007AE9CC (26B), cleanup 0x007B7BAA
POOL_INIT( rva007AE9CC, rva007B7BAA )
// ?rva007AEA02@Rva007AB800PoolInits@@SAXXZ @ 0x007AEA02 (26B), cleanup 0x007B7BB4
POOL_INIT( rva007AEA02, rva007B7BB4 )
// ?rva007AEA50@Rva007AB800PoolInits@@SAXXZ @ 0x007AEA50 (26B), cleanup 0x007B7BD2
POOL_INIT( rva007AEA50, rva007B7BD2 )
// ?rva007AEA6A@Rva007AB800PoolInits@@SAXXZ @ 0x007AEA6A (26B), cleanup 0x007B7BDC
POOL_INIT( rva007AEA6A, rva007B7BDC )
// ?rva007AEA94@Rva007AB800PoolInits@@SAXXZ @ 0x007AEA94 (26B), cleanup 0x007B7BE6
POOL_INIT( rva007AEA94, rva007B7BE6 )
// ?rva007AEABE@Rva007AB800PoolInits@@SAXXZ @ 0x007AEABE (26B), cleanup 0x007B7BF0
POOL_INIT( rva007AEABE, rva007B7BF0 )
// ?rva007AEAD8@Rva007AB800PoolInits@@SAXXZ @ 0x007AEAD8 (26B), cleanup 0x007B7BFA
POOL_INIT( rva007AEAD8, rva007B7BFA )
// ?rva007AEB02@Rva007AB800PoolInits@@SAXXZ @ 0x007AEB02 (26B), cleanup 0x007B7C0E
POOL_INIT( rva007AEB02, rva007B7C0E )
// ?rva007AEB2C@Rva007AB800PoolInits@@SAXXZ @ 0x007AEB2C (26B), cleanup 0x007B7C18
POOL_INIT( rva007AEB2C, rva007B7C18 )
// ?rva007AEB56@Rva007AB800PoolInits@@SAXXZ @ 0x007AEB56 (26B), cleanup 0x007B7C22
POOL_INIT( rva007AEB56, rva007B7C22 )
// ?rva007AEB80@Rva007AB800PoolInits@@SAXXZ @ 0x007AEB80 (26B), cleanup 0x007B7C2C
POOL_INIT( rva007AEB80, rva007B7C2C )
// ?rva007AEBE6@Rva007AB800PoolInits@@SAXXZ @ 0x007AEBE6 (26B), cleanup 0x007B7C36
POOL_INIT( rva007AEBE6, rva007B7C36 )
// ?rva007AEC00@Rva007AB800PoolInits@@SAXXZ @ 0x007AEC00 (26B), cleanup 0x007B7C4A
POOL_INIT( rva007AEC00, rva007B7C4A )
// ?rva007AEC2A@Rva007AB800PoolInits@@SAXXZ @ 0x007AEC2A (26B), cleanup 0x007B7C54
POOL_INIT( rva007AEC2A, rva007B7C54 )
// ?rva007AEC44@Rva007AB800PoolInits@@SAXXZ @ 0x007AEC44 (26B), cleanup 0x007B7C5E
POOL_INIT( rva007AEC44, rva007B7C5E )
// ?rva007AEC5E@Rva007AB800PoolInits@@SAXXZ @ 0x007AEC5E (26B), cleanup 0x007B7C68
POOL_INIT( rva007AEC5E, rva007B7C68 )
// ?rva007AECD6@Rva007AB800PoolInits@@SAXXZ @ 0x007AECD6 (26B), cleanup 0x007B7C91
POOL_INIT( rva007AECD6, rva007B7C91 )
// ?rva007AED00@Rva007AB800PoolInits@@SAXXZ @ 0x007AED00 (26B), cleanup 0x007B7C9B
POOL_INIT( rva007AED00, rva007B7C9B )
// ?rva007AED47@Rva007AB800PoolInits@@SAXXZ @ 0x007AED47 (26B), cleanup 0x007B7CA5
POOL_INIT( rva007AED47, rva007B7CA5 )
// ?rva007AED87@Rva007AB800PoolInits@@SAXXZ @ 0x007AED87 (26B), cleanup 0x007B7CB9
POOL_INIT( rva007AED87, rva007B7CB9 )
// ?rva007AEDB1@Rva007AB800PoolInits@@SAXXZ @ 0x007AEDB1 (26B), cleanup 0x007B7CCD
POOL_INIT( rva007AEDB1, rva007B7CCD )
// ?rva007AEE41@Rva007AB800PoolInits@@SAXXZ @ 0x007AEE41 (26B), cleanup 0x007B7CE1
POOL_INIT( rva007AEE41, rva007B7CE1 )
// ?rva007AEE95@Rva007AB800PoolInits@@SAXXZ @ 0x007AEE95 (26B), cleanup 0x007B7CEB
POOL_INIT( rva007AEE95, rva007B7CEB )
// ?rva007AEEBF@Rva007AB800PoolInits@@SAXXZ @ 0x007AEEBF (26B), cleanup 0x007B7CFF
POOL_INIT( rva007AEEBF, rva007B7CFF )
// ?rva007AEEE9@Rva007AB800PoolInits@@SAXXZ @ 0x007AEEE9 (26B), cleanup 0x007B7D09
POOL_INIT( rva007AEEE9, rva007B7D09 )
// ?rva007AEF5D@Rva007AB800PoolInits@@SAXXZ @ 0x007AEF5D (26B), cleanup 0x007B7D13
POOL_INIT( rva007AEF5D, rva007B7D13 )
// ?rva007AEF87@Rva007AB800PoolInits@@SAXXZ @ 0x007AEF87 (26B), cleanup 0x007B7D1D
POOL_INIT( rva007AEF87, rva007B7D1D )
// ?rva007AEFCB@Rva007AB800PoolInits@@SAXXZ @ 0x007AEFCB (26B), cleanup 0x007B7D4F
POOL_INIT( rva007AEFCB, rva007B7D4F )
// ?rva007AEFF5@Rva007AB800PoolInits@@SAXXZ @ 0x007AEFF5 (26B), cleanup 0x007B7D63
POOL_INIT( rva007AEFF5, rva007B7D63 )
// ?rva007AF01F@Rva007AB800PoolInits@@SAXXZ @ 0x007AF01F (26B), cleanup 0x007B7D6D
POOL_INIT( rva007AF01F, rva007B7D6D )
// ?rva007AF049@Rva007AB800PoolInits@@SAXXZ @ 0x007AF049 (26B), cleanup 0x007B7D8B
POOL_INIT( rva007AF049, rva007B7D8B )
// ?rva007AF0BD@Rva007AB800PoolInits@@SAXXZ @ 0x007AF0BD (26B), cleanup 0x007B7D9F
POOL_INIT( rva007AF0BD, rva007B7D9F )
// ?rva007AF0D7@Rva007AB800PoolInits@@SAXXZ @ 0x007AF0D7 (26B), cleanup 0x007B7DA9
POOL_INIT( rva007AF0D7, rva007B7DA9 )
// ?rva007AF146@Rva007AB800PoolInits@@SAXXZ @ 0x007AF146 (26B), cleanup 0x007B7DBD
POOL_INIT( rva007AF146, rva007B7DBD )
// ?rva007AF170@Rva007AB800PoolInits@@SAXXZ @ 0x007AF170 (26B), cleanup 0x007B7DE5
POOL_INIT( rva007AF170, rva007B7DE5 )
// ?rva007AF19A@Rva007AB800PoolInits@@SAXXZ @ 0x007AF19A (26B), cleanup 0x007B7DEF
POOL_INIT( rva007AF19A, rva007B7DEF )
// ?rva007AF1B4@Rva007AB800PoolInits@@SAXXZ @ 0x007AF1B4 (26B), cleanup 0x007B7DF9
POOL_INIT( rva007AF1B4, rva007B7DF9 )
// ?rva007AF22A@Rva007AB800PoolInits@@SAXXZ @ 0x007AF22A (26B), cleanup 0x007B7E03
POOL_INIT( rva007AF22A, rva007B7E03 )
// ?rva007AF26E@Rva007AB800PoolInits@@SAXXZ @ 0x007AF26E (26B), cleanup 0x007B7E17
POOL_INIT( rva007AF26E, rva007B7E17 )
// ?rva007AF298@Rva007AB800PoolInits@@SAXXZ @ 0x007AF298 (26B), cleanup 0x007B7E2B
POOL_INIT( rva007AF298, rva007B7E2B )
// ?rva007AF30A@Rva007AB800PoolInits@@SAXXZ @ 0x007AF30A (26B), cleanup 0x007B7E35
POOL_INIT( rva007AF30A, rva007B7E35 )
// ?rva007AF34F@Rva007AB800PoolInits@@SAXXZ @ 0x007AF34F (26B), cleanup 0x007B7E53
POOL_INIT( rva007AF34F, rva007B7E53 )
// ?rva007AF379@Rva007AB800PoolInits@@SAXXZ @ 0x007AF379 (26B), cleanup 0x007B7E5D
POOL_INIT( rva007AF379, rva007B7E5D )
// ?rva007AF3A3@Rva007AB800PoolInits@@SAXXZ @ 0x007AF3A3 (26B), cleanup 0x007B7E67
POOL_INIT( rva007AF3A3, rva007B7E67 )
// ?rva007AF3BD@Rva007AB800PoolInits@@SAXXZ @ 0x007AF3BD (26B), cleanup 0x007B7E71
POOL_INIT( rva007AF3BD, rva007B7E71 )
// ?rva007AF431@Rva007AB800PoolInits@@SAXXZ @ 0x007AF431 (26B), cleanup 0x007B7E7B
POOL_INIT( rva007AF431, rva007B7E7B )
// ?rva007AF45B@Rva007AB800PoolInits@@SAXXZ @ 0x007AF45B (26B), cleanup 0x007B7E85
POOL_INIT( rva007AF45B, rva007B7E85 )
// ?rva007AF75B@Rva007AB800PoolInits@@SAXXZ @ 0x007AF75B (26B), cleanup 0x007B806F
POOL_INIT( rva007AF75B, rva007B806F )
// ?rva007AF775@Rva007AB800PoolInits@@SAXXZ @ 0x007AF775 (26B), cleanup 0x007B8079
POOL_INIT( rva007AF775, rva007B8079 )
// ?rva007AF78F@Rva007AB800PoolInits@@SAXXZ @ 0x007AF78F (26B), cleanup 0x007B8083
POOL_INIT( rva007AF78F, rva007B8083 )
// ?rva007AF7A9@Rva007AB800PoolInits@@SAXXZ @ 0x007AF7A9 (26B), cleanup 0x007B808D
POOL_INIT( rva007AF7A9, rva007B808D )
// ?rva007AF7C3@Rva007AB800PoolInits@@SAXXZ @ 0x007AF7C3 (26B), cleanup 0x007B8097
POOL_INIT( rva007AF7C3, rva007B8097 )
// ?rva007AF819@Rva007AB800PoolInits@@SAXXZ @ 0x007AF819 (26B), cleanup 0x007B80AB
POOL_INIT( rva007AF819, rva007B80AB )
// ?rva007AF86F@Rva007AB800PoolInits@@SAXXZ @ 0x007AF86F (26B), cleanup 0x007B80D3
POOL_INIT( rva007AF86F, rva007B80D3 )
// ?rva007AF899@Rva007AB800PoolInits@@SAXXZ @ 0x007AF899 (26B), cleanup 0x007B80DD
POOL_INIT( rva007AF899, rva007B80DD )
// ?rva007AF8B3@Rva007AB800PoolInits@@SAXXZ @ 0x007AF8B3 (26B), cleanup 0x007B80E7
POOL_INIT( rva007AF8B3, rva007B80E7 )
// ?rva007AFC3C@Rva007AB800PoolInits@@SAXXZ @ 0x007AFC3C (26B), cleanup 0x007B815F
POOL_INIT( rva007AFC3C, rva007B815F )
// ?rva007AFCC9@Rva007AB800PoolInits@@SAXXZ @ 0x007AFCC9 (26B), cleanup 0x007B816B
POOL_INIT( rva007AFCC9, rva007B816B )
// ?rva007AFD08@Rva007AB800PoolInits@@SAXXZ @ 0x007AFD08 (26B), cleanup 0x007B819D
POOL_INIT( rva007AFD08, rva007B819D )
// ?rva007AFD32@Rva007AB800PoolInits@@SAXXZ @ 0x007AFD32 (26B), cleanup 0x007B81A7
POOL_INIT( rva007AFD32, rva007B81A7 )
// ?rva007AFD86@Rva007AB800PoolInits@@SAXXZ @ 0x007AFD86 (26B), cleanup 0x007B81B1
POOL_INIT( rva007AFD86, rva007B81B1 )
// ?rva007AFDB0@Rva007AB800PoolInits@@SAXXZ @ 0x007AFDB0 (26B), cleanup 0x007B81BB
POOL_INIT( rva007AFDB0, rva007B81BB )
// ?rva007AFDDA@Rva007AB800PoolInits@@SAXXZ @ 0x007AFDDA (26B), cleanup 0x007B81C5
POOL_INIT( rva007AFDDA, rva007B81C5 )
// ?rva007AFE04@Rva007AB800PoolInits@@SAXXZ @ 0x007AFE04 (26B), cleanup 0x007B81CF
POOL_INIT( rva007AFE04, rva007B81CF )
// ?rva007AFE43@Rva007AB800PoolInits@@SAXXZ @ 0x007AFE43 (26B), cleanup 0x007B81D9
POOL_INIT( rva007AFE43, rva007B81D9 )
// ?rva007AFE6D@Rva007AB800PoolInits@@SAXXZ @ 0x007AFE6D (26B), cleanup 0x007B81E3
POOL_INIT( rva007AFE6D, rva007B81E3 )
// ?rva007AFEC6@Rva007AB800PoolInits@@SAXXZ @ 0x007AFEC6 (26B), cleanup 0x007B81ED
POOL_INIT( rva007AFEC6, rva007B81ED )
// ?rva007AFEF0@Rva007AB800PoolInits@@SAXXZ @ 0x007AFEF0 (26B), cleanup 0x007B820B
POOL_INIT( rva007AFEF0, rva007B820B )
// ?rva007AFF88@Rva007AB800PoolInits@@SAXXZ @ 0x007AFF88 (26B), cleanup 0x007B8215
POOL_INIT( rva007AFF88, rva007B8215 )
// ?rva007AFFA2@Rva007AB800PoolInits@@SAXXZ @ 0x007AFFA2 (26B), cleanup 0x007B8251
POOL_INIT( rva007AFFA2, rva007B8251 )
// ?rva007B0025@Rva007AB800PoolInits@@SAXXZ @ 0x007B0025 (26B), cleanup 0x007B825B
POOL_INIT( rva007B0025, rva007B825B )
// ?rva007B0054@Rva007AB800PoolInits@@SAXXZ @ 0x007B0054 (26B), cleanup 0x007B826F
POOL_INIT( rva007B0054, rva007B826F )
// ?rva007B006E@Rva007AB800PoolInits@@SAXXZ @ 0x007B006E (26B), cleanup 0x007B8279
POOL_INIT( rva007B006E, rva007B8279 )
// ?rva007B0125@Rva007AB800PoolInits@@SAXXZ @ 0x007B0125 (26B), cleanup 0x007B828D
POOL_INIT( rva007B0125, rva007B828D )
// ?rva007B01B9@Rva007AB800PoolInits@@SAXXZ @ 0x007B01B9 (26B), cleanup 0x007B8297
POOL_INIT( rva007B01B9, rva007B8297 )
// ?rva007B0212@Rva007AB800PoolInits@@SAXXZ @ 0x007B0212 (26B), cleanup 0x007B82A1
POOL_INIT( rva007B0212, rva007B82A1 )
// ?rva007B0251@Rva007AB800PoolInits@@SAXXZ @ 0x007B0251 (26B), cleanup 0x007B82AB
POOL_INIT( rva007B0251, rva007B82AB )
// ?rva007B0325@Rva007AB800PoolInits@@SAXXZ @ 0x007B0325 (26B), cleanup 0x007B82B5
POOL_INIT( rva007B0325, rva007B82B5 )
// ?rva007B0369@Rva007AB800PoolInits@@SAXXZ @ 0x007B0369 (26B), cleanup 0x007B82F1
POOL_INIT( rva007B0369, rva007B82F1 )
// ?rva007B0398@Rva007AB800PoolInits@@SAXXZ @ 0x007B0398 (26B), cleanup 0x007B82FB
POOL_INIT( rva007B0398, rva007B82FB )
// ?rva007B03D7@Rva007AB800PoolInits@@SAXXZ @ 0x007B03D7 (26B), cleanup 0x007B8305
POOL_INIT( rva007B03D7, rva007B8305 )
// ?rva007B0401@Rva007AB800PoolInits@@SAXXZ @ 0x007B0401 (26B), cleanup 0x007B830F
POOL_INIT( rva007B0401, rva007B830F )
// ?rva007B0455@Rva007AB800PoolInits@@SAXXZ @ 0x007B0455 (26B), cleanup 0x007B8319
POOL_INIT( rva007B0455, rva007B8319 )
// ?rva007B046F@Rva007AB800PoolInits@@SAXXZ @ 0x007B046F (26B), cleanup 0x007B832D
POOL_INIT( rva007B046F, rva007B832D )
// ?rva007B0499@Rva007AB800PoolInits@@SAXXZ @ 0x007B0499 (26B), cleanup 0x007B8337
POOL_INIT( rva007B0499, rva007B8337 )
// ?rva007B04DD@Rva007AB800PoolInits@@SAXXZ @ 0x007B04DD (26B), cleanup 0x007B8341
POOL_INIT( rva007B04DD, rva007B8341 )
// ?rva007B0507@Rva007AB800PoolInits@@SAXXZ @ 0x007B0507 (26B), cleanup 0x007B8355
POOL_INIT( rva007B0507, rva007B8355 )
// ?rva007B0531@Rva007AB800PoolInits@@SAXXZ @ 0x007B0531 (26B), cleanup 0x007B835F
POOL_INIT( rva007B0531, rva007B835F )
// ?rva007B0575@Rva007AB800PoolInits@@SAXXZ @ 0x007B0575 (26B), cleanup 0x007B8373
POOL_INIT( rva007B0575, rva007B8373 )
// ?rva007B05B4@Rva007AB800PoolInits@@SAXXZ @ 0x007B05B4 (26B), cleanup 0x007B8387
POOL_INIT( rva007B05B4, rva007B8387 )
// ?rva007B05FB@Rva007AB800PoolInits@@SAXXZ @ 0x007B05FB (26B), cleanup 0x007B8391
POOL_INIT( rva007B05FB, rva007B8391 )
// ?rva007B0651@Rva007AB800PoolInits@@SAXXZ @ 0x007B0651 (26B), cleanup 0x007B83AF
POOL_INIT( rva007B0651, rva007B83AF )
// ?rva007B066B@Rva007AB800PoolInits@@SAXXZ @ 0x007B066B (26B), cleanup 0x007B83C3
POOL_INIT( rva007B066B, rva007B83C3 )
// ?rva007B0695@Rva007AB800PoolInits@@SAXXZ @ 0x007B0695 (26B), cleanup 0x007B83CD
POOL_INIT( rva007B0695, rva007B83CD )
// ?rva007B06BF@Rva007AB800PoolInits@@SAXXZ @ 0x007B06BF (26B), cleanup 0x007B83D7
POOL_INIT( rva007B06BF, rva007B83D7 )
// ?rva007B06D9@Rva007AB800PoolInits@@SAXXZ @ 0x007B06D9 (26B), cleanup 0x007B8413
POOL_INIT( rva007B06D9, rva007B8413 )
// ?rva007B0703@Rva007AB800PoolInits@@SAXXZ @ 0x007B0703 (26B), cleanup 0x007B841D
POOL_INIT( rva007B0703, rva007B841D )
// ?rva007B072D@Rva007AB800PoolInits@@SAXXZ @ 0x007B072D (26B), cleanup 0x007B8427
POOL_INIT( rva007B072D, rva007B8427 )
// ?rva007B0771@Rva007AB800PoolInits@@SAXXZ @ 0x007B0771 (26B), cleanup 0x007B8431
POOL_INIT( rva007B0771, rva007B8431 )
// ?rva007B081A@Rva007AB800PoolInits@@SAXXZ @ 0x007B081A (26B), cleanup 0x007B8445
POOL_INIT( rva007B081A, rva007B8445 )
// ?rva007B085E@Rva007AB800PoolInits@@SAXXZ @ 0x007B085E (26B), cleanup 0x007B8459
POOL_INIT( rva007B085E, rva007B8459 )
// ?rva007B0888@Rva007AB800PoolInits@@SAXXZ @ 0x007B0888 (26B), cleanup 0x007B846D
POOL_INIT( rva007B0888, rva007B846D )
// ?rva007B08DC@Rva007AB800PoolInits@@SAXXZ @ 0x007B08DC (26B), cleanup 0x007B8477
POOL_INIT( rva007B08DC, rva007B8477 )
// ?rva007B0906@Rva007AB800PoolInits@@SAXXZ @ 0x007B0906 (26B), cleanup 0x007B848B
POOL_INIT( rva007B0906, rva007B848B )
// ?rva007B0930@Rva007AB800PoolInits@@SAXXZ @ 0x007B0930 (26B), cleanup 0x007B8495
POOL_INIT( rva007B0930, rva007B8495 )
// ?rva007B095A@Rva007AB800PoolInits@@SAXXZ @ 0x007B095A (26B), cleanup 0x007B849F
POOL_INIT( rva007B095A, rva007B849F )
// ?rva007B0974@Rva007AB800PoolInits@@SAXXZ @ 0x007B0974 (26B), cleanup 0x007B84A9
POOL_INIT( rva007B0974, rva007B84A9 )
// ?rva007B098E@Rva007AB800PoolInits@@SAXXZ @ 0x007B098E (26B), cleanup 0x007B84B3
POOL_INIT( rva007B098E, rva007B84B3 )
// ?rva007B09B8@Rva007AB800PoolInits@@SAXXZ @ 0x007B09B8 (26B), cleanup 0x007B84BD
POOL_INIT( rva007B09B8, rva007B84BD )
// ?rva007B09D2@Rva007AB800PoolInits@@SAXXZ @ 0x007B09D2 (26B), cleanup 0x007B84C7
POOL_INIT( rva007B09D2, rva007B84C7 )
// ?rva007B09FC@Rva007AB800PoolInits@@SAXXZ @ 0x007B09FC (26B), cleanup 0x007B84D1
POOL_INIT( rva007B09FC, rva007B84D1 )
// ?rva007B0A26@Rva007AB800PoolInits@@SAXXZ @ 0x007B0A26 (26B), cleanup 0x007B84DB
POOL_INIT( rva007B0A26, rva007B84DB )
// ?rva007B0A50@Rva007AB800PoolInits@@SAXXZ @ 0x007B0A50 (26B), cleanup 0x007B84E5
POOL_INIT( rva007B0A50, rva007B84E5 )
// ?rva007B0ADE@Rva007AB800PoolInits@@SAXXZ @ 0x007B0ADE (26B), cleanup 0x007B84EF
POOL_INIT( rva007B0ADE, rva007B84EF )
// ?rva007B0AF8@Rva007AB800PoolInits@@SAXXZ @ 0x007B0AF8 (26B), cleanup 0x007B8503
POOL_INIT( rva007B0AF8, rva007B8503 )
// ?rva007B0B22@Rva007AB800PoolInits@@SAXXZ @ 0x007B0B22 (26B), cleanup 0x007B850D
POOL_INIT( rva007B0B22, rva007B850D )
// ?rva007B0B4C@Rva007AB800PoolInits@@SAXXZ @ 0x007B0B4C (26B), cleanup 0x007B8517
POOL_INIT( rva007B0B4C, rva007B8517 )
// ?rva007B0B76@Rva007AB800PoolInits@@SAXXZ @ 0x007B0B76 (26B), cleanup 0x007B8521
POOL_INIT( rva007B0B76, rva007B8521 )
// ?rva007B0BB1@Rva007AB800PoolInits@@SAXXZ @ 0x007B0BB1 (26B), cleanup 0x007B852B
POOL_INIT( rva007B0BB1, rva007B852B )
// ?rva007B0BCB@Rva007AB800PoolInits@@SAXXZ @ 0x007B0BCB (26B), cleanup 0x007B8535
POOL_INIT( rva007B0BCB, rva007B8535 )
// ?rva007B0BE5@Rva007AB800PoolInits@@SAXXZ @ 0x007B0BE5 (26B), cleanup 0x007B853F
POOL_INIT( rva007B0BE5, rva007B853F )
// ?rva007B0C1F@Rva007AB800PoolInits@@SAXXZ @ 0x007B0C1F (26B), cleanup 0x007B8549
POOL_INIT( rva007B0C1F, rva007B8549 )
// ?rva007B0C39@Rva007AB800PoolInits@@SAXXZ @ 0x007B0C39 (26B), cleanup 0x007B8553
POOL_INIT( rva007B0C39, rva007B8553 )
// ?rva007B0C63@Rva007AB800PoolInits@@SAXXZ @ 0x007B0C63 (26B), cleanup 0x007B855D
POOL_INIT( rva007B0C63, rva007B855D )
// ?rva007B0C8D@Rva007AB800PoolInits@@SAXXZ @ 0x007B0C8D (26B), cleanup 0x007B8567
POOL_INIT( rva007B0C8D, rva007B8567 )
// ?rva007B0D11@Rva007AB800PoolInits@@SAXXZ @ 0x007B0D11 (26B), cleanup 0x007B8571
POOL_INIT( rva007B0D11, rva007B8571 )
// ?rva007B0D2B@Rva007AB800PoolInits@@SAXXZ @ 0x007B0D2B (26B), cleanup 0x007B857B
POOL_INIT( rva007B0D2B, rva007B857B )
// ?rva007B0D72@Rva007AB800PoolInits@@SAXXZ @ 0x007B0D72 (26B), cleanup 0x007B8586
POOL_INIT( rva007B0D72, rva007B8586 )
// ?rva007B0D9C@Rva007AB800PoolInits@@SAXXZ @ 0x007B0D9C (26B), cleanup 0x007B859A
POOL_INIT( rva007B0D9C, rva007B859A )
// ?rva007B0DC6@Rva007AB800PoolInits@@SAXXZ @ 0x007B0DC6 (26B), cleanup 0x007B85A4
POOL_INIT( rva007B0DC6, rva007B85A4 )
// ?rva007B0E0A@Rva007AB800PoolInits@@SAXXZ @ 0x007B0E0A (26B), cleanup 0x007B85AE
POOL_INIT( rva007B0E0A, rva007B85AE )
// ?rva007B0E34@Rva007AB800PoolInits@@SAXXZ @ 0x007B0E34 (26B), cleanup 0x007B85C2
POOL_INIT( rva007B0E34, rva007B85C2 )
// ?rva007B0E5E@Rva007AB800PoolInits@@SAXXZ @ 0x007B0E5E (26B), cleanup 0x007B85CC
POOL_INIT( rva007B0E5E, rva007B85CC )
// ?rva007B0E88@Rva007AB800PoolInits@@SAXXZ @ 0x007B0E88 (26B), cleanup 0x007B85D6
POOL_INIT( rva007B0E88, rva007B85D6 )
// ?rva007B0EB2@Rva007AB800PoolInits@@SAXXZ @ 0x007B0EB2 (26B), cleanup 0x007B85E3
POOL_INIT( rva007B0EB2, rva007B85E3 )
// ?rva007B0EDC@Rva007AB800PoolInits@@SAXXZ @ 0x007B0EDC (26B), cleanup 0x007B85ED
POOL_INIT( rva007B0EDC, rva007B85ED )
// ?rva007B0F06@Rva007AB800PoolInits@@SAXXZ @ 0x007B0F06 (26B), cleanup 0x007B85F7
POOL_INIT( rva007B0F06, rva007B85F7 )
// ?rva007B0F30@Rva007AB800PoolInits@@SAXXZ @ 0x007B0F30 (26B), cleanup 0x007B8601
POOL_INIT( rva007B0F30, rva007B8601 )
// ?rva007B0F5A@Rva007AB800PoolInits@@SAXXZ @ 0x007B0F5A (26B), cleanup 0x007B860B
POOL_INIT( rva007B0F5A, rva007B860B )
// ?rva007B0F84@Rva007AB800PoolInits@@SAXXZ @ 0x007B0F84 (26B), cleanup 0x007B8615
POOL_INIT( rva007B0F84, rva007B8615 )
// ?rva007B0F9E@Rva007AB800PoolInits@@SAXXZ @ 0x007B0F9E (26B), cleanup 0x007B861F
POOL_INIT( rva007B0F9E, rva007B861F )
// ?rva007B0FC8@Rva007AB800PoolInits@@SAXXZ @ 0x007B0FC8 (26B), cleanup 0x007B8629
POOL_INIT( rva007B0FC8, rva007B8629 )
// ?rva007B0FE2@Rva007AB800PoolInits@@SAXXZ @ 0x007B0FE2 (26B), cleanup 0x007B8633
POOL_INIT( rva007B0FE2, rva007B8633 )
// ?rva007B100C@Rva007AB800PoolInits@@SAXXZ @ 0x007B100C (26B), cleanup 0x007B863D
POOL_INIT( rva007B100C, rva007B863D )
// ?rva007B1036@Rva007AB800PoolInits@@SAXXZ @ 0x007B1036 (26B), cleanup 0x007B8647
POOL_INIT( rva007B1036, rva007B8647 )
// ?rva007B1060@Rva007AB800PoolInits@@SAXXZ @ 0x007B1060 (26B), cleanup 0x007B8651
POOL_INIT( rva007B1060, rva007B8651 )
// ?rva007B107A@Rva007AB800PoolInits@@SAXXZ @ 0x007B107A (26B), cleanup 0x007B865B
POOL_INIT( rva007B107A, rva007B865B )
// ?rva007B10A4@Rva007AB800PoolInits@@SAXXZ @ 0x007B10A4 (26B), cleanup 0x007B8665
POOL_INIT( rva007B10A4, rva007B8665 )
// ?rva007B10CE@Rva007AB800PoolInits@@SAXXZ @ 0x007B10CE (26B), cleanup 0x007B866F
POOL_INIT( rva007B10CE, rva007B866F )
// ?rva007B10F8@Rva007AB800PoolInits@@SAXXZ @ 0x007B10F8 (26B), cleanup 0x007B8679
POOL_INIT( rva007B10F8, rva007B8679 )
// ?rva007B1132@Rva007AB800PoolInits@@SAXXZ @ 0x007B1132 (26B), cleanup 0x007B8683
POOL_INIT( rva007B1132, rva007B8683 )
// ?rva007B114C@Rva007AB800PoolInits@@SAXXZ @ 0x007B114C (26B), cleanup 0x007B868D
POOL_INIT( rva007B114C, rva007B868D )
// ?rva007B1176@Rva007AB800PoolInits@@SAXXZ @ 0x007B1176 (26B), cleanup 0x007B86A1
POOL_INIT( rva007B1176, rva007B86A1 )
// ?rva007B11AA@Rva007AB800PoolInits@@SAXXZ @ 0x007B11AA (26B), cleanup 0x007B86AB
POOL_INIT( rva007B11AA, rva007B86AB )
// ?rva007B11C4@Rva007AB800PoolInits@@SAXXZ @ 0x007B11C4 (26B), cleanup 0x007B86B5
POOL_INIT( rva007B11C4, rva007B86B5 )
// ?rva007B11DE@Rva007AB800PoolInits@@SAXXZ @ 0x007B11DE (26B), cleanup 0x007B86BF
POOL_INIT( rva007B11DE, rva007B86BF )
// ?rva007B11F8@Rva007AB800PoolInits@@SAXXZ @ 0x007B11F8 (26B), cleanup 0x007B86C9
POOL_INIT( rva007B11F8, rva007B86C9 )
// ?rva007B1222@Rva007AB800PoolInits@@SAXXZ @ 0x007B1222 (26B), cleanup 0x007B86D3
POOL_INIT( rva007B1222, rva007B86D3 )
// ?rva007B124C@Rva007AB800PoolInits@@SAXXZ @ 0x007B124C (26B), cleanup 0x007B86DD
POOL_INIT( rva007B124C, rva007B86DD )
// ?rva007B1276@Rva007AB800PoolInits@@SAXXZ @ 0x007B1276 (26B), cleanup 0x007B86E7
POOL_INIT( rva007B1276, rva007B86E7 )
// ?rva007B1290@Rva007AB800PoolInits@@SAXXZ @ 0x007B1290 (26B), cleanup 0x007B86F1
POOL_INIT( rva007B1290, rva007B86F1 )
// ?rva007B12BA@Rva007AB800PoolInits@@SAXXZ @ 0x007B12BA (26B), cleanup 0x007B86FB
POOL_INIT( rva007B12BA, rva007B86FB )
// ?rva007B12E4@Rva007AB800PoolInits@@SAXXZ @ 0x007B12E4 (26B), cleanup 0x007B8705
POOL_INIT( rva007B12E4, rva007B8705 )
// ?rva007B12FE@Rva007AB800PoolInits@@SAXXZ @ 0x007B12FE (26B), cleanup 0x007B870F
POOL_INIT( rva007B12FE, rva007B870F )
// ?rva007B1338@Rva007AB800PoolInits@@SAXXZ @ 0x007B1338 (26B), cleanup 0x007B8719
POOL_INIT( rva007B1338, rva007B8719 )
// ?rva007B1352@Rva007AB800PoolInits@@SAXXZ @ 0x007B1352 (26B), cleanup 0x007B8723
POOL_INIT( rva007B1352, rva007B8723 )
// ?rva007B137C@Rva007AB800PoolInits@@SAXXZ @ 0x007B137C (26B), cleanup 0x007B872D
POOL_INIT( rva007B137C, rva007B872D )
// ?rva007B13A6@Rva007AB800PoolInits@@SAXXZ @ 0x007B13A6 (26B), cleanup 0x007B8737
POOL_INIT( rva007B13A6, rva007B8737 )
// ?rva007B13D0@Rva007AB800PoolInits@@SAXXZ @ 0x007B13D0 (26B), cleanup 0x007B8741
POOL_INIT( rva007B13D0, rva007B8741 )
// ?rva007B13FA@Rva007AB800PoolInits@@SAXXZ @ 0x007B13FA (26B), cleanup 0x007B874B
POOL_INIT( rva007B13FA, rva007B874B )
// ?rva007B1414@Rva007AB800PoolInits@@SAXXZ @ 0x007B1414 (26B), cleanup 0x007B8755
POOL_INIT( rva007B1414, rva007B8755 )
// ?rva007B1458@Rva007AB800PoolInits@@SAXXZ @ 0x007B1458 (26B), cleanup 0x007B875F
POOL_INIT( rva007B1458, rva007B875F )
// ?rva007B1472@Rva007AB800PoolInits@@SAXXZ @ 0x007B1472 (26B), cleanup 0x007B8773
POOL_INIT( rva007B1472, rva007B8773 )
// ?rva007B149C@Rva007AB800PoolInits@@SAXXZ @ 0x007B149C (26B), cleanup 0x007B877D
POOL_INIT( rva007B149C, rva007B877D )
// ?rva007B14C6@Rva007AB800PoolInits@@SAXXZ @ 0x007B14C6 (26B), cleanup 0x007B8787
POOL_INIT( rva007B14C6, rva007B8787 )
// ?rva007B14F0@Rva007AB800PoolInits@@SAXXZ @ 0x007B14F0 (26B), cleanup 0x007B8791
POOL_INIT( rva007B14F0, rva007B8791 )
// ?rva007B151A@Rva007AB800PoolInits@@SAXXZ @ 0x007B151A (26B), cleanup 0x007B879B
POOL_INIT( rva007B151A, rva007B879B )
// ?rva007B1544@Rva007AB800PoolInits@@SAXXZ @ 0x007B1544 (26B), cleanup 0x007B87A5
POOL_INIT( rva007B1544, rva007B87A5 )
// ?rva007B156E@Rva007AB800PoolInits@@SAXXZ @ 0x007B156E (26B), cleanup 0x007B87AF
POOL_INIT( rva007B156E, rva007B87AF )
// ?rva007B1588@Rva007AB800PoolInits@@SAXXZ @ 0x007B1588 (26B), cleanup 0x007B87B9
POOL_INIT( rva007B1588, rva007B87B9 )
// ?rva007B15BD@Rva007AB800PoolInits@@SAXXZ @ 0x007B15BD (26B), cleanup 0x007B87C3
POOL_INIT( rva007B15BD, rva007B87C3 )
// ?rva007B15D7@Rva007AB800PoolInits@@SAXXZ @ 0x007B15D7 (26B), cleanup 0x007B87CD
POOL_INIT( rva007B15D7, rva007B87CD )
// ?rva007B1601@Rva007AB800PoolInits@@SAXXZ @ 0x007B1601 (26B), cleanup 0x007B87D7
POOL_INIT( rva007B1601, rva007B87D7 )
// ?rva007B161B@Rva007AB800PoolInits@@SAXXZ @ 0x007B161B (26B), cleanup 0x007B87E1
POOL_INIT( rva007B161B, rva007B87E1 )
// ?rva007B1635@Rva007AB800PoolInits@@SAXXZ @ 0x007B1635 (26B), cleanup 0x007B87EB
POOL_INIT( rva007B1635, rva007B87EB )
// ?rva007B164F@Rva007AB800PoolInits@@SAXXZ @ 0x007B164F (26B), cleanup 0x007B87F5
POOL_INIT( rva007B164F, rva007B87F5 )
// ?rva007B1669@Rva007AB800PoolInits@@SAXXZ @ 0x007B1669 (26B), cleanup 0x007B87FF
POOL_INIT( rva007B1669, rva007B87FF )
// ?rva007B1693@Rva007AB800PoolInits@@SAXXZ @ 0x007B1693 (26B), cleanup 0x007B8809
POOL_INIT( rva007B1693, rva007B8809 )
// ?rva007B16D7@Rva007AB800PoolInits@@SAXXZ @ 0x007B16D7 (26B), cleanup 0x007B8813
POOL_INIT( rva007B16D7, rva007B8813 )
// ?rva007B16F1@Rva007AB800PoolInits@@SAXXZ @ 0x007B16F1 (26B), cleanup 0x007B8827
POOL_INIT( rva007B16F1, rva007B8827 )
// ?rva007B171B@Rva007AB800PoolInits@@SAXXZ @ 0x007B171B (26B), cleanup 0x007B8831
POOL_INIT( rva007B171B, rva007B8831 )
// ?rva007B1745@Rva007AB800PoolInits@@SAXXZ @ 0x007B1745 (26B), cleanup 0x007B883B
POOL_INIT( rva007B1745, rva007B883B )
// ?rva007B176F@Rva007AB800PoolInits@@SAXXZ @ 0x007B176F (26B), cleanup 0x007B8845
POOL_INIT( rva007B176F, rva007B8845 )
// ?rva007B1789@Rva007AB800PoolInits@@SAXXZ @ 0x007B1789 (26B), cleanup 0x007B884F
POOL_INIT( rva007B1789, rva007B884F )
// ?rva007B17A3@Rva007AB800PoolInits@@SAXXZ @ 0x007B17A3 (26B), cleanup 0x007B8859
POOL_INIT( rva007B17A3, rva007B8859 )
// ?rva007B17CD@Rva007AB800PoolInits@@SAXXZ @ 0x007B17CD (26B), cleanup 0x007B8863
POOL_INIT( rva007B17CD, rva007B8863 )
// ?rva007B17F7@Rva007AB800PoolInits@@SAXXZ @ 0x007B17F7 (26B), cleanup 0x007B886D
POOL_INIT( rva007B17F7, rva007B886D )
// ?rva007B1811@Rva007AB800PoolInits@@SAXXZ @ 0x007B1811 (26B), cleanup 0x007B8877
POOL_INIT( rva007B1811, rva007B8877 )
// ?rva007B183B@Rva007AB800PoolInits@@SAXXZ @ 0x007B183B (26B), cleanup 0x007B8881
POOL_INIT( rva007B183B, rva007B8881 )
// ?rva007B1855@Rva007AB800PoolInits@@SAXXZ @ 0x007B1855 (26B), cleanup 0x007B888B
POOL_INIT( rva007B1855, rva007B888B )
// ?rva007B186F@Rva007AB800PoolInits@@SAXXZ @ 0x007B186F (26B), cleanup 0x007B8895
POOL_INIT( rva007B186F, rva007B8895 )
// ?rva007B1889@Rva007AB800PoolInits@@SAXXZ @ 0x007B1889 (26B), cleanup 0x007B889F
POOL_INIT( rva007B1889, rva007B889F )
// ?rva007B18B3@Rva007AB800PoolInits@@SAXXZ @ 0x007B18B3 (26B), cleanup 0x007B88A9
POOL_INIT( rva007B18B3, rva007B88A9 )
// ?rva007B18DD@Rva007AB800PoolInits@@SAXXZ @ 0x007B18DD (26B), cleanup 0x007B88B3
POOL_INIT( rva007B18DD, rva007B88B3 )
// ?rva007B1907@Rva007AB800PoolInits@@SAXXZ @ 0x007B1907 (26B), cleanup 0x007B88BD
POOL_INIT( rva007B1907, rva007B88BD )
// ?rva007B194B@Rva007AB800PoolInits@@SAXXZ @ 0x007B194B (26B), cleanup 0x007B88C7
POOL_INIT( rva007B194B, rva007B88C7 )
// ?rva007B1975@Rva007AB800PoolInits@@SAXXZ @ 0x007B1975 (26B), cleanup 0x007B88DB
POOL_INIT( rva007B1975, rva007B88DB )
// ?rva007B198F@Rva007AB800PoolInits@@SAXXZ @ 0x007B198F (26B), cleanup 0x007B88E5
POOL_INIT( rva007B198F, rva007B88E5 )
// ?rva007B19B9@Rva007AB800PoolInits@@SAXXZ @ 0x007B19B9 (26B), cleanup 0x007B88EF
POOL_INIT( rva007B19B9, rva007B88EF )
// ?rva007B19D3@Rva007AB800PoolInits@@SAXXZ @ 0x007B19D3 (26B), cleanup 0x007B88F9
POOL_INIT( rva007B19D3, rva007B88F9 )
// ?rva007B19FD@Rva007AB800PoolInits@@SAXXZ @ 0x007B19FD (26B), cleanup 0x007B8903
POOL_INIT( rva007B19FD, rva007B8903 )
// ?rva007B1A38@Rva007AB800PoolInits@@SAXXZ @ 0x007B1A38 (26B), cleanup 0x007B890D
POOL_INIT( rva007B1A38, rva007B890D )
// ?rva007B1A62@Rva007AB800PoolInits@@SAXXZ @ 0x007B1A62 (26B), cleanup 0x007B8917
POOL_INIT( rva007B1A62, rva007B8917 )
// ?rva007B1A8C@Rva007AB800PoolInits@@SAXXZ @ 0x007B1A8C (26B), cleanup 0x007B8921
POOL_INIT( rva007B1A8C, rva007B8921 )
// ?rva007B1AB6@Rva007AB800PoolInits@@SAXXZ @ 0x007B1AB6 (26B), cleanup 0x007B892B
POOL_INIT( rva007B1AB6, rva007B892B )
// ?rva007B1AE0@Rva007AB800PoolInits@@SAXXZ @ 0x007B1AE0 (26B), cleanup 0x007B8935
POOL_INIT( rva007B1AE0, rva007B8935 )
// ?rva007B1B0A@Rva007AB800PoolInits@@SAXXZ @ 0x007B1B0A (26B), cleanup 0x007B893F
POOL_INIT( rva007B1B0A, rva007B893F )
// ?rva007B1B34@Rva007AB800PoolInits@@SAXXZ @ 0x007B1B34 (26B), cleanup 0x007B8949
POOL_INIT( rva007B1B34, rva007B8949 )
// ?rva007B1B5E@Rva007AB800PoolInits@@SAXXZ @ 0x007B1B5E (26B), cleanup 0x007B8953
POOL_INIT( rva007B1B5E, rva007B8953 )
// ?rva007B1B78@Rva007AB800PoolInits@@SAXXZ @ 0x007B1B78 (26B), cleanup 0x007B895D
POOL_INIT( rva007B1B78, rva007B895D )
// ?rva007B1BA2@Rva007AB800PoolInits@@SAXXZ @ 0x007B1BA2 (26B), cleanup 0x007B8967
POOL_INIT( rva007B1BA2, rva007B8967 )
// ?rva007B1BCC@Rva007AB800PoolInits@@SAXXZ @ 0x007B1BCC (26B), cleanup 0x007B8971
POOL_INIT( rva007B1BCC, rva007B8971 )
// ?rva007B1BF6@Rva007AB800PoolInits@@SAXXZ @ 0x007B1BF6 (26B), cleanup 0x007B897B
POOL_INIT( rva007B1BF6, rva007B897B )
// ?rva007B1C20@Rva007AB800PoolInits@@SAXXZ @ 0x007B1C20 (26B), cleanup 0x007B8985
POOL_INIT( rva007B1C20, rva007B8985 )
// ?rva007B1C3A@Rva007AB800PoolInits@@SAXXZ @ 0x007B1C3A (26B), cleanup 0x007B898F
POOL_INIT( rva007B1C3A, rva007B898F )
// ?rva007B1C54@Rva007AB800PoolInits@@SAXXZ @ 0x007B1C54 (26B), cleanup 0x007B8999
POOL_INIT( rva007B1C54, rva007B8999 )
// ?rva007B1C6E@Rva007AB800PoolInits@@SAXXZ @ 0x007B1C6E (26B), cleanup 0x007B89A3
POOL_INIT( rva007B1C6E, rva007B89A3 )
// ?rva007B1C98@Rva007AB800PoolInits@@SAXXZ @ 0x007B1C98 (26B), cleanup 0x007B89AD
POOL_INIT( rva007B1C98, rva007B89AD )
// ?rva007B1CC2@Rva007AB800PoolInits@@SAXXZ @ 0x007B1CC2 (26B), cleanup 0x007B89B7
POOL_INIT( rva007B1CC2, rva007B89B7 )
// ?rva007B1D02@Rva007AB800PoolInits@@SAXXZ @ 0x007B1D02 (26B), cleanup 0x007B89CB
POOL_INIT( rva007B1D02, rva007B89CB )
// ?rva007B1D2C@Rva007AB800PoolInits@@SAXXZ @ 0x007B1D2C (26B), cleanup 0x007B89D5
POOL_INIT( rva007B1D2C, rva007B89D5 )
// ?rva007B1D56@Rva007AB800PoolInits@@SAXXZ @ 0x007B1D56 (26B), cleanup 0x007B89DF
POOL_INIT( rva007B1D56, rva007B89DF )
// ?rva007B1D80@Rva007AB800PoolInits@@SAXXZ @ 0x007B1D80 (26B), cleanup 0x007B89E9
POOL_INIT( rva007B1D80, rva007B89E9 )
// ?rva007B1D9A@Rva007AB800PoolInits@@SAXXZ @ 0x007B1D9A (26B), cleanup 0x007B89F3
POOL_INIT( rva007B1D9A, rva007B89F3 )
// ?rva007B1DB4@Rva007AB800PoolInits@@SAXXZ @ 0x007B1DB4 (26B), cleanup 0x007B89FD
POOL_INIT( rva007B1DB4, rva007B89FD )
// ?rva007B1DDE@Rva007AB800PoolInits@@SAXXZ @ 0x007B1DDE (26B), cleanup 0x007B8A07
POOL_INIT( rva007B1DDE, rva007B8A07 )
// ?rva007B1E08@Rva007AB800PoolInits@@SAXXZ @ 0x007B1E08 (26B), cleanup 0x007B8A11
POOL_INIT( rva007B1E08, rva007B8A11 )
// ?rva007B1E32@Rva007AB800PoolInits@@SAXXZ @ 0x007B1E32 (26B), cleanup 0x007B8A1B
POOL_INIT( rva007B1E32, rva007B8A1B )
// ?rva007B1E5C@Rva007AB800PoolInits@@SAXXZ @ 0x007B1E5C (26B), cleanup 0x007B8A25
POOL_INIT( rva007B1E5C, rva007B8A25 )
// ?rva007B1E76@Rva007AB800PoolInits@@SAXXZ @ 0x007B1E76 (26B), cleanup 0x007B8A2F
POOL_INIT( rva007B1E76, rva007B8A2F )
// ?rva007B1EA0@Rva007AB800PoolInits@@SAXXZ @ 0x007B1EA0 (26B), cleanup 0x007B8A39
POOL_INIT( rva007B1EA0, rva007B8A39 )
// ?rva007B1EBA@Rva007AB800PoolInits@@SAXXZ @ 0x007B1EBA (26B), cleanup 0x007B8A43
POOL_INIT( rva007B1EBA, rva007B8A43 )
// ?rva007B1EE4@Rva007AB800PoolInits@@SAXXZ @ 0x007B1EE4 (26B), cleanup 0x007B8A4D
POOL_INIT( rva007B1EE4, rva007B8A4D )
// ?rva007B1F0E@Rva007AB800PoolInits@@SAXXZ @ 0x007B1F0E (26B), cleanup 0x007B8A57
POOL_INIT( rva007B1F0E, rva007B8A57 )
// ?rva007B1F38@Rva007AB800PoolInits@@SAXXZ @ 0x007B1F38 (26B), cleanup 0x007B8A61
POOL_INIT( rva007B1F38, rva007B8A61 )
// ?rva007B1F62@Rva007AB800PoolInits@@SAXXZ @ 0x007B1F62 (26B), cleanup 0x007B8A6B
POOL_INIT( rva007B1F62, rva007B8A6B )
// ?rva007B1F8C@Rva007AB800PoolInits@@SAXXZ @ 0x007B1F8C (26B), cleanup 0x007B8A75
POOL_INIT( rva007B1F8C, rva007B8A75 )
// ?rva007B1FB6@Rva007AB800PoolInits@@SAXXZ @ 0x007B1FB6 (26B), cleanup 0x007B8A7F
POOL_INIT( rva007B1FB6, rva007B8A7F )
// ?rva007B1FE0@Rva007AB800PoolInits@@SAXXZ @ 0x007B1FE0 (26B), cleanup 0x007B8A89
POOL_INIT( rva007B1FE0, rva007B8A89 )
// ?rva007B200A@Rva007AB800PoolInits@@SAXXZ @ 0x007B200A (26B), cleanup 0x007B8A93
POOL_INIT( rva007B200A, rva007B8A93 )
// ?rva007B2034@Rva007AB800PoolInits@@SAXXZ @ 0x007B2034 (26B), cleanup 0x007B8A9D
POOL_INIT( rva007B2034, rva007B8A9D )
// ?rva007B205E@Rva007AB800PoolInits@@SAXXZ @ 0x007B205E (26B), cleanup 0x007B8AA7
POOL_INIT( rva007B205E, rva007B8AA7 )
// ?rva007B2088@Rva007AB800PoolInits@@SAXXZ @ 0x007B2088 (26B), cleanup 0x007B8AB1
POOL_INIT( rva007B2088, rva007B8AB1 )
// ?rva007B20B2@Rva007AB800PoolInits@@SAXXZ @ 0x007B20B2 (26B), cleanup 0x007B8ABB
POOL_INIT( rva007B20B2, rva007B8ABB )
// ?rva007B20DC@Rva007AB800PoolInits@@SAXXZ @ 0x007B20DC (26B), cleanup 0x007B8AC5
POOL_INIT( rva007B20DC, rva007B8AC5 )
// ?rva007B2106@Rva007AB800PoolInits@@SAXXZ @ 0x007B2106 (26B), cleanup 0x007B8ACF
POOL_INIT( rva007B2106, rva007B8ACF )
// ?rva007B2130@Rva007AB800PoolInits@@SAXXZ @ 0x007B2130 (26B), cleanup 0x007B8AD9
POOL_INIT( rva007B2130, rva007B8AD9 )
// ?rva007B215A@Rva007AB800PoolInits@@SAXXZ @ 0x007B215A (26B), cleanup 0x007B8AE3
POOL_INIT( rva007B215A, rva007B8AE3 )
// ?rva007B2184@Rva007AB800PoolInits@@SAXXZ @ 0x007B2184 (26B), cleanup 0x007B8AED
POOL_INIT( rva007B2184, rva007B8AED )
// ?rva007B21AE@Rva007AB800PoolInits@@SAXXZ @ 0x007B21AE (26B), cleanup 0x007B8AF7
POOL_INIT( rva007B21AE, rva007B8AF7 )
// ?rva007B21D8@Rva007AB800PoolInits@@SAXXZ @ 0x007B21D8 (26B), cleanup 0x007B8B01
POOL_INIT( rva007B21D8, rva007B8B01 )
// ?rva007B2202@Rva007AB800PoolInits@@SAXXZ @ 0x007B2202 (26B), cleanup 0x007B8B0B
POOL_INIT( rva007B2202, rva007B8B0B )
// ?rva007B222C@Rva007AB800PoolInits@@SAXXZ @ 0x007B222C (26B), cleanup 0x007B8B15
POOL_INIT( rva007B222C, rva007B8B15 )
// ?rva007B2256@Rva007AB800PoolInits@@SAXXZ @ 0x007B2256 (26B), cleanup 0x007B8B1F
POOL_INIT( rva007B2256, rva007B8B1F )
// ?rva007B2280@Rva007AB800PoolInits@@SAXXZ @ 0x007B2280 (26B), cleanup 0x007B8B29
POOL_INIT( rva007B2280, rva007B8B29 )
// ?rva007B22AA@Rva007AB800PoolInits@@SAXXZ @ 0x007B22AA (26B), cleanup 0x007B8B33
POOL_INIT( rva007B22AA, rva007B8B33 )
// ?rva007B22D4@Rva007AB800PoolInits@@SAXXZ @ 0x007B22D4 (26B), cleanup 0x007B8B3D
POOL_INIT( rva007B22D4, rva007B8B3D )
// ?rva007B22FE@Rva007AB800PoolInits@@SAXXZ @ 0x007B22FE (26B), cleanup 0x007B8B47
POOL_INIT( rva007B22FE, rva007B8B47 )
// ?rva007B2328@Rva007AB800PoolInits@@SAXXZ @ 0x007B2328 (26B), cleanup 0x007B8B51
POOL_INIT( rva007B2328, rva007B8B51 )
// ?rva007B2352@Rva007AB800PoolInits@@SAXXZ @ 0x007B2352 (26B), cleanup 0x007B8B5B
POOL_INIT( rva007B2352, rva007B8B5B )
// ?rva007B237C@Rva007AB800PoolInits@@SAXXZ @ 0x007B237C (26B), cleanup 0x007B8B65
POOL_INIT( rva007B237C, rva007B8B65 )
// ?rva007B23A6@Rva007AB800PoolInits@@SAXXZ @ 0x007B23A6 (26B), cleanup 0x007B8B6F
POOL_INIT( rva007B23A6, rva007B8B6F )
// ?rva007B23D0@Rva007AB800PoolInits@@SAXXZ @ 0x007B23D0 (26B), cleanup 0x007B8B79
POOL_INIT( rva007B23D0, rva007B8B79 )
// ?rva007B23FA@Rva007AB800PoolInits@@SAXXZ @ 0x007B23FA (26B), cleanup 0x007B8B83
POOL_INIT( rva007B23FA, rva007B8B83 )
// ?rva007B2424@Rva007AB800PoolInits@@SAXXZ @ 0x007B2424 (26B), cleanup 0x007B8B8D
POOL_INIT( rva007B2424, rva007B8B8D )
// ?rva007B243E@Rva007AB800PoolInits@@SAXXZ @ 0x007B243E (26B), cleanup 0x007B8B97
POOL_INIT( rva007B243E, rva007B8B97 )
// ?rva007B2458@Rva007AB800PoolInits@@SAXXZ @ 0x007B2458 (26B), cleanup 0x007B8BA1
POOL_INIT( rva007B2458, rva007B8BA1 )
// ?rva007B2472@Rva007AB800PoolInits@@SAXXZ @ 0x007B2472 (26B), cleanup 0x007B8BAB
POOL_INIT( rva007B2472, rva007B8BAB )
// ?rva007B248C@Rva007AB800PoolInits@@SAXXZ @ 0x007B248C (26B), cleanup 0x007B8BB5
POOL_INIT( rva007B248C, rva007B8BB5 )
// ?rva007B24A6@Rva007AB800PoolInits@@SAXXZ @ 0x007B24A6 (26B), cleanup 0x007B8BBF
POOL_INIT( rva007B24A6, rva007B8BBF )
// ?rva007B24D0@Rva007AB800PoolInits@@SAXXZ @ 0x007B24D0 (26B), cleanup 0x007B8BC9
POOL_INIT( rva007B24D0, rva007B8BC9 )
// ?rva007B24FA@Rva007AB800PoolInits@@SAXXZ @ 0x007B24FA (26B), cleanup 0x007B8BD3
POOL_INIT( rva007B24FA, rva007B8BD3 )
// ?rva007B2524@Rva007AB800PoolInits@@SAXXZ @ 0x007B2524 (26B), cleanup 0x007B8BDD
POOL_INIT( rva007B2524, rva007B8BDD )
// ?rva007B254E@Rva007AB800PoolInits@@SAXXZ @ 0x007B254E (26B), cleanup 0x007B8BE7
POOL_INIT( rva007B254E, rva007B8BE7 )
// ?rva007B2578@Rva007AB800PoolInits@@SAXXZ @ 0x007B2578 (26B), cleanup 0x007B8BF1
POOL_INIT( rva007B2578, rva007B8BF1 )
// ?rva007B2592@Rva007AB800PoolInits@@SAXXZ @ 0x007B2592 (26B), cleanup 0x007B8BFB
POOL_INIT( rva007B2592, rva007B8BFB )
// ?rva007B2616@Rva007AB800PoolInits@@SAXXZ @ 0x007B2616 (26B), cleanup 0x007B8C05
POOL_INIT( rva007B2616, rva007B8C05 )
// ?rva007B2640@Rva007AB800PoolInits@@SAXXZ @ 0x007B2640 (26B), cleanup 0x007B8C0F
POOL_INIT( rva007B2640, rva007B8C0F )
// ?rva007B266A@Rva007AB800PoolInits@@SAXXZ @ 0x007B266A (26B), cleanup 0x007B8C19
POOL_INIT( rva007B266A, rva007B8C19 )
// ?rva007B2684@Rva007AB800PoolInits@@SAXXZ @ 0x007B2684 (26B), cleanup 0x007B8C23
POOL_INIT( rva007B2684, rva007B8C23 )
// ?rva007B269E@Rva007AB800PoolInits@@SAXXZ @ 0x007B269E (26B), cleanup 0x007B8C2D
POOL_INIT( rva007B269E, rva007B8C2D )
// ?rva007B26B8@Rva007AB800PoolInits@@SAXXZ @ 0x007B26B8 (26B), cleanup 0x007B8C37
POOL_INIT( rva007B26B8, rva007B8C37 )
// ?rva007B26D2@Rva007AB800PoolInits@@SAXXZ @ 0x007B26D2 (26B), cleanup 0x007B8C41
POOL_INIT( rva007B26D2, rva007B8C41 )
// ?rva007B26FC@Rva007AB800PoolInits@@SAXXZ @ 0x007B26FC (26B), cleanup 0x007B8C4B
POOL_INIT( rva007B26FC, rva007B8C4B )
// ?rva007B2716@Rva007AB800PoolInits@@SAXXZ @ 0x007B2716 (26B), cleanup 0x007B8C55
POOL_INIT( rva007B2716, rva007B8C55 )
// ?rva007B2730@Rva007AB800PoolInits@@SAXXZ @ 0x007B2730 (26B), cleanup 0x007B8C5F
POOL_INIT( rva007B2730, rva007B8C5F )
// ?rva007B275A@Rva007AB800PoolInits@@SAXXZ @ 0x007B275A (26B), cleanup 0x007B8C69
POOL_INIT( rva007B275A, rva007B8C69 )
// ?rva007B279E@Rva007AB800PoolInits@@SAXXZ @ 0x007B279E (26B), cleanup 0x007B8C73
POOL_INIT( rva007B279E, rva007B8C73 )
// ?rva007B27C8@Rva007AB800PoolInits@@SAXXZ @ 0x007B27C8 (26B), cleanup 0x007B8C87
POOL_INIT( rva007B27C8, rva007B8C87 )
// ?rva007B27E2@Rva007AB800PoolInits@@SAXXZ @ 0x007B27E2 (26B), cleanup 0x007B8C91
POOL_INIT( rva007B27E2, rva007B8C91 )
// ?rva007B27FC@Rva007AB800PoolInits@@SAXXZ @ 0x007B27FC (26B), cleanup 0x007B8C9B
POOL_INIT( rva007B27FC, rva007B8C9B )
// ?rva007B2816@Rva007AB800PoolInits@@SAXXZ @ 0x007B2816 (26B), cleanup 0x007B8CA5
POOL_INIT( rva007B2816, rva007B8CA5 )
// ?rva007B2840@Rva007AB800PoolInits@@SAXXZ @ 0x007B2840 (26B), cleanup 0x007B8CAF
POOL_INIT( rva007B2840, rva007B8CAF )
// ?rva007B286A@Rva007AB800PoolInits@@SAXXZ @ 0x007B286A (26B), cleanup 0x007B8CB9
POOL_INIT( rva007B286A, rva007B8CB9 )
// ?rva007B2884@Rva007AB800PoolInits@@SAXXZ @ 0x007B2884 (26B), cleanup 0x007B8CC3
POOL_INIT( rva007B2884, rva007B8CC3 )
// ?rva007B289E@Rva007AB800PoolInits@@SAXXZ @ 0x007B289E (26B), cleanup 0x007B8CCD
POOL_INIT( rva007B289E, rva007B8CCD )
// ?rva007B28B8@Rva007AB800PoolInits@@SAXXZ @ 0x007B28B8 (26B), cleanup 0x007B8CD7
POOL_INIT( rva007B28B8, rva007B8CD7 )
// ?rva007B28D2@Rva007AB800PoolInits@@SAXXZ @ 0x007B28D2 (26B), cleanup 0x007B8CE1
POOL_INIT( rva007B28D2, rva007B8CE1 )
// ?rva007B28EC@Rva007AB800PoolInits@@SAXXZ @ 0x007B28EC (26B), cleanup 0x007B8CEB
POOL_INIT( rva007B28EC, rva007B8CEB )
// ?rva007B2916@Rva007AB800PoolInits@@SAXXZ @ 0x007B2916 (26B), cleanup 0x007B8CF5
POOL_INIT( rva007B2916, rva007B8CF5 )
// ?rva007B2930@Rva007AB800PoolInits@@SAXXZ @ 0x007B2930 (26B), cleanup 0x007B8CFF
POOL_INIT( rva007B2930, rva007B8CFF )
// ?rva007B295A@Rva007AB800PoolInits@@SAXXZ @ 0x007B295A (26B), cleanup 0x007B8D09
POOL_INIT( rva007B295A, rva007B8D09 )
// ?rva007B2984@Rva007AB800PoolInits@@SAXXZ @ 0x007B2984 (26B), cleanup 0x007B8D13
POOL_INIT( rva007B2984, rva007B8D13 )
// ?rva007B29AE@Rva007AB800PoolInits@@SAXXZ @ 0x007B29AE (26B), cleanup 0x007B8D1D
POOL_INIT( rva007B29AE, rva007B8D1D )
// ?rva007B29D8@Rva007AB800PoolInits@@SAXXZ @ 0x007B29D8 (26B), cleanup 0x007B8D27
POOL_INIT( rva007B29D8, rva007B8D27 )
// ?rva007B2A02@Rva007AB800PoolInits@@SAXXZ @ 0x007B2A02 (26B), cleanup 0x007B8D31
POOL_INIT( rva007B2A02, rva007B8D31 )
// ?rva007B2A2C@Rva007AB800PoolInits@@SAXXZ @ 0x007B2A2C (26B), cleanup 0x007B8D3B
POOL_INIT( rva007B2A2C, rva007B8D3B )
// ?rva007B2A46@Rva007AB800PoolInits@@SAXXZ @ 0x007B2A46 (26B), cleanup 0x007B8D45
POOL_INIT( rva007B2A46, rva007B8D45 )
// ?rva007B2A70@Rva007AB800PoolInits@@SAXXZ @ 0x007B2A70 (26B), cleanup 0x007B8D4F
POOL_INIT( rva007B2A70, rva007B8D4F )
// ?rva007B2A8A@Rva007AB800PoolInits@@SAXXZ @ 0x007B2A8A (26B), cleanup 0x007B8D59
POOL_INIT( rva007B2A8A, rva007B8D59 )
// ?rva007B2AB4@Rva007AB800PoolInits@@SAXXZ @ 0x007B2AB4 (26B), cleanup 0x007B8D63
POOL_INIT( rva007B2AB4, rva007B8D63 )
// ?rva007B2ACE@Rva007AB800PoolInits@@SAXXZ @ 0x007B2ACE (26B), cleanup 0x007B8D6D
POOL_INIT( rva007B2ACE, rva007B8D6D )
// ?rva007B2AE8@Rva007AB800PoolInits@@SAXXZ @ 0x007B2AE8 (26B), cleanup 0x007B8D77
POOL_INIT( rva007B2AE8, rva007B8D77 )
// ?rva007B2B02@Rva007AB800PoolInits@@SAXXZ @ 0x007B2B02 (26B), cleanup 0x007B8D81
POOL_INIT( rva007B2B02, rva007B8D81 )
// ?rva007B2B1C@Rva007AB800PoolInits@@SAXXZ @ 0x007B2B1C (26B), cleanup 0x007B8D8B
POOL_INIT( rva007B2B1C, rva007B8D8B )
// ?rva007B2B46@Rva007AB800PoolInits@@SAXXZ @ 0x007B2B46 (26B), cleanup 0x007B8D95
POOL_INIT( rva007B2B46, rva007B8D95 )
// ?rva007B2B70@Rva007AB800PoolInits@@SAXXZ @ 0x007B2B70 (26B), cleanup 0x007B8D9F
POOL_INIT( rva007B2B70, rva007B8D9F )
// ?rva007B2B9A@Rva007AB800PoolInits@@SAXXZ @ 0x007B2B9A (26B), cleanup 0x007B8DA9
POOL_INIT( rva007B2B9A, rva007B8DA9 )
// ?rva007B2BC4@Rva007AB800PoolInits@@SAXXZ @ 0x007B2BC4 (26B), cleanup 0x007B8DB3
POOL_INIT( rva007B2BC4, rva007B8DB3 )
// ?rva007B2BEE@Rva007AB800PoolInits@@SAXXZ @ 0x007B2BEE (26B), cleanup 0x007B8DBD
POOL_INIT( rva007B2BEE, rva007B8DBD )
// ?rva007B2C18@Rva007AB800PoolInits@@SAXXZ @ 0x007B2C18 (26B), cleanup 0x007B8DC7
POOL_INIT( rva007B2C18, rva007B8DC7 )
// ?rva007B2C42@Rva007AB800PoolInits@@SAXXZ @ 0x007B2C42 (26B), cleanup 0x007B8DD1
POOL_INIT( rva007B2C42, rva007B8DD1 )
// ?rva007B2C6C@Rva007AB800PoolInits@@SAXXZ @ 0x007B2C6C (26B), cleanup 0x007B8DDB
POOL_INIT( rva007B2C6C, rva007B8DDB )
// ?rva007B2C96@Rva007AB800PoolInits@@SAXXZ @ 0x007B2C96 (26B), cleanup 0x007B8DE5
POOL_INIT( rva007B2C96, rva007B8DE5 )
// ?rva007B2CC0@Rva007AB800PoolInits@@SAXXZ @ 0x007B2CC0 (26B), cleanup 0x007B8DEF
POOL_INIT( rva007B2CC0, rva007B8DEF )
// ?rva007B2CEA@Rva007AB800PoolInits@@SAXXZ @ 0x007B2CEA (26B), cleanup 0x007B8DF9
POOL_INIT( rva007B2CEA, rva007B8DF9 )
// ?rva007B2D04@Rva007AB800PoolInits@@SAXXZ @ 0x007B2D04 (26B), cleanup 0x007B8E03
POOL_INIT( rva007B2D04, rva007B8E03 )
// ?rva007B2D1E@Rva007AB800PoolInits@@SAXXZ @ 0x007B2D1E (26B), cleanup 0x007B8E0D
POOL_INIT( rva007B2D1E, rva007B8E0D )
// ?rva007B2D38@Rva007AB800PoolInits@@SAXXZ @ 0x007B2D38 (26B), cleanup 0x007B8E17
POOL_INIT( rva007B2D38, rva007B8E17 )
// ?rva007B2D52@Rva007AB800PoolInits@@SAXXZ @ 0x007B2D52 (26B), cleanup 0x007B8E21
POOL_INIT( rva007B2D52, rva007B8E21 )
// ?rva007B2D6C@Rva007AB800PoolInits@@SAXXZ @ 0x007B2D6C (26B), cleanup 0x007B8E2B
POOL_INIT( rva007B2D6C, rva007B8E2B )
// ?rva007B2D86@Rva007AB800PoolInits@@SAXXZ @ 0x007B2D86 (26B), cleanup 0x007B8E35
POOL_INIT( rva007B2D86, rva007B8E35 )
// ?rva007B2DA0@Rva007AB800PoolInits@@SAXXZ @ 0x007B2DA0 (26B), cleanup 0x007B8E3F
POOL_INIT( rva007B2DA0, rva007B8E3F )
// ?rva007B2DBA@Rva007AB800PoolInits@@SAXXZ @ 0x007B2DBA (26B), cleanup 0x007B8E49
POOL_INIT( rva007B2DBA, rva007B8E49 )
// ?rva007B2DD4@Rva007AB800PoolInits@@SAXXZ @ 0x007B2DD4 (26B), cleanup 0x007B8E53
POOL_INIT( rva007B2DD4, rva007B8E53 )
// ?rva007B2DFE@Rva007AB800PoolInits@@SAXXZ @ 0x007B2DFE (26B), cleanup 0x007B8E5D
POOL_INIT( rva007B2DFE, rva007B8E5D )
// ?rva007B2E28@Rva007AB800PoolInits@@SAXXZ @ 0x007B2E28 (26B), cleanup 0x007B8E67
POOL_INIT( rva007B2E28, rva007B8E67 )
// ?rva007B2E52@Rva007AB800PoolInits@@SAXXZ @ 0x007B2E52 (26B), cleanup 0x007B8E71
POOL_INIT( rva007B2E52, rva007B8E71 )
// ?rva007B2E6C@Rva007AB800PoolInits@@SAXXZ @ 0x007B2E6C (26B), cleanup 0x007B8E7B
POOL_INIT( rva007B2E6C, rva007B8E7B )
// ?rva007B2E86@Rva007AB800PoolInits@@SAXXZ @ 0x007B2E86 (26B), cleanup 0x007B8E85
POOL_INIT( rva007B2E86, rva007B8E85 )
// ?rva007B2EB0@Rva007AB800PoolInits@@SAXXZ @ 0x007B2EB0 (26B), cleanup 0x007B8E8F
POOL_INIT( rva007B2EB0, rva007B8E8F )
// ?rva007B2F00@Rva007AB800PoolInits@@SAXXZ @ 0x007B2F00 (26B), cleanup 0x007B8E9A
POOL_INIT( rva007B2F00, rva007B8E9A )
// ?rva007B2F1A@Rva007AB800PoolInits@@SAXXZ @ 0x007B2F1A (26B), cleanup 0x007B8EAE
POOL_INIT( rva007B2F1A, rva007B8EAE )
// ?rva007B2F34@Rva007AB800PoolInits@@SAXXZ @ 0x007B2F34 (26B), cleanup 0x007B8EB8
POOL_INIT( rva007B2F34, rva007B8EB8 )
// ?rva007B2F5E@Rva007AB800PoolInits@@SAXXZ @ 0x007B2F5E (26B), cleanup 0x007B8EC2
POOL_INIT( rva007B2F5E, rva007B8EC2 )
// ?rva007B2F92@Rva007AB800PoolInits@@SAXXZ @ 0x007B2F92 (26B), cleanup 0x007B8ECC
POOL_INIT( rva007B2F92, rva007B8ECC )
// ?rva007B2FAC@Rva007AB800PoolInits@@SAXXZ @ 0x007B2FAC (26B), cleanup 0x007B8EE0
POOL_INIT( rva007B2FAC, rva007B8EE0 )
// ?rva007B2FC6@Rva007AB800PoolInits@@SAXXZ @ 0x007B2FC6 (26B), cleanup 0x007B8EEA
POOL_INIT( rva007B2FC6, rva007B8EEA )
// ?rva007B2FF0@Rva007AB800PoolInits@@SAXXZ @ 0x007B2FF0 (26B), cleanup 0x007B8EF4
POOL_INIT( rva007B2FF0, rva007B8EF4 )
// ?rva007B3030@Rva007AB800PoolInits@@SAXXZ @ 0x007B3030 (26B), cleanup 0x007B8EFE
POOL_INIT( rva007B3030, rva007B8EFE )
// ?rva007B304A@Rva007AB800PoolInits@@SAXXZ @ 0x007B304A (26B), cleanup 0x007B8F30
POOL_INIT( rva007B304A, rva007B8F30 )
// ?rva007B3074@Rva007AB800PoolInits@@SAXXZ @ 0x007B3074 (26B), cleanup 0x007B8F3A
POOL_INIT( rva007B3074, rva007B8F3A )
// ?rva007B30AA@Rva007AB800PoolInits@@SAXXZ @ 0x007B30AA (26B), cleanup 0x007B8F45
POOL_INIT( rva007B30AA, rva007B8F45 )
