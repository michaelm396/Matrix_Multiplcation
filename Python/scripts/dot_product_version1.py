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

## Create 2 dot product implemention. One that uses libraries and one that does not
@timeout(500)
def dot_product_version1(x, y):
    #input should be 2 vectors
    """Dot product as sum of list comprehension doing element-wise multiplication"""
    return sum(x[i]*y[i] for i in range(len(y)))
    #return sum(x_i*y_i for x_i, y_i in zip(x, y))

def main():
    n = 100
    info = []
    t_end = time.time() + 60 * 10
    #w = pd.ExcelWriter('dot_product_version1.xlsx', engine='xlsxwriter')
    with pd.ExcelWriter('dot_product_version1.xlsx', engine='xlsxwriter') as w:
        while time.time() < t_end:
            operation_count = (2*n)**3
            start = time.time()
            a = dot_product_version1(np.random.randint(2,size = (n),dtype='uint8'),np.random.randint(2,size = (n),dtype='uint8'))
            end = time.time()
            total_time_running = end - start
            flops = (operation_count/total_time_running)/1000000000
            info.append([n,operation_count,total_time_running,flops])
            file_info = pd.DataFrame(info, columns = ['Size n','Operation Count','Exection Time','Flops'])
            file_info.to_excel(w)
            n = n * 2
    #w.save()
if __name__ == '__main__':
    main()

# python -m trace --trace dot_product_version1.py >> dot_product_version1.txt
