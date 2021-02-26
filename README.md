# keystore
A simple password manager with ncurses interface.
All data is stored securely in an encrypted sqlite database.

[simple]
[secure]

usage: 
keystore --db FILE
keystore --add USER@HOST --comment COMMENT
keystore --get USER@HOST


The database layout is pretty simple since it has only
a single table.

+---------------------------------------+
|                 keys                  |
+---------+---------+---------+---------+
| user    | host    | pass    | comment |
| VARCHAR | VARCHAR | VARCHAR | VARCHAR |
+---------+---------+---------+---------+
