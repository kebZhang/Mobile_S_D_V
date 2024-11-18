import errno
import os
import stat
import struct
import subprocess
import sys
import threading
import time
import timeit

ANDROID_SHELL = "/system/bin/sh"
workplace_path="/data/data/Ty/workplace"
fifo_path = os.path.join(workplace_path, "diag_revealer_fifo")
executable_path = os.path.join(workplace_path, "diag_revealer")
diag_cfg_path = os.path.join(workplace_path, "Diag.cfg")
input_dir = os.path.join(workplace_path, "mi2log")
log_cut_size=0.5


class ChronicleProcessor(object):
    TYPE_LOG = 1
    TYPE_START_LOG_FILE = 2
    TYPE_END_LOG_FILE = 3
    READ_TYPE = 0
    READ_MSG_LEN = 1
    READ_TS = 2
    READ_PAYLOAD = 3
    READ_FILENAME = 4

    def __init__(self):
        self._init_state()

    def _init_state(self):
        cls = self.__class__
        self.state = cls.READ_TYPE
        self.msg_type = None
        self.bytes = [b"", b"", b"", b"", b""]
        # short, short, double, varstring, varstring
        self.to_read = [2, 2, 8, None, None]

    def process(self, b):
        cls = self.__class__
        ret_msg_type = self.msg_type
        ret_ts = None
        ret_payload = None
        ret_filename = None

        while len(b) > 0:
            if len(b) <= self.to_read[self.state]:
                self.bytes[self.state] += b
                self.to_read[self.state] -= len(b)
                b = b""
            else:
                idx = self.to_read[self.state]
                self.bytes[self.state] += b[0:idx]
                self.to_read[self.state] = 0
                b = b[idx:]
            # Process input data
            if self.state == cls.READ_TYPE:
                if self.to_read[self.state] == 0:  # current field is complete
                    self.msg_type = struct.unpack(
                        "<h", self.bytes[self.state])[0]
                    ret_msg_type = self.msg_type
                    self.state = cls.READ_MSG_LEN
            elif self.state == cls.READ_MSG_LEN:
                if self.to_read[self.state] == 0:  # current field is complete
                    msg_len = struct.unpack("<h", self.bytes[self.state])[0]
                    if self.msg_type == cls.TYPE_LOG:
                        self.to_read[cls.READ_PAYLOAD] = msg_len - 8
                        self.state = cls.READ_TS
                    elif self.msg_type in {cls.TYPE_START_LOG_FILE, cls.TYPE_END_LOG_FILE}:
                        self.to_read[cls.READ_FILENAME] = msg_len
                        self.state = cls.READ_FILENAME
                    else:
                        # raise RuntimeError("Unknown msg type %s" % str(self.msg_type))
                        print(("Unknown msg type %s" % str(self.msg_type)))
            elif self.state == cls.READ_TS:
                if self.to_read[self.state] == 0:  # current field is complete
                    ret_ts = struct.unpack("<d", self.bytes[self.state])[0]
                    self.state = cls.READ_PAYLOAD
            elif self.state == cls.READ_PAYLOAD:
                if len(self.bytes[self.state]
                       ) > 0:  # don't need to wait for complete field
                    ret_payload = self.bytes[self.state]
                    self.bytes[self.state] = b""
                if self.to_read[self.state] == 0:  # current field is complete
                    self._init_state()
                    break
            else:  # READ_FILENAME
                if self.to_read[self.state] == 0:  # current field is complete
                    ret_filename = self.bytes[self.state]
                    self._init_state()
                    break
        remain = b
        return ret_msg_type, ret_ts, ret_payload, ret_filename, remain
    

