#include "decode.h"
#define PER_SECOND 52428800.0
#define PER_USECOND (PER_SECOND / 1.0e6)
FILE *debug_file_decode;
static const int ESCAPE_XOR = 0x20;


static unsigned short calc_crc (unsigned char *data, size_t len, unsigned short crc)
{
    static const short table[256] = {
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
        crc = table[*data ^ (unsigned char)crc] ^ (crc >> 8);
        data++;
        len--;
    }
    crc = crc ^ 0xFFFFU;
    return crc;
}

int unescape(char *ouput_frame, int output_frame_length)
{
    FILE *log_file_decode_unescape;
    // debug_file_decode = fopen("Ty_debug_file_decode.txt","a");
    // fprintf(debug_file_decode, "[unescape]  enter unescape\n");
    // fprintf(debug_file_decode, "[unescape]  output frame lenth=%d\n", output_frame_length);

    int esc = 0;
    size_t output_index = 0;

    for (size_t i = 0; i < output_frame_length; i++)
    {
        if (esc)
        {
            ouput_frame[output_index++] = ouput_frame[i] ^ ESCAPE_XOR;
            esc = 0;  
        }
        else if (ouput_frame[i] == '\x7d')
        {
            //log_file_decode_unescape = fopen("Log_file.txt","a+");
            //fprintf(log_file_decode_unescape, "Found 7d in %d\n", i);
            esc = 1;
            //fprintf(log_file_decode_unescape, "outframe length =%d\n", output_frame_length);
            //fclose(log_file_decode_unescape);

            // fprintf(debug_file_decode, "[unescape]  find 7d here in %d\n", i);
        }
        else
        {
            ouput_frame[output_index++] = ouput_frame[i];
        }
    }

    // clean unused
    for (size_t i = output_index; i < output_frame_length; i++)
    {
        ouput_frame[i] = 0; 
    }

    output_frame_length = output_index;

    // log_file_decode_unescape = fopen("Log_file.txt","a+");
    // fprintf(log_file_decode_unescape, "after esacpe\n");
    // for(int i=0;i<output_frame_length;i++)
    // {                        
    //     fprintf(log_file_decode_unescape, "%02X ", ouput_frame[i]);
    // }
    // fprintf(log_file_decode_unescape,"\n");
    // fclose(log_file_decode_unescape);

    return output_frame_length;
    // fclose(debug_file_decode);
}



