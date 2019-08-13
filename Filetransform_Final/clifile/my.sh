#!/bin/bash

a=`md5sum $1`
echo "$a" >>md5.c
