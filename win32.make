#************************************************************************
# 公式库的Makefile(Windows版本).
# Copyright (C) 2022-2023 NULL_703. All rights reserved.
# Created on 2022.9.27  16:29
# Created by NULL_703
# Last change time on 2023.4.13  22:10
#*************************************************************************
cpp := g++
gc := gcc
cflag := -O2 -std=c99 -Wall -fexec-charset=GBK -s -I ./include
flag := -O2 -std=c++11 -Wall -fexec-charset=GBK -s -I ./include
obj := formulas.o functions.o network.o phyformula.o hextrs.o cpcolfunc.o shvector.o
lib := libformula.dll
res := libformula.o

all: $(lib)
	mkdir "./bin"
	move $(lib) "./bin"

$(lib): $(obj) $(res)
	$(gc) -shared $(cflag) $(obj) $(res) -o $(lib)

$(res): libformula.rc
	windres -i libformula.rc -o $(res)

%.o: %.c
	$(gc) -c $(cflag) -fPIC $<

.PHONY: clean
clean:
	del "*.o"
	del "./bin"
	rmdir "./bin"