int get_next_frame(char *buffer_read, char *output_frame, int msg_len, int first_msg_index, int *current_index, int *crc_correct, int *output_frame_length)
{
    //const char *debug_decode_filename = "Ty_debug_file_decode.txt";
    // debug_file_decode = fopen(debug_decode_filename,"a");
    // fprintf(debug_file_decode, "[get next frame]    enter get next frame fun\n");
    // fprintf(debug_file_decode, "[get next frame]    current_index=%d\n", *current_index);
    // fclose(debug_file_decode);
    FILE *log_file_decode;

    for(int i = *current_index; i < (first_msg_index + msg_len); i++)
    {
        // in case num_data=2 falthly recognize
        // 这里循环只能循环在你这个特定的num_data里面的数据，超过，否则会到下一个num_data里面去
        // if(*current_index-12>=msg_len)
        // {
        //     return 0;
        // }

        if(buffer_read[i]=='\x7e')
        {
            // log_file_decode = fopen("Log_file.txt","a+");
            // fprintf(log_file_decode, "Met 7e\n");
            // fclose(log_file_decode);

            // there is no 7e in output_frame
            *output_frame_length = i - *current_index ;

            // fprintf(debug_file_decode, "[get next frame]    output_frame_length=%d\n", *output_frame_length);
            // fclose(debug_file_decode);

            // log_file_decode = fopen("Log_file.txt","a+");
            // fprintf(log_file_decode, "output frame length = %d\n", *output_frame_length);
            // fprintf(log_file_decode, "*current_index = %d\n", *current_index);
            // fprintf(log_file_decode, "msg_len = %d\n", msg_len);
            // fprintf(log_file_decode, "Found a frame and output 1 Bytes more\n");
            // for(int j=0;j<(*output_frame_length+1);j++)
            // {
            //     fprintf(log_file_decode,"%02X ", buffer_read[*current_index+j]);
            // }
            // fprintf(log_file_decode,"\n");
            // fclose(log_file_decode);

            if (*output_frame_length >= msg_len) 
            {
                return 0;
            }
            if(*output_frame_length<=2)
            {
                *crc_correct=0;
                return 0;
            }
            memcpy(output_frame, &buffer_read[*current_index], *output_frame_length);

            // for(int k=*current_index; k<i+1; k++)
            // {
            //     buffer_read[k] = 0;
            // }

            // debug_file_decode = fopen(debug_decode_filename,"a");
            // for(int j=0; j< *output_frame_length; j++)
            // {
            //     fprintf(debug_file_decode, "%02X", (unsigned char)output_frame[j]);
            // }
            // fprintf(debug_file_decode, "\n");
            // fclose(debug_file_decode);

            *output_frame_length = unescape(output_frame, *output_frame_length);
            
            *current_index = i + 1;

            uint8_t b1 = output_frame[*output_frame_length-1] & 0xFF;
            uint8_t b2 = output_frame[*output_frame_length-2] & 0xFF;
            uint16_t frame_crc16 = (b1<<8)+b2;
            

            *output_frame_length -= 2;
            // output_frame[output_frame_length]='\0';

            unsigned short crc16 = calc_crc((unsigned char *)output_frame, *output_frame_length, 0);
            *crc_correct = (frame_crc16==crc16);

            // log_file_decode = fopen("Log_file.txt","a+");
            // fprintf(log_file_decode, "out_frame_length=%d\n", *output_frame_length);
            // fprintf(log_file_decode, "b1 = %02X\tb2 = %02X\tframe_crc16=%02X\t\n", b1,b2,frame_crc16);
            // fprintf(log_file_decode, "crc_correct = %d\n", (*crc_correct));
            // fclose(log_file_decode);

            if(*crc_correct==0)
            {
                log_file_decode = fopen("Log_file.txt","a+");
                fprintf(log_file_decode, "crc_correct fail\n");

                for(int k=0;k<(*output_frame_length+4);k++)
                {
                    fprintf(log_file_decode, "%02X ", output_frame[k]);
                }
                fprintf(log_file_decode,"\n");
                fclose(log_file_decode);
            }



            // debug_file_decode = fopen(debug_decode_filename,"a");
            // fprintf(debug_file_decode, " b1 = %d, b2 = %d\n", b1, b2);
            // fprintf(debug_file_decode, " find 7e in current index %d\n", *current_index);
            // fprintf(debug_file_decode, " crc is %d\n", *crc_correct);
            // fclose(debug_file_decode);

            return 1;
        }
    }
    // debug_file_decode = fopen(debug_decode_filename,"a");
    // fprintf(debug_file_decode, "no found\n");
    // fclose(debug_file_decode);
    return 0;
}

int check_frame_format(char *output_frame)
{
    const char prefix[] = "\x98\x01\x00\x00\x01\x00\x00\x00";
    size_t prefix_length = sizeof(prefix) - 1;
    if (memcmp(output_frame, prefix, prefix_length) == 0)
    {
        return 1;
    }
    return 0;
}

static double get_posix_timestamp1 ()
{
	struct timeval tv;
	(void) gettimeofday(&tv, NULL);
	return (double)(tv.tv_sec) + (double)(tv.tv_usec) / 1.0e6;
}

int find_pkt_type(char *output_frame, int start_index)
{
    if(output_frame[start_index]=='\x10')
    {
        return 1;//log pkt
    }
    else if(output_frame[start_index]=='\x79' || output_frame[start_index]=='\x92')
    {
        return 2;//debug pkt
    }
    else if(output_frame[start_index]=='\xee' && output_frame[start_index+1]=='\xee')
    {
        return 3;//custom pkt
    }
    else
    {
        return 0;
    }
}

