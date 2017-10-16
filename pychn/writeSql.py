# coding: utf-8
def read_map(filename):
    maps = {}
    with open('\\'.join(['..', 'chn', filename]), 'r') as f:
        parent_line = f.readline().split()
        print parent_line[0], parent_line[1]
        child_line = f.readline().split()
        for item in child_line:
            

if __name__ == '__main__':
    read_map("maps.txt")
