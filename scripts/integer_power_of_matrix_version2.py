import numpy as np
import time
from numpy.linalg import matrix_power
import pdb
import pandas as pd

def integer_power_of_matrix_version2(matrix_a,power):
    #input should be one matrix and an integer
    return matrix_power(matrix_a, power)

def main():
    n = 100
    info = []
    t_end = time.time() + 60 * 10
    while time.time() < t_end:
        operation_count = (2*n)**3
        start = time.time()
        a = integer_power_of_matrix_version2(np.random.randint(2,size=(n,n)),2)
        end = time.time()
        total_time_running = end - start
        flops = (operation_count/total_time_running)/1000000000
        info.append([n,operation_count,total_time_running,flops])
        n = n * 2
    file_info = pd.DataFrame(info,columns = ['Size n','Operation Count','Exection Time','Flops'])
    writer = pd.ExcelWriter('integer_power_of_matrix_version2.xlsx', engine='xlsxwriter')
    file_info.to_excel(writer,sheet_name='welcome',index=False)
    writer.save()

if __name__ == '__main__':
    main()

    # python -m trace --trace integer_power_of_matrix_version2.py >> integer_power_of_matrix_version2.txt