void computer_timestamp(uint32_t t)
{
    // 基准时间 1980-01-06 00:00:00
    struct tm epoch = {0};
    epoch.tm_year = 1980 - 1900; // tm_year 从 1900 开始
    epoch.tm_mon = 0;            // 一月是 0
    epoch.tm_mday = 6;

    // 将基准时间转换为 time_t
    time_t epoch_time = mktime(&epoch);
    if (epoch_time == -1) {
        perror("mktime failed");
        return;
    }

    // 计算目标时间，将偏移量 t 加到基准时间
    time_t target_time = epoch_time + t;

    // 将目标时间转换为可读时间
    struct tm *result_time = localtime(&target_time);
    if (result_time == NULL) {
        perror("localtime failed");
        return;
    }

    FILE *debug_file_decode;
    debug_file_decode = fopen("Ty_debug_file_decode.txt","a");
    fprintf(debug_file_decode, "[decode header]     Date and Time: %04d-%02d-%02d %02d:%02d:%02d\n",
           result_time->tm_year + 1900,
           result_time->tm_mon + 1,
           result_time->tm_mday,
           result_time->tm_hour,
           result_time->tm_min,
           result_time->tm_sec);
    fclose(debug_file_decode);
}


void decode_header(char *output_frame, int start_index, uint64_t *msg_header)
{
    // debug_file_decode = fopen("Ty_debug_file_decode.txt","a");
    // fprintf(debug_file_decode, "[decode_header]    enter decode_header fun\n");
    

    int log_msg_len_start_index = start_index+2;
    uint16_t msglen_1 = (uint16_t)(output_frame[log_msg_len_start_index] & 0xFF);
    uint16_t msglen_2 = (uint16_t)(output_frame[log_msg_len_start_index+1] & 0xFF);
    uint16_t msg_len = (msglen_2<<8)+msglen_1;
    //fprintf(debug_file_decode, "[decode_header]    msg_len=%d\n", msg_len);

    int logcode_start_index = start_index+4;
    uint16_t logcode_1 = (uint16_t)(output_frame[logcode_start_index] & 0xFF);
    uint16_t logcode_2 = (uint16_t)(output_frame[logcode_start_index+1] & 0xFF);
    uint16_t logcode = (logcode_2<<8)+logcode_1;

    if(msg_len==0)
    {
        logcode=0;
    }
    // fprintf(debug_file_decode, "[decode_header]    logcode=%02X\n", logcode);
    // if(logcode==0xB063 || logcode == 0xB064 || logcode==0xB173)
    // {
    //     fprintf(debug_file_decode, "[decode_header]    logcode is %02X\n", logcode);
    //     fprintf(debug_file_decode, "[decode_header]    msglen is %d\n", (int)msg_len);
    //     if(msg_len==0)
    //     {
    //         fprintf(debug_file_decode, "[decode_header]    msg_len is 0!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    //     }
    // }



    int timestamp_start_index = start_index+6;
    uint64_t t_1 = (uint64_t)(output_frame[timestamp_start_index] & 0xFF);
    uint64_t t_2 = (uint64_t)(output_frame[timestamp_start_index+1] & 0xFF);
    uint64_t t_3 = (uint64_t)(output_frame[timestamp_start_index+2] & 0xFF);
    uint64_t t_4 = (uint64_t)(output_frame[timestamp_start_index+3] & 0xFF);
    uint64_t t_5 = (uint64_t)(output_frame[timestamp_start_index+4] & 0xFF);
    uint64_t t_6 = (uint64_t)(output_frame[timestamp_start_index+5] & 0xFF);
    uint64_t t_7 = (uint64_t)(output_frame[timestamp_start_index+6] & 0xFF);
    uint64_t t_8 = (uint64_t)(output_frame[timestamp_start_index+7] & 0xFF);

    uint64_t timestamp = ((t_8<<56)|(t_7<<48)|(t_6<<40)|(t_5<<32)|(t_4<<24)|(t_3<<16)|(t_2<<8)|t_1);
    int version = (output_frame[timestamp_start_index+8] & 0xFF);
    
    int B173_num_of_record = (output_frame[timestamp_start_index+9] & 0xFF);
    
    int B064_num_sample = (output_frame[timestamp_start_index+16] & 0xFF);
    int B064_subpkt_ver = (output_frame[timestamp_start_index+13] & 0xFF);
    int B139_num_record = (output_frame[timestamp_start_index+10] & 0xFE) >> 1;
    //fprintf(debug_file_decode, "[decode_header]    timestamp=%04X\n", timestamp);
    
    //fclose(debug_file_decode);


    msg_header[0]=0;
    msg_header[1]=0;
    msg_header[2]=0;
    msg_header[3]=0;
    msg_header[4]=0;

    msg_header[0]=msg_len;
    msg_header[1]=logcode;
    msg_header[2]=timestamp;

    if(logcode == 0xB173 && msg_len!=0)
    {
        msg_header[3]=version;
        msg_header[4]= B173_num_of_record;
    }
    else if(logcode == 0xB064 && msg_len!=0)
    {
        msg_header[3]= B064_subpkt_ver;
        msg_header[4]= B064_num_sample;
    }
    else if((logcode == 0xB139) && msg_len!=0)
    {
        msg_header[3]=version;
        msg_header[4]= B139_num_record;
    }
    else
    {
        msg_header[3]=version;
        msg_header[4]= 0;
    }


    //computer_timestamp(timestamp);
}

