#! python3
# coding: utf-8
'''
created on 10/19/2017

based on ../chn/main.cpp

'''


def remove_symbol(source):
    '''
    remove invalid character
    :para source: 源文件内容
    :returns: 格式化后的源文件内容
    '''
    dest = ""
    invalid_character = "\t\r\n，。：；“‘”【】『』|=+-——（）*&……%￥#@！~·《》？/?<>,.;:'\"[]{}_)(^$!` \
                    abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"
    for char in source:
        if char in invalid_character:
            char = ' '
        dest += char
    return dest


def read_file(file_name):
    '''
    readin file and formatted
    :para file_name: 源文件名
    :returns: 格式化后的文本
    '''
    with open(file_name, 'r') as file_handler:
        return remove_symbol(file_handler.read())
    return ""


def read_sentence(sentence, maps, max_len_word=6):
    '''
    录入内容
    :para sentence: 单句
    :para max_len_word: 最大识别字符长度
    :returns: 词典，字串数据
    maps: {"字串": [频数, 频率, 凝固程度, 凝固程度*出现次数, 自由程度, 前一字符, 后一字符], ...}
    '''
    length = len(sentence)
    for start in range(length):
        for len_word in range(1, max_len_word + 1):
            if start + len_word < length + 1:
                word = sentence[start:start + len_word]
                if word in maps:
                    maps[word][0] += 1
                    if start > 0:
                        maps[word][5].append(sentence[start - 1])
                    if start + length < length:
                        maps[word][6].append(sentence[start + len_word])
                else:
                    maps[word] = [
                        1, 0, 1, 1, 0,
                        [sentence[start - 1]] if start > 0 else [],
                        [sentence[start + len_word]] if start +
                        len_word < length else []
                    ]
    return maps


def read_source(source):
    '''
    被空格分割的格式化的源文件，生成统计集合
    :para source: 被空格分割的格式化过的源文件
    :return: 源文件生成的统计过频数的集合
    '''
    sentence_list = source.split()
    maps = {}
    for sentence in sentence_list:
        maps = read_sentence(sentence, maps)
    return maps

