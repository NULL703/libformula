#************************************************************************
# 公式库的Makefile.
# Copyright (C) 2022-2023 NULL_703. All rights reserved.
# Created on 2022.7.15  13:51
# Created by NULL_703
# Last change time on 2023.4.16  10:58
#*************************************************************************
cpp := g++
gc := gcc
cflag := -O2 -std=c99 -Wall -s -I ./include
flag := -O2 -std=c++11 -Wall -s -I ./include
obj := formulas.o functions.o network.o phyformula.o hextrs.o cpcolfunc.o shvector.o
lib := libformula.so

all: $(lib)
	mkdir ./bin
	mv $(lib) ./bin

$(lib): $(obj)
	$(gc) -shared $(cflag) $(obj) -o $(lib)

%.o: %.c
	$(gc) -c $(cflag) -fPIC $<

.PHONY: clean
clean:
	rm *.o
	rm -rf ./bin