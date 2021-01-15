import numpy as np
import time
from numpy.linalg import matrix_power
import pdb
import pandas as pd

from functools import wraps
import errno
import os
import signal

class TimeoutError(Exception):
    pass

def timeout(seconds=10, error_message=os.strerror(errno.ETIME)):
    def decorator(func):
        def _handle_timeout(signum, frame):
            raise TimeoutError(error_message)

        def wrapper(*args, **kwargs):
            signal.signal(signal.SIGALRM, _handle_timeout)
            signal.alarm(seconds)
            try:
                result = func(*args, **kwargs)
            finally:
                signal.alarm(0)
            return result

        return wraps(func)(wrapper)

    return decorator
@timeout(500)
def integer_power_of_matrix_version2(matrix_a,power):
    #input should be one matrix and an integer
    return matrix_power(matrix_a, power)

def main():
    n = 100
    info = []
    t_end = time.time() + 60 * 10
    #w = pd.ExcelWriter('integer_power_of_matrix_version2.xlsx', engine='xlsxwriter')
    with pd.ExcelWriter('integer_power_of_matrix_version2.xlsx', engine='xlsxwriter') as w:
        while time.time() < t_end:
            operation_count = (2*n)**3
            start = time.time()
            a = integer_power_of_matrix_version2(np.random.randint(2,size=(n,n),dtype='uint8'),2)
            end = time.time()
            total_time_running = end - start
            flops = (operation_count/total_time_running)/1000000000
            info.append([n,operation_count,total_time_running,flops])
            file_info = pd.DataFrame(info,columns = ['Size n','Operation Count','Exection Time','Flops'])
            file_info.to_excel(w)
            n = n * 2

if __name__ == '__main__':
    main()

    # python -m trace --trace integer_power_of_matrix_version2.py >> integer_power_of_matrix_version2.txt