# coding: utf-8
def read_map(filename):
    with open('\\'.join(['..', 'chn', filename]), 'r') as f:
        for line in f:
            