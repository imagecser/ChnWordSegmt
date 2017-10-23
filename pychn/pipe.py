#! python3
# coding: utf-8
"""
created on 10/23/2017

read & write sql

"""
import sqlalchemy
from sqlalchemy.ext.declarative import declarative_base
import analyze
import time
import pandas as pd

PARAS = {
    "table": "test"
}


class Word(declarative_base()):
    __tablename__ = PARAS['table']
    index = sqlalchemy.Column(sqlalchemy.Integer, primary_key=True)
    word = sqlalchemy.Column(sqlalchemy.String, default="")
    frequency = sqlalchemy.Column(sqlalchemy.BIGINT, default="")
    prefix = sqlalchemy.Column(sqlalchemy.String, default="")
    suffix = sqlalchemy.Column(sqlalchemy.String, default="")


def write_sql(maps):
    """
    将统计字典写入mysql
    存入数据结构的表结构：
    +-----------+--------+-----------+----------+----------+
    |  index  |  word  | frequency |  prefix  |  suffix  |
    +-----------+--------+-----------+----------+----------+
    :paras maps: 待写入统计集合
    """
    engine = sqlalchemy.create_engine(
        "mysql+pymysql://root:root@localhost/chn?charset=utf8", echo=True)
    engine.execute("create TABLE if not exists " + PARAS['table'] + "( \
                    id int AUTO_INCREMENT primary key, \
                    word text not null, \
                    frequency bigint not null, \
                    prefix longtext not null, \
                    suffix longtext not null) character set utf8; \
                   ")
    result_word = [item[0] for item in maps.items()]
    result_frequency = [value[0] for key, value in maps.items()]
    result_prefix = [','.join(value[4]) for key, value in maps.items()]
    result_suffix = [','.join(value[5]) for key, value in maps.items()]
    dataframe = pd.DataFrame({'word': result_word, 'frequency': result_frequency,
                              'prefix': result_prefix, 'suffix': result_suffix})
    dataframe.to_sql(PARAS['table'], engine, if_exists='append', index=False)


def read_sql():
    """
    从mysql读入未分析的统计字典
    :returns: 读入的统计字典
    """
    engine = sqlalchemy.create_engine(
        "mysql+pymysql://root:root@localhost/chn?charset=utf8", echo=True)
    dataframe = pd.read_sql(
        "SELECT word, frequency, prefix, suffix FROM " + PARAS['table'], engine)
    maps = {}
    for item in dataframe.itertuples():
        maps[item[1]] = [item[2], 0, 1, 0,
                         item[3].split(','), item[4].split(',')]
    return maps


def run():
    """
    template
    """
    GATHER = {}
    SOURCE = analyze.read_file(analyze.PARAS["source_file"])
    GATHER = analyze.read_source(GATHER, SOURCE, 4)
