#include <iostream>
#include <vector>
#include <fstream>

int main()
{
// 模拟区域
const double length_x = 1.0;
const double length_y = 1.0;


// 网格
const int nx = 51;
const int ny = 51;

const double dx = length_x / (nx - 1);
const double dy = length_y / (ny - 1);

// 温度
const double initial_temperature = 20.0;
const double hot_temperature = 100.0;
const double boundary_temperature = 20.0;

// 热扩散系数和时间步长
const double alpha = 0.01;
const double dt = 0.005;

// 稳定性参数
const double r = alpha * dt / (dx * dx);

// 温度场
std::vector<double> temperature(nx * ny, initial_temperature);
std::vector<double> new_temperature(nx * ny, initial_temperature);

// 中心位置
const int center_i = nx / 2;
const int center_j = ny / 2;
const int center_index = center_i + center_j * nx;

temperature[center_index] = hot_temperature;

// 时间步数
const int steps = 100;

// 打开 CSV 文件
std::ofstream output("../data/temperature.csv");

if (!output.is_open())
{
    std::cerr << "Failed to open output file." << std::endl;
    return 1;
}

// CSV 表头
output << "step,time,x,y,temperature\n";

// 保存初始状态
for (int j = 0; j < ny; ++j)
{
    for (int i = 0; i < nx; ++i)
    {
        const int index = i + j * nx;

        const double x = i * dx;
        const double y = j * dy;

        output << 0 << ","
               << 0.0 << ","
               << x << ","
               << y << ","
               << temperature[index] << "\n";
    }
}

// 时间推进
for (int step = 1; step <= steps; ++step)
{
    // 计算内部网格点
    for (int j = 1; j < ny - 1; ++j)
    {
        for (int i = 1; i < nx - 1; ++i)
        {
            const int index = i + j * nx;

            new_temperature[index] =
                temperature[index]
                + r * (
                    temperature[index - 1]
                    + temperature[index + 1]
                    + temperature[index - nx]
                    + temperature[index + nx]
                    - 4.0 * temperature[index]
                );
        }
    }

    // 固定边界温度
    for (int i = 0; i < nx; ++i)
    {
        new_temperature[i] = boundary_temperature;
        new_temperature[i + (ny - 1) * nx] = boundary_temperature;
    }

    for (int j = 0; j < ny; ++j)
    {
        new_temperature[j * nx] = boundary_temperature;
        new_temperature[j * nx + (nx - 1)] = boundary_temperature;
    }

    // 交换当前温度和下一时刻温度
    temperature.swap(new_temperature);

    // 保存当前时间步
    const double time = step * dt;

    for (int j = 0; j < ny; ++j)
    {
        for (int i = 0; i < nx; ++i)
        {
            const int index = i + j * nx;

            const double x = i * dx;
            const double y = j * dy;

            output << step << ","
                   << time << ","
                   << x << ","
                   << y << ","
                   << temperature[index] << "\n";
        }
    }
}

output.close();

std::cout << "Simulation finished." << std::endl;
std::cout << "Steps: " << steps << std::endl;
std::cout << "Final time: " << steps * dt << " s" << std::endl;
std::cout << "Output: data/temperature.csv" << std::endl;

return 0;


}

