mkdir build
cd build
cmake ..
make
./bank_app
sqlite3 bank.db
SELECT * FROM accounts;
tree -L 2 fluffy-palm-tree
