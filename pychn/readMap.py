#!/usr/bin/env python3
# coding: utf-8
import math
"""
created on 10/19/2017

based on ../chn/main.cpp

"""


def remove_symbol(source):
    """
    remove invalid character
    :para source: 源文件内容
    :returns: 格式化后的源文件内容
    """
    dest = ""
    invalid_character = "\t\r\n，。：；“‘”【】『』|=+-——（）*&……%￥#@！~·《》？/?<>,.;:'\"[]{}_)(^$!` \
                    abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"
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
    with open(file_name, 'r') as file_handler:
        return remove_symbol(file_handler.read())


def read_sentence(sentence, maps, max_len_word=6):
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


def read_source(source):
    """
    被空格分割的格式化的源文件，生成统计集合
    :para source: 被空格分割的格式化过的源文件
    :returns: 源文件生成的统计过频数的集合
    """
    sentence_list = source.split()
    maps = {}
    for sentence in sentence_list:
        read_sentence(sentence, maps, 2)
    return maps


def calc_freq(maps, length):
    """
    计算统计集合的词频
    :para maps: 统计集合
    :para length: 源文件总长度
    :returns: 计算出词频的统计集合
    """
    for key in maps.keys():
        maps[key][1] = maps[key][0] / length


def calc_condensation_degree(maps):
    """
    计算统计集合的凝聚程度
    :para maps: 统计集合
    :returns: 计算出凝聚程度的统计集合
    """
    for key in maps.keys():
        length_word = len(key)
        if length_word > 1:
            degs = []
            for index in range(1, length_word):
                degs.append(maps[key][1] / (maps[key[:index]]
                                            [1] * maps[key[index:]][1]))
            maps[key][2] = min(degs)


def calc_freedom_degree(maps):
    """
    计算统计集合的自由程度
    :para maps: 统计集合
    :returns: 计算出自由程度的统计集合
    """
    for key in maps.keys():
        beg_deg = 0
        end_deg = 0
        for beg in maps[key][4]:
            beg_value = 1 / len(maps[key][4])
            beg_deg -= math.log(beg_value) * beg_value
        for end in maps[key][5]:
            end_value = 1 / len(maps[key][5])
            end_deg -= math.log(end_value) * end_value
        maps[key][3] = min([beg_deg, end_deg])
    return maps


if __name__ == '__main__':
    SOURCE = read_file("test.txt")
    gather = read_source(SOURCE)
    # print(MAPS)
    LENGTH = len(SOURCE) - SOURCE.count(' ')
    calc_freq(gather, LENGTH)
    calc_condensation_degree(gather)
    gather = calc_freedom_degree(gather)
    for key, value in gather.items():
        print(key, value)
