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
		cout << "**** ����� ����� �����ּ��� ****" << endl;
		cout << "1) �߰� 2) ���� 3) ��ü���� 4) ���� 5) �ҷ����� 6) â Ŭ���� 99) ����" << endl;
		cin >> cmd;

		if (cmd == EXIT)
		{
			break;
		}

		switch (cmd)
		{
			case Add:
			{
				cout << "�̸��� �Է��ϼ��� : ";
				cin >> name;

				cout << "���� ������ �Է��ϼ��� : ";
				cin >> scorKor;

				cout << "���� ������ �Է��ϼ��� : ";
				cin >> scorEng;

				cout << "���� ������ �Է��ϼ��� : ";
				cin >> scorMath;

			
				StudManger.AddList(name, scorKor, scorEng, scorMath);
				StudManger.g_cnt++;
				break;
			}
			case Del:
			{
				cout << "������ �̸��� �Է��ϼ��� : ";
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
				printf("��ɾ Ȯ���� �ּ��� \n");
			}

		}
	}



}