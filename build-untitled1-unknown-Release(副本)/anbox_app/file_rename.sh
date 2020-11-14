#!/bin/sh
# 查找路径 旧字符串 新字符串
find_path=$1 
old_str=$2
new_str=$3
echo "old_str:${old_str}"
echo "new_str:${new_str}"

if [ "$find_path" = "" ];then
    echo "error: findPath not null"
    echo "find_rename path old_str new_str"
    exit 1
fi

if [ "$old_str" = "" ];then
    echo "old_str is empty"
    exit 1
fi

for file in `find $find_path -name "*$old_str*" -type f | xargs -I{} ls {}`

do

# 特别注意查找的路径，请根据实际情况进行修改

#  echo $file  # 注释  用于查看 查找数据是否正确

  /bin/mv $file `echo $file | sed s#${old_str}#${new_str}#`   # 也可使用 /bin/mv
done
