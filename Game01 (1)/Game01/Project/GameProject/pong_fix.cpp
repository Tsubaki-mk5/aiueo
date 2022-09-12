//�Q�[���W�@�\�̃C���N���[�h
#include <GLLibrary.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


//--------------------------------------------
//�O���[�o���ϐ��̈�
//--------------------------------------------


//�{�[���̉摜�I�u�W�F�N�g
CImage ball;
CVector2D ball_pos(SCREEN_WIDTH / 2 - 32 / 2, SCREEN_HEIGHT / 2 - 32 / 2);
//�{�[���̈ړ���
CVector2D ball_vec(0, 0);

//�o�[�̉摜�I�u�W�F�N�g
//bar[0]��1P�Abar[1]��2P
CImage bar[2];
CVector2D bar_pos[2] = {
	CVector2D(0, SCREEN_HEIGHT / 2 - 128 / 2),
	CVector2D(SCREEN_WIDTH - 32, SCREEN_HEIGHT / 2 - 128 / 2)
};

//�Q�[���̏��
//0:�ҋ@��
//1:�Q�[����
int game_state = 0;


//�X�R�A
int point[2] = { 0,0 };
//�X�R�A�̉摜
CImage score;

bool CollisionRect(CRect rect1, CRect rect2) {
	if (rect1.m_left <= rect2.m_right && rect1.m_right >= rect2.m_left &&
		rect1.m_top <= rect2.m_bottom && rect1.m_bottom >= rect2.m_top)
		return true;
	return false;
}

