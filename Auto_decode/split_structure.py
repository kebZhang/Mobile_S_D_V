'''
完成切分工作
输入：一共有几种结构，每个结构有几个字节
输出：每一种结构输出到一个文件，decode结构+对应binary数据

以B0A1为例
Header: 22 Byte                     S1  
PDCP State: 16 Byte                 S2
Meta Log Buffer: 39 Byte            S3



'''



S1_start = "2024"
S1_len = 22

S2_start = "PDCP State"
S2_end = "Next Count"
S2_len = 16

S3_start = "Meta Log Buffer"
S3_end = "Number IP bytes"
S3_len = 39


import re

def format_binary_for_write(binary_str, bytes_per_line=8):
    # 每两个字符代表一个字节，因此每8字节为16字符
    grouped = [binary_str[i:i+2] for i in range(0, len(binary_str), 2)]
    # 将每8字节分为一行
    lines = [' '.join(grouped[i:i+bytes_per_line]) for i in range(0, len(grouped), bytes_per_line)]
    # 将各行用换行符连接
    return '\n'.join(lines)


def process_file(input_file, structure1_file, structure2_file, structure3_file):
    with open(input_file, 'r') as file:
        data = file.read()
        
    # divide message
    messages = re.split(r'(\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}\.\d{3} LTE PDCP DL Data PDU)', data)

    # include first line in divided message
    combined_messages = []
    combined_messages.append(messages[0].strip())  # include first line
    for i in range(1, len(messages), 2):
        combined_messages.append(messages[i] + messages[i + 1])  # 

    with open(structure1_file, 'w') as struct1, open(structure2_file, 'w') as struct2, open(structure3_file, 'w') as struct3:
        for message in combined_messages:
            '''
            Structure 1
            '''
            # 提取Structure1的数据部分（从第一个S1_start开头到S2_start）
            match_struct1 = re.search(r'(' + re.escape(S1_start) + r'.*?)(?=' + re.escape(S2_start) + ')', message, re.S)
            if match_struct1:
                struct1.write(match_struct1.group(1).strip() + "\n")
            
            # 提取二进制部分（匹配 Binary: 后的内容）
            match_binary = re.search(r'Binary:(.*?)$', message, re.S)
            if match_binary:
                binary_data = match_binary.group(1)
                # 逐行处理二进制数据，去除行号和解码信息
                cleaned_binary = ""
                for line in binary_data.strip().splitlines():
                    # 去除行号 (前四个字符) 和解码信息 (最后的非十六进制部分)
                    hex_part = re.sub(r'^.{4}\s+([0-9A-Fa-f\s]+)\s+.*$', r'\1', line)
                    # 移除所有空格
                    cleaned_binary += hex_part.replace(" ", "")
                
                # 处理 Structure1 的二进制部分
                first_22_bytes = cleaned_binary[:S1_len * 2]  # 22 * 2 表示前22个字节（每字节2个字符）
                formatted_bytes = format_binary_for_write(first_22_bytes)
                struct1.write(formatted_bytes + "\n\n")

                # 初始化 remaining_binary 为清理后的剩余二进制数据
                remaining_binary = cleaned_binary[22 * 2:]  # 去掉已处理的22字节
            else:
                # 如果没有匹配到二进制部分，初始化为空字符串
                remaining_binary = ""

            '''
            Structure 2
            '''
            # 提取S2_start 到 S3_start之间的数据 (Structure2)
            match_struct2 = re.search(r'(' + re.escape(S2_start) + r'.*?)(?=' + re.escape(S3_start) + ')', message, re.S)
            if match_struct2:
                state_data = match_struct2.group(1)
                # 提取每个 Structure2 的部分
                rb_matches = re.findall(fr'(\[\d+\].*?{S2_end} : \d+)', state_data, re.S)

                # 处理每个 Structure2 的文本和二进制部分
                for idx, rb_data in enumerate(rb_matches):
                    struct2.write(f"Structure2 Group [{idx}] \n{rb_data.strip()}\n")

                    if len(remaining_binary) >= S2_len * 2:
                        binary_length = S2_len * 2  # 每字节2个字符
                        binary_for_struct2 = remaining_binary[:binary_length]

                        formatted_bytes_2 = format_binary_for_write(binary_for_struct2)
                        struct2.write(formatted_bytes_2 + "\n\n")

                        remaining_binary = remaining_binary[binary_length:]
                    else:
                        struct2.write("Not enough binary data available for this Structure2\n\n")

            '''
            Structure 3
            '''
            # 提取S3_start 到Binary之间的数据 (Structure3)
            match_struct3 = re.search(fr'{S3_start}(.*?)Binary', message, re.S)
            if match_struct3:
                meta_log_buffer_data = match_struct3.group(1)
                # 提取每个 Structure3 的部分
                meta_matches = re.findall(fr'(\[\d+\].*?{S3_end} : \d+)', meta_log_buffer_data, re.S)

                # 处理每个 Structure3 的文本和二进制部分
                for idx, meta_data in enumerate(meta_matches):
                    # 将 Structure3 数据写入
                    struct3.write(f"Structure3 Group [{idx}] \n{meta_data.strip()}\n")

                    # 确保 remaining_binary 中有足够的数据可供处理
                    if len(remaining_binary) >= S3_len * 2:
                        binary_length = S3_len * 2  # 每字节2个字符
                        binary_for_struct3 = remaining_binary[:binary_length]

                        formatted_bytes_3 = format_binary_for_write(binary_for_struct3)
                        struct3.write(formatted_bytes_3 + "\n\n")

                        remaining_binary = remaining_binary[binary_length:]
                    else:
                        struct3.write("Not enough binary data available for this Structure3\n\n")

# 输入和输出文件路径
input_file = 'seperate_message/log_0xB0A1.txt'
structure1_file = 'split_structure/Structure1.txt'
structure2_file = 'split_structure/Structure2.txt'
structure3_file = 'split_structure/Structure3.txt'

# 处理文件
process_file(input_file, structure1_file, structure2_file, structure3_file)
