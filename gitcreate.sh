#!/bin/bash

# https://gist.github.com/robwierzbowski/5430952/
# Create and push to a new github repo from the command line.  
# Grabs sensible defaults from the containing folder and `.gitconfig`.  
# Refinements welcome.

# Gather constant vars
CURRENTDIR=${PWD##*/}

curl -u 'dan13ram' https://api.github.com/user/repos -d "{\"name\":\"${CURRENTDIR}\"}"
git init
echo "#${CURRENTDIR}" >> README.md
git add .
git commit -m "First Commit"
git remote add origin https://github.com/dan13ram/${CURRENTDIR}.git
git push --set-upstream origin master
