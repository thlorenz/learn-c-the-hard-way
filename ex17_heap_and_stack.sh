#!/usr/bin/env bash

set -e

make ex17_heap_and_stack
ex17_heap_and_stack test.db c

echo -- created empty db, listing
ex17_heap_and_stack test.db l

echo -- adding records
ex17_heap_and_stack test.db s 1 joe shmoe@g.com
ex17_heap_and_stack test.db s 2 huck finn@g.com
ex17_heap_and_stack test.db s 3 tom sawyer@g.com

echo -- added 3 records, listing
ex17_heap_and_stack test.db l

echo -- getting 1st record
ex17_heap_and_stack test.db g 1

echo -- finding huck
ex17_heap_and_stack test.db f huck

echo -- deleting 2nd record
ex17_heap_and_stack test.db d 2

echo -- finding huck
ex17_heap_and_stack test.db f huck

echo -- remaining records, listing
ex17_heap_and_stack test.db l

echo -- cleaning up
rm -f test.db ex17_heap_and_stack
