import numpy as np
import time
import pdb
import pandas as pd

def matrix_vector_multiplication_version1(matrix,vector):
    #input should be 1 matrix and one vector
    result = []
    for i in range(len(matrix[0])): #this loops through columns of the matrix
        total = 0
        for j in range(len(vector)): #this loops through vector coordinates & rows of matrix
            total += vector[j] * matrix[i][j]
        result.append(total)
    return result

def main():
    n = 100
    info = []
    t_end = time.time() + 60 * 10
    while time.time() < t_end:
        operation_count = (2*n)**3
        start = time.time()
        a = matrix_vector_multiplication_version1(np.random.randint(2,size=(n,n)),np.random.randint(2,size = (n)))
        end = time.time()
        total_time_running = end - start
        flops = (operation_count/total_time_running)/1000000000
        info.append([n,operation_count,total_time_running,flops])
        n = n * 2
    file_info = pd.DataFrame(info,columns = ['Size n','Operation Count','Exection Time','Flops'])
    writer = pd.ExcelWriter('matrix__vector_multiplication_version1.xlsx', engine='xlsxwriter')
    file_info.to_excel(writer,sheet_name='welcome',index=False)
    writer.save()

if __name__ == '__main__':
    main()

    # python -m trace --trace matrix__vector_multiplication_version1.py >> matrix__vector_multiplication_version1.txt