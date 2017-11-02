"""
created on 11/2/2017

"""
# coding: utf-8
from pipe_sql import *
from analyze import *
import os

rootdir = "files/"
l = []
i = 0
m = 0
for parent, dirname, filenames in os.walk(rootdir):
    for filename in filenames:
        source = read_file('files/' + filename)
        gather = {}
        gather = read_source(gather, source, 4)
        try:
            write_sql(gather)
            print(i)
            i += 1
            m += 1
        except:
            continue
        combine_sql()
