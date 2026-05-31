#!/usr/bin/env bash
set -euo pipefail

show_help() {
  cat <<EOF
Использование: $0 [--help] <путь/к/CMakeLists.txt>

Создаёт чистую директорию 'build' в текущей рабочей директории
и собирает CMake-проект из указанного CMakeLists.txt.

Аргументы:
  <путь/к/CMakeLists.txt>  Путь к CMakeLists.txt (может находиться где угодно)

Опции:
  --help, -h                Показать эту справку и выйти
EOF
}

if [ $# -eq 0 ] || [ "$1" = "--help" ] || [ "$1" = "-h" ]; then
  show_help
  exit 0
fi

cmakelists="$1"

if [ ! -f "$cmakelists" ]; then
  echo "Ошибка: файл не найден: $cmakelists" >&2
  exit 1
fi

rm -rf build
mkdir build
cmake -S "$(dirname "$cmakelists")" -B build
cmake --build build