void MainLoop(void) {

	//--------------------------------------------------------------
	//�Q�[�����̓����͂����ɏ���
	//�Q�[�����͂��̊֐�_��1�b�Ԃ�60��Ăяo���Ă���
	//--------------------------------------------------------------

	switch (game_state) {
	case 0: //�ҋ@��
		if (PUSH(CInput::eButton10)) {
			game_state = 1;
		}
		break;
	case 1: //�Q�[����
		ball_pos += ball_vec;
		if (ball_pos.y < 0 ||
			ball_pos.y > SCREEN_HEIGHT - 32) {
			ball_vec.y *= -1;
			SOUND("SE_Wall")->Play();
		}

		//���L�[�������Ə�Ɉړ�����
		if (HOLD(CInput::eDown)) {
			bar_pos[0].y += 8;
		}
		//��L�[�������Ə�Ɉړ�����
		if (HOLD(CInput::eUp)) {
			bar_pos[0].y -= 8;
		}
		//CPU�̓��������
		if (ball_pos.y < bar_pos[1].y + 16) {
			bar_pos[1].y -= 8;
		}
		if (ball_pos.y > bar_pos[1].y + 16) {
			bar_pos[1].y += 8;
		}
		//�Q�̃o�[�̈ړ��������[�v
		for (int i = 0; i < 2; i++) {
			//�o�[�ƃ{�[���̓����蔻��
			//��`���m�̏Փˏ���
			if (bar_pos[i].x + 32 >= ball_pos.x &&
				bar_pos[i].x <= ball_pos.x + 64 &&
				bar_pos[i].y <= ball_pos.y + 64 &&
				bar_pos[i].y + 128 >= ball_pos.y) {
				//���ʉ��Đ�
				SOUND("SE_Hit")->Play();
				//�{�[���𒵂˕Ԃ�
				//X���̈ړ��ʂ𔽓]����
				ball_vec.x *= -1;
				//���x��1.5�{��
				ball_vec *= 1.5;
				//Y���̓����_���ŕω�
				ball_vec.y += Utility::Rand(-5.0f, 5.0f);
				//���x��16���傫���Ȃ��
				if (ball_vec.Length() > 16) {
					//���x��16�ɐ�������
					ball_vec = ball_vec.GetNormalize() * 16;
				}
			}
		}
		//1P���S�[��
		if (ball_pos.x < 0) {
			ball_pos = CVector2D(SCREEN_WIDTH / 2 - 32 / 2, SCREEN_HEIGHT / 2 - 32 / 2);
			ball_vec = CVector2D(-4, 4);
			game_state = 0;
			point[1]++;
			SOUND("SE_Get")->Play();
		}
		//2P���S�[��
		if (ball_pos.x > SCREEN_WIDTH) {
			ball_pos = CVector2D(SCREEN_WIDTH / 2 - 32 / 2, SCREEN_HEIGHT / 2 - 32 / 2);
			ball_vec = CVector2D(4, 4);
			game_state = 0;
			point[0]++;
			SOUND("SE_Get")->Play();
		}
		break;
	}


	//��������\���̖���
	ball.SetPos(ball_pos);
	ball.Draw();
	//�o�[�̕\��
	//�o�[���W�̐ݒ�
	for (int i = 0; i < 2; i++) {
		bar[i].SetPos(bar_pos[i]);
		bar[i].Draw();
	}

	//�X�R�A�̕\��
	for (int k = 0; k < 2; ++k) {
		int p = point[k];
		//�ꌅ���\��
		for (int i = 0; i < 2; ++i, p /= 10) {
			int pp = p % 10;
			int base_x[2] = { SCREEN_WIDTH / 2 - 48,SCREEN_WIDTH / 2 + 48 };
			score.SetPos(base_x[k] - 48 * i, 0);
			score.SetRect(48 * pp, 48 * k,48 * pp + 48, 48 * k + 48);
			score.SetSize(48, 48);
			score.Draw();
		}
	}



}
void Init(void)
{
	
	CFPS::SetFPS(60);
	//�t���[�����䏉����
	CFPS::Init();
	//�{�^���̐ݒ�
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
	//�������̖��߂�����
	//�Q�[���N�����Ɉ�x�����Ă΂��
	//-----------------------------------------------------

	//�{�[���ǂݍ���
	ball.Load("Image/anatora.png");
	//�\���T�C�Y�ύX
	ball.SetSize(32, 32);
	//�ړ��x�N�g���ݒ�
	ball_vec = CVector2D(4, 4);

	//�摜�̓ǂݍ���
	//�v���C���[1
	bar[0].Load("Image/bar.png");
	//�v���C���[2(CPU)
	bar[1].Load("Image/bar.png");


	//�X�R�A�摜�̓ǂݍ���
	score.Load("Image/Number.png");

	//�T�E���h�ǂݍ���
	SOUND("SE_Hit")->Load("Sound/SE/SE_Hit.wav", 10);
	SOUND("SE_Get")->Load("Sound/SE/SE_Get.wav", 10);
	SOUND("SE_Wall")->Load("Sound/SE/SE_Wall.wav", 10);

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

	//��ʉ𑜓x�ϓ�
	CCamera::GetCamera()->SetSize((float)w, (float)h);
	//��ʉ𑜓x�Œ�
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

//�t���X�N���[��?�E�C���h�E���[�h�̐؂�ւ�
//Alt+Enter�Ő؂�ւ���
void CheckFullScreen() {
	static int key_enter = 0;
	int key_enter_buf = key_enter;
	if (key_enter_buf ^ (key_enter = glfwGetKey(GL::window, GLFW_KEY_ENTER)) && key_enter && (glfwGetKey(GL::window, GLFW_KEY_LEFT_ALT) || glfwGetKey(GL::window, GLFW_KEY_RIGHT_ALT))) {
		GL::ChangeFullScreen(!GL::full_screen);
	}
}

int __main(int* argcp, char** argv) {
	// ���������[�N���o
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
	glEnable(GL_BLEND);//�u�����h�̗L����
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//�Œ�V�F�[�_�[�p
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_ALPHA_TEST);
	Init();
	while (!glfwWindowShouldClose(GL::window)) {
		CheckFullScreen();


		CInput::Update();
		//�e�o�b�t�@�[���N���A
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
