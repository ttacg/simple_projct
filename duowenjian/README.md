# 多文件 Console RPG 练习

这是一个命令行回合战斗练习。代码在 `duowenjian/` 下，通过多个类和多个源文件组织；`main.cpp` 创建 `Game` 并启动战斗。

## 结构与职责

| 文件 | 职责 |
| --- | --- |
| `Character.h/.cpp` | 角色共同的生命、攻击、防御数据，以及受伤、死亡判断等操作。 |
| `Player.h/.cpp` | 玩家继承 `Character`，管理药水、回血和胜利奖励。 |
| `Enemy.h/.cpp` | 敌人继承 `Character`，设置敌人的初始属性。 |
| `Game.h/.cpp` | 持有一个 `Player` 和一个 `Enemy`，安排输入、回合和胜负流程。 |
| `main.cpp` | 创建游戏对象并调用 `combat()`。 |

这里同时用到了继承（`Player`、`Enemy` → `Character`）和组合（`Game` 持有玩家与敌人）。类声明放在 `.h`，实现放在 `.cpp`；构建时需要一起编译所有 `.cpp`。

## 编译与运行

在 Windows PowerShell 中进入 `duowenjian` 目录，并确保 `g++` 在 PATH 中：

```powershell
g++ -std=c++17 Character.cpp Player.cpp Enemy.cpp Game.cpp main.cpp -o RPG.exe
.\RPG.exe
```

运行后输入 `1` 攻击，或输入 `2` 使用药水。当前 `main.cpp` 固定玩家为 100 HP、30 攻击、10 防御，敌人为 80 HP、20 攻击。实际编译命令、输入和终端输出见 [运行结果记录](RUN_RESULT.md)。

## 当前范围

已验证上述文件能共同编译，攻击胜利和使用药水的流程能运行。`Game.cpp` 末尾另有一个尚未接入战斗流程的通用 `attack(Character&, Character&)` 函数；它目前会覆盖“最低 1 点伤害”的计算，本记录不把它算作已完成或已验证的战斗功能。输入非数字等异常情况也尚未处理。
