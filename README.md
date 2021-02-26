# keystore

A simple password manager with ncurses interface.
All data is stored securely in an encrypted sqlite database.

## Usage
       # Start keystore with default database ~/.keystore.db
       $ keystore
       
       # Start keystore with given database file
       $ keystore --db FILE
       
       # Add new key to database
       $ keystore --add USER@HOST --comment COMMENT
       
       # Get password by user and host
       $ keystore --get USER@HOST

## Database
The database layout is pretty simple since it has only
a single table.

       +---------------------------------------+
       |                 keys                  |
       +---------+---------+---------+---------+
       | user    | host    | pass    | comment |
       | VARCHAR | VARCHAR | VARCHAR | VARCHAR |
       +---------+---------+---------+---------+
