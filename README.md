# Five-Staged RISCV Simulator
  在串行版本上稍作修改，调整执行顺序，得到五级流水线。  
使用forwaring和互锁解决流水线冒险和分支预测（取近五次的跳转结果进行预测）的并行版本：https://github.com/sjxer723/RISCV_parrel.git

## Build

Run the following commands to build the binary files:
```
  mkdir build && cd build
  cmake ..
  make
```

# 实现效果
  在oj上的测试时间2272ms
  完成了基础的要求，没有做bonus  
  分支预测的准确度，在一些跳转次数少的数据点上，准确度较低，跳转次数多的数据点上还可以…  
  Arrary_test1  
  Success 13 total 22  
  rate=0.590909  
  array_test2  
  success 15 total 26  
  rate=0.576923  
basicopt1  
success 117134 total 155139   
rate=0.755026  
Bulgarian  
Success 40819 total 71493  
rate=0.570951  
expr  
success 89 total 111  
rate=0.801802  
gcd  
success 78 total 120  
rate=0.65  
Hanoi  
Success 8748 total 17457  
rate=0.501117  
lvalue2  
success 3 total 6  
rate=0.5  
multiarray  
success 138 total 162  
rate=0.851852  
pi  
success3.18631e+07 total3.99564e+07  
rate=0.797447  
