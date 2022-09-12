//ゲーム係機能のインクルード
#include <GLLibrary.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


//--------------------------------------------
//グローバル変数領域
//--------------------------------------------

//ボール
CImage ball;
CVector2D ball_pos(600, 300);
CVector2D ball_vec(4, 4);

//バー
CImage bar[2];
CVector2D bar_pos[2] = { CVector2D(0,300),CVector2D(1240 - 32,300) };
//スコア
CImage score;
int point[2] = { 0,0 };

//ゲームの状態 (:ポーズ,1:ゲーム中)
int game_state = 0;


void MainLoop(void) {

    //--------------------------------------------------------------
    //ゲーム中の動きはここに書く
    //ゲーム中はこの関数_を1秒間に60回呼び出している
    //--------------------------------------------------------------
    
    switch (game_state) {
    case 0:
            //ポーズ中の更新処理
        if (PUSH(CInput::eButton10))
            game_state = 1;
            break;
    case 1:
            //ゲーム中の更新処理
        ball_pos += ball_vec;
        if (ball_pos.y < 0 || ball_pos.y > 720 - 32) {
            ball_vec.y *= -1;
            SOUND("SE_Wall")->Play();
        }
        //左右の反射
        /*if (ball_pos.x < 0 || ball_pos.x > 1280 - 32) {
            ball_vec.x *= -1;
        }*/
        //バーの下移動
        if (HOLD(CInput::eDown)) {
            bar_pos[0].y += 8;
        }
        //バーの上移動
        if (HOLD(CInput::eUp)) {
            bar_pos[0].y -= 8;
        }
        //COMの上移動
        if (ball_pos.y + 16 < bar_pos[1].y + 64)
            bar_pos[1].y -= 4;

        //COMの下移動
        if (ball_pos.y + 16 > bar_pos[1].y + 64)
            bar_pos[1].y += 4;
        
        for (int i = 0; i < 2; i++) {
            if (bar_pos[i].x + 32 > ball_pos.x &&
                bar_pos[i].x < ball_pos.x + 32 &&
                bar_pos[i].y + 128 > ball_pos.y &&
                bar_pos[i].y < ball_pos.y + 32) {
                //跳ね返る
                ball_vec.x *= -1;
                ball_vec *= 1.1f;
                SOUND("SE_Hit")->Play();
            }
        }
        
            break;
    }
    //1P側ゴール
    if (ball_pos.x < 0) {
        //ボールの位置を中央にセット
        ball_pos = CVector2D(600, 300);
        //移動量もリセット
        ball_vec = CVector2D(-4, -4);
        //ポーズ状態へ
        game_state = 0;
        //2P側得点アップ
        point[1]++;
        SOUND("SE_Get")->Play();
    }
    if (ball_pos.x >1280 ) {
        //ボールの位置を中央にセット
        ball_pos = CVector2D(600, 300);
        //移動量もリセット
        ball_vec = CVector2D(-4, -4);
        //ポーズ状態へ
        game_state = 0;
        //1P側得点アップ
        point[0]++;
        SOUND("SE_Get")->Play();
    }


   


    //ball.SetPos(600, 300);
    ball.SetPos(ball_pos);
    ball.SetSize(32, 32);
    ball.Draw();

    for (int i = 0; i < 2; i++) {
        bar[i].SetPos(bar_pos[i]);
        bar[i].Draw();
    }
    int base_x[2] = { 640 - 48,640 + 48 };
    for (int j = 0; j < 2; j++) {
        int n = point[j];
        for (int i = 0; i < 2; i++, n /= 10) {
            int p = n % 10;
            score.SetRect(48 * p, 48 * j, 48 * (p + 1), 48 * (j + 1));
            score.SetSize(48, 48);
            score.SetPos(base_x[j] - i * 48, 0);
            score.Draw();
        }
    }
}


void Init(void)
{
    
    CFPS::SetFPS(60);
    //フレーム制御初期化
    CFPS::Init();
    //ボタンの設定
    CInput::Init();
    //1P
    CInput::SetButton(0, CInput::eButton1, 'Z');
    CInput::SetButton(0, CInput::eButton2, 'X');
    CInput::SetButton(0, CInput::eButton3, 'R');
    CInput::SetButton(0, CInput::eButton4, 'V');
    CInput::SetButton(0, CInput::eButton5, VK_SPACE);
    CInput::SetButton(0, CInput::eButton10, VK_RETURN);
    CInput::SetButton(0, CInput::eUp, 'W');
    CInput::SetButton(0, CInput::eDown, 'S');
    CInput::SetButton(0, CInput::eLeft, 'A');
    CInput::SetButton(0, CInput::eRight, 'D');
    CInput::SetButton(0, CInput::eMouseL, VK_LBUTTON);
    CInput::SetButton(0, CInput::eMouseR, VK_RBUTTON);
    CInput::SetButton(0, CInput::eMouseC, VK_MBUTTON);

    //2P
    CInput::SetButton(1, CInput::eUp, VK_UP);
    CInput::SetButton(1, CInput::eDown, VK_DOWN);


    //	CInput::SetMouseInside(true);
    //	CInput::ShowCursor(false);
    CInput::Update();
    CInput::Update();



    SetCurrentDirectory("data");
    CSound::GetInstance();

    //-----------------------------------------------------
    //初期化の命令を書く
    //ゲーム起動時に一度だけ呼ばれる
    //-----------------------------------------------------
    
    //ボールの読み込み
    ball.Load("Image/anatora.png");
    //バーの読み込み
    bar[0].Load("Image/bar.png");
    bar[1].Load("Image/bar.png");
    //数字の読み込み
    score.Load("Image/Number.png");
    //SEの読み込み
    SOUND("SE_Wall")->Load("Sound/SE/SE_Wall.wav", 10);
    SOUND("SE_Hit")->Load("Sound/SE/SE_Hit.wav", 10);
    SOUND("SE_Get")->Load("Sound/SE/SE_Get.wav", 10);
    //BGMの読み込み
    SOUND("BGM_Game")->Load("Sound/BGM/BGM_Game.wav", 1);
    SOUND("BGM_Game")->Play(true);

}


