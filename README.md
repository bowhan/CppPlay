# CppPlay
[![Build Status](https://travis-ci.org/bowhan/CppPlay.svg?branch=master)](https://travis-ci.org/bowhan/CppPlay)

## Introduction
This repository contains some of my codes to explore C++.

## Modules

### 1. Functional Programming with C++

```C++
#include "functional.hpp"

int add1(int k) { return k + 1; }

int mul2(int k) { return k * 2; }

int sub3(int k) { return k - 3; }

// 1
FP::Run(3, &add1, &mul2, &add1, &sub3); // (3+1)*2+1-3 = 6 

// 2
FP::Pipeline<int> math;
math.Register(&add1).Register(&mul2).Register(&add1).Register(&sub3);
math.Run(); // 6
```

### 2. A Generic Matrix class

```C++
#include "matrix.hpp"

nMatrix<int, 2, 3> mx1{1, 2, 3, 0, 5, 1};
nMatrix<int, 2, 3> mx2{2, 2, 2, 2, 2, 2} ;

auto mx3 = mx1 + mx2;
mx3(0, 0); // (2 + 1) == 3
mx3(1, 1); // (2 + 5) == 7

```
