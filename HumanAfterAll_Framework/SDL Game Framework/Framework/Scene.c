#include "stdafx.h"
#include "Scene.h"
#include "Csv.h"
#include "Common.h"

#include "Framework.h"
#include "Framework/Text.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;

#pragma region TITLE_SCENE

/*
	�̹��� ����ϰ� ���� �����̽��ٸ� �����ٸ� ���� ������ �Ѿ
	���ٸ� ��ư�� ������?
*/

typedef struct TitleSceneData
{
	Image TitleImage;
	Music TitleBGM;
	//SoundEffect TitleSound;
} TitleSceneData;

void init_title()
{
	g_Scene.Data = malloc(sizeof(TitleSceneData));
	memset(g_Scene.Data, 0, sizeof(TitleSceneData));

	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	Image_LoadImage(&data->TitleImage, "corridor_bright.jpg");

	Audio_LoadMusic(&data->TitleBGM, "space_bgm.mp3");
	Audio_PlayFadeIn(&data->TitleBGM, INFINITY_LOOP, 3000);
}

void update_title()
{
	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_DESCRIPTION);
	}

	if (Input_GetKeyDown(VK_RETURN))
	{
		Scene_SetNextScene(SCENE_DESCRIPTION);
	}
}

void render_title()
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	Renderer_DrawImage(&data->TitleImage, 0, 0);
}

void release_title()
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	Audio_FreeMusic(&data->TitleBGM);

	SafeFree(g_Scene.Data);
}

#pragma endregion

#pragma region DESCRIPTION_SCENE
typedef struct DescriptionSceneData
{
	Image DescriptionImage;
	Music DescriptionBGM;
} DescriptionSceneData;

void init_description()
{
	g_Scene.Data = malloc(sizeof(DescriptionSceneData));
	memset(g_Scene.Data, 0, sizeof(DescriptionSceneData));

	DescriptionSceneData* data = (DescriptionSceneData*)g_Scene.Data;

	Image_LoadImage(&data->DescriptionImage, "corridor_dark.png");

	Audio_LoadMusic(&data->DescriptionBGM, "space_bgm.mp3");
	Audio_PlayFadeIn(&data->DescriptionBGM, INFINITY_LOOP, 3000);
}

void update_description()
{
	if (Input_GetKeyDown(VK_SPACE))
	{
		/*
			�Ƹ� ���� �̹����� �ִٸ� �� �̹����� �����ִ� ������ �ؾ���.
			�̹����� �迭�� �޾ƾ��� ���� ����
		*/
	}

	if (Input_GetKeyDown(VK_RETURN))
	{
		Scene_SetNextScene(SCENE_STORY);
	}
}

void render_description()
{
	DescriptionSceneData* data = (DescriptionSceneData*)g_Scene.Data;

	Renderer_DrawImage(&data->DescriptionImage, 0, 0);
}

void release_description()
{
	DescriptionSceneData* data = (DescriptionSceneData*)g_Scene.Data;

	Audio_FreeMusic(&data->DescriptionBGM);

	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region STORY_SCENE
/*
	������ �ؽ�Ʈ�θ� ����Ǵ� �κ�
	���� ������ �ʿ��� ���� ����
*/

CsvFile csvFile;

void init_story()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	
	memset(&csvFile, 0, sizeof(CsvFile));
	CreateCsvFile(&csvFile, "test.csv");

	// CSV ���� �Ľ��� �� �ؽ�Ʈ �׷��� ����
	// �����ڵ� ����� ��� �ȵǸ�
	// App_Init()�� �Ʒ� ���� �߰�
	// setlocale(LC_ALL, "kr_KR.utf8");

	for (int r = 0; r < csvFile.RowCount; ++r)
	{
		for (int c = 0; c < csvFile.ColumnCount; ++c)
		{
			char* str = ParseToAscii(csvFile.Items[r][c]);
			printf("%s", str);
			free(str);
		}

		puts("");
	}

}

void update_story()
{
	//StorySceneData* data = (StorySceneData*)g_Scene.Data;

	if (Input_GetKeyDown(VK_SPACE))
	{
		/*
			�ؽ�Ʈ �ٴ����� ��ŵ.
			������ ��ŵ�� �Ǵ� ���� �ƴ� �ؽ�Ʈ�� ��µǾ��־�� ��
		*/


	}

	if (Input_GetKeyDown(VK_RETURN))
	{
		/*
			���� ��, Ȥ�� ������ ������
			������ ��ŵ�� ���� ����
		*/
	}

}

void render_story()
{

}

void release_story()
{
	FreeCsvFile(&csvFile);
}
#pragma endregion

#pragma region CHOICE_SCENE
/*
Ÿ�̸ӿ� ���� ����â�� ���� �Ǹ� �׶� �ǵ帮�� �ɷ�
*/

#define SOLID 0
#define SHADED 1
#define BLENDED 2

typedef struct StorySceneText
{
	Text SceneNumber;
	Text SceneText;
} StorySceneText;

