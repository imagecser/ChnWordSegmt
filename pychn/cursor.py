#coding: utf-8
import sqlalchemy

engine = sqlalchemy.create_engine("mysql+pymysql://root:root@localhost/chn?charset=utf8")
res = engine.execute("select  word from out48;")
while True:
    word = res.fetchone()[0]
    print(word)
    row = "select * from out48 where word=\"" + word + "\";"
    if not res.fetchone()[0]:
        break
    engine.execute(row)
