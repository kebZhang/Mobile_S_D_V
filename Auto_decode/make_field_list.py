'''
对于structure的txt,拉一个list
对于每个field
如果是数值：记录他的最大值，最小值，值的种类数，每个种类分别是什么，最大值对应的bit数
不是数值：种类数，每个种类分别是什么
'''
import re
from collections import defaultdict

def process_file(input_file):
    # 使用defaultdict存储每个变量的所有值
    data_dict = defaultdict(list)
    
    # 打开并读取文件
    with open(input_file, 'r') as file:
        for line in file:
            # 查找冒号前的变量名和冒号后的值
            match = re.match(r'^(.*?):\s*(.*)$', line)
            if match:
                variable = match.group(1).strip()
                value = match.group(2).strip()
                
                # 跳过变量名为 "Timestamp" 或变量名以 "2024" 开头的行
                if variable == "Timestamp" or variable.startswith("2024"):
                    continue
            
                # 将值添加到变量对应的列表中
                data_dict[variable].append(value)
    
    # 处理数据并输出
    for variable, values in data_dict.items():
        print(f"Variable: {variable}")
        
        # 尝试将值转换为数字
        numeric_values = []
        for v in values:
            try:
                numeric_values.append(float(v))
            except ValueError:
                pass
        
        # 如果所有值是数字，计算最大值、最小值和种类数
        if numeric_values:
            print(f"  Max: {max(numeric_values)}")
            print(f"  Min: {min(numeric_values)}")
            print(f"  Num of Value: {len(set(numeric_values))}")
                
            # 转换最大值为二进制并输出其位数
            max_value_int = int(max(numeric_values))  # 将浮点数转换为整数
            max_value_bin = bin(max_value_int)  # 转换为二进制
            num_bits = len(max_value_bin) - 2  # 去掉 '0b' 前缀计算位数
            print(f"  Max value in binary: {max_value_bin} ({num_bits} bits)")
            
            for value in set(numeric_values):
                print(f"    - {value}")
        else:
            # 如果不是数字，输出种类数以及每种选项
            unique_values = set(values)
            print(f"  Num of non-numeric value: {len(unique_values)}")
            print("  Options:")
            for value in unique_values:
                print(f"    - {value}")

# 输入文件路径
input_file = 'split_structure/Structure3.txt'

# 处理文件
process_file(input_file)
