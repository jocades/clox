#!/usr/bin/env bash

CMD="./lox"

for file in test/*; do
    if [ -f "$file" ]; then
        $CMD "$file" >/dev/null

        if [ $? -eq 0 ]; then
            echo -e "\033[32mOK\033[0m   | $(basename $file)"

        else
            echo -e "\033[31mFAIL\033[0m | $(basename $file)"
        fi
    fi
done