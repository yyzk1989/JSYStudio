#include  "Main.h"


void main()
{
	int cmd;
	int scorKor, scorEng, scorMath;
	char name[4] = {0,};

	Linked_List StudManger;
	FileClas FData;
	while (1)
	{
		cout << "**** 사용할 명령을 내려주세요 ****" << endl;
		cout << "1) 추가 2) 삭제 3) 전체보기 4) 저장 5) 불러오기 6) 창 클리어 99) 종료" << endl;
		cin >> cmd;

		if (cmd == EXIT)
		{
			break;
		}

		switch (cmd)
		{
			case Add:
			{
				cout << "이름을 입력하세요 : ";
				cin >> name;

				cout << "국어 점수를 입력하세요 : ";
				cin >> scorKor;

				cout << "영어 점수를 입력하세요 : ";
				cin >> scorEng;

				cout << "수학 점수를 입력하세요 : ";
				cin >> scorMath;

			
				StudManger.AddList(name, scorKor, scorEng, scorMath);
				StudManger.g_cnt++;
				break;
			}
			case Del:
			{
				cout << "삭제할 이름을 입력하세요 : ";
				cin >> name;
				StudManger.DelList(name);
				break;
			}
			case Show:
			{
				StudManger.ShowList();
				break;
			}
			case Save:
			{
				FData.SaveFile(StudManger);
				break;
			}
			case Load:
			{
				StudManger.g_cnt= FData.LoadFile(StudManger);
				break;
			}			
			case Cls:
			{
				system("cls");
				break;
			}			
			default:
			{
				printf("명령어를 확인해 주세요 \n");
			}

		}
	}



}