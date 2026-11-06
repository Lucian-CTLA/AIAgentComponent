# AIInteractionPlugin

一个基于 Unreal Engine 5.7 的 AI 驱动 Actor 交互插件。

插件的目标是让罐子、宝箱、门、机关和可拾取物等 Actor，通过添加组件和实现接口后，具备统一的交互能力。

## 当前进度

当前已完成第二天功能：

- 创建运行时插件
- 创建可交互 Actor 接口
- 创建可交互组件
- 创建 Character 交互组件
- 检测范围内的可交互 Actor
- 保存当前交互目标
- 校验交互动作是否合法
- 通过接口向目标 Actor 发送动作
- 完成可破坏罐子示例
- 支持 Attack 动作
- 支持生命值扣除
- 支持隐藏 Actor
- 支持关闭 Actor 碰撞

当前暂未接入本地 AI API。

## 第二天完成内容

### Character 交互组件

`UAIInteractionComponent` 挂载到 Character 上，负责处理角色侧的交互逻辑。

主要功能包括：

- 检测指定半径内的 Actor
- 查找 Actor 上的交互组件
- 过滤不可交互对象
- 保存检测到的 Actor
- 设置当前目标
- 执行动作前进行合法性校验
- 通过交互接口发送动作

核心流程：

```text
Character
↓
范围检测
↓
筛选可交互 Actor
↓
保存当前目标
↓
检查动作是否合法
↓
发送交互事件
```

### 目标检测

角色按下 E 键后执行：

```text
Scan Interactable Actors
→ Get Detected Actors
→ 检查数组长度
→ Get(0)
→ Set Current Target
```

当目标数量为 0 时，不访问数组的第一个元素，避免出现数组越界错误。

### 动作执行

角色按下 F 键后执行：

```text
Interact With Current Target
Action Name = Attack
```

插件会依次检查：

- 当前目标是否有效
- 目标是否存在交互组件
- 目标是否支持 Attack
- 目标是否实现交互接口

所有条件满足后，调用：

```text
Event ReceiveInteraction
```

### 可破坏罐子示例

`BP_BreakablePot` 使用以下配置：

```text
Can Interact: true
Interaction Range: 250
Interaction Type: Destructible
Available Actions: Interact、Attack
```

罐子收到 `Attack` 后执行：

```text
Current Health - 1
→ 判断 Current Health <= 0
→ 设置 Broken = true
→ 隐藏 Actor
→ 关闭 Actor 碰撞
```

### 当前测试结果

```text
按 E 选择罐子 → 按 F 执行 Attack → 罐子成功隐藏 → 罐子碰撞关闭
```

## 技术栈

- Unreal Engine 5.7
- C++
- Blueprint
- Actor Component
- Unreal Interface
- Visual Studio

## 插件目录

```text
Plugins/AIInteractionPlugin
├── AIInteractionPlugin.uplugin
├── Source
│   └── AIInteractionPlugin
│       ├── AIInteractionPlugin.Build.cs
│       ├── Public
│       │   ├── Components
│       │   │   ├── InteractableComponent.h
│       │   │   └── AIInteractionComponent.h
│       │   └── Interfaces
│       │       └── AIInteractableInterface.h
│       └── Private
│           └── Components
│               ├── InteractableComponent.cpp
│               └── AIInteractionComponent.cpp
└── Resources
```

## 插件功能

### 可交互组件

`UInteractableComponent` 用于配置 Actor 的交互属性。

主要属性包括：

| 属性               | 说明                 |
| ------------------ | -------------------- |
| Can Interact       | 是否允许交互         |
| Interaction Range  | 交互距离             |
| Interaction Type   | 交互对象类型         |
| Available Actions  | 支持的动作列表       |

示例配置：

```text
Can Interact: true
Interaction Range: 250
Interaction Type: Destructible
Available Actions: Interact、Attack
```

### 交互接口

`AIInteractableInterface` 提供两个通用接口：

- **CanInteract**：判断当前 Actor 是否允许交互。
- **ReceiveInteraction**：接收具体动作，例如：
  - Interact
  - Attack
  - PickUp
  - Open
  - Talk

## 使用方式

### 1. 启用插件

打开项目后进入：

```text
Edit → Plugins
```

搜索：

```text
AIInteractionPlugin
```

确认插件左侧为蓝色勾选状态。

### 2. 创建交互对象

创建一个继承自 Actor 的蓝图：

```text
BP_BreakablePot
```

### 3. 添加组件

打开 `BP_BreakablePot`，在 Components 面板中选择：

```text
Add → Interactable Component
```

### 4. 配置组件

在 Details 面板中设置：

```text
Can Interact: true
Interaction Range: 250
Interaction Type: Destructible
```

在 Available Actions 中添加：

```text
Interact
Attack
```

### 5. 添加接口

打开蓝图的 Class Settings，在 Interfaces 中添加：

```text
AIInteractableInterface
```

然后在 Event Graph 中实现：

```text
Event Receive Interaction
```

第一天可以使用 `Print String` 测试是否收到动作。

## 编译方式

关闭 Unreal Editor 后，右键项目文件：

```text
AIInteractionDemo.uproject
```

选择：

```text
Generate Visual Studio project files
```

打开 Visual Studio 项目，选择：

```text
Development Editor
Win64
```

然后执行：

```text
Build Solution
```

编译成功后重新打开项目。

## 后续扩展

- 支持拾取、开门、对话和机关操作
- 接入 Gameplay Ability System
- 接入行为树和 Utility AI
- 增加编辑器配置面板
- 增加调试显示和自动化测试
