/*
* Copyright (c) 2009-2019 Brian Waters
* Copyright (c) 2019 Sprint
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "etypes.h"
#include "ehash.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

ULong EHash::getHash(EString &str)
{
   return getHash((cpUChar)str.c_str(), (ULong)str.length());
}

ULong EHash::getHash(cpChar val, ULong len)
{
   return getHash((cpUChar)val, len);
}

ULong EHash::getHash(cpUChar val, ULong len)
{
   ULong crc = 0xFFFFFFFF;

   for (ULong i = 0; i < len; i++)
   {
      UShort idx = (UShort)((crc ^ val[i]) & 0x000000FF);
      crc = ((crc >> 8) & 0x00FFFFFF) ^ m_crcTable[idx];
   }

   for (ULong i = len; i < 64; i++)
   {
      UShort idx = (UShort)((crc ^ 0) & 0x000000FF);
      crc = ((crc >> 8) & 0x00FFFFFF) ^ m_crcTable[idx];
   }

   return ~crc;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

ULong EHash::m_crcTable[] =
    {
        0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, //0x000
        0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3, //0x004
        0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988, //0x008
        0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91, //0x00C
        0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE, //0x010
        0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7, //0x014
        0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, //0x018
        0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5, //0x01C
        0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172, //0x020
        0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B, //0x024
        0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940, //0x028
        0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59, //0x02C
        0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, //0x030
        0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F, //0x034
        0x2902B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924, //0x038
        0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D, //0x03C
        0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A, //0x040
        0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433, //0x044
        0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, //0x048
        0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01, //0x04C
        0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E, //0x050
        0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457, //0x054
        0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C, //0x058
        0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65, //0x05C
        0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, //0x060
        0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB, //0x064
        0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0, //0x068
        0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9, //0x06C
        0x5505713C, 0x270241AA, 0xBE0B1010, 0xC90C2086, //0x070
        0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F, //0x074
        0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, //0x078
        0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD, //0x07C
        0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A, //0x080
        0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683, //0x084
        0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8, //0x088
        0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1, //0x08C
        0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, //0x090
        0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7, //0x094
        0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC, //0x098
        0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5, //0x09C
        0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252, //0x0A0
        0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B, //0x0A4
        0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60, //0x0A8
        0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79, //0x0AC
        0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236, //0x0B0
        0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F, //0x0B4
        0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04, //0x0B8
        0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D, //0x0BC
        0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, //0x0C0
        0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713, //0x0C4
        0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38, //0x0C8
        0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21, //0x0CC
        0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E, //0x0D0
        0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777, //0x0D4
        0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C, //0x0D8
        0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45, //0x0DC
        0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2, //0x0E0
        0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB, //0x0E4
        0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0, //0x0E8
        0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9, //0x0EC
        0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, //0x0F0
        0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF, //0x0F4
        0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94, //0x0F8
        0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D, //0x0FC
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

ESipHash24::Key ESipHash24::key_(
   (cUChar[]){0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}, 16
);

// UChar ESipHash24::key_[16] = {
//    0,  1,  2,  3,  4,  5,  6,  7,
//    8,  9, 10, 11, 12, 13, 14, 15
// };

ULong ESipHash24::getHash32(cpUChar in, size_t inlen, const Key &key)
{
   union
   {
      ULong val;
      UChar bytes[sizeof(val)];
   } result;

   getHalfHash(in, inlen, key.data(), result.bytes, sizeof(result.bytes));

   return result.val;
}

Bool ESipHash24::getHash32(cpUChar in, size_t inlen, pUChar out, const size_t outlen, const Key &key)
{
   return getHalfHash(in, inlen, key, out, outlen);
}

ULongLong ESipHash24::getHash64(cpUChar in, size_t inlen, const Key &key)
{
   union
   {
      ULongLong val;
      UChar bytes[sizeof(val)];
   } result;

   getHalfHash(in, inlen, key, result.bytes, sizeof(result.bytes));

   return result.val;
}

Bool ESipHash24::getHash64(cpUChar in, size_t inlen, pUChar out, const size_t outlen, const Key &key)
{
   return getHalfHash(in, inlen, key, out, outlen);
}

Bool ESipHash24::getHash128(cpUChar in, size_t inlen, pUChar out, const size_t outlen, const Key &key)
{
   return getFullHash(in, inlen, key, out, outlen);
}

#define ROTATELEFT_FULL(x, b) (uint64_t)(((x) << (b)) | ((x) >> (64 - (b))))
#define ROTATELEFT_HALF(x, b) (uint32_t)(((x) << (b)) | ((x) >> (32 - (b))))

#define SIP_ROUND_FULL                 \
    do {                               \
        v0 += v1;                      \
        v1 = ROTATELEFT_FULL(v1, 13);  \
        v1 ^= v0;                      \
        v0 = ROTATELEFT_FULL(v0, 32);  \
        v2 += v3;                      \
        v3 = ROTATELEFT_FULL(v3, 16);  \
        v3 ^= v2;                      \
        v0 += v3;                      \
        v3 = ROTATELEFT_FULL(v3, 21);  \
        v3 ^= v0;                      \
        v2 += v1;                      \
        v1 = ROTATELEFT_FULL(v1, 17);  \
        v1 ^= v2;                      \
        v2 = ROTATELEFT_FULL(v2, 32);  \
    } while (0)

#define SIP_ROUND_HALF                 \
    do {                               \
        v0 += v1;                      \
        v1 = ROTATELEFT_HALF(v1, 5);   \
        v1 ^= v0;                      \
        v0 = ROTATELEFT_HALF(v0, 16);  \
        v2 += v3;                      \
        v3 = ROTATELEFT_HALF(v3, 8);   \
        v3 ^= v2;                      \
        v0 += v3;                      \
        v3 = ROTATELEFT_HALF(v3, 7);   \
        v3 ^= v0;                      \
        v2 += v1;                      \
        v1 = ROTATELEFT_HALF(v1, 13);  \
        v1 ^= v2;                      \
        v2 = ROTATELEFT_HALF(v2, 16);  \
    } while (0)

#define SIP_ROUND_FULL_C   \
({                         \
   SIP_ROUND_FULL;         \
   SIP_ROUND_FULL;         \
})

#define SIP_ROUND_FULL_D   \
({                         \
   SIP_ROUND_FULL;         \
   SIP_ROUND_FULL;         \
   SIP_ROUND_FULL;         \
   SIP_ROUND_FULL;         \
})

#define SIP_ROUND_HALF_C   \
({                         \
   SIP_ROUND_HALF;         \
   SIP_ROUND_HALF;         \
})

#define SIP_ROUND_HALF_D   \
({                         \
   SIP_ROUND_HALF;         \
   SIP_ROUND_HALF;         \
   SIP_ROUND_HALF;         \
   SIP_ROUND_HALF;         \
})

Bool ESipHash24::getFullHash(cpUChar in, size_t inlen, cpUChar k, pUChar out, const size_t outlen)
{
   if (outlen != 16)
      throw ESipHash24Error_InvalidKeyLength();

   union
   {
      ULongLong val;
      UChar bytes[sizeof(val)];
   } k0, k1;

   for (int i=0; i<sizeof(k0.val); i++)
      k0.bytes[i] = k[i];

   for (int i=0; i<sizeof(k1.val); i++)
      k1.bytes[i] = k[sizeof(k1.val)+i];

   ULongLong v0 = 0x736f6d6570736575ull ^ k0.val;
   ULongLong v1 = 0x646f72616e646f6dull ^ k1.val;
   ULongLong v2 = 0x6c7967656e657261ull ^ k0.val;
   ULongLong v3 = 0x7465646279746573ull ^ k1.val;

   union
   {
      UChar bytes[128];
      struct
      {
         ULongLong low;
         ULongLong high;
      } u;
   } result = {0};
   
   union
   {
      ULongLong val;
      UChar bytes[sizeof(val)];
   } m;
   
   cpUChar end = in + inlen - (inlen % sizeof(ULongLong));
   const cInt left = inlen & 7;
   ULongLong b = ((ULongLong)inlen) << 56;

   v1 ^= 0xee;

   for (; in != end; in += 8)
   {
      m.bytes[0] = in[0];
      m.bytes[1] = in[1];
      m.bytes[2] = in[2];
      m.bytes[3] = in[3];
      m.bytes[4] = in[4];
      m.bytes[5] = in[5];
      m.bytes[6] = in[6];
      m.bytes[7] = in[7];

      v3 ^= m.val;

      SIP_ROUND_FULL_C;

      v0 ^= m.val;
   }

   switch (left)
   {
      case 7: b |= ((ULongLong)in[6]) << 48;
      case 6: b |= ((ULongLong)in[5]) << 40;
      case 5: b |= ((ULongLong)in[4]) << 32;
      case 4: b |= ((ULongLong)in[3]) << 24;
      case 3: b |= ((ULongLong)in[2]) << 16;
      case 2: b |= ((ULongLong)in[1]) << 8;
      case 1: b |= ((ULongLong)in[0]);
   }

   v3 ^= b;

   SIP_ROUND_FULL_C;

   v0 ^= b;

   v2 ^= 0xee;

   SIP_ROUND_FULL_D;

   result.u.low = v0 ^ v1 ^ v2 ^ v3;

   out[0] = result.bytes[0];
   out[1] = result.bytes[1];
   out[2] = result.bytes[2];
   out[3] = result.bytes[3];
   out[4] = result.bytes[4];
   out[5] = result.bytes[5];
   out[6] = result.bytes[6];
   out[7] = result.bytes[7];

   v1 ^= 0xdd;

   SIP_ROUND_FULL_D;
   
   result.u.high = v0 ^ v1 ^ v2 ^ v3;

   out[8] = result.bytes[8];
   out[9] = result.bytes[9];
   out[10] = result.bytes[10];
   out[11] = result.bytes[11];
   out[12] = result.bytes[12];
   out[13] = result.bytes[13];
   out[14] = result.bytes[14];
   out[15] = result.bytes[15];

   return True;
}

Bool ESipHash24::getHalfHash(cpUChar in, size_t inlen, cpUChar k, pUChar out, const size_t outlen)
{
   if (outlen != 4 && outlen != 8)
      throw ESipHash24Error_InvalidKeyLength();

   union
   {
      ULong val;
      UChar bytes[sizeof(val)];
   } k0, k1;

   for (int i=0; i<sizeof(k0.val); i++)
      k0.bytes[i] = k[i];

   for (int i=0; i<sizeof(k1.val); i++)
      k1.bytes[i] = k[sizeof(k1.val)+i];

   ULong v0 = 0 ^ k0.val;
   ULong v1 = 0 ^ k1.val;
   ULong v2 = 0x6c796765ul ^ k0.val;
   ULong v3 = 0x74656462ul ^ k1.val;

   union
   {
      ULongLong val;
      struct
      {
         ULong low;
         ULong high;
      } u;
      UChar bytes[sizeof(val)];
   } result;
   result.val = 0;
   
   union
   {
      ULong val;
      UChar bytes[sizeof(val)];
   } m;
   
   cpUChar end = in + inlen - (inlen % sizeof(ULong));
   const cInt left = inlen & 3;
   ULong b = ((ULong)inlen) << 24;

   if (outlen == 8)
      v1 ^= 0xee;

   for (; in != end; in += 4)
   {
      m.bytes[0] = in[0];
      m.bytes[1] = in[1];
      m.bytes[2] = in[2];
      m.bytes[3] = in[3];

      v3 ^= m.val;

      SIP_ROUND_HALF_C;

      v0 ^= m.val;
   }

   switch (left)
   {
      case 3: b |= ((ULong)in[2]) << 16;
      case 2: b |= ((ULong)in[1]) << 8;
      case 1: b |= ((ULong)in[0]);
   }

   v3 ^= b;

   SIP_ROUND_HALF_C;

   v0 ^= b;

   v2 ^= (outlen == 8) ? 0xee : 0xff;

   SIP_ROUND_HALF_D;

   result.u.low = v1 ^ v3;

   out[0] = result.bytes[0];
   out[1] = result.bytes[1];
   out[2] = result.bytes[2];
   out[3] = result.bytes[3];

   if (outlen == 4)
      return True;

   v1 ^= 0xdd;

   SIP_ROUND_HALF_D;
   
   result.u.high = v1 ^ v3;

   out[4] = result.bytes[4];
   out[5] = result.bytes[5];
   out[6] = result.bytes[6];
   out[7] = result.bytes[7];

   return True;
}