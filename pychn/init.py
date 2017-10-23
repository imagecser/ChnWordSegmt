"""
created on 10/23/2017

start here

"""
#! python3
# coding: utf-8
import pipe
import analyze

PARAS = {
    'source_file': 'sc.txt',
    'output_file': 'sc.output',
    'max_word_length': 8,
    'table': 'test'
}

switch_list = {
    'pipe.read_sql',
    'pipe.write_sql',
    'analyze.read_file',
    'analyze.read_source',
    'analyze.calc_freq',
    'analyze.calc_condensation_degree',
    'analyze.calc_freedom_degree'
}

if __name__ == '__main__':
    pass
    