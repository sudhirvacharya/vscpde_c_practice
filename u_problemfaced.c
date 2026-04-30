
//problem faced in my project and how resolved
1. mcu was reseting due to divide by zero
    found reeset reason which line causing, in that line written /0 

2.due to adding nvm block, rcc clock reated test case failing, in nvm integrity check testcase

3. sw buil failing dude to no space in flash region, 
    solutuion:adjusted memory in linker from from other region, updated adress