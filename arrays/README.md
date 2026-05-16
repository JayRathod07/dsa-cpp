# Arrays in Data Structures & Algorithms (DSA)

# What is an Array?

An array is a linear data structure that stores elements in **continuous memory locations**.

Example:

```cpp
int arr[5] = {1, 2, 3, 4, 5};
```

Here:

- `arr[0] = 1`
- `arr[1] = 2`
- `arr[2] = 3`
- `arr[3] = 4`
- `arr[4] = 5`

Arrays store data of the **same data type**.

---

# Real Life Example

Think about a classroom roll number list.

| Index | Student |
|------|------|
| 0 | Jay |
| 1 | Rahul |
| 2 | Amit |
| 3 | Priya |

Each student is stored at a fixed position (index).

---

# Properties of Array

## 1. Fixed Size

Array size is fixed after creation.

```cpp
int arr[5];
```

You cannot store more than 5 elements.

---

## 2. Continuous Memory

All elements are stored one after another in memory.

Because of this:

- Access is very fast
- Indexing works in O(1)

---

## 3. Same Data Type

All values must be same type.

Correct:

```cpp
int arr[5];
```

Wrong:

```cpp
int arr[5] = {1, "jay", 3};
```


# Types of Arrays

## 1. One Dimensional Array

```cpp
int arr[5] = {1,2,3,4,5};
```

---

## 2. Two Dimensional Array

```cpp
int arr[2][3] = {
    {1,2,3},
    {4,5,6}
};
```

Used in:

- Matrix problems
- Graphs
- Grid problems

---

# Advantages of Arrays

- Fast access using index
- Easy traversal
- Memory efficient
- Useful in searching and sorting

---

# Disadvantages of Arrays

- Fixed size
- Insertion and deletion are costly
- Cannot store different data types

---
