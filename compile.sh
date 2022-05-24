clang++ \
  main.cpp \
  -Os \
  -std=c++11 \
  -o layout

if [ $? -eq 0 ]; then
  echo "Compiled :)"; echo
  if [ $# -eq 1 ] && [ $1 == "r" ]; then
    ./layout
  fi
fi
