# coding: utf-8

str = ',,,葡萄皮,,'

ls = str.split(',')
ls = list(filter(lambda x: x, ls))
print(ls)