void decode(char *buffer_read, int msglen, int offset, int msglen_effect_time[2])
{
    msglen_effect_time[0]=0;//msg num
    msglen_effect_time[1]=0;//total msg len

    int success=1;
    int current_index = offset + 4 ;
    // record the first msg index in this num_data flow
    // control how many data should be checked 7e this time
    int first_msg_index = current_index;
    int crc_correct=1;
    
    // debug_file_decode = fopen("Ty_debug_file_decode.txt","a");
    // fprintf(debug_file_decode, "enter decode fun\n");
    // fprintf(debug_file_decode, "current_index = %d\n", current_index);
    // fclose(debug_file_decode);

    FILE *log_file_decode;
    FILE *crc_frame_pkt_msgh_check;
    int frame_num = 0;

    while(success)
    {
        //init output_frame 
        char output_frame[65536] = {};
        for(int k=0;k<msglen;k++)
        {
            output_frame[k]=0;
        }
        int output_frame_length=0;

        success = get_next_frame(buffer_read, output_frame, msglen, first_msg_index, &current_index, &crc_correct, &output_frame_length);
        int start_index=0;

        int crc_check = crc_correct;

        if(success && crc_correct)
        {
            int check_format = check_frame_format(output_frame);
            if(check_format)
            {
                // log_file_decode = fopen("Log_file.txt","a+");
                // fprintf(log_file_decode,"check_format pass\n");
                // fclose(log_file_decode);

                start_index+=8;
            }
            else
            {
                log_file_decode = fopen("Log_file.txt","a+");
                fprintf(log_file_decode,"check_format fail\n");
                fclose(log_file_decode);
            }
            int pkt_type = find_pkt_type(output_frame, start_index);
            start_index+=2;

            if(pkt_type==1)//log pkt
            {
                frame_num+=1;
                // log_file_decode = fopen("Log_file.txt","a+");
                // fprintf(log_file_decode,"pkt_type = %d, pass\n", pkt_type);
                // fclose(log_file_decode);

                uint64_t msg_header[5];

                decode_header(output_frame, start_index, msg_header);
                start_index+=14;

                // crc_frame_pkt_msgh_check = fopen("Check.txt","a+");
                // if(msg_header[1]==0xB16C)
                // {
                //     fprintf(crc_frame_pkt_msgh_check, "%d\t%d\t%d\t%02X\t%d\n", crc_check, check_format, pkt_type, msg_header[1], msg_header[0]);
                // }
                // fclose(crc_frame_pkt_msgh_check);

                if(msg_header[0]>0)
                {
                    //double t_pkt_after_crc_log = get_posix_timestamp1();
                    //fprintf(log_file_decode, "Userspace recognize and decode this Msg at %lf \n", (t_pkt_after_crc_log));

                    msglen_effect_time[0] +=1;
                    //msglen_effect_time[1] += msg_len;

                    uint64_t time_real = msg_header[2];
                    int second = (int)(time_real/PER_SECOND);
                    int usecond = (int)((time_real/PER_USECOND)-(second*1.0e6));

                    uint64_t time_in_us_total = (uint64_t)second * 1000000 + (uint64_t)usecond;
                    uint64_t time_in_us_1970 = time_in_us_total + 315928800000000;
                    int t1 = 1.0e6;
                    int second1 = time_in_us_1970/(t1);
                    int usecond1 = time_in_us_1970 % (t1);



                    log_file_decode = fopen("Log_file.txt","a+");
                    if(msg_header[1]==0xB173)
                    {
                        fprintf(log_file_decode, "This Msg is %02X: Msg_len = %d, logcode = %02X, timestamp in us from 1970 = %llu, version = %d, num of record = %d \n", 
                            msg_header[1], msg_header[0], msg_header[1], time_in_us_1970, msg_header[3], msg_header[4]);
                    }
                    else if(msg_header[1]==0xB064)
                    {
                        fprintf(log_file_decode, "This Msg is %02X: Msg_len = %d, logcode = %02X, timestamp in us from 1970 = %llu, Subpkt version = %d, num of sample = %d \n", 
                            msg_header[1], msg_header[0], msg_header[1], time_in_us_1970, msg_header[3], msg_header[4]);
                    }
                    else if(msg_header[1]==0xB139)
                    {
                        fprintf(log_file_decode, "This Msg is %02X: Msg_len = %d, logcode = %02X, timestamp in us from 1970 = %llu, version = %d, num of record = %d \n", 
                            msg_header[1], msg_header[0], msg_header[1], time_in_us_1970, msg_header[3], msg_header[4]);
                    }
                    else
                    {
                        fprintf(log_file_decode, "This Msg is %02X: Msg_len = %d, logcode = %02X, timestamp in us from 1970 = %llu, version = %d\n", 
                            msg_header[1], msg_header[0], msg_header[1], time_in_us_1970, msg_header[3]);
                    }
                    fclose(log_file_decode);

                    // log_file_decode = fopen("Log_file.txt","a+");
                    // fprintf(log_file_decode, "This Msg is %02X: Msg_len = %d, logcode = %02X, timestamp in us = %llu, version = %d \n", 
                    //     msg_header[1], msg_header[0], msg_header[1], time_in_us_total, msg_header[3]);
                    // fclose(log_file_decode);


                    // log_file_decode = fopen("Log_file.txt","a+");
                    // fprintf(log_file_decode, "This Msg is %02X\n", msg_header[1]);
                    // fclose(log_file_decode);

                    // 基准时间 1980-01-06
                    struct tm epoch = {0};
                    epoch.tm_year = 1980 - 1900; // 年份从1900开始计算
                    epoch.tm_mon = 1 - 1;        // 月份从0开始计数，1月为0
                    epoch.tm_mday = 5;
                    epoch.tm_hour = 14;
                    epoch.tm_min = 0;
                    epoch.tm_sec = 0;
                    // 将基准时间转换为 time_t 类型
                    time_t epoch_time = mktime(&epoch);
                    if (epoch_time == -1) {
                        printf("Error: Unable to convert epoch to time_t.\n");
                    }
                    // 增加秒数
                    epoch_time += second;
                    // 将时间转换为 struct tm
                    struct tm *final_time = gmtime(&epoch_time);
                    if (final_time == NULL) {
                        printf("Error: Unable to convert time to struct tm.\n");
                    }
                
                    /*print real time*/
                    log_file_decode = fopen("Log_file.txt","a+");
                    fprintf(log_file_decode, "Final datetime: %d-%02d-%02d %02d:%02d:%02d.%06d\n",
                        final_time->tm_year + 1900, final_time->tm_mon + 1, final_time->tm_mday,
                        final_time->tm_hour, final_time->tm_min, final_time->tm_sec, usecond);
                    fclose(log_file_decode);

                    /* Get the Android real time*/
                    // double time_now = get_posix_timestamp1();
                    // time_t seconds = (time_t)time_now;                // 整数部分为秒
                    // long microseconds = (long)((time_now - seconds) * 1e6); // 微秒部分
                    // // 转换为本地时间
                    // struct tm *local_time = localtime(&seconds);
                    // if (local_time == NULL) {
                    //     printf("Error: Unable to convert time to struct tm.\n");
                    //     return;
                    // }
                    // log_file_decode = fopen("Log_file.txt","a+");
                    // fprintf(log_file_decode,"Human-readable time: %04d-%02d-%02d %02d:%02d:%02d.%06ld\n",
                    //     local_time->tm_year + 1900,
                    //     local_time->tm_mon + 1,
                    //     local_time->tm_mday,
                    //     local_time->tm_hour,
                    //     local_time->tm_min,
                    //     local_time->tm_sec,
                    //     microseconds);
                    // fclose(log_file_decode);



                    /* Using the time_in_us_1970 to compute the real time from 1970 1 1 0 0*/
                    // struct tm epoch1 = {0};
                    // epoch1.tm_year = 1970 - 1900; // 年份从1900开始计算
                    // epoch1.tm_mon = 1 - 1;        // 月份从0开始计数，1月为0
                    // epoch1.tm_mday = 1;
                    // epoch1.tm_hour = 0;
                    // epoch1.tm_min = 0;
                    // epoch1.tm_sec = 0;
                    // // 将基准时间转换为 time_t 类型
                    // time_t epoch_time1 = mktime(&epoch1);
                    // if (epoch_time1 == -1) {
                    //     printf("Error: Unable to convert epoch to time_t.\n");
                    // }
                    // // 增加秒数
                    // epoch_time1 += second1;
                    // // 将时间转换为 struct tm
                    // struct tm *final_time1 = gmtime(&epoch_time1);
                    // if (final_time1 == NULL) {
                    //     printf("Error: Unable to convert time to struct tm.\n");
                    // }
                
                    // /*print real time*/
                    // log_file_decode = fopen("Log_file.txt","a+");
                    // fprintf(log_file_decode, "Final datetime in 1970: %d-%02d-%02d %02d:%02d:%02d.%06d\n",
                    //     final_time1->tm_year + 1900, final_time1->tm_mon + 1, final_time1->tm_mday,
                    //     final_time1->tm_hour, final_time1->tm_min, final_time1->tm_sec, usecond1);
                    // fclose(log_file_decode);



                    // fprintf(decode_file, "Final datetime: %d-%02d-%02d %02d:%02d:%02d.%06d\n",
                    //     final_time->tm_year + 1900, final_time->tm_mon + 1, final_time->tm_mday,
                    //     final_time->tm_hour, final_time->tm_min, final_time->tm_sec, usecond);
                    // fclose(decode_file);

                    uint16_t logcode_now = (uint16_t) msg_header[1];

                    /*decode library part*/

                    double t_before_decode_libarary = get_posix_timestamp1();
                    int decode_libarary = S_D_V_decode((uint8_t *)output_frame, 65536, logcode_now, &start_index, time_in_us_total, crc_check, check_format, pkt_type);
                    double t_after_decode_libarary = get_posix_timestamp1();

                    log_file_decode = fopen("Log_file.txt","a+");
                    fprintf(log_file_decode, "Decode Library using %lf for this MSG\n", (t_after_decode_libarary-t_before_decode_libarary));
                    fclose(log_file_decode);
                }
                
                
                // next we need the asn1 decode libaray here

                continue;
            }
            else
            {
                log_file_decode = fopen("Log_file.txt","a+");
                fprintf(log_file_decode,"pkt_type = %d, fail\n", pkt_type);
                fclose(log_file_decode);
                continue;
            }
        }
        else
        {
            continue;
        }
    }
    log_file_decode = fopen("Log_file.txt","a+");
    // fprintf(log_file_decode,"In this decode func, the frame Num = %d\n", frame_num);
    fclose(log_file_decode);
    //fclose(log_file_decode);
}