void Release()
{
    CLoadThread::ClearInstance();
    CSound::ClearInstance();
    CResourceManager::ClearInstance();
}

static void ResizeCallback(GLFWwindow* window, int w, int h)
{
    glViewport(0, 0, w, h);

    //画面解像度変動
    CCamera::GetCamera()->SetSize((float)w, (float)h);
    //画面解像度固定
    //CCamera::GetCamera()->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    CCamera::GetCamera()->Viewport(0, 0, w, h);
    CCamera::GetCurrent()->Perspective(DtoR(60.0), (float)w / (float)h, 1.0, 1000.0);

    glfwGetWindowPos(window, &GL::window_x, &GL::window_y);
    GL::UpdateWindowRect(GL::window_x, GL::window_y, w, h);
    CInput::UpdateClipCursor(true);

}
static void WheelCallback(GLFWwindow* _window, double _offsetx, double _offsety) {
    CInput::AddMouseWheel((int)_offsety);

}
static void PosCallback(GLFWwindow* _window, int x, int y) {
    GL::window_x = x;
    GL::window_y = y;
    GL::UpdateWindosRect(x, y, GL::window_width, GL::window_height);
    CInput::UpdateClipCursor(true);

}
static void FocusCallback(GLFWwindow* _window, int f) {
    CInput::UpdateClipCursor(f);
    GL::focus = f;
}

static void error_callback(int error, const char* description)
{
    printf("Error: %s\n", description);
}

//フルスクリーン?ウインドウモードの切り替え
//Alt+Enterで切り替える
void CheckFullScreen() {
    static int key_enter = 0;
    int key_enter_buf = key_enter;
    if (key_enter_buf ^ (key_enter = glfwGetKey(GL::window, GLFW_KEY_ENTER)) && key_enter && (glfwGetKey(GL::window, GLFW_KEY_LEFT_ALT) || glfwGetKey(GL::window, GLFW_KEY_RIGHT_ALT))) {
        GL::ChangeFullScreen(!GL::full_screen);
    }
}

int __main(int* argcp, char** argv) {
    // メモリリーク検出
    //	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


    //OpenGL4.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) return -1;
    //	glutInit(argcp, argv);

    GL::window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Simple", nullptr, nullptr);
    glfwGetWindowSize(GL::window, &GL::window_width, &GL::window_height);
    glfwGetWindowPos(GL::window, &GL::window_x, &GL::window_y);

    glfwSetFramebufferSizeCallback(GL::window, ResizeCallback);
    glfwSetScrollCallback(GL::window, WheelCallback);
    glfwSetWindowFocusCallback(GL::window, FocusCallback);
    glfwSetWindowPosCallback(GL::window, PosCallback);
    if (!GL::window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(GL::window);
    glfwSwapInterval(1);
    ResizeCallback(GL::window, SCREEN_WIDTH, SCREEN_HEIGHT);

    GLenum err = glewInit();
    if (err == GLEW_OK) {
        printf("%s\n", glewGetString(GLEW_VERSION));
    }
    else {
        printf("%s\n", glewGetErrorString(err));
        getchar();
        return -1;
    }
    HDC glDc = wglGetCurrentDC();
    GL::hWnd = WindowFromDC(glDc);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);//ブレンドの有効化
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    //固定シェーダー用
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_ALPHA_TEST);

    Init();
    while (!glfwWindowShouldClose(GL::window)) {
        CheckFullScreen();


        CInput::Update();
        //各バッファーをクリア
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        MainLoop();


        glfwSwapBuffers(GL::window);


        CFPS::Wait();

        char title[32];
        sprintf_s(title, "math fps:%d dt:%.3f", CFPS::GetFPS(), CFPS::GetDeltaTime());
        glfwSetWindowTitle(GL::window, title);

        glfwPollEvents();
        if (glfwGetKey(GL::window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(GL::window, GL_TRUE);
        }

    }

    glfwTerminate();




    Release();
    return 0;
}

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR argv, INT argc)
{
    return __main(&__argc, __argv);
}

int main(int argc, char** argv)
{
    return __main(&argc, argv);
}
