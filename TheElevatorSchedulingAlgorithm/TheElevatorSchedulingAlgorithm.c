#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXPASSENGER 10        //�˿�����

/*�˵�����Ա��Ϣ*/
typedef struct Person
{
	char name[10];             //����
	char initialFloor;         //��ʼ¥��
	char targetFloor;          //Ŀ��¥��
	struct Person *next;
}Person, *pPerson;

/*����״̬*/
struct ElevatorState
{
	int nowFloor;              //��ǰ¥��
	int nowPeople;             //��ǰ����
	char nowState;             //��ǰ���з���
};

struct ElevatorState NowState; //��ǰ����״̬
int num;                       //�˵�������

pPerson CreateUpLink();
pPerson CreateDownLink();
void InitElevator(pPerson up, pPerson down);
void InitState();
void Run(pPerson upLink, pPerson downLink);

int main(void)
{
	pPerson goingUp;           //��������
	pPerson goingDown;         //��������
	goingUp = CreateUpLink();
	goingDown = CreateDownLink();

	InitElevator(goingUp, goingDown);
	InitState();

//	/*����״̬���Դ���*/
//	printf("%d, %d, %c\N", NowState.nowFloor, NowState.nowPeople, NowState.nowState);

	/*������Դ���*/
/*	while(goingUp -> next != NULL)
	{
		printf("%s, %d, %d\n", goingUp -> next -> name, goingUp -> next -> initialFloor, goingUp -> next -> targetFloor);
		goingUp = goingUp ->next;
	}

	while(goingDown -> next != NULL)
	{
		printf("%s, %d, %d\n", goingDown -> next -> name, goingDown -> next -> initialFloor, goingDown -> next -> targetFloor);
		goingDown = goingDown ->next;
	}*/

	Run(goingUp, goingDown);

	return 0;
}

/*������������*/
pPerson CreateUpLink()
{
	pPerson upNode;
	upNode = (pPerson) malloc (sizeof (Person) );
	upNode -> next = NULL;
	return upNode;
}

/*������������*/
pPerson CreateDownLink()
{
	pPerson downNode;
	downNode = (pPerson) malloc (sizeof (Person) );
	downNode -> next = NULL;
	return downNode;
}

/*��ʼ���˵�����Ա����*/
void InitElevator(pPerson upLink, pPerson downLink)
{

	int i;
	char personName[10];
	int personInitialFloor;
	int personTargetFloor;
	pPerson upNode;
	pPerson downNode;
	pPerson Node;

	printf("�������������:");
	scanf("%d", &num);
	for(i = 1; i <= num; i++)
	{
		printf("�������%d���˵�����:", i);
		scanf("%s", personName);
		printf("��������˳�ʼ¥��->Ŀ��¥��:");
		scanf("%d->%d", &personInitialFloor, &personTargetFloor);

		Node = (pPerson) malloc (sizeof (Person) );
		strcpy (Node -> name, personName);
		Node -> initialFloor = personInitialFloor;
		Node -> targetFloor = personTargetFloor;

		/*������������*/
		if(personInitialFloor <= personTargetFloor)
		{
			
			if( upLink -> next == NULL)
			{
				upLink -> next = Node;
				Node -> next = NULL;
			}

			else if(personInitialFloor < upLink -> next -> initialFloor)
			{
				Node -> next = upLink -> next;
				upLink -> next = Node;
			}

			else
			{
				upNode = upLink;
				
				while(upNode -> next -> initialFloor < personInitialFloor)
				{
					upNode = upNode ->next;
					if(upNode -> next ==NULL)
					{
						break;
					}
				}

				if(upNode -> next == NULL)
				{
					Node ->next = NULL;
					upNode -> next = Node;
				}

				else
				{
					Node -> next = upNode -> next;
					upNode -> next = Node;
				}

			}

		}

		/*������������*/
		else
		{
			if( downLink -> next == NULL)
			{
				downLink -> next = Node;
				Node -> next = NULL;
			}

			else if(personInitialFloor > downLink -> next -> initialFloor)
			{
				Node -> next = downLink -> next;
				downLink -> next = Node;
			}

			else
			{
				downNode = downLink;
				
				while(downNode -> next -> initialFloor > personInitialFloor)
				{
					downNode = downNode ->next;
					if(downNode -> next ==NULL)
					{
						break;
					}
				}

				if(downNode -> next == NULL)
				{
					Node ->next = NULL;
					downNode -> next = Node;
				}

				else
				{
					Node -> next = downNode -> next;
					downNode -> next = Node;
				}

			}
		}

	}
}

