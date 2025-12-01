**The path can be checked by adding the following code to main after the call to CreatMatrix().**

```c++
for(int i=0; i<(int)_matrix.size(); i++) {
    for(int j=0; j<(int)_matrix[i].size(); j++) {
        if (_matrix[i][j]) printf("\x1b[41m");
        cout << ".";
        if (_matrix[i][j]) printf("\x1b[40m");
    }
    cout << endl;
}
```
**Colours can be by changing the 1st printf(path colour) or 2nd printf(default colour)**
**Here´s a list of some ANSI Colour Codes:** https://talyian.github.io/ansicolors/

**The output will be something like:**

![Alt text](https://github.com/Dacops/AoC/blob/main/AoC_22/Day_9/Matrix.png)
