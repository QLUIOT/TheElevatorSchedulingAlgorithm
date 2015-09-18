#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXPASSENGER 10        //乘客上限

/*乘电梯人员信息*/
typedef struct Person
{
	char name[10];             //姓名
	char initialFloor;         //初始楼层
	char targetFloor;          //目标楼层
	struct Person *next;
}Person, *pPerson;

/*电梯状态*/
struct ElevatorState
{
	int nowFloor;              //当前楼层
	int nowPeople;             //当前人数
	char nowState;             //当前运行方向
};

struct ElevatorState NowState; //当前电梯状态
int num;                       //乘电梯人数

pPerson CreateUpLink();
pPerson CreateDownLink();
void InitElevator(pPerson up, pPerson down);
void InitState();
void Run(pPerson upLink, pPerson downLink);

int main(void)
{
	pPerson goingUp;           //上行链表
	pPerson goingDown;         //下行链表
	goingUp = CreateUpLink();
	goingDown = CreateDownLink();

	InitElevator(goingUp, goingDown);
	InitState();

//	/*电梯状态测试代码*/
//	printf("%d, %d, %c\N", NowState.nowFloor, NowState.nowPeople, NowState.nowState);

	/*链表测试代码*/
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

/*创建上行链表*/
pPerson CreateUpLink()
{
	pPerson upNode;
	upNode = (pPerson) malloc (sizeof (Person) );
	upNode -> next = NULL;
	return upNode;
}

/*创建下行链表*/
pPerson CreateDownLink()
{
	pPerson downNode;
	downNode = (pPerson) malloc (sizeof (Person) );
	downNode -> next = NULL;
	return downNode;
}

/*初始化乘电梯人员链表*/
void InitElevator(pPerson upLink, pPerson downLink)
{

	int i;
	char personName[10];
	int personInitialFloor;
	int personTargetFloor;
	pPerson upNode;
	pPerson downNode;
	pPerson Node;

	printf("请输入乘梯人数:");
	scanf("%d", &num);
	for(i = 1; i <= num; i++)
	{
		printf("请输入第%d个人的姓名:", i);
		scanf("%s", personName);
		printf("请输入该人初始楼层->目标楼层:");
		scanf("%d->%d", &personInitialFloor, &personTargetFloor);

		Node = (pPerson) malloc (sizeof (Person) );
		strcpy (Node -> name, personName);
		Node -> initialFloor = personInitialFloor;
		Node -> targetFloor = personTargetFloor;

		/*构建上行链表*/
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

		/*构建下行链表*/
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

/*初始化电梯状态*/
void InitState()
{
	printf("请输入电梯初始楼层:");
	scanf("%d", &(NowState.nowFloor));
	NowState.nowPeople = 0;
	NowState.nowState = '1';
}

/*电梯运行算法*/
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
		/*电梯上行算法*/
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
					printf("电梯到达%d楼", NowState.nowFloor);
				}
				if(upNode -> next -> initialFloor == NowState.nowFloor)
				{
					printf(",%s进入电梯", upNode -> next -> name);

					/*构建输出链表*/
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
							printf(",%s走出电梯", outLink -> next -> name);
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
							printf(",%s走出电梯", outLink -> next -> name);
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
						printf("电梯到达%d层", NowState.nowFloor);
					}
					if(outLink -> next != NULL)
					{
						if(NowState.nowFloor == outLink -> next -> targetFloor)
						{
							printf(",%s走出电梯", outLink -> next -> name);
							outLink -> next = outLink -> next -> next;
						}
					}
					printf("\n");
				}
			}
			else
			{
				printf("电梯运行结束\n");
				break;
			}
		}
	
		/*电梯下行算法*/
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
					printf("电梯到达%d楼", NowState.nowFloor);
				}
				if(downNode -> next -> initialFloor == NowState.nowFloor)
				{
					printf(",%s进入电梯", downNode -> next -> name);
					
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
							printf(",%s走出电梯", outLink -> next -> name);
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
							printf(",%s走出电梯", outLink -> next -> name);
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
						printf("电梯到达%d层", NowState.nowFloor);
					}
					if(outLink -> next != NULL)
					{
						if(NowState.nowFloor == outLink -> next -> targetFloor)
						{
							printf(",%s走出电梯", outLink -> next -> name);
							outLink -> next = outLink -> next -> next;
						}
					}
					printf("\n");
				}
			}
			else
			{
				printf("电梯运行结束\n");
				break;
			}
		}
	}
}