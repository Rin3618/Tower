#include"all.h"


void print_floor()
{
	int x, y;
	system("cls");
	std::cout << "第" << Hero.floor + 1 << "層" << std::endl;
	std::cout << "hp: " << Hero.hp << std::endl;
	std::cout << "atk: " << Hero.atk << std::endl;
	std::cout << "def: " << Hero.def << std::endl;
	std::cout << "gold: " << Hero.gold << std::endl;
	std::cout << "key: " << Hero.key << std::endl;
	std::cout << std::endl;
	std::cout << "esc:ゲーム終了  i:info  操作:wasd" << std::endl;

	std::cout << std::endl;
	for (y = 0; y < Y; y++)
		{
		for (x = 0; x <= X - 1; x++) {
			if (Hero.pos_x == x && Hero.pos_y == y)std::cout << "主";
			else if (Tower[Hero.floor][y * X + x] == 0)std::cout << "  ";
			else if (Tower[Hero.floor][y * X + x] == 1)std::cout << "■";
			else if (Tower[Hero.floor][y * X + x] == 12)std::cout << "下";
			else if (Tower[Hero.floor][y * X + x] == 11)std::cout << "上";
			else if (Tower[Hero.floor][y * X + x] == 10)std::cout << "門";
			else if (Tower[Hero.floor][y * X + x] == 22)std::cout << "鍵";
			else if (Tower[Hero.floor][y * X + x] == 20)std::cout << "攻";
			else if (Tower[Hero.floor][y * X + x] == 21)std::cout << "守";
			else if (Tower[Hero.floor][y * X + x] == 30)std::cout << "回";
			else if (Tower[Hero.floor][y * X + x] == 40)std::cout << "剣";
			else if (Tower[Hero.floor][y * X + x] == 41)std::cout << "盾";
			else if (Tower[Hero.floor][y * X + x] == 50)std::cout << "ス";
			else if (Tower[Hero.floor][y * X + x] == 51)std::cout << "死";
			else if (Tower[Hero.floor][y * X + x] == 52)std::cout << "魔";
			else if (Tower[Hero.floor][y * X + x] == 53)std::cout << "衛";
			else if (Tower[Hero.floor][y * X + x] == 54)std::cout << "ボ";
			else if (Tower[Hero.floor][y * X + x] == 23)std::cout << "商";
			else if (Tower[Hero.floor][y * X + x] == 2)std::cout << "終";

		}
		std::cout << std::endl;
		}
	std::cout << std::endl;

}


void game_init()
{
	init_tower();
	init_monsters();
	Hero = HERO();
	print_floor();
}

void gameplay()
{
	int input;
	while (1)
	{
		if (Hero.hp <= 0)
		{
			std::cout << "残念でした" << std::endl;
			break;
		}
		if (Tower[9][1 * X + 6] == 0)
		{
			std::cout << "おめでとうございます" << std::endl;
			break;
		}
		print_floor();
		input = _getch();

		if (input == 27)//終了
		{
			std::cout << "ゲーム終了してよろしいでしょうか？" << std::endl;
			std::cout << "0:いいえ  1:はい" << std::endl;
			while (1)
			{
				input = _getch();
				if (input == '1')return;
				else if (input == '0')break;
				else std::cout << "1か0を入力してください" << std::endl;
			}
		}

		if (input == 'i')//info
		{
			info();
			std::cout << std::endl;
			std::cout << "よろしいでしょうか？" << std::endl;
			std::cout << "1:はい" << std::endl;
			while (1)
			{
				input = _getch();
				if (input == '1')break;
				else std::cout << "正しいコマンドを入力してください" << std::endl;
			}
		}

		init_monsters();
		operation(input);
		
	}
}

