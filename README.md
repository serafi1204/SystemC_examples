# SystemC_examples

### List
- clk generator : a clk with auto GTKwave.
- Adder : adder block with clk, nrst, template(parameter)
    - r1 : using header(hpp)

# Examples
### 1. clk generator
    #define CLK_PERIOD 1 // 1ns
    #define CLK_TIME_UNIT 2 // 2 ns
    #define	CLK_DUTY_CYCLE 0.3 // 30%
<p align="center"><img src = "https://github.com/serafi1204/SystemC_examples/assets/122208990/61293010-8d1c-44dd-8ad6-cb50cd525ebc" width=60%></img></p>

### 2. Adder
<p align="center"><img src = "https://github.com/serafi1204/SystemC_examples/assets/122208990/6bc1b67d-05e1-4b8d-9ded-726d988b8aee" width=60%></img></p>
r1 (using header)
<p align="center"><img src = "https://github.com/serafi1204/SystemC_examples/assets/122208990/bd55421d-42fe-4f69-a7f0-de79b6387790" width=60%></img></p>


# Tips
### Build systemC
1. Open systemc-x.x.x\msvc16\SystemC\SystemC.sln
2. project > Congifuration Properies > C/C++ > Commend Line > additional Option > add "/std:c++17"
3. Build > Build Solution

### Project configuration for systemC
> {systemc} : root of systemc libray (ex. C:\visual_studio\systemc)

    project > Congifuration Properies > 
        VC++ Directories > 
            include Diretories > add "{systemc}/src"
            library Diretories > add "{systemc}/msvc16/SystemC/Debug"
        C/C++ > Commend Line > additional Option > add "/vmg /std:c++17"
        Linker > Input > Additional Dependencies > add "systemc.lib"

# Referance
- Examples
    - [clk generator](https://leehc257.tistory.com/72)
    - adder [0](https://funnyfab.tistory.com/2) [1](https://gtrfx.github.io/2020/02/16/systemc-basics.html) [2](https://leehc257.tistory.com/83)
- [Project option for systemC](https://www.youtube.com/watch?v=0VxvIzVdoaI&t=16s)
- [Build systemC](https://www.youtube.com/watch?v=0VxvIzVdoaI&t=16s)
