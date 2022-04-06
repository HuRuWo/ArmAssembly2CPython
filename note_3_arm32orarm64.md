### ARM32和ARM64

#### 定义

- ARM是RISC（精简指令集）处理器，不同于x86指令集（CISC,复杂指令集）。
- Arm32位是ARMV7架构，32位的，对应处理器为Cortex-A15等； iphone5以前均是32位的；
需要注意：ARMV7-A和ARMV7-R系列支持neon指令集，ARMv7-M系列不支持neon指令集。
- ARM64位采用ARMv8架构，64位操作长度，对应处理器有Cortex-A53、Cortex-A57、Cortex-A73、iphones的A7和A8等，苹果手机从iphone 5s开始使用64位的处理器。

ARM64是未来趋势，ARM32最终一定会被淘汰。所以学习ARM64才是未来趋势，分析应用的SO也应该以64为架构优先。

#### Android SO