import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation, PillowWriter

# 读取模拟数据

data = np.loadtxt(
"data/temperature.csv",
delimiter=",",
skiprows=1
)

# 网格大小

nx = 51
ny = 51

# 获取所有时间步

steps = np.unique(data[:, 0])

# 创建图像

fig, ax = plt.subplots()

# 第一帧

frame = data[data[:, 0] == steps[0]]
temperature = frame[:, 4].reshape(ny, nx)

# 显示温度场

image = ax.imshow(
temperature,
origin="lower",
extent=[0, 1, 0, 1],
vmin=20,
vmax=100,
cmap="hot"
)

# 添加颜色条

colorbar = fig.colorbar(image, ax=ax)
colorbar.set_label("Temperature (°C)")

ax.set_xlabel("x (m)")
ax.set_ylabel("y (m)")

title = ax.set_title("2D Heat Diffusion")

# 更新每一帧

def update(frame_number):
    frame = data[data[:, 0] == steps[frame_number]]


    temperature = frame[:, 4].reshape(ny, nx)

    image.set_data(temperature)

    time = frame[0, 1]

    title.set_text(f"2D Heat Diffusion — t = {time:.3f} s")

    return image, title


# 创建动画

animation = FuncAnimation(
    fig,
    update,
    frames=len(steps),
    interval=50,
    blit=True
)

# 保存为 GIF

animation.save(
"data/temperature.gif",
writer=PillowWriter(fps=20)
)

print("Animation saved to data/temperature.gif")

