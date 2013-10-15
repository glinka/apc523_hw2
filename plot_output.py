import numpy as np
import matplotlib.pyplot as plt
import os

def get_data(filename, header_rows=1, **kwargs):
    path_to_file = os.path.realpath(filename)
    data = np.genfromtxt(path_to_file, delimiter=",", skip_header=header_rows, **kwargs)
    if header_rows > 0:
        f = open(path_to_file, "r")
        params_str = f.readline()
        params = get_header_data(params_str)
        f.close()
        print params
        return data, params
    else:
        return data

def make_filename(base_name, params, unique_id=''):
    filename = base_name
    for key in params.keys():
        filename = filename + '_' + key + '_' + str(params[key])
    if not unique_id:
        filename = filename + '_' + unique_id
    return filename

if __name__=="__main__":
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('input_files', nargs='+')
    args = parser.parse_args()
    #change after properly including header in data files
    for file in args.input_files:
        data = get_data(file, header_rows=0)
        fig = plt.figure()
        ax = fig.add_subplot(111)
        ax.plot(data)
        ax.set_xlabel("jacobi step")
        ax.set_ylabel("error")
        ax.set_yscale('log')
        ax.set_ylim((0.09, 1))
        ax.set_yticks((0.1, 0.3, 0.5, 0.7, 0.9, 1))
        ax.set_yticklabels((0.1, 0.3, 0.5, 0.7, 0.9, 1))
        plt.show()
        
        
