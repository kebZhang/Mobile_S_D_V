/*
generate diag cfg

input: logcode array
output: Diag.cfg

To easy the process, we manully assign the part of 
generate_header + disable_debug + disable + generate_end
We just need to finish the mask part
*/


#include "generate_diag_cfg.h"

int get_equip_id (int type_id) 
{
    const int EQUIP_ID_MASK = 0x0000F000;
    return (type_id & EQUIP_ID_MASK) >> 12;
}

int get_item_id (int type_id) 
{
    const int ITEM_ID_MASK  = 0x00000FFF;
    return type_id & ITEM_ID_MASK;
}

uint16_t calc_crc (uint8_t *data, size_t len, uint16_t crc)
{
    static const uint16_t table[256] = {
    0x0000U,0x1189U,0x2312U,0x329BU,0x4624U,0x57ADU,0x6536U,0x74BFU,
    0x8C48U,0x9DC1U,0xAF5AU,0xBED3U,0xCA6CU,0xDBE5U,0xE97EU,0xF8F7U,
    0x1081U,0x0108U,0x3393U,0x221AU,0x56A5U,0x472CU,0x75B7U,0x643EU,
    0x9CC9U,0x8D40U,0xBFDBU,0xAE52U,0xDAEDU,0xCB64U,0xF9FFU,0xE876U,
    0x2102U,0x308BU,0x0210U,0x1399U,0x6726U,0x76AFU,0x4434U,0x55BDU,
    0xAD4AU,0xBCC3U,0x8E58U,0x9FD1U,0xEB6EU,0xFAE7U,0xC87CU,0xD9F5U,
    0x3183U,0x200AU,0x1291U,0x0318U,0x77A7U,0x662EU,0x54B5U,0x453CU,
    0xBDCBU,0xAC42U,0x9ED9U,0x8F50U,0xFBEFU,0xEA66U,0xD8FDU,0xC974U,
    0x4204U,0x538DU,0x6116U,0x709FU,0x0420U,0x15A9U,0x2732U,0x36BBU,
    0xCE4CU,0xDFC5U,0xED5EU,0xFCD7U,0x8868U,0x99E1U,0xAB7AU,0xBAF3U,
    0x5285U,0x430CU,0x7197U,0x601EU,0x14A1U,0x0528U,0x37B3U,0x263AU,
    0xDECDU,0xCF44U,0xFDDFU,0xEC56U,0x98E9U,0x8960U,0xBBFBU,0xAA72U,
    0x6306U,0x728FU,0x4014U,0x519DU,0x2522U,0x34ABU,0x0630U,0x17B9U,
    0xEF4EU,0xFEC7U,0xCC5CU,0xDDD5U,0xA96AU,0xB8E3U,0x8A78U,0x9BF1U,
    0x7387U,0x620EU,0x5095U,0x411CU,0x35A3U,0x242AU,0x16B1U,0x0738U,
    0xFFCFU,0xEE46U,0xDCDDU,0xCD54U,0xB9EBU,0xA862U,0x9AF9U,0x8B70U,
    0x8408U,0x9581U,0xA71AU,0xB693U,0xC22CU,0xD3A5U,0xE13EU,0xF0B7U,
    0x0840U,0x19C9U,0x2B52U,0x3ADBU,0x4E64U,0x5FEDU,0x6D76U,0x7CFFU,
    0x9489U,0x8500U,0xB79BU,0xA612U,0xD2ADU,0xC324U,0xF1BFU,0xE036U,
    0x18C1U,0x0948U,0x3BD3U,0x2A5AU,0x5EE5U,0x4F6CU,0x7DF7U,0x6C7EU,
    0xA50AU,0xB483U,0x8618U,0x9791U,0xE32EU,0xF2A7U,0xC03CU,0xD1B5U,
    0x2942U,0x38CBU,0x0A50U,0x1BD9U,0x6F66U,0x7EEFU,0x4C74U,0x5DFDU,
    0xB58BU,0xA402U,0x9699U,0x8710U,0xF3AFU,0xE226U,0xD0BDU,0xC134U,
    0x39C3U,0x284AU,0x1AD1U,0x0B58U,0x7FE7U,0x6E6EU,0x5CF5U,0x4D7CU,
    0xC60CU,0xD785U,0xE51EU,0xF497U,0x8028U,0x91A1U,0xA33AU,0xB2B3U,
    0x4A44U,0x5BCDU,0x6956U,0x78DFU,0x0C60U,0x1DE9U,0x2F72U,0x3EFBU,
    0xD68DU,0xC704U,0xF59FU,0xE416U,0x90A9U,0x8120U,0xB3BBU,0xA232U,
    0x5AC5U,0x4B4CU,0x79D7U,0x685EU,0x1CE1U,0x0D68U,0x3FF3U,0x2E7AU,
    0xE70EU,0xF687U,0xC41CU,0xD595U,0xA12AU,0xB0A3U,0x8238U,0x93B1U,
    0x6B46U,0x7ACFU,0x4854U,0x59DDU,0x2D62U,0x3CEBU,0x0E70U,0x1FF9U,
    0xF78FU,0xE606U,0xD49DU,0xC514U,0xB1ABU,0xA022U,0x92B9U,0x8330U,
    0x7BC7U,0x6A4EU,0x58D5U,0x495CU,0x3DE3U,0x2C6AU,0x1EF1U,0x0F78U,
    };

    crc = crc ^ 0xFFFFU;
    while (len > 0)
    {
        crc = table[*data ^ (uint8_t)crc] ^ (crc >> 8);
        data++;
        len--;
    }
    crc = crc ^ 0xFFFFU;
    return crc;
}

