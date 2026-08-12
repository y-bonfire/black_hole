#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

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

    double c = 299792458.0;
    double G = 6.67430e-11;
    double r_s = 2.0 * G * 8.54e36 / (c * c);

    glBegin(GL_TRIANGLE_FAN);
    //glBegin(GL_LINE_LOOP); // Use GL_LINE_LOOP for a dashed effect

    glColor3f(1.0f, 0.0f, 0.0f);

    glVertex2f(0.0f, 0.0f);

    for (int i = 0; i <= 100; i+=1)
    {
        //if(i%2==0) continue; // Skip every other point to create a dashed effect
        float angle = 2.0f * 3.14f * i / 100;

        float x = r_s * cos(angle);
        float y = r_s * sin(angle);

        glVertex2f(x, y);
    }

    glEnd();
}

int main()
{
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
        "Black Hole Study - Step 01",
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