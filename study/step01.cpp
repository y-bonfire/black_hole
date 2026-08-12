#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

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

        // 描画した画面を表示
        glfwSwapBuffers(window);

        // マウスやキーボード、閉じるボタンなどを処理
        glfwPollEvents();
    }

    // GLFWを終了
    glfwTerminate();

    return 0;
}