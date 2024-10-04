from datetime import datetime, timedelta
import pytz

# 定义常量
PER_SECOND = 52428800.0
PER_USECOND = PER_SECOND / 1.0e6

# 输入的时间戳
iiii = 72785507772504927  # 示例的时间戳

# 计算秒和微秒
seconds = int(iiii / PER_SECOND)
useconds = int((iiii / PER_USECOND) - seconds * 1.0e6)

# 基准时间为1980年1月6日，设定为UTC时区
epoch = datetime(1980, 1, 6, 0, 0, 0, tzinfo=pytz.UTC)

# 使用timedelta加上秒和微秒
delta = timedelta(seconds=seconds, microseconds=useconds)

# 计算最终时间
decoded_time = epoch + delta

# 如果需要转换到其他时区，比如美国东部时间
eastern = pytz.timezone('US/Eastern')
decoded_time_in_eastern = decoded_time.astimezone(eastern)

decoded_time_in_eastern
