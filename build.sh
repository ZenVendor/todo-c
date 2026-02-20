#!/bin/bash
clang -lsqlite3 -o build/todo todo.c db.c parser.c
