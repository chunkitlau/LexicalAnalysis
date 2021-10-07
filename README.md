# LexicalAnalysis

该项目是北京邮电大学计算机学院2021年秋季本科三年级《编译原理与技术》课程作业。

Github Repository Link [https://github.com/chunkitlau/LexicalAnalysis](https://github.com/chunkitlau/LexicalAnalysis)

## 题目：词法分析程序的设计与实现

## 实验内容：设计并实现 C 语言的词法分析程序，要求实现如下功能。

1. 可以识别出 C 语言编写的源程序中的每个单词符号，并以记号的形式输出每个单词符号。
2. 可以识别并跳过源程序中的注释。
3. 可以统计源程序中的语句行数、各类单词的个数、以及字符总数，并输出统计结果。
4. 检查源程序中存在的词法错误，并报告错误存在的位置。
5. 对源程序中出现的错误进行适当的恢复，使词法分析可以继续进行，对源程序进行一次扫描，即可检查并报告源程序中存在的所有词法错误。

## 实现要求：分别用以下两种方法实现

方法1：采用 C/C++ 作为实现语言，手工编写词法分析程序。

方法2：编写 LEX 源程序，利用 LEX 编译程序自动生成词法分析程序。

## 编译

Linux 环境下，在当前目录（LexicalAnalysis/）打开终端，输入命令：

```
mkdir build && make
```

## 运行

### 简单运行

编译后，Linux 环境下，在当前目录（LexicalAnalysis/）打开终端，输入命令：

```
./build/lexicalAnalysis
```

默认样例程序为 LexicalAnalysis/demo/hello.c 。

### 高级选项

编写 C 程序，将程序放置在 LexicalAnalysis/demo/ 目录下，若程序为filename.c，则输入命令：

```
./build/lexicalAnalysis -p filename
```

### 样例

在 LexicalAnalysis/demo/ 目录下提供样例程序：hello.c aPlusB.c helloError.c 三个样例程序，输入命令：

```
./build/lexicalAnalysis -p hello
```

```
./build/lexicalAnalysis -p aPlusB
```

```
./build/lexicalAnalysis -p helloError
```

分别运行三个样例程序。

## 文档

实验报告在 ./document/experimental report.md

## 版权

Copyright © 2021 Chunkit Lau. All rights reserved.