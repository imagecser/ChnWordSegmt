# coding: utf-8
import sqlalchemy

def update(i):
    i = int(i)
    engine = sqlalchemy.create_engine("mysql+pymysql://root:root@localhost/chn?charset=utf8", echo=True)
    engine.execute("create table in" + str(i) + " character set utf8 collate utf8_unicode_ci(select * from test limit " + str(i - 1) + "000000, 1000000);");
    engine.execute("create table com" + str(i) + "(select word, sum(frequency) as frequency, group_concat(prefix, ',') as prefix, group_concat(suffix, ',') as suffix from in"  + str(i) + " group by word);")
    engine.execute("insert into com" + str(i) + "(word, frequency, prefix, suffix) select word, frequency, prefix, suffix from out" + str(i -2) + ";")
    engine.execute("create table out" + str(i - 1) + "(select word, sum(frequency) as frequency, group_concat(prefix, ',') as prefix, group_concat(suffix, ',') as suffix from com" + str(i) + " group by word);")

def clean(i):
    i = int(i)
    engine = sqlalchemy.create_engine("mysql+pymysql://root:root@localhost/chn?charset=utf8", echo=True)
    engine.execute("delete from out" + str(i - 1) + " where char_length(word) > 2 and frequency = 1;");

for i in range(12, 40):
    update(i)
    if i % 3 == 0:
        clean(i)
