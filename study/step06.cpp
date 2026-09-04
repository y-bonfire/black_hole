#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>

double point_x = -1e11f;
double point_y = 0.0f;
double vector_x = 2e11f / 10.0f;
double vector_y = 0.0f;
double dt = 0.0f;
double currentTime = 0.0f;
double previousTime = 0.0f;
double updateTime = 0.0f;

struct Point
{
    double x;
    double y;
};
std::vector<Point> points;

void draw()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(
        -100000000000.0,
        100000000000.0,
        -75000000000.0,
        75000000000.0,
        -1.0,
        1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 光速 30万km/s 299792458 m/s
    double c = 299792458.0;
    double G = 6.67430e-11;

    double mass = 8.54e36; // 質量 (kg)

    // シュワルツシルト半径 r_s = 2GM/c^2
    // r_s ≒ 12,700,000 km
    // 射手座A*の質量は約4.3百万太陽質量で、シュワルツシルト半径は約12.7百万キロメートルです。
    double r_s = 2.0 * G * mass / (c * c);

    glBegin(GL_TRIANGLE_FAN);
    // glBegin(GL_LINE_LOOP); // Use GL_LINE_LOOP for a dashed effect

    glColor3f(1.0f, 0.0f, 0.0f);

    glVertex2f(0.0f, 0.0f);

    for (int i = 0; i <= 100; i += 1)
    {
        // if(i%2==0) continue; // Skip every other point to create a dashed effect
        float angle = 2.0f * 3.14f * i / 100;

        float x = r_s * cos(angle);
        float y = r_s * sin(angle);

        glVertex2f(x, y);
    }

    glEnd();

    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    double x1 = -1e11f;
    double x2 = 1e11f;
    double y1 = -30000000000.0f;
    double y2 = 30000000000.0f;

    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x1, y2);
    glVertex2f(x2, y2);

    glEnd();

    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(point_x, point_y);
    dt = currentTime - previousTime;
    previousTime = currentTime;
    point_x += (vector_x * dt);
    point_y += (vector_y * dt);
    if (currentTime - updateTime >= 1.0)
    {
        points.push_back({point_x, point_y});
        updateTime += 1.0f;
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 1.0f, 0.0f);
    for (auto it = points.begin(); it != points.end(); ++it)
    {
        if (points.size() > 5)
        {
            if(it > points.end() - 5)
            {
                glVertex2f(it->x, it->y);
            }
        }
        else
        {
            glVertex2f(it->x, it->y);
        }
    }
    glVertex2f(point_x, point_y);
    glEnd();
}

int main()
{
    int nbFrames = 0;
    double lastTime = glfwGetTime();

    // GLFWを初期化
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return 1;
    }

    // 800x600のウィンドウを作る
    GLFWwindow *window = glfwCreateWindow(
        800,
        600,
        "Black Hole Study - Step 02",
        nullptr,
        nullptr);

    if (!window)
    {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return 1;
    }

    // このウィンドウのOpenGLコンテキストを使用する
    glfwMakeContextCurrent(window);

    // GLEWを初期化
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW\n";
        glfwTerminate();
        return 1;
    }

    // 背景色を黒にする
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // ウィンドウが閉じられるまで繰り返す
    while (!glfwWindowShouldClose(window))
    {
        currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0)
        {
            std::cout << 1000.0 / double(nbFrames) << " ms/frame\n";
            std::cout << point_x << " " << point_y << "\n";
            nbFrames = 0;
            lastTime += 1.0;
        }

        // 画面を背景色で消去
        glClear(GL_COLOR_BUFFER_BIT);

        draw(); // Draw the black hole

        // 描画した画面を表示
        glfwSwapBuffers(window);

        // マウスやキーボード、閉じるボタンなどを処理
        glfwPollEvents();
    }

    // GLFWを終了
    glfwTerminate();

    return 0;
}