"""
created on 11/1/2017

"""
# coding: utf-8
import json
import hashlib



with open('result.json', 'r', errors='ignore') as f:
    while True:
        line = str(f.readline())
        if len(line) == 0:
            break
        res = json.loads(line)
        m = hashlib.md5(line.encode())
        md5value = m.hexdigest()
        filename = res['url'].replace('.', '').replace('/', '').replace(':', '')
        with open('files/' +md5value, 'a') as fwrite:
            fwrite.write(res['content'])
