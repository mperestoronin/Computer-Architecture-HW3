# Результаты тестов:
**Примичание:** Программа выводит лог о проделанной работе в консоль, но не записывает его в файл, т.к. это бессмысленно. 
### тест № 1 консольный ввод:
Входные даннные: 3 3 3
<br>![](photos/tests1.png)
<br>![](photos/tests2.png)
<br>Вывод в файл:
<br>![](photos/tests3.png)
### тест № 2 файловый ввод:
Входные данные: 3 2 4
<br> Аргументы командной строки:
<br>![](photos/file1.png)
<br> Файл с входными данными
<br>![](photos/file4.png)
<br> Вывод результата работы программы в консоль. Обратите внимание, что программа распознала режим ввода и верно определила количество аргументов.
<br>![](photos/file2.png)
<br>![](photos/file3.png)
<br> Вывод результата работы программы в файл:
<br>![](photos/file5.png)
### тест № 3 ввод через аргументы командной строки:
Входные даннные: 2 5 2
<br> Аргументы командной строки:
<br>![](photos/cmd1.png)
<br> Вывод результата работы программы в консоль.
<br>![](photos/cmd2.png)
<br>![](photos/cmd3.png)
<br> Т.к. в этом режиме ввода, пользователь сразу не вводит файл для вывода данных, в конце работы программы, приложение спрашивает, желает ли пользователь записать данные в файл. Мы ввели имя файла для вывода, вот, что программа туда записала:
<br>![](photos/cmd4.png)
### тест № 4 рандомная генерация входных данных:
<br> Аргументы командной строки:
<br>![](photos/rnd1.png)
<br> Вывод результата работы программы в консоль.
<br>![](photos/rnd2.png)
<br>![](photos/rnd3.png)
<br>![](photos/rnd4.png)
<br>![](photos/rnd5.png)
<br> Вывод результата работы программы в файл:
<br>![](photos/rnd6.png)
<br>![](photos/rnd7.png)
### Что если ввести некорректные значения M N K?
<br>![](photos/wd.png)
### Вердикт
В ходе проверки использовались самые разные данные, программа корректно отработала во всех случаях со всеми режимами ввода. Вывод **католога** в консоль совпадает с выводом католога в файл (как уже писалось ранее, программа дополнительно выводит лог работы перед каталогом в консоль).
### Тестовые файлы
<br>тест1(https://github.com/mperestoronin/Computer-Architecture-HW4/blob/main/testfiles/test1output.txt)
<br>тест2 [input](https://github.com/mperestoronin/Computer-Architecture-HW4/blob/main/testfiles/test2input.txt) [output](https://github.com/mperestoronin/Computer-Architecture-HW4/blob/main/testfiles/test2output.txt)
<br>[тест3](https://github.com/mperestoronin/Computer-Architecture-HW4/blob/main/testfiles/test3output.txt)
<br>[тест4](https://github.com/mperestoronin/Computer-Architecture-HW4/blob/main/testfiles/test4output.txt)
<br>а также [тест](https://github.com/mperestoronin/Computer-Architecture-HW4/blob/main/testfiles/output.txt) на 1000 книг (входные данные 10 10 10)
