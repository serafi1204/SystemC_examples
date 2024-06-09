# SystemC_examples

### Outline
- clk generator : a clk with auto GTKwave.

# Tips
## Project option for systemC
> {systemc} : root of systemc libray (ex. C:\visual_studio\systemc)

    project > Congifuration Properies > 
                                        VC++ Directories > 
                                                            include Diretories > add "{systemc}/src"
                                                            library Diretories > add "{systemc}/msvc16/SystemC/Debug"
                                        C/C++ > Commend Line > additional Option > add "/vmg /std:c++17"
                                        Linker > Input > Additional Dependencies > add "systemc.lib"
                                                            


## Build systemC
1. Open systemc-x.x.x\msvc16\SystemC\SystemC.sln
2. project > Congifuration Properies > C/C++ > Commend Line > additional Option > add "/std:c++17"
3. Build > Build Solution
