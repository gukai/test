#!/usr/bin/python
import sqlite3

conn=sqlite3.connect('userDB.db')
cur=conn.cursor()
print "----------------Before Change------------------"
cur.execute("select * from address")
res=cur.fetchall()
for line in res:
    print line

strUpdate=raw_input('please input the num of date which you want to modify: ')
strID = raw_input('please input the num of date which you want to delete:')

conn.execute("update address set name='maxinglin' where id="+strUpdate)
conn.execute("delete from address where id="+strID)
conn.commit()

print"--------------After Change-----------------------"
cur.execute("select * from address")
res=cur.fetchall()
for line in res:
    print line

cur.close()
conn.close()
