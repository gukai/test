#!/usr/bin/python
import sqlite3

conn=sqlite3.connect('/home/gukai/sqlite-learning/userDB.db')
conn.execute("create table if not exists address(id integer primary key autoincrement, name varchar(128), address varchar(128))")
conn.execute("insert into address(name, address)values('dct','zhengzhou')")
conn.execute("insert into address(name, address)values('duanchunyang','beijingchaogyangqu')")
conn.commit()
cur=conn.cursor()
cur.execute("select * from address")
res=cur.fetchall()
for line in res:
    for f in line:
        print f

cur.close()
conn.close()

