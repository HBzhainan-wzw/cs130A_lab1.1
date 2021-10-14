#!/usr/bin/env bash


rm -rf .out_TEMP out
mkdir .out_TEMP


./main parameters/tiny.const datasets/0.data &> .out_TEMP/tiny-0.basic.out

./main parameters/tiny.const datasets/1.data &> .out_TEMP/tiny-1.basic.out

./main parameters/small.const datasets/47.data &> .out_TEMP/small-47.basic.out

./main parameters/large.const datasets/10000.data &> .out_TEMP/large-10000.basic.out
./main parameters/huge.const datasets/10000.data &> .out_TEMP/huge-10000.basic.out

./main parameters/large.const datasets/349900.data &> .out_TEMP/large-349900.basic.out
./main parameters/huge.const datasets/349900.data &> .out_TEMP/huge-349900.basic.out



./main parameters/tiny.const datasets/0.data queries/0.query &> .out_TEMP/tiny-0.query.out

./main parameters/tiny.const datasets/1.data queries/1.query &> .out_TEMP/tiny-1.query.out
./main parameters/small.const datasets/1.data queries/1.query &> .out_TEMP/small-1.query.out
./main parameters/large.const datasets/1.data queries/1.query &> .out_TEMP/large-1.query.out
./main parameters/huge.const datasets/1.data queries/1.query &> .out_TEMP/huge-1.query.out

./main parameters/small.const datasets/47.data queries/47.query &> .out_TEMP/small-47.query.out
./main parameters/large.const datasets/47.data queries/47.query &> .out_TEMP/large-47.query.out

./main parameters/large.const datasets/10000.data queries/10000.query &> .out_TEMP/large-10000.query.out
./main parameters/huge.const datasets/10000.data queries/10000.query &> .out_TEMP/huge-10000.query.out

./main parameters/large.const datasets/349900.data queries/349900.query &> .out_TEMP/large-349900.query.out
./main parameters/huge.const datasets/349900.data queries/349900.query &> .out_TEMP/huge-349900.query.out


mv .out_TEMP out
