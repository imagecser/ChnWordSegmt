#! python3
# coding: utf-8
import write_sql


if __name__ == '__main__':
    write_sql.write_sql(write_sql.read_map("maps.txt"))
