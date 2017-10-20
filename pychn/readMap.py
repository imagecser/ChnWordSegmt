#!/usr/bin/env python3
# coding: utf-8
import math
import time
import collections
"""
created on 10/19/2017

based on ../chn/main.cpp

"""

paras = {
    "source_file": "sc.txt",
    "output_file": "sc.output",
    "max_word_length": 8
}


def remove_symbol(source):
    """
    remove invalid character
    :para source: 源文件内容
    :returns: 格式化后的源文件内容
    """
    dest = ""
    invalid_character = "\t\r\n，。：；“‘”【】『』|=+-—－（）*&……%￥#@！~·《》、？/?<>,.;:'\"[]{}_)(^$!` \
                    abcсdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"
    for char in source:
        if char in invalid_character:
            char = ' '
        dest += char
    return dest


def read_file(file_name):
    """
    read in file and formatted
    :para file_name: 源文件名
    :returns: 格式化后的文本
    """
    print("loading source file...")
    with open(file_name, 'r') as file_handler:
        return remove_symbol(file_handler.read())


def read_sentence(sentence, maps, max_len_word):
    """
    录入内容
    :para sentence: 单句
    :para max_len_word: 最大识别字符长度
    :returns: 词典，字串数据
    maps: {"字串": [频数, 频率, 凝聚程度, 自由程度, 前一字符, 后一字符], ...}
    """
    length = len(sentence)
    for start in range(length):
        for len_word in range(1, max_len_word + 1):
            if start + len_word < length + 1:
                word = sentence[start:start + len_word]
                if word in maps:
                    maps[word][0] += 1
                    if start > 0:
                        maps[word][4].append(sentence[start - 1])
                    if start + len_word < length:
                        maps[word][5].append(sentence[start + len_word])
                else:
                    maps[word] = [
                        1, 0, 1, 0,
                        [sentence[start - 1]] if start > 0 else [],
                        [sentence[start + len_word]] if start +
                        len_word < length else []
                    ]
    return maps


def read_source(source, max_len_word=2):
    """
    被空格分割的格式化的源文件，生成统计集合
    :para source: 被空格分割的格式化过的源文件
    :returns: 源文件生成的统计过频数的集合
    """
    print("loading file content...")
    setup = time.time()
    sentence_list = source.split()
    maps = {}
    for sentence in sentence_list:
        read_sentence(sentence, maps, max_len_word)
    print("time: %.4fs"%(time.time() - setup))
    return maps


def calc_freq(maps, length):
    """
    计算统计集合的词频
    :para maps: 统计集合
    :para length: 源文件总长度
    :returns: 计算出词频的统计集合
    """
    print("calculating word frequences...")
    for key in maps.keys():
        maps[key][1] = float(maps[key][0]) / length


def calc_condensation_degree(maps):
    """
    计算统计集合的凝聚程度
    :para maps: 统计集合
    :returns: 计算出凝聚程度的统计集合
    """
    print("calculating condensation degrees...")
    for key in maps.keys():
        length_word = len(key)
        if length_word > 1:
            ''' degs = []
            for index in range(1, length_word):
                div = 10000 * (maps[key[:index]][1] * maps[key[index:]][1])
                result = maps[key][1] / div
                degs.append(result) 
            maps[key][2] = min(degs)'''
            front_deg = maps[key][1] / \
                (maps[key[:1]][1] * maps[key[1:]][1] *10000)
            back_deg = maps[key][1] / \
                (maps[key[:-1]][1] * maps[key[-1:]][1] * 10000)
            maps[key][2] = min([front_deg, back_deg])


def calc_freedom_degree(maps):
    """
    计算统计集合的自由程度
    :para maps: 统计集合
    :returns: 计算出自由程度的统计集合
    """
    print("calculating freedom degrees...")
    for key in maps.keys():
        degs = []
        for index in range(4,6):
            deg = 0
            freq_counter = collections.Counter(maps[key][index])
            data_length = len(maps[key][index])
            for value in freq_counter.values():
                freq = float(value) / data_length
                deg -= math.log(freq) * freq
            degs.append(deg)
        maps[key][3] = min(degs)
    return maps


def filter_map(maps):
    """
    输出指定筛选结果
    :para maps:统计集合
    """
    result = {}
    print("filtering special condition...")
    for key, value in maps.items():
        if len(key) > 1 and value[2] > 0.0015 and value[3] > 2:
            result[key] = value
    ordered = {}
    for key, value in result.items():
        ordered[key] = [value[1], 122 * value[2], value[3]]
        # print(key + ": %.8f, %.2f, %.2f" % (value[1], value[2], value[3]))
    res = sorted(ordered.items(), key=lambda x: x[1][0])
    for item in res:
        yield(str(item[0]) + str(item[1]) + '\n')
    # ordered = [0]
    # for key, value in maps.items():
    #     ordered.append(value[3])
    # ordered = sorted(ordered)
    # for item in ordered:
    #    print(item)


def write_output(iter, file_name):
    """
    将筛选结果输出到指定文件
    :para iter: 筛选结果迭代器
    :para file_name: 输出文件名
    """
    with open(file_name, "w") as f:
        f.writelines(iter)
    f.close()


if __name__ == '__main__':
    SOURCE = read_file(paras["source_file"])
    GATHER = read_source(SOURCE, paras["max_word_length"])
    LENGTH = len(SOURCE) - SOURCE.count(' ')
    calc_freq(GATHER, LENGTH)
    calc_condensation_degree(GATHER)
    calc_freedom_degree(GATHER)
    OUTPUT_ITER = filter_map(GATHER)
    write_output(OUTPUT_ITER, paras["output_file"])
    # for key, value in gather.items():
    #     print(key, value)
