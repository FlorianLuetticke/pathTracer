#!/usr/bin/zsh

jq -s 'map(.[])' **/compile_commands.json > compile_commands.json