/*��ʼ������״̬*/
void InitState()
{
	printf("��������ݳ�ʼ¥��:");
	scanf("%d", &(NowState.nowFloor));
	NowState.nowPeople = 0;
	NowState.nowState = '1';
}

/*���������㷨*/
void Run(pPerson upLink, pPerson downLink)
{
	pPerson upNode;
	pPerson downNode;
	pPerson outLink;
	pPerson outNode;
	pPerson Node;
	int connect = 0;

	outLink = (pPerson) malloc (sizeof (Person) );
	outLink -> next = NULL;

	while(1)
	{
		/*���������㷨*/
		if(NowState.nowState == '1')
		{
			upNode = upLink;
	
			while(upNode -> next -> initialFloor < NowState.nowFloor)
			{
				upNode = upNode ->next;
				if(upNode -> next == NULL)
				{
					break;
				}
			}
	
			connect = 0;
			while(upNode -> next != NULL)
			{
				if(connect == 0)
				{
					printf("���ݵ���%d¥", NowState.nowFloor);
				}
				if(upNode -> next -> initialFloor == NowState.nowFloor)
				{
					printf(",%s�������", upNode -> next -> name);

					/*�����������*/
					Node = (pPerson) malloc (sizeof (Person) );
					strcpy (Node -> name, upNode -> next -> name);
					Node -> initialFloor = upNode -> next -> initialFloor;
					Node -> targetFloor = upNode -> next -> targetFloor;
					Node -> next = NULL;
					if( outLink -> next == NULL)
					{
						outLink -> next = Node;
						Node -> next = NULL;
					}
					else if(Node -> targetFloor < outLink -> next -> targetFloor)
					{
						Node -> next = upLink -> next;
						outLink -> next = Node;
					}
					else
					{
						outNode = outLink;
			
						while(outNode -> next -> targetFloor < Node -> targetFloor)
						{
							outNode = outNode ->next;
							if(outNode -> next ==NULL)
							{
								break;
							}
						}

						if(outNode -> next == NULL)
						{
							Node ->next = NULL;
							outNode -> next = Node;
						}
						else
						{
							Node -> next = outNode -> next;
							outNode -> next = Node;
						}

					}

					upNode -> next = upNode -> next -> next;
					connect = 1;
					if(upNode -> next == NULL)
					{
						printf("\n");
						break;
					}
					if(outLink -> next != NULL)
					{
						if(NowState.nowFloor == outLink -> next -> targetFloor)
						{
							printf(",%s�߳�����", outLink -> next -> name);
							outLink -> next = outLink -> next -> next;
						}
					}
					if(upNode -> next -> initialFloor != NowState.nowFloor)
					{
						connect = 0;
						NowState.nowFloor++;
						printf("\n");
					}
				}
				else
				{
					if(outLink -> next != NULL)
					{
						if(NowState.nowFloor == outLink -> next -> targetFloor)
						{
							printf(",%s�߳�����", outLink -> next -> name);
							outLink -> next = outLink -> next -> next;
						}
					}
					printf("\n");
					NowState.nowFloor++;
				}
			}

			if(downLink -> next != NULL)
			{
				NowState.nowState = '0';
				downNode = downLink;
				while(NowState.nowFloor < downNode -> next -> initialFloor)
				{
					NowState.nowFloor++;
					if(NowState.nowFloor != downNode -> next -> initialFloor)
					{
						printf("���ݵ���%d��", NowState.nowFloor);
					}
					if(outLink -> next != NULL)
					{
						if(NowState.nowFloor == outLink -> next -> targetFloor)
						{
							printf(",%s�߳�����", outLink -> next -> name);
							outLink -> next = outLink -> next -> next;
						}
					}
					printf("\n");
				}
			}
			else
			{
				printf("�������н���\n");
				break;
			}
		}
	
		/*���������㷨*/
		if(NowState.nowState == '0')
		{
			downNode = downLink;
			
			while(downNode -> next -> initialFloor > NowState.nowFloor)
			{
				downNode = downNode ->next;
				if(downNode -> next == NULL)
				{
					break;
				}
			}
	
			connect = 0;
			while(downNode -> next != NULL)
			{
				if(connect == 0)
				{
					printf("���ݵ���%d¥", NowState.nowFloor);
				}
				if(downNode -> next -> initialFloor == NowState.nowFloor)
				{
					printf(",%s�������", downNode -> next -> name);
					
					Node = (pPerson) malloc (sizeof (Person) );
					strcpy (Node -> name, downNode -> next -> name);
					Node -> initialFloor = downNode -> next -> initialFloor;
					Node -> targetFloor = downNode -> next -> targetFloor;
					Node -> next = NULL;
					
					if( outLink -> next == NULL)
					{
						outLink -> next = Node;
						Node -> next = NULL;
					}
					else if(Node -> targetFloor > outLink -> next -> targetFloor)
					{
						Node -> next = upLink -> next;
						outLink -> next = Node;
					}
					else
					{
						outNode = outLink;
			
						while(outNode -> next -> targetFloor > Node -> targetFloor)
						{
							outNode = outNode ->next;
							if(outNode -> next ==NULL)
							{
								break;
							}
						}

						if(outNode -> next == NULL)
						{
							Node ->next = NULL;
							outNode -> next = Node;
						}
						else
						{
							Node -> next = outNode -> next;
							outNode -> next = Node;
						}

					}

					downNode ->next = downNode -> next ->next;
					connect = 1;
					if(downNode -> next == NULL)
					{
						printf("\n");
						break;
					}
					if(outLink -> next != NULL)
					{
						if(NowState.nowFloor == outLink -> next -> targetFloor)
						{
							printf(",%s�߳�����", outLink -> next -> name);
							outLink -> next = outLink -> next -> next;
						}
					}
					if(downNode -> next -> initialFloor != NowState.nowFloor)
					{
						connect = 0;
						NowState.nowFloor--;
						printf("\n");
					}
				}
				else
				{
					if(outLink -> next != NULL)
					{
						if(NowState.nowFloor == outLink -> next -> targetFloor)
						{
							printf(",%s�߳�����", outLink -> next -> name);
							outLink -> next = outLink -> next -> next;
						}
					}
					printf("\n", NowState.nowFloor);
					NowState.nowFloor--;
				}
			}
	
			if(upLink -> next != NULL)
			{
				NowState.nowState = '1';
				upNode = upLink;
				while(NowState.nowFloor > upNode -> next -> initialFloor)
				{
					NowState.nowFloor--;
					if(NowState.nowFloor != upNode -> next -> initialFloor)
					{
						printf("���ݵ���%d��", NowState.nowFloor);
					}
					if(outLink -> next != NULL)
					{
						if(NowState.nowFloor == outLink -> next -> targetFloor)
						{
							printf(",%s�߳�����", outLink -> next -> name);
							outLink -> next = outLink -> next -> next;
						}
					}
					printf("\n");
				}
			}
			else
			{
				printf("�������н���\n");
				break;
			}
		}
	}
}