const wchar_t* str[] = {
	L"�ƹ��͵� �𸣰ڴ�",
	L"���� �ƹ��͵� �𸣰ڴ�",
	L"���� ��",
	L"�ƹ��͵� �𸣰ڴ�",
	L"�ֳ��ϸ�",
	L"��",
	L"�ƹ��͵� �𸣱� �����̴�",
	L"�ϳ��� �𸣰ڴ�",
	L"�����",
	L"...---..."
};


typedef struct StorySceneData
{
	/*Image StoryBackgroundImage;
	Music StoryBGM;*/
	//SoundEffect TitleSound;
	Text	GuideLine[10];
	Text	TestText;
	int32	FontSize;
	int32	RenderMode;
	Image	TestImage;
} StorySceneData;

void init_choice()
{
	g_Scene.Data = malloc(sizeof(StorySceneData));
	memset(g_Scene.Data, 0, sizeof(StorySceneData));

	StorySceneData* data = (StorySceneData*)g_Scene.Data;
	for (int32 i = 0; i < 10; ++i)
	{
		Text_CreateText(&data->GuideLine[i], "d2coding.ttf", 16, str[i], wcslen(str[i]));
	}

	data->FontSize = 24;
	Text_CreateText(&data->TestText, "d2coding.ttf", data->FontSize, L"�� �ؽ�Ʈ�� ���մϴ�.", 13);

	data->RenderMode = SOLID;

	Image_LoadImage(&data->TestImage, "Background.jfif");
}

void update_choice()
{
	if (Input_GetKeyDown(VK_SPACE))
	{

	}

	if (Input_GetKeyDown(VK_RETURN))
	{

	}

	if (Input_GetKeyDown(VK_NUMPAD1))
	{

	}

	if (Input_GetKeyDown(VK_NUMPAD2))
	{

	}

	if (Input_GetKeyDown(VK_NUMPAD3))
	{

	}
}

void render_choice()
{
	/*
		�ؽ�Ʈ, �̹���, ���� ��� ��½�Ŵ
	*/


	StorySceneData* data = (StorySceneData*)g_Scene.Data;

	SDL_Color color = { .a = 255 };
	//Renderer_DrawTextSolid(&data->GuideLine[3], 10, 20 * 3, color);
	for (int32 i = 0; i < 10; ++i)
	{
		SDL_Color color = { .a = 255 };
		Renderer_DrawTextSolid(&data->GuideLine[i], 10, 20 * i, color);
	}

	switch (data->RenderMode)
	{
	case SOLID:
	{
		SDL_Color color = { .a = 255 };
		Renderer_DrawTextSolid(&data->TestText, 400, 400, color);
	}
	break;
	case SHADED:
	{
		SDL_Color bg = { .a = 255 };
		SDL_Color fg = { .r = 255, .g = 255, .a = 255 };
		Renderer_DrawTextShaded(&data->TestText, 400, 400, fg, bg);
	}
	break;
	case BLENDED:
	{
		Renderer_DrawImage(&data->TestImage, 400, 400);
		SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
		Renderer_DrawTextBlended(&data->TestText, 400, 400, color);
	}
	break;
	}
}

void release_choice()
{
	/*
		���丮�������� ����
	*/

	StorySceneData* data = (StorySceneData*)g_Scene.Data;

	for (int32 i = 0; i < 10; ++i)
	{
		Text_FreeText(&data->GuideLine[i]);
	}
	Text_FreeText(&data->TestText);

	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region ENDING_SCENE
/*

	���� A, B, C �׸��� ��忣�� ���� ���������� ���������� �� ����

*/


void init_ending()
{

}

void update_ending()
{

}

void render_ending()
{

}

void release_ending()
{

}
#pragma endregion

bool Scene_IsSetNextScene(void)
{
	if (SCENE_NULL == s_nextScene)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Scene_SetNextScene(ESceneType scene)
{
	assert(s_nextScene == SCENE_NULL);
	assert(SCENE_NULL < scene&& scene < SCENE_MAX);

	s_nextScene = scene;
}

void Scene_Change(void)
{
	assert(s_nextScene != SCENE_NULL);

	if (g_Scene.Release)
	{
		g_Scene.Release();
	}

	switch (s_nextScene)
	{
	case SCENE_TITLE:
		g_Scene.Init = init_title;
		g_Scene.Update = update_title;
		g_Scene.Render = render_title;
		g_Scene.Release = release_title;
		break;
	case SCENE_DESCRIPTION:
		g_Scene.Init = init_description;
		g_Scene.Update = update_description;
		g_Scene.Render = render_description;
		g_Scene.Release = release_description;
		break;
	case SCENE_STORY:
		g_Scene.Init = init_story;
		g_Scene.Update = update_story;
		g_Scene.Render = render_story;
		g_Scene.Release = release_story;
		break;
	case SCENE_CHOICE:
		g_Scene.Init = init_choice;
		g_Scene.Update = update_choice;
		g_Scene.Render = render_choice;
		g_Scene.Release = release_choice;
		break;
	case SCENE_ENDING:
		g_Scene.Init = init_ending;
		g_Scene.Update = update_ending;
		g_Scene.Render = render_ending;
		g_Scene.Release = release_ending;
		break;

	}

	g_Scene.Init();

	s_nextScene = SCENE_NULL;
}