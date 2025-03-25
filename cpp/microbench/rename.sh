#!/bin/bash

find . -type f -name '*numThreads_16_*' -print0 | while IFS= read -r -d '' file; do
    # Получаем директорию и имя файла
    dir=$(dirname "$file")
    filename=$(basename "$file")
    
    # Удаляем все вхождения подстроки "numThreads_16_"
    newname=${filename//numThreads_16_/}
    
    # Переименовываем только если имя изменилось
    if [ "$newname" != "$filename" ]; then
        mv -v -- "$file" "$dir/$newname"
    fi
done