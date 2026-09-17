# Heat-Simulation 开发日志

## 阶段一：环境与项目初始化

**时间：2026-09-17**

### 1. 搭建 Linux 开发环境

使用 **WSL + Ubuntu 26.04 LTS** 作为项目开发环境，项目放置于 Linux 文件系统：

```text
~/project/Heat-Simulation
```

更新软件源并安装基础开发工具：

```bash
sudo apt update
sudo apt install build-essential
```

随后安装 CMake、GDB、Git、Ninja 等工具，完成 C++ 基础开发环境搭建。

---

### 2. 创建项目

建立项目目录及基础结构：

```bash
mkdir -p src include build data
```

创建 `src/main.cpp`，编写第一个 C++ 程序，并使用 G++ 编译运行：

```bash
g++ src/main.cpp -o build/heat_sim
./build/heat_sim
```

成功输出：

```text
Heat Simulation Start!
```

完成 C++ 从编写、编译到运行的基本流程。

---

### 3. 配置 Python 环境

在项目中创建 Python 虚拟环境：

```bash
python3 -m venv .venv
```

安装 NumPy 并完成验证。Python 后续主要用于模拟数据的处理、分析和可视化，核心数值计算使用 C++ 完成。

---

### 4. 配置 Git 与 GitHub

初始化 Git 仓库，创建 `.gitignore`，忽略 `build/`、`.venv/` 等文件。

完成 Git 用户信息配置后进行首次提交：

```bash
git add .
git commit -m "Initial commit"
```

随后创建 GitHub 远程仓库 `Heat-Simulation`，配置 `origin` 并完成：

```bash
git push -u origin main
```

至此，本地项目与 GitHub 建立连接。

---

### 阶段一总结

完成 **WSL + C++ + CMake + GDB + Git + Python** 基础环境搭建，并完成项目初始化及 GitHub 远程仓库连接。

下一阶段进入二维热传导问题的**数学建模与数值方法设计**。

