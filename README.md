Sudoku
------

A highly efficient sudoku-solving program, open sourced under MIT license.

### Input Sample

Input the sudoku however you want. Use 1 - 9 for known number, and 0/./? for unknown number.

**A Possible Valid Input**
~~~~
0 0 0 4 0 0 8 7 3
0 4 0 0 5 0 0 0 0
8 0 0 2 1 0 0 0 0
0 2 4 0 0 0 0 0 0
3 0 5 0 0 0 7 0 9
0 0 0 0 0 0 5 3 0
0 0 0 0 4 9 0 0 1
0 0 0 0 6 0 0 8 0
5 1 3 0 0 2 0 0 0
~~~~

Can also be inputed this way:

~~~~
0 ? ? 4 . 0 8 7 3
0 400 5 ? 0 0 0
8 0 0 2 1 0000
0 2 4 0 0 0 0 0 0 3 0 5 0 0 0 7 0 9
0 0 0sudoku is fun0lol?-0	5 3 0
0..049??1000060080513?.2.00
~~~~

### Performance

It uses avg 7 ms to solve evil-level problem sets generated on www.websudoku.com with a single-core 2.0GHz Skylake Xeon CPU.

More detailed testing results will be added in the future.