def mkfifo():
    try:
        if os.path.exists(fifo_path):
            # self._run_shell_cmd("rm %s " % fifo_path, wait=True)
            os.remove(fifo_path)
        os.mknod(fifo_path, 0o666 | stat.S_IFIFO)
        debug_file_in_decode = open('debug_file_in_decode.txt','a')
        debug_file_in_decode.write("diag revealer fifo make")
        debug_file_in_decode.close()
    except OSError as err:
        if err.errno == errno.EEXIST:  # if already exists, skip this step
            pass
            # print "Fifo file already exists, skipping..."
        elif err.errno == errno.EPERM:  # not permitted, try shell command
            # print "Not permitted to create fifo file, try to switch to
            # root..."
            debug_file_in_decode = open('debug_file_in_decode.txt','a')
            debug_file_in_decode.write("mkdido errno eperm")
            debug_file_in_decode.close()
            
            # retcode = self._run_shell_cmd(
            #     "mknod %s p" %
            #     fifo_path, wait=True)
            # if retcode is not None:
            #     raise RuntimeError("mknod returns %s" % str(retcode))
        else:
            raise err

def run_shell_cmd(cmd, wait=False):
    if isinstance(cmd, str):
        cmd = cmd.encode()
    p = subprocess.Popen(
        "su",
        executable=ANDROID_SHELL,
        shell=True,
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE)
    res, err = p.communicate(cmd + b'\n')
    # print("Running CMD: ", cmd)
    # print("RES:", res)
    # p.stdin.write(cmd+'\n')
    if wait:
        p.wait()
        # return p.returncode
        return res.decode()
    else:
        # return None
        return res.decode()
        
        

def start_diag_revealer(self):
    """
    Initialize diag_revealer with correct parameters
    """
    # TODO(likayo): need to protect against user input
    cmd = "%s %s %s" % (executable_path,diag_cfg_path,fifo_path)
    cmd += " %s %.6f" % (input_dir, log_cut_size)

    if os.path.exists(input_dir):
        run_shell_cmd(
            "chmod -R 777 \"%s\"" % input_dir, wait=True)

    run_shell_cmd("mkdir \"%s\"" % input_dir)
    run_shell_cmd("chmod -R 777 \"%s\"" % input_dir, wait=True)
    
    debug_file_in_decode = open('debug_file_in_decode.txt','a')
    debug_file_in_decode.write("Start diag revealer and running cmd: " + cmd + "\n")
    debug_file_in_decode.close()
    
    subprocess.Popen(
        "su -c " + cmd,
        executable=ANDROID_SHELL,
        shell=True,
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE)
            
            
            
def run():
    debug_file_in_decode = open('debug_file_in_decode.txt','w')
    debug_file_in_decode.write("enter run\n")
    debug_file_in_decode.close()
        
    try:
        mkfifo()
        start_diag_revealer()
        debug_file_in_decode = open('debug_file_in_decode.txt','a')
        debug_file_in_decode.write("Start diag revealer end\n")
        debug_file_in_decode.close()
        fifo = os.open(fifo_path, os.O_RDONLY)
        chproc = ChronicleProcessor()
        
        while 1:
            try:
                s = os.read(fifo, 64)
                debug_file_in_decode = open('debug_file_in_decode.txt','w')
                debug_file_in_decode.write("s read\n")
                debug_file_in_decode.close()
            except OSError as err:
                if err.errno == errno.EAGAIN or err.errno == errno.EWOULDBLOCK:
                    debug_file_in_decode = open('debug_file_in_decode.txt','w')
                    debug_file_in_decode.write("run while try error\n")
                    debug_file_in_decode.close()
                    s = None
                else:
                    raise err  # something else has happened -- better reraise
        
        
    except (KeyboardInterrupt, RuntimeError) as e:
        import traceback
        self.log_error(str(traceback.format_exc()))
        os.close(fifo)
        # proc.terminate()
        self._stop_collection()
        packet = DMLogPacket([])
        event = Event(timeit.default_timer(),
                        "sys_shutdown",
                        packet)
        self.send(event)
        sys.exit(str(traceback.format_exc()))
        # sys.exit(e)
    except Exception as e:
        import traceback
        self.log_error(str(traceback.format_exc()))
        os.close(fifo)
        # proc.terminate()
        self._stop_collection()
        packet = DMLogPacket([])
        event = Event(timeit.default_timer(),
                        "sys_shutdown",
                        packet)
        self.send(event)
        sys.exit(str(traceback.format_exc()))
        # sys.exit(e)