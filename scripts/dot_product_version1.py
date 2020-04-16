import numpy as np
import time
import pdb
import pandas as pd

## Create 2 dot product implemention. One that uses libraries and one that does not
def dot_product_version1(x, y):
    #input should be 2 vectors
    """Dot product as sum of list comprehension doing element-wise multiplication"""
    return sum(x_i*y_i for x_i, y_i in zip(x, y))

def main():
    n = 100
    info = []
    t_end = time.time() + 60 * 10
    while time.time() < t_end:
        operation_count = (2*n)**3
        start = time.time()
        a = dot_product_version1(np.random.randint(2,size = (n)),np.random.randint(2,size = (n)))
        end = time.time()
        total_time_running = end - start
        flops = (operation_count/total_time_running)/1000000000
        info.append([n,operation_count,total_time_running,flops])
        n = n * 2
    file_info = pd.DataFrame(info,columns = ['Size n','Operation Count','Exection Time','Flops'])
    writer = pd.ExcelWriter('dot_product_version1.xlsx', engine='xlsxwriter')
    file_info.to_excel(writer,sheet_name='welcome',index=False)
    writer.save()

if __name__ == '__main__':
    main()

# python -m trace --trace dot_product_version1.py >> dot_product_version1.txt
