# Explanation of some Algorithms

## > evaluateInput()
**With score combinations given as:**

$$
\begin{matrix}
score&A&B&C\\
X&3&0&6\\
Y&6&3&0\\
Z&0&6&3\\
\end{matrix}
$$

**This can be expressed with the function:**
* `line - column=0 => score=3.`
* `line - column=1 => score=6.`
* `line - column=2 => score=0.`

`If line - column < 0, %3 can be used to get the pretended result once in x%3 x can't be negative we add a value 'a', such that (a+x)%3 where 'a' doesn't change the pretended result (a%3 = 0).`

`It was chosen the value of 3 for this matrix since there's no values smaller than -3 given by the formula line - column.`

**Finally the lines can be given as lines X, Y, Z and columns as columns
A, B, C, these can be given as ASCII calculations.**
* `Line can be get by subtracting the current line by X.`
* `Column can be get by subtracting the current column by A.`

**Score by play X=1point, Y=2points, Z=3points can be get in a similar way.**
* `Score equals played move minus 1 (X-1).`

## > changeInput()
**Losing:**
`Given a vector: `

$$
\begin{pmatrix}
played:&rock&paper&scissors&\\
return:&scissors&rock&paper&\\
\end{pmatrix}
$$

`Losing is equal to increasing the index of the vector by 2 % 3. Once the vector only has 3 Values we can use -1 % 3 instead.`

**Drawing:**
`Given a vector: `

$$
\begin{pmatrix}
played:&rock&paper&scissors&\\
return:&rock&paper&scissors&\\
\end{pmatrix}
$$

`Drawing is equal to returning the same vector index.`

**Losing:**
`Given a vector: `

$$
\begin{pmatrix}
played:&rock&paper&scissors&\\
return:&paper&scissors&rock&\\
\end{pmatrix}
$$

`Winning is equal to increasing the index of the vector by 1 % 3.`