char* encode_hdlc_frame(const char *payld, int length, int *hdlc_length) 
{
    uint16_t crc16 = calc_crc((uint8_t *)payld, length, 0);
    char *retstr = (char *)malloc(length * 2 + 4); // Allocating enough space
    int idx = 0;

    for (int i = 0; i < length + 2; i++) {
        char c;
        if (i < length)
            c = payld[i];
        else if (i == length)   // little endian
            c = crc16 & 0x00FF;
        else
            c = (crc16 & 0xFF00) >> 8;

        if (c == 0x7d || c == 0x7e) {
            retstr[idx++] = 0x7d;
            retstr[idx++] = c ^ 0x20;   // ESCAPE_XOR is 0x20
        } else {
            retstr[idx++] = c;
        }
    }
    retstr[idx++] = 0x7e;
    *hdlc_length = idx;
    printf("hdlc_length=%d\n",*hdlc_length);

    return retstr;
}


void generate_diag_cfg(uint16_t *logcode, int logcode_num)
{
    // printf("222\n");

    int equip_id = -1;
    int highest = 0;
    for(int i=0;i<logcode_num;i++)
    {
        int id = logcode[i];
        int e = get_equip_id(id);
        if (equip_id == -1) 
        {
            equip_id = e;
            highest = (highest > get_item_id(id)) ? highest : get_item_id(id);
        } 
        else if (equip_id == e) 
        {
            highest = (highest > get_item_id(id)) ? highest : get_item_id(id);
        } 
        else 
        {
            equip_id = -1;
            break;
        }
    }

    // printf("after equip_id %d\n", equip_id);

    switch (equip_id) 
    {
        case 0x00000001:    // CDMA, _1xEV, ......
            highest = 0x00000FD3;
            break;
        case 0x00000004:    // WCDMA, ......
            highest = 0x00000920;
            break;
        case 0x00000007:    // UMTS, ......
            highest = 0x00000B56;
            break;
        case 0x0000000b:    // LTE, ......
            highest = 0x00000FFF;
            //highest = 0x000001C4;
            break;
        default:
            break;
    }

    // printf("after highest %d\n", highest);

    int mask_len = (highest / 8) + 1;
    int buf_size = sizeof(char) * 4 + sizeof(int) * 3 + mask_len;
    char *buf = (char *)malloc(buf_size);
    buf[0] = 115; // 0x73
    buf[1] = 0;
    buf[2] = 0;
    buf[3] = 0;
    *((int *)(buf + 4)) = 3;
    *((int *)(buf + 8)) = equip_id;
    *((int *)(buf + 12)) = highest + 1;

    char *mask = buf + 16;
    memset(mask, 0, mask_len);
    for (int i = 0; i < logcode_num; i++) 
    {
        int id = logcode[i] & 0x0FFF;
        mask[id / 8] |= 1 << (id % 8);
    }

    // printf("buf content:\n");
    // for(int j=0;j<buf_size;j++)
    // {
    //     printf("%02X", buf[j]);
    // }
    // printf("\n");

    int hdlc_length = 0;
    char *mask_msg = encode_hdlc_frame(buf,buf_size, &hdlc_length);

    // printf("buf size=%d\n",buf_size);
    // printf("hdlc_length =%d\n",hdlc_length);

    FILE *file = fopen("Diag_ty.cfg", "wb+");
    char pre_msg[89]={0x1d,0x1c,0x3b,0x7e,0x00,0x78,0xf0,0x7e,0x7c,0x93,0x49,0x7e,0x1c,0x95,0x2a,0x7e,
                      0x0c,0x14,0x3a,0x7e,0x63,0xe5,0xa1,0x7e,0x4b,0x0f,0x00,0x00,0xbb,0x60,0x7e,0x4b,
                      0x09,0x00,0x00,0x62,0xb6,0x7e,0x4b,0x08,0x00,0x00,0xbe,0xec,0x7e,0x4b,0x08,0x01,
                      0x00,0x66,0xf5,0x7e,0x4b,0x04,0x00,0x00,0x1d,0x49,0x7e,0x4b,0x04,0x0f,0x00,0xd5,
                      0xca,0x7e,0x7d,0x5d,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x74,0x41,0x7e,0x73,0x00,
                      0x00,0x00,0x00,0x00,0x00,0x00,0xda,0x81,0x7e};

    for(int j=0;j<89;j++)
    {
        fprintf(file, "%c", pre_msg[j]);
    }

    // Write mask_msg to Diag.cfg file

    for(int j=0;j<hdlc_length;j++)
    {
        fprintf(file, "%c", mask_msg[j]);
    }

    char after_msg[5]={0x60,0x00,0x12,0x6a,0x7e};
    for(int j=0;j<5;j++)
    {
        fprintf(file, "%c", after_msg[j]);
    }

    free(buf);
    free(mask_msg);
    fclose(file);

}


// int main()
// {
//     int logcode_num=3;
//     uint16_t logcode[3]= {0xB173, 0xB063, 0xB064};
//     printf("111\n");
//     generate_diag_cfg(logcode,3);
// }