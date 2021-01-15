import numpy as np
import time
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
def matrix_vector_multiplication_version2(matrix,vector):
    #input should be 1 matrix and one vector
    return np.dot(matrix,vector)

def main():
    n = 100
    info = []
    t_end = time.time() + 60 * 10
    #w = pd.ExcelWriter('matrix_vector_multiplication_version2.xlsx',engine='xlsxwriter')
    with pd.ExcelWriter('matrix_vector_multiplication_version2.xlsx', engine='xlsxwriter') as w:
        while time.time() < t_end:
            operation_count = (2*n)**3
            start = time.time()
            a = matrix_vector_multiplication_version2(np.random.randint(2,size=(n,n)),np.random.randint(2,size = (n)))
            end = time.time()
            total_time_running = end - start
            flops = (operation_count/total_time_running)/1000000000
            info.append([n,operation_count,total_time_running,flops])
            file_info = pd.DataFrame(info,columns = ['Size n','Operation Count','Exection Time','Flops'])
            file_info.to_excel(w)
            n = n * 2

if __name__ == '__main__':
    main()

    # python -m trace --trace matrix__vector_multiplication_version2.py >> matrix__vector_multiplication_version2.txt
