# Test Repo for C files
This repository contains C example programs purposely crafted to help test and validate tools that **detect dangerous C functions** and **hard-coded secrets / credentials** in source code.

## Includes:
- secrets.c (contains three dummy keys)
- file1.c (unsafe string usage examples)
- file6.c (format-string example)
- other example C files for varied patterns

### Quick use:
1. Compile: gcc -Wall -o secrets secrets.c
2. Run: ./secrets

## What it tests:
- gets(), strcpy(), strcat(), sprintf() — buffer overflow risks
- printf(user_input) — format string risk
- Hard-coded API keys, tokens, SSH blocks

### Safety notes:
- All keys in this repo are fake/dummy.
- Do NOT commit real credentials. If leaked, rotate immediately.

### Fix suggestions:
- Use fgets, snprintf, printf("%s", input)
- Use environment variables or secret manager for real keys

## Organization:
- Put intentionally vulnerable examples under examples/vulns/
- Mark files with a warning comment at top
