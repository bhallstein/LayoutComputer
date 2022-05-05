clang++ \
  main.cpp LayoutComputer/*.cpp \
  -Os \
  -I . \
  -std=c++11 \
  -o layout

if [ $? -eq 0 ]; then
  echo "Compiled successfully."; echo
  if [ $# -eq 1 ] && [ $1 == "r" ]; then
    ./layout
  fi
fi
