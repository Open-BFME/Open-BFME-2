// ?rva0014DCC8@@YGXPAM@Z
// partial score=0.75 date=2026-10-06
// cl: /O1 /DNDEBUG /MD /arch:SSE
// VA 0x00DEC4F6 bit 3 (8) identity flag; VA 0x00DEE804 16-float source matrix.
unsigned char g_matrixIdentityFlag14DCC8;
float g_matrixSrc14DCC8[16];
void __stdcall rva0014DCC8(float *out) {
  volatile float tmp[16];
  if ((g_matrixIdentityFlag14DCC8 & 8) != 0) {
    out[0] = 1.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    out[3] = 0.0f;
    out[4] = 0.0f;
    out[5] = 1.0f;
    out[6] = 0.0f;
    out[7] = 0.0f;
    out[8] = 0.0f;
    out[9] = 0.0f;
    out[10] = 1.0f;
    out[11] = 0.0f;
    out[12] = 0.0f;
    out[13] = 0.0f;
    out[14] = 0.0f;
    out[15] = 1.0f;
  } else {
    tmp[0] = g_matrixSrc14DCC8[2];
    tmp[1] = g_matrixSrc14DCC8[6];
    tmp[2] = g_matrixSrc14DCC8[10];
    tmp[3] = g_matrixSrc14DCC8[14];
    tmp[4] = g_matrixSrc14DCC8[3];
    tmp[5] = g_matrixSrc14DCC8[7];
    tmp[6] = g_matrixSrc14DCC8[11];
    tmp[7] = g_matrixSrc14DCC8[15];
    out[1] = g_matrixSrc14DCC8[4];
    out[0] = g_matrixSrc14DCC8[0];
    out[2] = g_matrixSrc14DCC8[8];
    out[3] = g_matrixSrc14DCC8[12];
    out[4] = g_matrixSrc14DCC8[1];
    out[5] = g_matrixSrc14DCC8[5];
    out[6] = g_matrixSrc14DCC8[9];
    out[7] = g_matrixSrc14DCC8[13];
    out[8] = tmp[0];
    out[9] = tmp[1];
    out[10] = tmp[2];
    out[11] = tmp[3];
    out[12] = tmp[4];
    out[13] = tmp[5];
    out[14] = tmp[6];
    out[15] = tmp[7];
  }
}
