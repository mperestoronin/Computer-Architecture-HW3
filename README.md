# Computer-Architecture-HW4
### Выполнил Пересторонин Максим БПИ 217 Вариант 22
Четвертое ДЗ по предмету "Архитектура вычислительных систем"
<br>Surprisingly, no assembler this time :)
## Общие сведения:
### Условье задачи:
```
Задача об инвентаризации по книгам. После нового года в библиотеке университета обнаружилась пропажа каталога.
После поиска и наказания, виноватых ректор дал указание восстановить каталог силами студентов.
Фонд библиотека представляет собой прямоугольное помещение, в котором находится M рядов по N шкафов по K книг в каждом шкафу.
Требуется создать многопоточное приложение, составляющее каталог.
При решении задачи использовать метод «портфель задач», причем в качестве отдельной задачи задается внесение в каталог записи
об отдельной книге.
Примечание.
Каталог — это список книг, упорядоченный по их инвентарному номеру или по алфавиту (на выбор разработчика).
Каждая строка каталога содержит идентифицирующее значение (номер или название), номер ряда, номер
шкафа, номер книги в шкафу.
```
### На чем написана программа?
Я использовал c++ 17, писал в Clion, которая использует g++
### Как работает ввод данных?
Для выбора режима работы программы необходимо ввести нужное количество аргументов командной строки:
<br>Вот как [я это делал](https://github.com/mperestoronin/Computer-Architecture-HW4/blob/main/commandlineArgs.md) в CLion.
<br>В зависимости от количества аргументов командной строки выбирается способ получения входных данных для работы программы.
* Если не вводить ни одного аргумента, то автоматически включится консольный ввод данных.
* Если предоставить один аргумент, то программа сгенерирует данные сама. Аргумент должен содержать имя файла, куда вы хотите записать результат работы программы.
* При вводе двух аргументов, программа войдет в режим ввода и вывода данных через файл. Первый аргумент - файл с входными данными, содержащий 3 числа, разделяемых пробелом - количество рядов, шкафов с книгами и непосредственно самих книг. Второй файл - файл для вывода данных. 
* Если же вы предоставите три входных параметра, то программа будет получать данные через командную строку. Сами параметры - это числа M N K строго в этом порядке, где M - кол-во рядов, N - кол-во шкафов в ряду и K - количество книг в шкафу.
### Что если ввести некорректные входные данные?
<br>В случае ввода неккоректных входных данных, программа досрочно завершит свою работу. Обычно программы разрешают пользователю повторно ввести данные, но поскольку здесь мы работаем с командной строкой и файлами, текущая реализация мне показалась лучшей.
### Входные данные
Если не считать имена файлов, описаных выше, входные данные представляют собой три положительных числа:
<br>M - кол-во рядов в библиотеке
<br>N - кол-во шкафов в каждом ряду библиотки
<br>K - кол-во книг в каждом шкафу
Вне зависимости от режима ввода, данные нужно вводить именно в этом порядке.