void operation(int input)
{
	int next_pos;

	

	//判定
	if (input == 'w')
	{
		next_pos = (Hero.pos_y - 1) * X + Hero.pos_x;
		if (Tower[Hero.floor][next_pos] == 0)
		{
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			return;//空地
		}
		if (Tower[Hero.floor][next_pos] == 22)
		{
			Hero.key++;
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;//鍵
		}
		if (Tower[Hero.floor][next_pos] == 10)
		{
			if (Hero.key > 0)
			{
				Hero.key--;
				Hero.pos_x = next_pos % X;
				Hero.pos_y = next_pos / X;
				Tower[Hero.floor][next_pos] = 0;
			}
			else return;//門
		}
		if (Tower[Hero.floor][next_pos] == 20)
		{
			Hero.atk++;
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;//攻
		}
		if (Tower[Hero.floor][next_pos] == 21)
		{
			Hero.def++;
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;//守
		}
		if (Tower[Hero.floor][next_pos] == 30)
		{
			Hero.hp += 200;
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;//回復
		}
		if (Tower[Hero.floor][next_pos] == 40)
		{
			Hero.atk += 10;
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;//剣
		}
		if (Tower[Hero.floor][next_pos] == 41)
		{
			Hero.def += 10;
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;//盾
		}
		if (Tower[Hero.floor][next_pos] == 11)
		{
			Hero.floor++;
			if (Hero.floor > 9)return;
			int upper_pos = 0;
			for (int i = 0; i <= X * Y - 1; i++)
			{
				if (Tower[Hero.floor][i] == 12)
				{
					upper_pos = i;
					break;
				}
			}
			Hero.pos_x = upper_pos % X;
			Hero.pos_y = upper_pos / Y;
			return;//上
		}
		if (Tower[Hero.floor][next_pos] == 12)
		{
			Hero.floor--;
			if (Hero.floor < 0)return;
			int upper_pos = 0;
			for (int i = 0; i <= X * Y - 1; i++)
			{
				if (Tower[Hero.floor][i] == 11)
				{
					upper_pos = i;
					break;
				}
			}
			Hero.pos_x = upper_pos % X;
			Hero.pos_y = upper_pos / Y;
			return;//下
		}
		if (Tower[Hero.floor][next_pos] >= 50)
		{
			int monster_id = Tower[Hero.floor][next_pos] - 50;
			int tmp = battle(monster_id);
			if (tmp > 0)
			{
				Hero.hp = tmp;
				Hero.gold += Monster[monster_id].gold;
				Hero.pos_x = next_pos % X;
				Hero.pos_y = next_pos / X;
				Tower[Hero.floor][next_pos] = 0;
			}
			else if (tmp == -1)
			{
				std::cout << "不可能な戦い" << std::endl;
			}
			else if (tmp == -2)
			{
				std::cout << "戦死" << std::endl;
			}
		}//戦闘
		if (Tower[Hero.floor][next_pos] == 23) 
		{ 
			shop(); 
			return;
		}//商店
		if (Tower[Hero.floor][next_pos] == 2)
		{
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;
		}

	}

	if (input == 'a')
	{
		next_pos = Hero.pos_y * X + (Hero.pos_x - 1);
		if (Tower[Hero.floor][next_pos] == 0)
		{
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			return;//空地
		}
		if (Tower[Hero.floor][next_pos] == 22)
		{
			Hero.key++;
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;//鍵
		}
		if (Tower[Hero.floor][next_pos] == 10)
		{
			if (Hero.key > 0)
			{
				Hero.key--;
				Hero.pos_x = next_pos % X;
				Hero.pos_y = next_pos / X;
				Tower[Hero.floor][next_pos] = 0;
			}
			else return;//門
		}
		if (Tower[Hero.floor][next_pos] == 20)
		{
			Hero.atk++;
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;//攻
		}
		if (Tower[Hero.floor][next_pos] == 21)
		{
			Hero.def++;
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;//守
		}
		if (Tower[Hero.floor][next_pos] == 30)
		{
			Hero.hp += 200;
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;//回復
		}
		if (Tower[Hero.floor][next_pos] == 40)
		{
			Hero.atk += 10;
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;//剣
		}
		if (Tower[Hero.floor][next_pos] == 41)
		{
			Hero.def += 10;
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;//盾
		}
		if (Tower[Hero.floor][next_pos] == 11)
		{
			Hero.floor++;
			if (Hero.floor > 9)return;
			int upper_pos = 0;
			for (int i = 0; i <= X * Y - 1; i++)
			{
				if (Tower[Hero.floor][i] == 12)
				{
					upper_pos = i;
					break;
				}
			}
			Hero.pos_x = upper_pos % X;
			Hero.pos_y = upper_pos / Y;
			return;//上
		}
		if (Tower[Hero.floor][next_pos] == 12)
		{
			Hero.floor--;
			if (Hero.floor < 0)return;
			int upper_pos = 0;
			for (int i = 0; i <= X * Y - 1; i++)
			{
				if (Tower[Hero.floor][i] == 11)
				{
					upper_pos = i;
					break;
				}
			}
			Hero.pos_x = upper_pos % X;
			Hero.pos_y = upper_pos / Y;
			return;//下
		}
		if (Tower[Hero.floor][next_pos] >= 50)
		{
			int monster_id = Tower[Hero.floor][next_pos] - 50;
			int tmp = battle(monster_id);
			if (tmp > 0)
			{
				Hero.hp = tmp;
				Hero.gold += Monster[monster_id].gold;
				Hero.pos_x = next_pos % X;
				Hero.pos_y = next_pos / X;
				Tower[Hero.floor][next_pos] = 0;
			}
			else if (tmp == -1)
			{
				std::cout << "不可能な戦い" << std::endl;
			}
			else if (tmp == -2)
			{
				std::cout << "戦死" << std::endl;
			}
		}//戦闘
		if (Tower[Hero.floor][next_pos] == 23)
		{
			shop();
			return;
		}//商店
	}

	if (input == 's')
	{
		next_pos = (Hero.pos_y + 1) * X + Hero.pos_x;
		if (Tower[Hero.floor][next_pos] == 0)
		{
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			return;//空地
		}
		if (Tower[Hero.floor][next_pos] == 22)
		{
			Hero.key++;
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;//鍵
		}
		if (Tower[Hero.floor][next_pos] == 10)
		{
			if (Hero.key > 0)
			{
				Hero.key--;
				Hero.pos_x = next_pos % X;
				Hero.pos_y = next_pos / X;
				Tower[Hero.floor][next_pos] = 0;
			}
			else return;//門
		}
		if (Tower[Hero.floor][next_pos] == 20)
		{
			Hero.atk++;
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;//攻
		}
		if (Tower[Hero.floor][next_pos] == 21)
		{
			Hero.def++;
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;//守
		}
		if (Tower[Hero.floor][next_pos] == 30)
		{
			Hero.hp += 200;
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;//回復
		}
		if (Tower[Hero.floor][next_pos] == 40)
		{
			Hero.atk += 10;
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;//剣
		}
		if (Tower[Hero.floor][next_pos] == 41)
		{
			Hero.def += 10;
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;//盾
		}
		if (Tower[Hero.floor][next_pos] == 11)
		{
			Hero.floor++;
			if (Hero.floor > 9)return;
			int upper_pos = 0;
			for (int i = 0; i <= X * Y - 1; i++)
			{
				if (Tower[Hero.floor][i] == 12)
				{
					upper_pos = i;
					break;
				}
			}
			Hero.pos_x = upper_pos % X;
			Hero.pos_y = upper_pos / Y;
			return;//上
		}
		if (Tower[Hero.floor][next_pos] == 12)
		{
			Hero.floor--;
			if (Hero.floor < 0)return;
			int upper_pos = 0;
			for (int i = 0; i <= X * Y - 1; i++)
			{
				if (Tower[Hero.floor][i] == 11)
				{
					upper_pos = i;
					break;
				}
			}
			Hero.pos_x = upper_pos % X;
			Hero.pos_y = upper_pos / Y;
			return;//下
		}
		if (Tower[Hero.floor][next_pos] >= 50)
		{
			int monster_id = Tower[Hero.floor][next_pos] - 50;
			int tmp = battle(monster_id);
			if (tmp > 0)
			{
				Hero.hp = tmp;
				Hero.gold += Monster[monster_id].gold;
				Hero.pos_x = next_pos % X;
				Hero.pos_y = next_pos / X;
				Tower[Hero.floor][next_pos] = 0;
			}
			else if (tmp == -1)
			{
				std::cout << "不可能な戦い" << std::endl;
			}
			else if (tmp == -2)
			{
				std::cout << "戦死" << std::endl;
			}
		}//戦闘
		if (Tower[Hero.floor][next_pos] == 23)
		{
			shop();
			return;
		}//商店
	}

	if (input == 'd')
	{
		next_pos = Hero.pos_y * X + (Hero.pos_x + 1);
		if (Tower[Hero.floor][next_pos] == 0)
		{
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			return;//空地
		}
		if (Tower[Hero.floor][next_pos] == 22)
		{
			Hero.key++;
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;//鍵
		}
		if (Tower[Hero.floor][next_pos] == 10)
		{
			if (Hero.key > 0)
			{
				Hero.key--;
				Hero.pos_x = next_pos % X;
				Hero.pos_y = next_pos / X;
				Tower[Hero.floor][next_pos] = 0;
			}
			else return;//門
		}
		if (Tower[Hero.floor][next_pos] == 20)
		{
			Hero.atk++;
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;//攻
		}
		if (Tower[Hero.floor][next_pos] == 21)
		{
			Hero.def++;
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;//守
		}
		if (Tower[Hero.floor][next_pos] == 30)
		{
			Hero.hp += 200;
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;//回復
		}
		if (Tower[Hero.floor][next_pos] == 40)
		{
			Hero.atk += 10;
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;//剣
		}
		if (Tower[Hero.floor][next_pos] == 41)
		{
			Hero.def += 10;
			Hero.pos_x = next_pos % X;
			Hero.pos_y = next_pos / X;
			Tower[Hero.floor][next_pos] = 0;
			return;//盾
		}
		if (Tower[Hero.floor][next_pos] == 11)
		{
			Hero.floor++;
			if (Hero.floor > 9)return;
			int upper_pos = 0;
			for (int i = 0; i <= X * Y - 1; i++)
			{
				if (Tower[Hero.floor][i] == 12)
				{
					upper_pos = i;
					break;
				}
			}
			Hero.pos_x = upper_pos % X;
			Hero.pos_y = upper_pos / Y;
			return;//上
		}
		if (Tower[Hero.floor][next_pos] == 12)
		{
			Hero.floor--;
			if (Hero.floor < 0)return;
			int upper_pos = 0;
			for (int i = 0; i <= X * Y - 1; i++)
			{
				if (Tower[Hero.floor][i] == 11)
				{
					upper_pos = i;
					break;
				}
			}
			Hero.pos_x = upper_pos % X;
			Hero.pos_y = upper_pos / Y;
			return;//下
		}
		if (Tower[Hero.floor][next_pos] >= 50)
		{
			int monster_id = Tower[Hero.floor][next_pos] - 50;
			int tmp = battle(monster_id);
			if (tmp > 0)
			{
				Hero.hp = tmp;
				Hero.gold += Monster[monster_id].gold;
				Hero.pos_x = next_pos % X;
				Hero.pos_y = next_pos / X;
				Tower[Hero.floor][next_pos] = 0;
			}
			else if (tmp == -1)
			{
				std::cout << "不可能な戦い" << std::endl;
			}
			else if (tmp == -2)
			{
				std::cout << "戦死" << std::endl;
			}
		}//戦闘
		if (Tower[Hero.floor][next_pos] == 23)
		{
			shop();
			return;
		}//商店
	}
}

