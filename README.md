# Learner для планарного лабиринта
- Представляет из себя угадыватель регулярного языка, загаданного МАТом.
- Реализуется с помощью алгоритма L*
## Сборка и запуск Learner'а
### Сборка 
- Создадим папку сборки и перейдём в неё:
```bash
mkdir cmake-build-debug
cd cmake-build-debug
```
- Сделаем сборку файлов Makefile с помощью CMake:
```bash
make ..
```
- Сделаем сборку исполняемого файла:
```bash
make
```
### Запуск
- Запустим МАТ, генерирующий планарный лабиринт, например: https://github.com/RelictRLCT/labTFL/tree/lab2.
- Запуск Learner'а производится командой:
```bash
./Learner-RoFL 
```
## Взаимодействие с МАТом
- Запрос `"membership"` - POST на `*:8095/checkWord` в виде JSONа:

```json
{
    "word": "LRRLR"
}
```
В ответ от МАТа вернётся JSON
```json
{
    "response": true
}
```
(если строка принадлежит языку) или
```json
{
    "response": false
}
```
(если не принадлежит).
- Запрос `"equivalence"` - POST на `*:8095/checkTable` в виде JSONа:

```json
{
  "main_prefixes": "ε L R RL RR",
  "non_main_prefixes": "LL LR RLL RLR RRL RRR",
  "suffixes": "ε LRL RL L ", 
  "table": "1 0 0 0 0 0 1 0 1 0 0 0 0 0 1 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0"
}
```

Здесь `main_prefixes` - префиксы из основной части таблицы,

`non_main_prefixes` - префиксы из расширенной части таблицы,

`suffixes` - суффиксы,

`table` - таблица в виде строки - раскрыта по строкам. 

Если лабиринт МАТа имеет слова, которые не принадлежат языку
пользователя, то в ответ вернётся JSON, где в поле `type` лежит `true`, а в поле `response` - контрпример:

```json
{
    "type": true,
    "response": "LLR"
}
```
Если лабиринты эквивалентны, то вернется JSON с null'ами:

```json
{
    "type": null,
    "response": null
}
```
