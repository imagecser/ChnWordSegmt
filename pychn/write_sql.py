# coding: utf-8
import sqlalchemy
import sqlalchemy.orm
import sqlalchemy.ext.declarative


class Word(sqlalchemy.ext.declarative.declarative_base()):
    __tablename__ = 'map'
    id = sqlalchemy.Column(sqlalchemy.Integer, primary_key=True)
    key = sqlalchemy.Column(sqlalchemy.String(20))
    num = sqlalchemy.Column(sqlalchemy.Integer, default=0)


def read_map(filename):
    reading_map = []
    with open('\\'.join(['..', 'chn', filename]), 'r') as f:
        while True:
            parent_line = f.readline().split()
            if not parent_line:
                break
            child_line = f.readline().split()
            for i in xrange(0, len(child_line), 2):
                item = child_line[i: i + 2]
                reading_map.append({'key': ''.join([item[0], parent_line[0]]), 'num': int(item[1].replace(',', ''))})
    return reading_map


def write_sql(sum_map):
    db_engine = sqlalchemy.create_engine("mysql+mysqldb://root:root@localhost/chn?charset=gbk", echo=True)
    metadata = sqlalchemy.MetaData(db_engine)
    conn = db_engine.connect()
    table = sqlalchemy.Table('map', metadata,
                             sqlalchemy.Column('id', sqlalchemy.Integer, primary_key=True),
                             sqlalchemy.Column('key', sqlalchemy.String(20)),
                             sqlalchemy.Column('num', sqlalchemy.Integer, default=0)
                             )
    metadata.create_all()
    conn.execute(table.insert(), sum_map)
