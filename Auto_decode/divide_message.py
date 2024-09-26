'''
这段代码的主要目的是根据logcode区分message
我们输入一个logcode,搜索所有的数据文件,将所有这种logcode的message提取到一个特定的文件中

修改log code
修改message type在文件中名称
修改输出文件名
'''
import os

# 函数用于处理单个文件
def process_file(input_file, output_file):
    with open(input_file, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    results = []  # 用于存储所有符合条件的片段

    # 从上向下遍历文件，找到所有Log Code : 0xB083
    for log_code_index in range(len(lines)):
        if 'Log Code : 0xB1B2' in lines[log_code_index]:
            pdu_index = None
            start_2024_index = None

            # 向上查找最近的包含LTE RLC DL AM Control PDU的行
            for i in range(log_code_index, -1, -1):
                if 'LTE ML1 Common DC Offset' in lines[i]:
                    pdu_index = i
                    break

            # 向下找最近以2024或2023开头的行
            if pdu_index is not None:
                for i in range(log_code_index, len(lines)):
                    if lines[i].startswith('2024') or lines[i].startswith('2023'):
                        start_year_index = i
                        break

            # 如果找到了PDU行和年开头的行，保存结果
            if pdu_index is not None and start_year_index is not None:
                results.append(lines[pdu_index:start_year_index])

    # 将所有符合条件的片段追加写入输出文件
    if results:
        with open(output_file, 'a', encoding='utf-8') as f:  # 以追加模式打开文件
            for result in results:
                f.write(''.join(result))  # 将每个结果写入文件
                f.write("\n")  # 添加换行符，分隔每个结果

# 处理目录中的所有txt文件
def process_directory(input_directories, output_file):
    for directory in input_directories:
        print(f"Processing directory: {directory}")  
        for filename in os.listdir(directory):
            if filename.endswith('.txt'):
                input_file = os.path.join(directory, filename)
                print(f"Processing file: {input_file}")
                process_file(input_file, output_file)

# 输入多个目录
input_directories = ['1_2_data', '1_3_data', '1_7_data', '1_9_data', '12_31', 'ngscope']  # 替换为你的多个输入目录
output_file = 'seperate_message/log_0xB1B2.txt'  # 替换为你的输出文件路径

process_directory(input_directories, output_file)
