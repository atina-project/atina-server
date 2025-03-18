#!/bin/bash

set -e
while IFS= read -r package; do
    apt install -y "$package"
done < apt-packages.txt
