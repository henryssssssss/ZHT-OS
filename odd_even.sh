#!/bin/bash
# 判断输入整数是奇数还是偶数
read -p "请输入一个整数: " n
if [ $((n % 2)) -eq 0 ]; then
    echo "$n 是偶数"
else
    echo "$n 是奇数"
fi
