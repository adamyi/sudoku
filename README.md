Sudoku
------

A highly efficient sudoku-solving program, open sourced under [CC0 1.0 Universal License (Public Domain)](LICENSE.md).

### Input Sample

Input the sudoku however you want. Use 1 - 9 for known number, and 0/./? for unknown number.

**A Possible Valid Input**
~~~
0 0 0 4 0 0 8 7 3
0 4 0 0 5 0 0 0 0
8 0 0 2 1 0 0 0 0
0 2 4 0 0 0 0 0 0
3 0 5 0 0 0 7 0 9
0 0 0 0 0 0 5 3 0
0 0 0 0 4 9 0 0 1
0 0 0 0 6 0 0 8 0
5 1 3 0 0 2 0 0 0
~~~

Hmmm... The creepy way works as well:

~~~
0 ? ? 4 . 0 8 7 3
0 400 5 ? 0 0 0
8 0 0 2 1 0000
0 2 4 0 0 0 0 0 0 3 0 5 0 0 0 7 0 9
0 0 0sudoku is fun0lol?-0	5 3 0
0..049??1000060080513?.2.00
~~~

And there comes the magical result:

~~~
2 5 1	4 9 6	8 7 3
9 4 7	8 5 3	1 2 6
8 3 6	2 1 7	4 9 5

7 2 4	9 3 5	6 1 8
3 6 5	1 2 8	7 4 9
1 8 9	6 7 4	5 3 2

6 7 8	3 4 9	2 5 1
4 9 2	5 6 1	3 8 7
5 1 3	7 8 2	9 6 4

Used time: 1.938000 milliseconds.
~~~

### Performance

sudoku.fast.cpp utilyzes bitwise operations to optimize the speed, yet there could be some compilation errors using old operating systems and/or old compilers. It uses avg **2.0 ms** (compiled with G++ 6.3.0 with -O3 flag) / 3.8 ms (compiled with G++ 6.3.0 with -O0 flag) to solve **evil-level** problem sets generated on www.websudoku.com with Ubuntu 16.04 on a single-core 2.0GHz 64-bit Skylake Xeon CPU.

If you do encounter such errors, please compile using sudoku.legacy.cpp, which should be compatible with most of the OSs and compilers. It uses avg 3.0 ms (compiled with G++ 6.3.0 with -O3 flag) / 6.5 ms (compiled with G++ 6.3.0 with -O0 flag) to solve evil-level problem sets generated on www.websudoku.com with Ubuntu 16.04 on a single-core 2.0GHz 64-bit Skylake Xeon CPU.

More detailed testing results will be added in the future.

