# cping
linux 7 cping
## Build
1. git clone https://github.com/shokerplz/cping.git; cd cping;
2. docker build -t c7-cping .; docker run -it --mount type=bind,source="$(pwd)",target=/cping c7-cping bash;<br/>
   OR<br/>
   docker run -it --mount type=bind,source="$(pwd)",target=/cping c7-cping sh -c "g++ -std=c++11 main.cpp utils/*.cpp && ./a.out"<br/>
   And skip part 3
3. g++ -std=c++11 main.cpp utils/*.cpp

## TODO
1. Validation (WIP)
2. DNS resolving ✔
3. ICMP socket creating and sending ✔
4. ICMP answer getting and validating (getting ✔, validating WIP)
