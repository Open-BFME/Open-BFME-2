// cl: /O2 /GX /DNDEBUG /MD
// RVA 0x0070B670..0x0070D9E8, 9,080 bytes: APT constant-string pool setup.
// Target evidence: caller 0x006CF865 passes the configured bucket count;
// the StringPool.cpp/CheckContent assertion identifies the subsystem.
// The original exported method name is unproven, so keep an address name.
// All 178 index/literal pairs and their order are read from retail. The
// previously recovered shutdown and CheckContent routines independently
// establish the same 178 one-pointer slots at VA 0x00E18388..0x00E18650.
// bfmeObjDAE's existing owner supplies that storage and its startup lifetime.
//
// Each assignment has a separate named string lifetime. Passing an unnamed
// temporary reuses the constructor's EAX result and removes four bytes per
// entry; named locals reproduce retail's independent LEA and EH states.
// All helpers have existing matched owners. The pointer predicate's fold
// owner is AsciiString::hasData; no original EAStringC method name is assumed.
// Reference search at open-bfme-1 d6db6bfa4fd3bd86c1d7ca4a5ab882d7c453a92c
// found no corresponding clean C++ initializer; this reconstruction uses
// target control flow, literals and the recovered EAStringC operations.
extern "C" void *memset(void *,int,unsigned int);
#pragma intrinsic(memset)
void __debugbreak();
#pragma intrinsic(__debugbreak)
class EAStringC {
 void *m_data;
public:
 EAStringC(const char *);
 ~EAStringC();
 EAStringC &operator=(const EAStringC &);
 bool rva006CD4A0() const;
 void rva006D3C60();
};
class Rva006DB160 { public: void *allocBlock(int); };
extern Rva006DB160 *g_aptPoolAllocator;
extern "C" EAStringC bfmeObjDAE[178];
struct StringNode0070D9F0;
extern StringNode0070D9F0 **g_00E18368;
extern int g_00E1836C;
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
bool Rva0070B5D0Check();
void Rva0070B670Initialize(int bucketCount) {
 EAStringC *p=bfmeObjDAE;
 do {
  if (!p->rva006CD4A0()) p->rva006D3C60();
  ++p;
 } while ((int)p < (int)(bfmeObjDAE+178));
 { EAStringC text("__proto__"); bfmeObjDAE[0] = text; }
 { EAStringC text("_alpha"); bfmeObjDAE[1] = text; }
 { EAStringC text("_currentframe"); bfmeObjDAE[2] = text; }
 { EAStringC text("_down"); bfmeObjDAE[3] = text; }
 { EAStringC text("_droptarget"); bfmeObjDAE[4] = text; }
 { EAStringC text("_focusrect"); bfmeObjDAE[5] = text; }
 { EAStringC text("_framesloaded"); bfmeObjDAE[6] = text; }
 { EAStringC text("_global"); bfmeObjDAE[7] = text; }
 { EAStringC text("_height"); bfmeObjDAE[8] = text; }
 { EAStringC text("_highquality"); bfmeObjDAE[9] = text; }
 { EAStringC text("_left"); bfmeObjDAE[10] = text; }
 { EAStringC text("_name"); bfmeObjDAE[11] = text; }
 { EAStringC text("_quality"); bfmeObjDAE[12] = text; }
 { EAStringC text("_right"); bfmeObjDAE[13] = text; }
 { EAStringC text("_rotation"); bfmeObjDAE[14] = text; }
 { EAStringC text("_soundbuftime"); bfmeObjDAE[15] = text; }
 { EAStringC text("_target"); bfmeObjDAE[16] = text; }
 { EAStringC text("_totalframes"); bfmeObjDAE[17] = text; }
 { EAStringC text("_type"); bfmeObjDAE[18] = text; }
 { EAStringC text("_up"); bfmeObjDAE[19] = text; }
 { EAStringC text("_url"); bfmeObjDAE[20] = text; }
 { EAStringC text("_visible"); bfmeObjDAE[21] = text; }
 { EAStringC text("_width"); bfmeObjDAE[22] = text; }
 { EAStringC text("_x"); bfmeObjDAE[23] = text; }
 { EAStringC text("_xmouse"); bfmeObjDAE[24] = text; }
 { EAStringC text("_xscale"); bfmeObjDAE[25] = text; }
 { EAStringC text("_y"); bfmeObjDAE[26] = text; }
 { EAStringC text("_ymouse"); bfmeObjDAE[27] = text; }
 { EAStringC text("_yscale"); bfmeObjDAE[28] = text; }
 { EAStringC text("aa"); bfmeObjDAE[29] = text; }
 { EAStringC text("ab"); bfmeObjDAE[30] = text; }
 { EAStringC text("abs"); bfmeObjDAE[31] = text; }
 { EAStringC text("acos"); bfmeObjDAE[32] = text; }
 { EAStringC text("Array"); bfmeObjDAE[33] = text; }
 { EAStringC text("asin"); bfmeObjDAE[34] = text; }
 { EAStringC text("atan"); bfmeObjDAE[35] = text; }
 { EAStringC text("atan2"); bfmeObjDAE[36] = text; }
 { EAStringC text("ba"); bfmeObjDAE[37] = text; }
 { EAStringC text("bb"); bfmeObjDAE[38] = text; }
 { EAStringC text("boolean"); bfmeObjDAE[39] = text; }
 { EAStringC text("ceil"); bfmeObjDAE[40] = text; }
 { EAStringC text("center"); bfmeObjDAE[41] = text; }
 { EAStringC text("charAt"); bfmeObjDAE[42] = text; }
 { EAStringC text("charCodeAt"); bfmeObjDAE[43] = text; }
 { EAStringC text("Color"); bfmeObjDAE[44] = text; }
 { EAStringC text("concat"); bfmeObjDAE[45] = text; }
 { EAStringC text("contentType"); bfmeObjDAE[46] = text; }
 { EAStringC text("controller"); bfmeObjDAE[47] = text; }
 { EAStringC text("cos"); bfmeObjDAE[48] = text; }
 { EAStringC text("Date"); bfmeObjDAE[49] = text; }
 { EAStringC text("Error"); bfmeObjDAE[50] = text; }
 { EAStringC text("exp"); bfmeObjDAE[51] = text; }
 { EAStringC text("false"); bfmeObjDAE[52] = text; }
 { EAStringC text("floor"); bfmeObjDAE[53] = text; }
 { EAStringC text("fromCharCode"); bfmeObjDAE[54] = text; }
 { EAStringC text("function"); bfmeObjDAE[55] = text; }
 { EAStringC text("fXAxisValue"); bfmeObjDAE[56] = text; }
 { EAStringC text("fYAxisValue"); bfmeObjDAE[57] = text; }
 { EAStringC text("ga"); bfmeObjDAE[58] = text; }
 { EAStringC text("gb"); bfmeObjDAE[59] = text; }
 { EAStringC text("getBytesLoaded"); bfmeObjDAE[60] = text; }
 { EAStringC text("getBytesTotal"); bfmeObjDAE[61] = text; }
 { EAStringC text("getDate"); bfmeObjDAE[62] = text; }
 { EAStringC text("getDay"); bfmeObjDAE[63] = text; }
 { EAStringC text("getFullYear"); bfmeObjDAE[64] = text; }
 { EAStringC text("getHours"); bfmeObjDAE[65] = text; }
 { EAStringC text("getMilliseconds"); bfmeObjDAE[66] = text; }
 { EAStringC text("getMinutes"); bfmeObjDAE[67] = text; }
 { EAStringC text("getMonth"); bfmeObjDAE[68] = text; }
 { EAStringC text("getRGB"); bfmeObjDAE[69] = text; }
 { EAStringC text("getSeconds"); bfmeObjDAE[70] = text; }
 { EAStringC text("getTime"); bfmeObjDAE[71] = text; }
 { EAStringC text("getTimezoneOffset"); bfmeObjDAE[72] = text; }
 { EAStringC text("getTransform"); bfmeObjDAE[73] = text; }
 { EAStringC text("getUTCDate"); bfmeObjDAE[74] = text; }
 { EAStringC text("getUTCDay"); bfmeObjDAE[75] = text; }
 { EAStringC text("getUTCFullYear"); bfmeObjDAE[76] = text; }
 { EAStringC text("getUTCHours"); bfmeObjDAE[77] = text; }
 { EAStringC text("getUTCMilliseconds"); bfmeObjDAE[78] = text; }
 { EAStringC text("getUTCMinutes"); bfmeObjDAE[79] = text; }
 { EAStringC text("getUTCMonth"); bfmeObjDAE[80] = text; }
 { EAStringC text("getUTCSeconds"); bfmeObjDAE[81] = text; }
 { EAStringC text("getYear"); bfmeObjDAE[82] = text; }
 { EAStringC text("indexOf"); bfmeObjDAE[83] = text; }
 { EAStringC text("join"); bfmeObjDAE[84] = text; }
 { EAStringC text("lastIndexOf"); bfmeObjDAE[85] = text; }
 { EAStringC text("left"); bfmeObjDAE[86] = text; }
 { EAStringC text("length"); bfmeObjDAE[87] = text; }
 { EAStringC text("load"); bfmeObjDAE[88] = text; }
 { EAStringC text("loaded"); bfmeObjDAE[89] = text; }
 { EAStringC text("LoadVars"); bfmeObjDAE[90] = text; }
 { EAStringC text("log"); bfmeObjDAE[91] = text; }
 { EAStringC text("max"); bfmeObjDAE[92] = text; }
 { EAStringC text("min"); bfmeObjDAE[93] = text; }
 { EAStringC text("movieclip"); bfmeObjDAE[94] = text; }
 { EAStringC text("NodeName"); bfmeObjDAE[95] = text; }
 { EAStringC text("NodeValue"); bfmeObjDAE[96] = text; }
 { EAStringC text("none"); bfmeObjDAE[97] = text; }
 { EAStringC text("null"); bfmeObjDAE[98] = text; }
 { EAStringC text("number"); bfmeObjDAE[99] = text; }
 { EAStringC text("object"); bfmeObjDAE[100] = text; }
 { EAStringC text("onData"); bfmeObjDAE[101] = text; }
 { EAStringC text("onDragOut"); bfmeObjDAE[102] = text; }
 { EAStringC text("onDragOver"); bfmeObjDAE[103] = text; }
 { EAStringC text("onEnterFrame"); bfmeObjDAE[104] = text; }
 { EAStringC text("onKeyDown"); bfmeObjDAE[105] = text; }
 { EAStringC text("onKeyUp"); bfmeObjDAE[106] = text; }
 { EAStringC text("onLoad"); bfmeObjDAE[107] = text; }
 { EAStringC text("onMouseDown"); bfmeObjDAE[108] = text; }
 { EAStringC text("onMouseMove"); bfmeObjDAE[109] = text; }
 { EAStringC text("onMouseUp"); bfmeObjDAE[110] = text; }
 { EAStringC text("onMouseWheel"); bfmeObjDAE[111] = text; }
 { EAStringC text("onPress"); bfmeObjDAE[112] = text; }
 { EAStringC text("onRelease"); bfmeObjDAE[113] = text; }
 { EAStringC text("onReleaseOutside"); bfmeObjDAE[114] = text; }
 { EAStringC text("onRollOut"); bfmeObjDAE[115] = text; }
 { EAStringC text("onRollOver"); bfmeObjDAE[116] = text; }
 { EAStringC text("onUnload"); bfmeObjDAE[117] = text; }
 { EAStringC text("pop"); bfmeObjDAE[118] = text; }
 { EAStringC text("pow"); bfmeObjDAE[119] = text; }
 { EAStringC text("prototype"); bfmeObjDAE[120] = text; }
 { EAStringC text("push"); bfmeObjDAE[121] = text; }
 { EAStringC text("ra"); bfmeObjDAE[122] = text; }
 { EAStringC text("random"); bfmeObjDAE[123] = text; }
 { EAStringC text("rb"); bfmeObjDAE[124] = text; }
 { EAStringC text("reverse"); bfmeObjDAE[125] = text; }
 { EAStringC text("right"); bfmeObjDAE[126] = text; }
 { EAStringC text("round"); bfmeObjDAE[127] = text; }
 { EAStringC text("send"); bfmeObjDAE[128] = text; }
 { EAStringC text("sendAndLoad"); bfmeObjDAE[129] = text; }
 { EAStringC text("setDate"); bfmeObjDAE[130] = text; }
 { EAStringC text("setFullYear"); bfmeObjDAE[131] = text; }
 { EAStringC text("setHours"); bfmeObjDAE[132] = text; }
 { EAStringC text("setMilliseconds"); bfmeObjDAE[133] = text; }
 { EAStringC text("setMinutes"); bfmeObjDAE[134] = text; }
 { EAStringC text("setMonth"); bfmeObjDAE[135] = text; }
 { EAStringC text("setRGB"); bfmeObjDAE[136] = text; }
 { EAStringC text("setSeconds"); bfmeObjDAE[137] = text; }
 { EAStringC text("setTime"); bfmeObjDAE[138] = text; }
 { EAStringC text("setTransform"); bfmeObjDAE[139] = text; }
 { EAStringC text("setUTCDate"); bfmeObjDAE[140] = text; }
 { EAStringC text("setUTCFullYear"); bfmeObjDAE[141] = text; }
 { EAStringC text("setUTCHours"); bfmeObjDAE[142] = text; }
 { EAStringC text("setUTCMilliseconds"); bfmeObjDAE[143] = text; }
 { EAStringC text("setUTCMinutes"); bfmeObjDAE[144] = text; }
 { EAStringC text("setUTCMonth"); bfmeObjDAE[145] = text; }
 { EAStringC text("setUTCSeconds"); bfmeObjDAE[146] = text; }
 { EAStringC text("setYear"); bfmeObjDAE[147] = text; }
 { EAStringC text("shift"); bfmeObjDAE[148] = text; }
 { EAStringC text("sin"); bfmeObjDAE[149] = text; }
 { EAStringC text("slice"); bfmeObjDAE[150] = text; }
 { EAStringC text("sort"); bfmeObjDAE[151] = text; }
 { EAStringC text("sortOn"); bfmeObjDAE[152] = text; }
 { EAStringC text("Sound"); bfmeObjDAE[153] = text; }
 { EAStringC text("splice"); bfmeObjDAE[154] = text; }
 { EAStringC text("split"); bfmeObjDAE[155] = text; }
 { EAStringC text("sqrt"); bfmeObjDAE[156] = text; }
 { EAStringC text("string"); bfmeObjDAE[157] = text; }
 { EAStringC text("substr"); bfmeObjDAE[158] = text; }
 { EAStringC text("substring"); bfmeObjDAE[159] = text; }
 { EAStringC text("super"); bfmeObjDAE[160] = text; }
 { EAStringC text("tan"); bfmeObjDAE[161] = text; }
 { EAStringC text("target"); bfmeObjDAE[162] = text; }
 { EAStringC text("TextFormat"); bfmeObjDAE[163] = text; }
 { EAStringC text("this"); bfmeObjDAE[164] = text; }
 { EAStringC text("toLowerCase"); bfmeObjDAE[165] = text; }
 { EAStringC text("toString"); bfmeObjDAE[166] = text; }
 { EAStringC text("toUpperCase"); bfmeObjDAE[167] = text; }
 { EAStringC text("true"); bfmeObjDAE[168] = text; }
 { EAStringC text("undefined"); bfmeObjDAE[169] = text; }
 { EAStringC text("undefKey"); bfmeObjDAE[170] = text; }
 { EAStringC text("unshift"); bfmeObjDAE[171] = text; }
 { EAStringC text("UTC"); bfmeObjDAE[172] = text; }
 { EAStringC text("xMax"); bfmeObjDAE[173] = text; }
 { EAStringC text("xMin"); bfmeObjDAE[174] = text; }
 { EAStringC text("XML"); bfmeObjDAE[175] = text; }
 { EAStringC text("yMax"); bfmeObjDAE[176] = text; }
 { EAStringC text("yMin"); bfmeObjDAE[177] = text; }
 if (!Rva0070B5D0Check()) {
  g_bfmeAptAssertAtE17734("CheckContent()","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\StringPool.cpp",0x104);
  if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
 }
 g_00E18368=(StringNode0070D9F0 **)g_aptPoolAllocator->allocBlock(bucketCount*4);
 memset(g_00E18368,0,bucketCount*4);
 g_00E1836C=bucketCount;
}

// Generated by tools/allowed_symbols.py for the sole folded predicate.
#pragma comment(linker, "/ALTERNATENAME:?rva006CD4A0@EAStringC@@QBE_NXZ=?hasData@AsciiString@@QBE_NXZ")
