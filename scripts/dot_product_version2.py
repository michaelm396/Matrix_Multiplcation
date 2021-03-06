import numpy as np
import time
import pdb
import pandas as pd

def dot_product_version2(x,y):
    #input should be 2 vectors
    dot_product = np.array(x) @ np.array(y)
    return dot_product

def main():
    n = 100
    info = []
    t_end = time.time() + 60 * 10
    while time.time() < t_end:
        operation_count = (2*n)**3
        start = time.time()
        a = dot_product_version2(np.random.randint(2,size = (n)),np.random.randint(2,size = (n)))
        end = time.time()
        total_time_running = end - start
        flops = (operation_count/total_time_running)/1000000000
        info.append([n,operation_count,total_time_running,flops])
        n = n * 2
    file_info = pd.DataFrame(info,columns = ['Size n','Operation Count','Exection Time','Flops'])
    writer = pd.ExcelWriter('dot_product_version2.xlsx', engine='xlsxwriter')
    file_info.to_excel(writer,sheet_name='welcome',index=False)
    writer.save()

if __name__ == '__main__':
    main()

    # python -m trace --trace dot_product_version2.py >> dot_product_version2.txt