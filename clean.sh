#!/bin/bash

# 删除所有 .out 文件
find . -type f -name "*.out" -exec rm -f {} +

# 删除所有 build 目录
find . -type d -name "build" -exec rm -rf {} +

echo "清理完成！"
