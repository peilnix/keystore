# keystore
<p>
A simple password manager with ncurses interface.
All data is stored securely in an encrypted sqlite database.
</p>

<pre>
usage: keystore --db FILE
       keystore --add USER@HOST --comment COMMENT
       keystore --get USER@HOST
</pre>

The database layout is pretty simple since it has only
a single table.
<pre>
+---------------------------------------+
|                 keys                  |
+---------+---------+---------+---------+
| user    | host    | pass    | comment |
| VARCHAR | VARCHAR | VARCHAR | VARCHAR |
+---------+---------+---------+---------+
</pre>