int battle(int monster_id)
{
	int tmp = Hero.hp;
	if (Monster[monster_id].def >= Hero.atk) 
	{
		return -1;//不可能
	}
	else
	{
		while (Monster[monster_id].hp > 0 || Hero.hp > 0)
		{
			Monster[monster_id].hp -= Hero.atk - Monster[monster_id].def;
			if (Monster[monster_id].hp <= 0) 
			{
				if (tmp < Hero.hp)return tmp;
				else return Hero.hp;//赢
			}
			Hero.hp -= Monster[monster_id].atk - Hero.def;
			if (Hero.hp <= 0)return -2;//输
		}
		if (Monster[monster_id].hp <= 0)
		{
			if (tmp < Hero.hp)return tmp;
			else return Hero.hp;//赢
		}
		else 
		{
			return -2;//输
		}
	}
}

void shop()
{
	int input;
	int count = 1;
	if (Hero.gold < count * 20) 
	{
		std::cout << "お金が足りない" << std::endl;
		return;
	}
	while (1)
	{
		std::cout << 20 * count << " goldで一つの属性をアップすることができます(現在:" << Hero.gold << ")" << std::endl;
		std::cout << "0:要らない  1:hp+100  2:atd+2  3:def+4" << std::endl;
		input = _getch();
		if (input == '0')break;
		else if (input == '1')
		{
			Hero.hp += 100;
			Hero.gold -= count * 20;
			count++;
		}
		else if (input == '2')
		{
			Hero.atk += 2;
			Hero.gold -= count * 20;
			count++;
		}
		else if (input == '3')
		{
			Hero.def += 4;
			Hero.gold -= count * 20;
			count++;
		}
		else std::cout << "0から3の数字を入力してください" << std::endl;
	}
}

