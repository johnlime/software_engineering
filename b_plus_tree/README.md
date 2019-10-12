## 10/11 B+tree(insert)
Shifts and inserts a value onto a leaf.

`insert_in_leaf` function first finds an acceptable slot to
insert the value, shifts the prexisting values to the right
in order to make space for the new value, and finally inserts
the new value.

The following are some examples of the code running.
```
Key: 1
[1]
Key: 4
[1 4]
Key: 2
[1 2 4]
```
