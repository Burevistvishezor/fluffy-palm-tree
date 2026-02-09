
## Сборка и запуск
1. Клонируйте репозиторий:
```bash
git clone https://github.com/Burevistvishezor/fluffy-palm-tree.git
cd fluffy-palm-tree


mkdir build
cd build
cmake ..
make
./FluffyPalmTree

./bank_app
sqlite3 bank.db
SELECT * FROM accounts;
tree -L 2 fluffy-palm-tree