void info()
{
	int* f = new int[5];
	for (int i = 0; i < 5; i++)
	{
		f[i] = 0;
	}

	for (int y = 0; y < Y; y++)
	{
		for (int x = 0; x <= X - 1; x++) {
			
			if (Tower[Hero.floor][y * X + x] == 50)f[0] = 1;
			if (Tower[Hero.floor][y * X + x] == 51)f[1] = 1;
			if (Tower[Hero.floor][y * X + x] == 52)f[2] = 1;
			if (Tower[Hero.floor][y * X + x] == 53)f[3] = 1;
			if (Tower[Hero.floor][y * X + x] == 54)f[4] = 1;
		}
	}

	for (int j = 0; j < 5; j++)
	{
		if (f[j] == 1)
		{
			std::cout << "名前: " << Monster[j].name << std::endl;
			std::cout << "hp: " << Monster[j].hp << std::endl;
			std::cout << "atk: " << Monster[j].atk << std::endl;
			std::cout << "def:" << Monster[j].def << std::endl;
			std::cout << "gold: " << Monster[j].gold << std::endl;
			std::cout << std::endl;
		}
	}

	delete[] f;
}


void game_start()
{
	std::cout << "■■■■■■■■■■■■■" << std::endl;
	std::cout << "■                      ■" << std::endl;
	std::cout << "■                      ■" << std::endl;
	std::cout << "■                      ■" << std::endl;
	std::cout << "■                      ■" << std::endl;
	std::cout << "■       魔法の塔       ■" << std::endl;
	std::cout << "■                      ■" << std::endl;
	std::cout << "■        START         ■" << std::endl;
	std::cout << "■                      ■" << std::endl;
	std::cout << "■                      ■" << std::endl;
	std::cout << "■                      ■" << std::endl;
	std::cout << "■       リクキョウリン ■" << std::endl;
	std::cout << "■■■■■■■■■■■■■" << std::endl;
}