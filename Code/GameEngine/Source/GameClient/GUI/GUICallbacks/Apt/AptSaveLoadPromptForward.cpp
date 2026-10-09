// cl: /O1 /MD /EHsc
// Native435CCC..435CDB is a complete15B cdecl wrapper. The target/WB
// direct call reaches named static PromptAddFriend and tests AL; false
// tail-forwards to434EFA, which independently shows the saved-game prompt.
// BF1 clean BfmeConv435.cpp at current2f243e26d supplies the same conditional
// wrapper shape. The outer wrapper original name remains unproven.
class AptSaveLoad {public: static bool PromptAddFriend();};
void Rva00434EFA();
void Rva00435CCC() { if(!AptSaveLoad::PromptAddFriend())Rva00434EFA(); }
