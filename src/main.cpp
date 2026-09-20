#include <iostream>
#include <vector>
#include <fstream>

int main() {


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

// 热传导参数
const double alpha = 0.01;
const double dt = 0.005;

// 稳定性系数
const double r = alpha * dt / (dx * dx);

// 当前温度
std::vector<double> temperature(
    nx * ny,
    initial_temperature
);

// 下一时刻温度
std::vector<double> new_temperature(
    nx * ny,
    initial_temperature
);

// 中心点
const int center_x = nx / 2;
const int center_y = ny / 2;

const int center_index =
    center_x + center_y * nx;

// 设置中心高温
temperature[center_index] = hot_temperature;

// 模拟步数
const int steps = 100;

// 时间迭代
for (int step = 0; step < steps; ++step) {

    // 计算内部网格点
    for (int j = 1; j < ny - 1; ++j) {

        for (int i = 1; i < nx - 1; ++i) {

            const int index = i + j * nx;

            // 四个方向的温度
            const double left =
                temperature[index - 1];

            const double right =
                temperature[index + 1];

            const double down =
                temperature[index - nx];

            const double up =
                temperature[index + nx];

            // 热传导有限差分公式
            new_temperature[index] =
                temperature[index]
                + r * (
                    left
                    + right
                    + down
                    + up
                    - 4.0 * temperature[index]
                );
        }
    }

    // 保持边界温度
    for (int i = 0; i < nx; ++i) {

        new_temperature[i] =
            initial_temperature;

        new_temperature[(ny - 1) * nx + i] =
            initial_temperature;
    }

    for (int j = 0; j < ny; ++j) {

        new_temperature[j * nx] =
            initial_temperature;

        new_temperature[j * nx + (nx - 1)] =
            initial_temperature;
    }

    // 更新当前温度
    temperature.swap(new_temperature);
}

// 创建数据文件
std::ofstream output("../data/temperature.csv");

if (!output) {
    std::cerr << "Failed to open data/temperature.csv\n";
    return 1;
}

// 写入 CSV 表头
output << "x,y,temperature\n";

// 写入每个网格点
for (int j = 0; j < ny; ++j) {

    for (int i = 0; i < nx; ++i) {

        const int index = i + j * nx;

        const double x = i * dx;
        const double y = j * dy;

        output << x << ","
               << y << ","
               << temperature[index]
               << "\n";
    }
}

output.close();

// 输出结果
std::cout << "Heat Simulation\n";
std::cout << "-------------------------\n";

std::cout << "Grid: "
          << nx << " x " << ny << '\n';

std::cout << "Steps: "
          << steps << '\n';

std::cout << "Simulation time: "
          << steps * dt
          << " s\n";

std::cout << "Center temperature: "
          << temperature[center_index]
          << " C\n";

std::cout << "Output: data/temperature.csv\n";

return 0;


}

