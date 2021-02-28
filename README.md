# cping
centos 7 cping
## Build
1. git clone https://github.com/shokerplz/cping.git; cd cping;
2. docker build -t c7-cping .; docker run -it --mount type=bind,source="$(pwd)",target=/cping c7-cping bash; OR docker run -it --mount type=bind,source="$(pwd)",target=/cping c7-cping sh -c "g++ main.cpp; ./a.out" And skip part 3
3. g++ main.cpp
